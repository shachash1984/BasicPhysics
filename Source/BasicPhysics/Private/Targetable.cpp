// Fill out your copyright notice in the Description page of Project Settings.


#include "Targetable.h"
#include "BasicPhysics/BasicPhysics.h"

// Sets default values
ATargetable::ATargetable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Load and assign Static MeshComponent for Arrow Head
    if (!MeshComponent)
    {
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target_Mesh"));

	    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("'/Game/Meshes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
		if (Mesh.Succeeded())
		{
			MeshComponent->SetStaticMesh(Mesh.Object);
		}
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshComponent->SetupAttachment(RootComponent);
    }
}

// Called when the game starts or when spawned
void ATargetable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetable::OnHit()
{
	UE_LOG(LogBasicPhysicsGame, Log, TEXT("Oww!"));
	Destroy();
}

