// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSystem.h"

void ALevelSystem::Initialise()
{
	Super::Initialise();

	SetGameState(EGameState::Active);
}

void ALevelSystem::SetGameState(EGameState newState)
{
	if (newState == CurrentState)
	{
		return;
	}

	CurrentState = newState;


}

EGameState ALevelSystem::GetGameState()
{
	return CurrentState;
}

void ALevelSystem::HandleDeathEvent()
{
	if (CurrentState == EGameState::Active)
	{
		SetGameState(EGameState::Lose);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("DEAD."));
	}
}
