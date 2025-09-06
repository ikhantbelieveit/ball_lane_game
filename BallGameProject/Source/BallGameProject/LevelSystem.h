// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSystem.h"
#include "EGameState.h"
#include "DeathCollisionComponent.h"
#include "LevelSystem.generated.h"

/**
 * 
 */
UCLASS()
class BALLGAMEPROJECT_API ALevelSystem : public AGameSystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialise() override;

	void SetGameState(EGameState newState);
	EGameState GetGameState();

	UFUNCTION()
	void HandleDeathEvent();

	void RegisterDeathTrigger(UDeathCollisionComponent trigger);

protected:
	EGameState CurrentState;

	
	
};
