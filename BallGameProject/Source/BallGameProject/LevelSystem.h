// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "DeathCollisionComponent.h"
#include "GameFramework/Actor.h"
#include "EGameState.h"
#include "LevelSystem.generated.h"
class APlayerCharacter;

UCLASS()
class BALLGAMEPROJECT_API ALevelSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	EGameState CurrentState;

	bool Initialised;

	APlayerCharacter* Player;

	void InitialiseOnPlay();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void KillPlayer();

	void SetGameState(EGameState newState);
	EGameState GetGameState();

	UFUNCTION(BlueprintCallable)
	void StartLevel();

};
