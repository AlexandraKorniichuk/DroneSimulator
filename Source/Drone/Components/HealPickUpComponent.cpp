// Fill out your copyright notice in the Description page of Project Settings.


#include "HealPickUpComponent.h"
#include "UHealthComponent.h"

UHealPickUpComponent::UHealPickUpComponent()
{
	OnPickUp.AddDynamic(this, &UHealPickUpComponent::TryToHeal);
}

void UHealPickUpComponent::TryToHeal(APawn* PawnToHeal) 
{
	UHealthComponent* HealthComponent = Cast<UHealthComponent>(PawnToHeal->GetComponentByClass(UHealthComponent::StaticClass()));
	if (HealthComponent &&HealthComponent->TryToHeal(HealAmount))
	{
		GetOwner()->Destroy();
	}
}
