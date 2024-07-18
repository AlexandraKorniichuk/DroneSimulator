// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickUpComponent.h"

#include "TP_WeaponComponent.h"

UAmmoPickUpComponent::UAmmoPickUpComponent()
{
	OnPickUp.AddDynamic(this, &UAmmoPickUpComponent::TryToAddAmmo);
}

void UAmmoPickUpComponent::TryToAddAmmo(APawn* Pawn)
{
	ADroneCharacter* DroneCharacter = Cast<ADroneCharacter>(Pawn);
	UTP_WeaponComponent* WeaponComponent = DroneCharacter->GetWeaponComponent();
	
	if (!WeaponComponent) return;
	
	if (WeaponComponent->TryToAddAmmo(AmmoAmount))
	{
		GetOwner()->Destroy();
	}
}
