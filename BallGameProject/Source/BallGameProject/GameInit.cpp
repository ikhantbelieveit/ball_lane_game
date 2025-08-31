// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInit.h"
#include "PlayerCharacter.h"

// Sets default values
AGameInit::AGameInit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameInit::BeginPlay()
{
	Super::BeginPlay();
	
	InitialiseOnPlay();
	
}

void AGameInit::InitialiseOnPlay()
{
	if (Initialised)
	{
		return;
	}

	//get player ref
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerCharacter* PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));

	if (PlayerRef)
	{
		Player = PlayerRef;
		Player->Initialise();
	}

	SetGameState(EGameState::Dormant);

	Initialised = true;
}

// Called every frame
void AGameInit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameInit::SetGameState(EGameState newState)
{
	CurrentState = newState;

	if (Player)
	{
		Player->UpdateOnGameStateChange(newState);
	}
}

EGameState AGameInit::GetGameState()
{
	return CurrentState;
}