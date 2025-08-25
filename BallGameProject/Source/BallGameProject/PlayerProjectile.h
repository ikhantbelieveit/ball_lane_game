// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "EPlayerProjectileDirection.h"
#include "LifespanDelegateComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProjectile.generated.h"

class UScrollWithPlayerComponent;
class APlayerCharacter;

UCLASS()
class BALLGAMEPROJECT_API APlayerProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	//Scroll with player component
	UPROPERTY(VisibleAnywhere)
	UScrollWithPlayerComponent* ScrollWithPlayerComponent;

	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	ULifespanDelegateComponent* LifespanComponent;

	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

	void InitialiseBeforeShoot(EPlayerProjectileDirection directionEnum);

	EPlayerProjectileDirection ShootInDirection;

	APlayerCharacter* PlayerRef;
	bool HasPlayerRef;

	void OnComponentLifespanEnded();
};
