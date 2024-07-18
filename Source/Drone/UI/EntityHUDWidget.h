// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntityHUDWidget.generated.h"

class UHealthComponent;
/**
 * 
 */
UCLASS()
class DRONE_API UEntityHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetHealthPercent();
	void SetHealthComponent(UHealthComponent* InHealthComponent);

protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Health")
	void OnHealthChanged(float Health);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	FLinearColor GetHealthBarColor(float HealthPercent) const;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	UCurveLinearColor* HealthColorCurve;
	
private:
	UPROPERTY()
	UHealthComponent* HealthComponent;
};
