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

	// Position the camera slightly above the eyes.
	//CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	// Enable the pawn to control camera rotation.
	//CameraComponent->bUsePawnControlRotation = true;
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

	FVector lastPos = RootComponent->GetRelativeLocation();

	FVector newPos = FVector(lastPos.X + (GetCurrentRunSpeed() * DeltaTime), lastPos.Y, lastPos.Z);
	
	RootComponent->SetRelativeLocation(newPos);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("NEW POSITION IS " + RootComponent->GetRelativeLocation().ToString()));
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

void APlayerCharacter::Input_Jump(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Jump."));
}

void APlayerCharacter::Input_SpeedUp(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Speed up."));
}

void APlayerCharacter::Input_SlowDown(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Slow down."));
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
	return DefaultRunSpeed;
}