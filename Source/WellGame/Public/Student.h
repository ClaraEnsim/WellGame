
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Student.generated.h"

// Forward declaration de ABonus
class ABonus;

UCLASS()
class WELLGAME_API AStudent : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;
                    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

public:
	// Sets default values for this actor's properties
	AStudent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float Speed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MinX = -500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxX = 500.f;

	UPROPERTY(EditAnywhere, Category="Bonus")
	TArray<TSubclassOf<ABonus>> BonusClasses;

	// Timer pour spawn bonus
	FTimerHandle BonusTimerHandle;

	void DropBonus();
};
