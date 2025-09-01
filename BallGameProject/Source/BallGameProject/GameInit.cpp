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

// Called every frame
void AGameInit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}