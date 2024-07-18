// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityHUDWidget.h"
#include "TurretHUDWidget.generated.h"

class ATurretPawn;
/**
 * 
 */
UCLASS()
class DRONE_API UTurretHUDWidget : public UEntityHUDWidget
{
	GENERATED_BODY()


public:
	void SetOwner(ATurretPawn* Pawn);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWarning(bool IsWarning);
	
private:
	ATurretPawn* Owner;
};
