// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	check(CameraComponent != nullptr);

	// Attach the camera component to our capsule component.
	CameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	SetRunSpeed(DefaultRunSpeed);
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

	//if less than max speed
	if (GetVelocity().X <= MaxRunSpeed)
	{
		//build up speed to max
		AddMovementInput(FVector(GetCurrentRunSpeed(), 0.0f, 0.0f));
	}

	if (JumpInput_Triggered)
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

	ClearInputValues();
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
		EnhancedInputComponent->BindAction(Input_LeftAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Left);
	}
	//right
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_RightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Right);
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
	//slow down
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_SlowDownAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_SlowDown);
	}
	//shoot left
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootLeftAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_ShootLeft);
	}
	//shoot right
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_ShootRight);
	}
	//shoot up
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootUpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_ShootUp);
	}
	//shoot forward
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_ShootForwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_ShootForward);
	}


}

void APlayerCharacter::Input_Left(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Left."));
}

void APlayerCharacter::Input_Right(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Right."));
}

void APlayerCharacter::Input_JumpStart(const FInputActionValue& Value)
{
	JumpInput_Triggered = true;
	JumpInput_Pressed = true;
}

void APlayerCharacter::Input_Jump(const FInputActionValue& Value)
{
	JumpInput_Triggered = true;
}

void APlayerCharacter::Input_JumpCancel(const FInputActionValue& Value)
{
	bool lastInputTrigger = JumpInput_Triggered;

	JumpInput_Triggered = false;
	JumpInput_Released = true;
}

void APlayerCharacter::Input_SpeedUp(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Speed up."));

	SetRunSpeed(DefaultRunSpeed + 200);
}

void APlayerCharacter::Input_SlowDown(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Slow down."));

	SetRunSpeed(DefaultRunSpeed - 200);
}

void APlayerCharacter::Input_ShootLeft(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Shoot left."));
}

void APlayerCharacter::Input_ShootRight(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Shoot right."));
}

void APlayerCharacter::Input_ShootUp(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Shoot up."));
}

void APlayerCharacter::Input_ShootForward(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Shoot forward."));
}

float APlayerCharacter::GetCurrentRunSpeed()
{
	return CurrentRunSpeed;
}

void APlayerCharacter::SetRunSpeed(float newSpeed)
{
	CurrentRunSpeed = newSpeed;
}

void APlayerCharacter::ClearInputValues()
{
	JumpInput_Pressed = false;
	JumpInput_Released = false;
	JumpInput_Triggered = false;
}
