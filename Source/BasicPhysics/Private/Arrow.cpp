// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPhysics/Public/Arrow.h"
#include "BasicPhysics/BasicPhysics.h"
#include "Misc/AssertionMacros.h"
#include "BasicPhysics/Public/Targetable.h"

// Sets default values
AArrow::AArrow()
{
	//UE_LOG(LogBasicPhysicsGame, Log, TEXT("Arrow Ctor called"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Load and assign Static MeshComponent for Arrow Head
    if (!ArrowHead)
    {
		ArrowHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));

	    static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowHeadMesh(TEXT("'/Game/Meshes/Cone.Cone'"));
		if (ArrowHeadMesh.Succeeded())
		{
			ArrowHead->SetStaticMesh(ArrowHeadMesh.Object);
		}
    }
	check(ArrowHead);
	//Change Root Component
	

	RootComponent = ArrowHead;
	ArrowHead->SetRelativeLocation(FVector::ZeroVector);

	// Handle Physics for the Arrow head
	ArrowHead->SetSimulatePhysics(true);
	//ArrowHead->SetCollisionProfileName(TEXT("PhysicsActor"));
	// Arrow doesn't collide with player
	ArrowHead->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	ArrowHead->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//ArrowHead->SetupAttachment(RootComponent);
	
	ArrowHead->SetNotifyRigidBodyCollision(true);
	 
	ArrowHead->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.2f));

	if (!ArrowBody)
	{
		ArrowBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowBodyMesh(TEXT("'/Game/Meshes/Cylinder.Cylinder'"));
		if (ArrowBodyMesh.Succeeded())
		{
			ArrowBody->SetStaticMesh(ArrowBodyMesh.Object);
		}
	}
	check(ArrowBody);

	ArrowBody->SetSimulatePhysics(false);
	ArrowBody->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ArrowBody->SetupAttachment(ArrowHead);
	ArrowBody->SetRelativeLocation(FVector(0.0f, 0.0f, -230.0f));
	ArrowBody->SetRelativeScale3D(FVector(0.3f, 0.3f, 2.0f));

	// Generate Hit Event
	FScriptDelegate CollisionDelegate;
	CollisionDelegate.BindUFunction(this, "OnCollision");
	ArrowHead->OnComponentHit.Add(CollisionDelegate);
	

	//Load and assign material for Arrow MeshComponent
	static ConstructorHelpers::FObjectFinder<UMaterial> ArrowMaterial(TEXT("'/Game/Materials/M_Arrow.M_Arrow'"));
	if (ArrowMaterial.Succeeded())
    {
		ArrowHead->SetMaterial(0, ArrowMaterial.Object);
		ArrowBody->SetMaterial(0, ArrowMaterial.Object);
    }

	//ArrowHead->SetMassOverrideInKg(NAME_None, 1.0f, true);
	
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogBasicPhysicsGame, Log, TEXT("Arrow BeginPlay called"));
	this->SetLifeSpan(5.0f);
	// Add Impulse to Arrow Head
	
}

void AArrow::OnCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this))
	{
		ATargetable* Target = Cast<ATargetable>(OtherActor);
		if (Target)
		{
			UE_LOG(LogBasicPhysicsGame, Log, TEXT("Arrow Hit Target"));
			Target->OnHit();
			Destroy();
		}
		
	}
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArrow::Launch(FVector Direction, FRotator Rotation, float Speed)
{
	const FRotator WantedRotation = FRotator(Rotation.Pitch + 270, Rotation.Yaw, 0.0);
	ArrowHead->SetWorldRotation(WantedRotation);
	ArrowHead->AddImpulse(Direction*Speed, NAME_None, true);
}

