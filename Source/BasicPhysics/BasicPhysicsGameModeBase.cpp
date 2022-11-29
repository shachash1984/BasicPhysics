// Copyright Epic Games, Inc. All Rights Reserved.


#include "BasicPhysicsGameModeBase.h"

#include "Public/BasicPhysicsGamePlayerController.h"

ABasicPhysicsGameModeBase::ABasicPhysicsGameModeBase()
{
	PlayerControllerClass = ABasicPhysicsGamePlayerController::StaticClass();
}
