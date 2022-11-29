// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPhysics/Public/BasicPhysicsGamePlayerController.h"
#include "BasicPhysics/Public/Arrow.h"
#include "Kismet/GameplayStatics.h"

ABasicPhysicsGamePlayerController::ABasicPhysicsGamePlayerController()
{
	
}

void ABasicPhysicsGamePlayerController::OnShootPressed()
{
	UWorld* World = GetWorld();
	if (World)
	{
		if (!CameraManager)
		{
			CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		}

		AArrow* Arrow = World->SpawnActor<AArrow>(GetPawn()->GetActorLocation()+CameraManager->GetActorForwardVector()*100, GetPawn()->GetControlRotation());
		if (Arrow)
		{

			Arrow->Launch(CameraManager->GetActorForwardVector(), CameraManager->GetCameraRotation() ,2000.0f);
		}
	}
	
}

void ABasicPhysicsGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Shoot", IE_Pressed, this, &ABasicPhysicsGamePlayerController::OnShootPressed);
}
