// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneHUDWidget.h"

#include "TP_WeaponComponent.h"
#include "Curves/CurveLinearColor.h"
#include "Drone/DroneCharacter.h"
#include "Drone/Components/UHealthComponent.h"

void UDroneHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthComponent();

	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UDroneHUDWidget::OnHealthChanged);
	}

	ADroneCharacter* DroneCharacter = Cast<ADroneCharacter>(GetOwningPlayerPawn());
	DroneCharacter->OnWeaponUnequipped.AddUObject(this, &UDroneHUDWidget::OnWeaponUnequipped);
	DroneCharacter->OnWeaponEquipped.AddUObject(this, &UDroneHUDWidget::OnWeaponEquipped);
}

void UDroneHUDWidget::OnWeaponEquipped(UTP_WeaponComponent* WeaponComponent)
{
	WeaponComponent->OnAmmoChanged.AddUObject(this, &UDroneHUDWidget::OnAmmoChanged);
}

float UDroneHUDWidget::GetHealthPercent()
{
	APawn* Owner = GetOwningPlayerPawn();
	if (!Owner)
	{
		return 0.0f;
	}

	if (!HealthComponent)
	{
		SetHealthComponent();
	}
	
	return HealthComponent ? HealthComponent->GetHealthPercent() : 0.0f;
}


void UDroneHUDWidget::SetHealthComponent()
{
	HealthComponent = Cast<UHealthComponent>(GetOwningPlayerPawn()->GetComponentByClass(UHealthComponent::StaticClass()));
}

FLinearColor UDroneHUDWidget::GetHealthBarColor(float HealthPercent) const
{
	FLinearColor HealthColor = HealthColorCurve->GetLinearColorValue(HealthPercent);
	return HealthColor;
}
