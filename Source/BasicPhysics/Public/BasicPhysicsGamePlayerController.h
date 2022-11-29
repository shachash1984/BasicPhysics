// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPhysicsGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BASICPHYSICS_API ABasicPhysicsGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasicPhysicsGamePlayerController();

protected:

	void OnShootPressed();
	virtual void SetupInputComponent() override;

	APlayerCameraManager* CameraManager;
};


