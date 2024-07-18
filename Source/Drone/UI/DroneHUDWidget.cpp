// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneHUDWidget.h"

#include "TP_WeaponComponent.h"
#include "DroneCharacter.h"

void UDroneHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ADroneCharacter* DroneCharacter = Cast<ADroneCharacter>(GetOwningPlayerPawn());
	DroneCharacter->OnWeaponUnequipped.AddUObject(this, &UDroneHUDWidget::OnWeaponUnequipped);
	DroneCharacter->OnWeaponEquipped.AddUObject(this, &UDroneHUDWidget::OnWeaponEquipped);
}

void UDroneHUDWidget::OnWeaponEquipped(UTP_WeaponComponent* WeaponComponent)
{
	WeaponComponent->OnAmmoChanged.AddUObject(this, &UDroneHUDWidget::OnAmmoChanged);
}
