// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float Health);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const { return Health / MaxHealth; }

	float GetHealth() const { return Health; }
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }
	bool IsFullHealth() const { return FMath::IsNearlyEqual(Health, MaxHealth); }
	bool TryToHeal(float HealAmount);

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	
protected:	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

private:
	float Health = 0.0f;

	void UpdateHealth(float UpdatedHealth);

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);
};
