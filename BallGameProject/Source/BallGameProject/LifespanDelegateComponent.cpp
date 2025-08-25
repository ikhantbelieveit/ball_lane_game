// Fill out your copyright notice in the Description page of Project Settings.


#include "LifespanDelegateComponent.h"

// Sets default values for this component's properties
ULifespanDelegateComponent::ULifespanDelegateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	CurrentLifetime = MaxLifespan;

	
}



// Called when the game starts
void ULifespanDelegateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULifespanDelegateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	CurrentLifetime += DeltaTime;

	FString TheFloatStr = FString::SanitizeFloat(CurrentLifetime);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, GetName() + " LIFETIME LEFT: " + TheFloatStr);

	if (CurrentLifetime >= MaxLifespan)
	{
		OnLifetimeEnded.ExecuteIfBound();
	}
}

