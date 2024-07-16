// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneHUD.h"
#include "Blueprint/UserWidget.h"

void ADroneHUD::BeginPlay()
{
	Super::BeginPlay();

	auto HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}
