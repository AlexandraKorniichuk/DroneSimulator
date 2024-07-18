// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretController.h"

#include "TurretPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
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

void ATurretController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (BlackboardComponent && BlackboardComponent->GetValueAsBool("CanSeePlayer"))
	{
		FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		BlackboardComponent->SetValueAsVector("PlayerLocation", PlayerLocation);
	}
}
