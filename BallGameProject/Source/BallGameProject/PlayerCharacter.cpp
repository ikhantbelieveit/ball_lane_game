// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	// Create a first person camera component.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	check(CameraComponent != nullptr);

	// Attach the camera component to our capsule component.
	CameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("PlayerCharacter start."));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLaneScroll();

	UpdateSpeedFromInput();
	UpdateLaneFromInput();
	UpdateJumpFromInput();
	UpdateShootFromInput();


	//clamp camera Z pos
	FVector CameraClampZPos = FVector(CameraComponent->GetComponentLocation().X, CameraComponent->GetComponentLocation().Y, CameraHeight);
	CameraComponent->SetWorldLocation(CameraClampZPos);
	
	//Debug_PrintInputValues();

	//clear stuff at end
	ClearInputValues();

	
}

void APlayerCharacter::UpdateShootFromInput()
{
	if (ShootLeftInput_Pressed)
	{
		Shoot(EPlayerProjectileDirection::Left);
	}
	if (ShootRightInput_Pressed)
	{
		Shoot(EPlayerProjectileDirection::Right);
	}
	if (ShootUpInput_Pressed)
	{
		Shoot(EPlayerProjectileDirection::Up);
	}
	if (ShootForwardInput_Pressed)
	{
		Shoot(EPlayerProjectileDirection::Forward);
	}
}

void APlayerCharacter::UpdateLaneFromInput()
{
	if (LeftInput_Pressed)
	{
		FVector offset = FVector(0, -LaneDistance, 0);
		AddActorWorldOffset(offset);

		CameraComponent->SetWorldLocation(FVector(
			CameraComponent->GetComponentLocation().X,
			0,
			CameraComponent->GetComponentLocation().Z));
	}

	if (RightInput_Pressed)
	{
		FVector offset = FVector(0, LaneDistance, 0);
		AddActorWorldOffset(offset);

		CameraComponent->SetWorldLocation(FVector(
			CameraComponent->GetComponentLocation().X,
			0,
			CameraComponent->GetComponentLocation().Z));
	}
}

void APlayerCharacter::UpdateSpeedFromInput()
{
	EPlayerSpeedState newState = EPlayerSpeedState::Default;

	if (SpeedInput_Active)
	{
		newState = EPlayerSpeedState::Fast;
	}

	if (SlowInput_Active)
	{
		newState = EPlayerSpeedState::Slow;
	}

	if (SpeedInput_Active && SlowInput_Active)
	{
		newState = EPlayerSpeedState::Default;
	}

	SetSpeedState(newState);


	switch (CurrentSpeedState)
	{
	case EPlayerSpeedState::Fast:
		GetCharacterMovement()->MaxWalkSpeed = FastRunSpeed;
		break;
	case EPlayerSpeedState::Slow:
		GetCharacterMovement()->MaxWalkSpeed = SlowRunSpeed;
		break;
	default:
		GetCharacterMovement()->MaxWalkSpeed = DefaultRunSpeed;
		break;
	}
}

void APlayerCharacter::UpdateJumpFromInput()
{
	if (JumpInput_Active)
	{
		bPressedJump = true;
	}

	if (JumpInput_Released)
	{
		bPressedJump = false;
	}
}

void APlayerCharacter::UpdateLaneScroll()
{
	//scroll behaviour
	AddMovementInput(FVector(GetCurrentRunSpeed(), 0.0f, 0.0f));
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//get local player instance
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//add input context
			SubSystem->AddMappingContext(InputMap, 0);
		}
	}

	//left
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_LeftAction, ETriggerEvent::Started, this, &APlayerCharacter::Input_LeftStart);
	}
	//right
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_RightAction, ETriggerEvent::Started, this, &APlayerCharacter::Input_RightStart);
	}
	//jump
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Jump);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::Input_JumpCancel);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Input_JumpStart);
	}

	//speed up
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_SpeedUpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_SpeedUp);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_SpeedUpAction, ETriggerEvent::Completed, this, &APlayerCharacter::Input_SpeedUpCancel);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_SpeedUpAction, ETriggerEvent::Started, this, &APlayerCharacter::Input_SpeedUpStart);
	}


	//slow down
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_SlowDownAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_SlowDown);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_SlowDownAction, ETriggerEvent::Completed, this, &APlayerCharacter::Input_SlowDownCancel);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_SlowDownAction, ETriggerEvent::Started, this, &APlayerCharacter::Input_SlowDownStart);
	}

	//shoot left
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootLeftAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_ShootLeft);
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootLeftAction, ETriggerEvent::Started, this, &APlayerCharacter::Input_ShootLeftStart);
	}

	//shoot right
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_ShootRight);
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootRightAction, ETriggerEvent::Started, this, &APlayerCharacter::Input_ShootRightStart);
	}

	//shoot up
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootUpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_ShootUp);
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootUpAction, ETriggerEvent::Started, this, &APlayerCharacter::Input_ShootUpStart);
	}

	//shoot forward
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootForwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_ShootForward);
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootForwardAction, ETriggerEvent::Started, this, &APlayerCharacter::Input_ShootForwardStart);
	}
}

void APlayerCharacter::Input_LeftStart(const FInputActionValue& Value)
{
	LeftInput_Pressed = true;
}

void APlayerCharacter::Input_RightStart(const FInputActionValue& Value)
{
	RightInput_Pressed = true;
}

void APlayerCharacter::Input_JumpStart(const FInputActionValue& Value)
{
	JumpInput_Pressed = true;
}

