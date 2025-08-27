// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EPlayerJumpState.h"
#include "EPlayerProjectileDirection.h"
#include "PlayerProjectile.h"
#include "EPlayerSpeedState.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.generated.h"

// Forward declaration of Paper2D component

class UPaperSpriteComponent;
class UScrollWithPlayerComponent;

UCLASS()
class BALLGAMEPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateSpeedFromInput();

	void UpdateLaneFromInput();

	bool MoveLane_Left();
	bool MoveLane_Right();
	bool SetLane(int laneIndex);
	bool CanPlayerOccupyLane(int laneIndex);

	void UpdateJumpFromInput();

	void UpdateShootValues(float DeltaTime);

	void UpdateShootFromInput();

	void UpdateLaneScroll();

	void UpdateJumpState(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Input_LeftStart(const FInputActionValue& Value);
	virtual void Input_RightStart(const FInputActionValue& Value);

	virtual void Input_JumpStart(const FInputActionValue& Value);
	virtual void Input_Jump(const FInputActionValue& Value);
	virtual void Input_JumpCancel(const FInputActionValue& Value);

	virtual void Input_SpeedUpStart(const FInputActionValue& Value);
	virtual void Input_SpeedUp(const FInputActionValue& Value);
	virtual void Input_SpeedUpCancel(const FInputActionValue& Value);

	virtual void Input_SlowDownStart(const FInputActionValue& Value);
	virtual void Input_SlowDown(const FInputActionValue& Value);
	virtual void Input_SlowDownCancel(const FInputActionValue& Value);

	virtual void Input_ShootLeft(const FInputActionValue& Value);
	virtual void Input_ShootRight(const FInputActionValue& Value);
	virtual void Input_ShootUp(const FInputActionValue& Value);
	virtual void Input_ShootForward(const FInputActionValue& Value);

	virtual void Input_ShootLeftStart(const FInputActionValue& Value);
	virtual void Input_ShootRightStart(const FInputActionValue& Value);
	virtual void Input_ShootUpStart(const FInputActionValue& Value);
	virtual void Input_ShootForwardStart(const FInputActionValue& Value);

	void Shoot(EPlayerProjectileDirection direction, bool bypassDelay, bool holdNotTap);
	bool CanShootInDirection(EPlayerProjectileDirection direction, bool bypassDelay, bool holdNotTap);
	bool DelayPreventsShootInDirection(EPlayerProjectileDirection direction);
	bool ExceededProjCountForDirection(EPlayerProjectileDirection direction);

	float TimeSinceShoot_Left;
	float TimeSinceShoot_Right;
	float TimeSinceShoot_Up;
	float TimeSinceShoot_Forward;

	int HoldShotsRemaining_Left;
	int HoldShotsRemaining_Right;
	int HoldShotsRemaining_Up;
	int HoldShotsRemaining_Forward;

	UPROPERTY(EditAnywhere)
	float ShootHoldInputDelay = 0.5f;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere)
	float DefaultRunSpeed = 600.0f;

	UPROPERTY(EditAnywhere)
	float FastRunSpeed = 1200.0f;

	UPROPERTY(EditAnywhere)
	float SlowRunSpeed = 200.0f;

	UPROPERTY(EditAnywhere)
	float JumpRiseGravity = 0.7f;

	UPROPERTY(EditAnywhere)
	float JumpFallGravity = 0.2f;

	UPROPERTY(EditAnywhere)
	float JumpApexHangTime = 0.1f;

	bool JumpedThisFrame;

	virtual float GetCurrentRunSpeed();

	void SetSpeedState(EPlayerSpeedState newState);
	void SetJumpState(EPlayerJumpState newState);
	float TimeSinceJumpStateChange;

	UPROPERTY(EditAnywhere)
	float LaneDistance = 500.0f;

	UPROPERTY(EditAnywhere)
	float CameraHeight = 175.0f;

	UPROPERTY(EditAnywhere)
	int HoldShoot_MaxProjectiles = 1;



protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_LeftAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_RightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_SpeedUpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_SlowDownAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_ShootLeftAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_ShootRightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_ShootUpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_ShootForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMap;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class APlayerProjectile> ProjectileClass;

	float CurrentRunSpeed;

	void ClearInputValues();

	bool JumpInput_Active;
	bool JumpInput_Pressed;
	bool JumpInput_Released;

	bool SpeedInput_Active;
	bool SpeedInput_Pressed;
	bool SpeedInput_Released;

	bool SlowInput_Active;
	bool SlowInput_Pressed;
	bool SlowInput_Released;

	bool LeftInput_Pressed;

	bool RightInput_Pressed;

	bool ShootLeftInput_Active;
	bool ShootRightInput_Active;
	bool ShootUpInput_Active;
	bool ShootForwardInput_Active;

	bool ShootLeftInput_Pressed;
	bool ShootRightInput_Pressed;
	bool ShootUpInput_Pressed;
	bool ShootForwardInput_Pressed;

	void Debug_PrintInputValues();

	EPlayerSpeedState CurrentSpeedState;

	EPlayerJumpState CurrentJumpState;

	void CancelVerticalSpeed();

	int CurrentLaneIndex;	//0-4 left-right
};
