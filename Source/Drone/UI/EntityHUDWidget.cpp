// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityHUDWidget.h"

#include "Curves/CurveLinearColor.h"
#include "Drone/Components/UHealthComponent.h"

void UEntityHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

float UEntityHUDWidget::GetHealthPercent()
{
	return HealthComponent ? HealthComponent->GetHealthPercent() : 0.0f;
}


void UEntityHUDWidget::SetHealthComponent(UHealthComponent* InHealthComponent)
{
	if (!InHealthComponent) return;
	
	HealthComponent = InHealthComponent;
	HealthComponent->OnHealthChanged.AddUObject(this, &UEntityHUDWidget::OnHealthChanged);
}

FLinearColor UEntityHUDWidget::GetHealthBarColor(float HealthPercent) const
{
	FLinearColor HealthColor = HealthColorCurve->GetLinearColorValue(HealthPercent);
	return HealthColor;
}

