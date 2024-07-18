// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"

#include "TurretWeaponComponent.h"
#include "UHealthComponent.h"

ATurretPawn::ATurretPawn()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UTurretWeaponComponent>("WeaponComponent");
}

void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddUObject(this, &ATurretPawn::Die);
}

void ATurretPawn::Die()
{
	Destroy();
}

