// Fill out your copyright notice in the Description page of Project Settings.


#include "WellGame/Public/Student.h"
#include "Components/BoxComponent.h"
#include "WellGame/Public/Bonus.h"


// Sets default values
AStudent::AStudent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void AStudent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(BonusTimerHandle, this, &AStudent::DropBonus, 2.f, true);
	
}

// Called every frame
void AStudent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;

	if (NewLocation.X > MaxX || NewLocation.X < MinX)
	{
		Speed *= -1;
		NewLocation.X = FMath::Clamp(NewLocation.X, MinX, MaxX);
	}

	SetActorLocation(NewLocation);

}

void AStudent::DropBonus()
{
	if (BonusClass)
	{
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z -= 50.f; // un peu en dessous du student
		GetWorld()->SpawnActor<ABonus>(BonusClass, SpawnLocation, FRotator::ZeroRotator);
	}
}

