// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_PickUpComponent.h"
#include "HealPickUpComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DRONE_API UHealPickUpComponent : public UTP_PickUpComponent
{
	GENERATED_BODY()

public:
	UHealPickUpComponent();
	
protected:
	UFUNCTION()
	void TryToHeal(APawn* PawnToHeal);

	UPROPERTY(EditDefaultsOnly, Category="Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float HealAmount = 10.0f;
};
