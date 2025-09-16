// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUI.h"


float UScoreUI::GetSuccessPercent() const
{
	if (BonusSpawned == 0) return 0.f;
	return (float(BonusCaught) / float(BonusSpawned)) * 100.f;
} 
