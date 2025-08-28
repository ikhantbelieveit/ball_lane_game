// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathCollisionComponent.h"

// Sets default values for this component's properties
UDeathCollisionComponent::UDeathCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

}


// Called when the game starts
void UDeathCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!CollisionComponent)
	{
		// Automatically find the first primitive component with collision
		CollisionComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	}

	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UDeathCollisionComponent::HandleBeginOverlap);
	}
}

void UDeathCollisionComponent::HandleBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	if (!OtherActor || OtherActor == GetOwner())
	{
		return;
	}

	// Check for tag
	if (OtherActor->ActorHasTag(PlayerTag))
	{
		TriggerKillPlayer();
	}
}


// Called every frame
void UDeathCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDeathCollisionComponent::TriggerKillPlayer()
{
	OnPlayerEnter.Broadcast();
}


