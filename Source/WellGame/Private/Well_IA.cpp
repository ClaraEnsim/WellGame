// Fill out your copyright notice in the Description page of Project Settings.


#include "WellGame/Public/Well_IA.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "WellGame/Public/Bonus.h"


// Sets default values
AWell_IA::AWell_IA()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent0"));
	MovementComponent->UpdatedComponent = BoxCollision;
}

// Called when the game starts or when spawned
void AWell_IA::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AWell_IA::Seek(FVector TargetLocation)
{
	FVector Desired = TargetLocation - GetActorLocation();
	Desired.Z = 0;
	Desired.Normalize();
	Desired *= MovementComponent->GetMaxSpeed();

	FVector Steering = Desired - MovementComponent->Velocity;
	Steering.Z = 0;
	return Steering;
}

// Called every frame
void AWell_IA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABonus* TargetBonus = nullptr;
	TArray<AActor*> FoundBonuses;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABonus::StaticClass(), FoundBonuses);

	if (FoundBonuses.Num() > 0)
	{
		TargetBonus = Cast<ABonus>(FoundBonuses[0]);
	}

	if (TargetBonus)
	{
		FVector Steering = Seek(TargetBonus->GetActorLocation());
		MovementComponent->AddInputVector(Steering * DeltaTime);

		// Clamp horizontal
		FVector NewLocation = GetActorLocation() + MovementComponent->Velocity * DeltaTime;
		NewLocation.X = FMath::Clamp(NewLocation.X, MinX, MaxX);
		SetActorLocation(NewLocation);
	}
}

void AWell_IA::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ABonus* Bonus = Cast<ABonus>(OtherActor);
	if (Bonus)
	{
		Bonus->Destroy();
		// Score ou feedback ici
	}
}

void AWell_IA::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
