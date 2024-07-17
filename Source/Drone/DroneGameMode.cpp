// Copyright Epic Games, Inc. All Rights Reserved.

#include "DroneGameMode.h"
#include "DroneCharacter.h"
#include "DroneHUD.h"
#include "UObject/ConstructorHelpers.h"

ADroneGameMode::ADroneGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
