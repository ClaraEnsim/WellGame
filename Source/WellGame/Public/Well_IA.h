// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Well_IA.generated.h"

UCLASS()
class WELLGAME_API AWell_IA : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;

public:
	// Sets default values for this pawn's properties
	AWell_IA();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Seek(FVector TargetLocation);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Limites caméra
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinX = -500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxX = 500.f;
};
