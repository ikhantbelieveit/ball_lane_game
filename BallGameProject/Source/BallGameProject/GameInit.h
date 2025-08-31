// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EGameState.h"
#include "Kismet/GameplayStatics.h"

#include "GameInit.generated.h"

class APlayerCharacter;


UCLASS()
class BALLGAMEPROJECT_API AGameInit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameInit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	EGameState CurrentState;

	bool Initialised;

	APlayerCharacter* Player;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitialiseOnPlay();

	void SetGameState(EGameState newState);
	EGameState GetGameState();
};
