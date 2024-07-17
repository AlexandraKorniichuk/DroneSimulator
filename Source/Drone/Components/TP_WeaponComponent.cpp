// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "Drone/DroneCharacter.h"
#include "Drone/DroneProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY(LogWeapon);


UTP_WeaponComponent::UTP_WeaponComponent()
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UTP_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponData = DefaultWeaponData;
}

void UTP_WeaponComponent::Fire()
{
	if (!Character || !Character->GetController())
	{
		return;
	}

	if (IsAmmoEmpty())
	{
		return;
	}

	DecreaseAmmo();

	UWorld* const World = GetWorld();
	if (ProjectileClass && World)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
		World->SpawnActor<ADroneProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
	
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	if (FireAnimation)
	{
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

bool UTP_WeaponComponent::AttachWeapon(ADroneCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	if (!Character || Character->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>())
	{
		return false;
	}

	Character->OnWeaponEquipped.Broadcast(this);

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	Character->AddInstanceComponent(this);

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		}
	}

	OnAmmoChanged.Broadcast(CurrentWeaponData.Bullets, CurrentWeaponData.Clips);

	return true;
}

bool UTP_WeaponComponent::TryToAddAmmo(int Ammo)
{
	if (IsAmmoFull())
	{
		return false;
	}

	int CurrentTotal = CurrentWeaponData.Bullets + CurrentWeaponData.Clips * DefaultWeaponData.Bullets;
	int NewTotal = FMath::Clamp(CurrentTotal + Ammo, 0, DefaultWeaponData.Bullets * (DefaultWeaponData.Clips + 1));

	int NewBullets = NewTotal % DefaultWeaponData.Bullets;
	CurrentWeaponData.Bullets = NewBullets ? NewBullets : DefaultWeaponData.Bullets;
	CurrentWeaponData.Clips = (NewTotal - CurrentWeaponData.Bullets) / DefaultWeaponData.Bullets;
	
	OnAmmoChanged.Broadcast(CurrentWeaponData.Bullets, CurrentWeaponData.Clips);
	
	return true;
}

void UTP_WeaponComponent::DecreaseAmmo()
{
	CurrentWeaponData.Bullets--;

	if (CurrentWeaponData.Bullets <= 0)
	{
		Reload();
	}

	OnAmmoChanged.Broadcast(CurrentWeaponData.Bullets, CurrentWeaponData.Clips);
}

void UTP_WeaponComponent::Reload()
{
	if (CurrentWeaponData.Clips <= 0) return;

	CurrentWeaponData.Clips--;
	CurrentWeaponData.Bullets = DefaultWeaponData.Bullets;
}

bool UTP_WeaponComponent::IsAmmoEmpty() const
{
	return CurrentWeaponData.Bullets == 0 && CurrentWeaponData.Clips == 0;
}

bool UTP_WeaponComponent::IsAmmoFull() const
{
	return CurrentWeaponData.Bullets == DefaultWeaponData.Bullets &&
		CurrentWeaponData.Clips == DefaultWeaponData.Clips;
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (!Character)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}
