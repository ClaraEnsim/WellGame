// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUI.generated.h"

/**
 * 
 */
UCLASS()
class WELLGAME_API UScoreUI : public UUserWidget
{
	GENERATED_BODY()

public:

	// Score réel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score")
	int32 BonusCaught = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score")
	int32 BonusMissed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score")
	int32 BonusSpawned = 0;
    
	// Fonction pour calculer le pourcentage de réussite
	UFUNCTION(BlueprintCallable, Category="Score")
	float GetSuccessPercent() const;
};
