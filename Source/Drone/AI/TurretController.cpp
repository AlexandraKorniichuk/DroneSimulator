// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretController.h"

#include "TurretPawn.h"
#include "Perception/AIPerceptionComponent.h"

ATurretController::ATurretController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);
}

void ATurretController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ATurretPawn* Turret = Cast<ATurretPawn>(InPawn);
	if (Turret)
	{
		RunBehaviorTree(Turret->BehaviorTree);
	}
}
