// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "DeathCollisionComponent.generated.h"

// Declare a delegate so you can bind functions to it in Blueprints or C++
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerEnter);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BALLGAMEPROJECT_API UDeathCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDeathCollisionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// The collision component we want to listen on (assignable in Blueprint instance)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	TObjectPtr<UPrimitiveComponent> CollisionComponent;

	// Tag to check against (default: "Player")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	FName PlayerTag = "Player";

	UFUNCTION()
	void HandleBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Overlap")
	FOnPlayerEnter OnPlayerEnter;

	void TriggerKillPlayer();

		
};
