// Fill out your copyright notice in the Description page of Project Settings.


#include "UHealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);
	
	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}
}

void UHealthComponent::UpdateHealth(float UpdatedHealth)
{
	Health = FMath::Clamp(UpdatedHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                       AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f || IsDead()) return;
	
	UpdateHealth(Health - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

bool UHealthComponent::TryToHeal(float HealAmount)
{
	if (IsDead() || IsFullHealth())
	{
		return false;
	}
	UpdateHealth(Health + HealAmount);
	return true;
}


