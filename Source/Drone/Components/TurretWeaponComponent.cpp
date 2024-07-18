// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretWeaponComponent.h"

#include "Drone/DroneProjectile.h"
#include "Kismet/KismetMathLibrary.h"

void UTurretWeaponComponent::FireInPlayer(FVector PlayerLocation)
{
	if (UWorld* const World = GetWorld())
	{
		const FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorRotation().RotateVector(MuzzleOffset);
		const FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, PlayerLocation);
		
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
		auto Projectile = World->SpawnActor<ADroneProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		Projectile->SetDamage(CurrentWeaponData.Damage);
		Projectile->SetInstigator(GetOwner());
	}
}
