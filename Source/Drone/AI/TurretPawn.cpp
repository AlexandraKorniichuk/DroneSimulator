// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"

#include "UHealthComponent.h"

ATurretPawn::ATurretPawn()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

