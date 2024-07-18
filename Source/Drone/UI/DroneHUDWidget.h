// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityHUDWidget.h"
#include "TP_WeaponComponent.h"
#include "Blueprint/UserWidget.h"
#include "DroneHUDWidget.generated.h"


class UHealthComponent;

UCLASS()
class DRONE_API UDroneHUDWidget : public UEntityHUDWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnAmmoChanged(float Bullets, float Clips);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnWeaponUnequipped(UTP_WeaponComponent* WeaponComponent);
	void OnWeaponEquipped(UTP_WeaponComponent* WeaponComponent);
};
