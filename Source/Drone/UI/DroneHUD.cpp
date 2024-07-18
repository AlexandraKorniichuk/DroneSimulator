// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneHUD.h"

#include "UHealthComponent.h"
#include "Blueprint/UserWidget.h"
#include "DroneCharacter.h"

void ADroneHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass);
	if (GameWidget)
	{
		GameWidget->AddToViewport();
		Owner = GameWidget->GetOwningPlayerPawn();
	}

	UHealthComponent* HealthComponent = Cast<ADroneCharacter>(Owner)->GetHealthComponent();
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddUObject(this, &ADroneHUD::SetDeathWidget);
	}
}

void ADroneHUD::SetDeathWidget() const
{
	if (GameWidget)
	{
		GameWidget->RemoveFromParent();
	}
	
	auto Widget = CreateWidget<UUserWidget>(GetWorld(), DeathWidgetClass);
	if (Widget)
	{
		Widget->AddToViewport();
	}
}
