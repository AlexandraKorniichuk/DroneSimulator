// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurretPawn.generated.h"

class UWidgetComponent;
class UEntityHUDWidget;
class UTurretWeaponComponent;
class UTP_WeaponComponent;
class UHealthComponent;
class UBehaviorTree;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCanSeePlayerUpdated, bool, CanSeePlayer);

UCLASS()
class DRONE_API ATurretPawn : public APawn
{
	GENERATED_BODY()

public:
	ATurretPawn();

	UPROPERTY(BlueprintCallable)
	FOnCanSeePlayerUpdated OnCanSeePlayerUpdated;

	UFUNCTION(BlueprintPure)
	UTurretWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

protected:
	virtual void BeginPlay() override;
	void Die();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	UHealthComponent* HealthComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	UTurretWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> TurretHUDWidgetClass;
};
