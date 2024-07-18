// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class ADroneCharacter;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta =(EditCondition = "!bInfiniteClips"))
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, meta =(EditCondition = "!bInfiniteClips"))
	int Clips = 30;

	UPROPERTY(EditDefaultsOnly, meta =(EditCondition = "!bInfiniteClips"))
	int Bullets = 15;

	UPROPERTY(EditDefaultsOnly)
	bool bInfiniteClips = false;
};
DECLARE_LOG_CATEGORY_EXTERN(LogWeapon, Log, All);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, float Bullets, float Clips);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONE_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ADroneProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(ADroneCharacter* TargetCharacter);

	bool TryToAddAmmo(int Ammo);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void Fire();

	FOnAmmoChanged OnAmmoChanged;

protected:
	virtual void BeginPlay() override;
	
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FWeaponData DefaultWeaponData;

private:
	/** The Character holding this weapon*/
	ADroneCharacter* Character;
	FWeaponData CurrentWeaponData;

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsAmmoFull() const;
	void Reload();
};
