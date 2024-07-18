// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "TurretWeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONE_API UTurretWeaponComponent : public UTP_WeaponComponent
{
	GENERATED_BODY()

public:
	virtual void Fire() override;
};
