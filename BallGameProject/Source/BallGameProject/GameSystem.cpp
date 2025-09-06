// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem.h"

// Sets default values
AGameSystem::AGameSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameSystem::Initialise()
{

}