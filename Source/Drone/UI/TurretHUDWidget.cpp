// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretHUDWidget.h"

#include "TurretPawn.h"

void UTurretHUDWidget::SetOwner(ATurretPawn* Pawn)
{
	Owner = Pawn;

	if (Owner)
	{
		Owner->OnCanSeePlayerUpdated.AddDynamic(this, &UTurretHUDWidget::UpdateWarning);
	}
}
