// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_PickUpComponent.h"
#include "AmmoPickUpComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DRONE_API UAmmoPickUpComponent : public UTP_PickUpComponent
{
	GENERATED_BODY()
public:
	UAmmoPickUpComponent();

protected:
	UFUNCTION()
	void TryToAddAmmo(APawn* Pawn);
	
	UPROPERTY(EditDefaultsOnly, Category="Ammo", meta = (ClampMin = "0", ClampMax = "100"))
	int AmmoAmount = 10;
};
