// Fill out your copyright notice in the Description page of Project Settings.


#include "IAGameMode.h"

float AIAGameMode::GetSuccessPercent() const
{
	if (BonusSpawned == 0) return 0.f;
	return (float(BonusCaught) / float(BonusSpawned)) * 100.f;
}

void AIAGameMode::AddBonus()
{
	BonusCaught++;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
			FString::Printf(TEXT("BonusCaught = %d"), BonusCaught));
}

void AIAGameMode::AddBonusSpawn()
{
	BonusSpawned++;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
			FString::Printf(TEXT("BonusSpawned = %d"), BonusSpawned));
}

