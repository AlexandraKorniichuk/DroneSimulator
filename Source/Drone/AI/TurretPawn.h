// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurretPawn.generated.h"

class UHealthComponent;
class UBehaviorTree;

UCLASS()
class DRONE_API ATurretPawn : public APawn
{
	GENERATED_BODY()

public:
	ATurretPawn();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	UHealthComponent* HealthComponent;
};
