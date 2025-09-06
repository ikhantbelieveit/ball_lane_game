// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInit.h"

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
	
	Initialise();
}

// Sets default values
void AGameInit::Initialise()
{
	if (Initialised)
	{
		return;
	}

	//create all game system actors
    if (UWorld* World = GetWorld())
    {
        FVector SpawnLocation(0.f, 0.f, 100.f);
        FRotator SpawnRotation(0.f, 0.f, 0.f);

        // Spawn parameters
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        // Spawn the actor
        ALevelSystem* SpawnedActor = World->SpawnActor<ALevelSystem>(
            ALevelSystem::StaticClass(),
            SpawnLocation,
            SpawnRotation,
            SpawnParams
        );

        if (SpawnedActor)
        {
            SpawnedActor->Initialise();

            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Spawned level system"));
        }
    }

	Initialised = true;
}


// Called every frame
void AGameInit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