void APlayerCharacter::Input_Jump(const FInputActionValue& Value)
{
	JumpInput_Active = true;
}

void APlayerCharacter::Input_JumpCancel(const FInputActionValue& Value)
{
	JumpInput_Released = true;
}

void APlayerCharacter::Input_SpeedUp(const FInputActionValue& Value)
{
	SpeedInput_Active = true;
}

void APlayerCharacter::Input_SpeedUpStart(const FInputActionValue& Value)
{
	SpeedInput_Pressed = true;
}

void APlayerCharacter::Input_SpeedUpCancel(const FInputActionValue& Value)
{
	SpeedInput_Released = true;
}

void APlayerCharacter::Input_SlowDownStart(const FInputActionValue& Value)
{
	SlowInput_Pressed = true;
}

void APlayerCharacter::Input_SlowDown(const FInputActionValue& Value)
{
	SlowInput_Active = true;
}

void APlayerCharacter::Input_SlowDownCancel(const FInputActionValue& Value)
{
	SlowInput_Released = true;
}

void APlayerCharacter::Input_ShootLeft(const FInputActionValue& Value)
{
	ShootLeftInput_Active = true;
}

void APlayerCharacter::Input_ShootRight(const FInputActionValue& Value)
{
	ShootRightInput_Active = true;
}

void APlayerCharacter::Input_ShootUp(const FInputActionValue& Value)
{
	ShootUpInput_Active = true;
}

void APlayerCharacter::Input_ShootForward(const FInputActionValue& Value)
{
	ShootForwardInput_Active = true;
}

void APlayerCharacter::Input_ShootLeftStart(const FInputActionValue& Value)
{
	ShootLeftInput_Pressed = true;
}

void APlayerCharacter::Input_ShootRightStart(const FInputActionValue& Value)
{
	ShootRightInput_Pressed = true;
}

void APlayerCharacter::Input_ShootUpStart(const FInputActionValue& Value)
{
	ShootUpInput_Pressed = true;
}

void APlayerCharacter::Input_ShootForwardStart(const FInputActionValue& Value)
{
	ShootForwardInput_Pressed = true;
}

void APlayerCharacter::Shoot(EPlayerProjectileDirection direction)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		FVector shootPos = GetActorLocation();
		FRotator defaultRotation = FRotator();


		switch (direction)
		{
		case EPlayerProjectileDirection::Left:
			break;
		case EPlayerProjectileDirection::Right:
			break;
		case EPlayerProjectileDirection::Up:
			break;
		case EPlayerProjectileDirection::Forward:
			break;
		}

		// Spawn the projectile at the muzzle.
		APlayerProjectile* Projectile = World->SpawnActor<APlayerProjectile>(ProjectileClass, shootPos, defaultRotation, SpawnParams);
		if (Projectile)
		{
			// Set the projectile's initial trajectory.
			FVector LaunchDirection = FVector();
			
			switch (direction)
			{
			case EPlayerProjectileDirection::Left:
				LaunchDirection = FVector(0, -1, 0);
				break;
			case EPlayerProjectileDirection::Right:
				LaunchDirection = FVector(0, 1, 0);
				break;
			case EPlayerProjectileDirection::Up:
				LaunchDirection = FVector(0, 0, 1);
				break;
			case EPlayerProjectileDirection::Forward:
				LaunchDirection = FVector(1, 0, 0);
				break;
			}

			Projectile->FireInDirection(LaunchDirection);
		}
	}
}

float APlayerCharacter::GetCurrentRunSpeed()
{
	switch (CurrentSpeedState)
	{
	case EPlayerSpeedState::Slow:
		return SlowRunSpeed;
	case EPlayerSpeedState::Fast:
		return FastRunSpeed;
	default:
		return DefaultRunSpeed;
	}
}



void APlayerCharacter::ClearInputValues()
{
	JumpInput_Pressed = false;
	JumpInput_Released = false;
	JumpInput_Active = false;

	SpeedInput_Pressed = false;
	SpeedInput_Released = false;
	SpeedInput_Active = false;

	SlowInput_Pressed = false;
	SlowInput_Released = false;
	SlowInput_Active = false;

	LeftInput_Pressed = false;
	RightInput_Pressed = false;

	ShootLeftInput_Active = false;
	ShootRightInput_Active = false;
	ShootUpInput_Active = false;
	ShootForwardInput_Active = false;

	ShootLeftInput_Pressed = false;
	ShootRightInput_Pressed = false;
	ShootUpInput_Pressed = false;
	ShootForwardInput_Pressed = false;
}



EPlayerSpeedState APlayerCharacter::GetCurrentSpeedState()
{
	return EPlayerSpeedState();
}

void APlayerCharacter::SetSpeedState(EPlayerSpeedState newState)
{
	CurrentSpeedState = newState;
}




void APlayerCharacter::Debug_PrintInputValues()
{
	if (JumpInput_Active)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Jump Active."));
	}
	if (JumpInput_Released)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Jump Released."));
	}
	if (JumpInput_Pressed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Jump Pressed."));
	}

	if (SpeedInput_Active)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Speed Active."));
	}
	if (SpeedInput_Released)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Speed Released."));
	}
	if (SpeedInput_Pressed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Speed Pressed."));
	}

	if (SlowInput_Active)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Slow Active."));
	}
	if (SlowInput_Released)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Slow Released."));
	}
	if (SlowInput_Pressed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Slow Pressed."));
	}

	if (LeftInput_Pressed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Left Pressed."));
	}

	if (RightInput_Pressed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Right Pressed."));
	}
}