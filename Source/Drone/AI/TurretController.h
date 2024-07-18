// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TurretController.generated.h"

struct FAIStimulus;
/**
 * 
 */
UCLASS()
class DRONE_API ATurretController : public AAIController
{
	GENERATED_BODY()

public:
	ATurretController();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAIPerceptionComponent* AIPerceptionComponent;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;
};
