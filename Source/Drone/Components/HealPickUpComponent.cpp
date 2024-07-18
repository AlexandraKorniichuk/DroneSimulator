// Fill out your copyright notice in the Description page of Project Settings.


#include "HealPickUpComponent.h"

#include "DroneCharacter.h"
#include "UHealthComponent.h"

UHealPickUpComponent::UHealPickUpComponent()
{
	OnPickUp.AddDynamic(this, &UHealPickUpComponent::TryToHeal);
}

void UHealPickUpComponent::TryToHeal(APawn* PawnToHeal) 
{
	UHealthComponent* HealthComponent = Cast<ADroneCharacter>(PawnToHeal)->GetHealthComponent();
	if (HealthComponent && HealthComponent->TryToHeal(HealAmount))
	{
		GetOwner()->Destroy();
	}
}
