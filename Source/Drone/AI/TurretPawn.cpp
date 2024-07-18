// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"

#include "EntityHUDWidget.h"
#include "TurretWeaponComponent.h"
#include "UHealthComponent.h"
#include "Components/WidgetComponent.h"

ATurretPawn::ATurretPawn()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UTurretWeaponComponent>("WeaponComponent");

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();

	UEntityHUDWidget* Widget = CreateWidget<UEntityHUDWidget>(GetWorld(), EntityHUDWidgetClass);
	WidgetComponent->SetWidget(Widget);
	Widget = Cast<UEntityHUDWidget>(WidgetComponent->GetWidget());
	if (Widget)
	{
		Widget->SetHealthComponent(HealthComponent);
		WidgetComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	HealthComponent->OnDeath.AddUObject(this, &ATurretPawn::Die);
}

void ATurretPawn::Die()
{
	Destroy();
}

