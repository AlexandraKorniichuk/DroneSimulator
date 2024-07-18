// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretWeaponComponent.h"

#include "Drone/DroneProjectile.h"

void UTurretWeaponComponent::Fire()
{
	if (UWorld* const World = GetWorld())
	{
		//AController* Controller = Cast<AController>(Cast<APawn>(GetOwner())->GetController());
		const FRotator SpawnRotation = GetOwner()->GetActorRotation();
		const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
		World->SpawnActor<ADroneProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}
