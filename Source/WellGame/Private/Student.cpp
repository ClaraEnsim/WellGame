// Fill out your copyright notice in the Description page of Project Settings.


#include "WellGame/Public/Student.h"
#include "EngineUtils.h"
#include "IAGameMode.h"
#include "Well_IA.h"
#include "Components/BoxComponent.h"
#include "WellGame/Public/Bonus.h"
#include "ScoreUI.h"


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
	if (BonusClasses.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, BonusClasses.Num() - 1);
		TSubclassOf<ABonus> ChosenBonus = BonusClasses[RandomIndex];
		if (ChosenBonus)
		{
			FVector SpawnLocation = GetActorLocation();
			SpawnLocation.Z -= 50.f;

			GetWorld()->SpawnActor<ABonus>(ChosenBonus, SpawnLocation, FRotator::ZeroRotator);

			// Récupérer Well_IA dans la scène pour compter
			for (TActorIterator<AWell_IA> It(GetWorld()); It; ++It)
			{
				AIAGameMode* GameMode = (AIAGameMode*)GetWorld()->GetAuthGameMode();

				GameMode->AddBonusSpawn();
			}
		}
	}
}

