// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DroneHUDWidget.generated.h"


class UHealthComponent;

UCLASS()
class DRONE_API UDroneHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetHealthPercent();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Health")
	void OnHealthChanged(float Health);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	FLinearColor GetHealthBarColor(float HealthPercent) const;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
    UCurveLinearColor* HealthColorCurve;
	
private:
	UHealthComponent* HealthComponent;
	void SetHealthComponent();
};
