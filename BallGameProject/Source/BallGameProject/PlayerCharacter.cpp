// Fill out your copyright notice in the Description page of Project Settings.

#include "LifespanDelegateComponent.h"
#include "ScrollWithPlayerComponent.h"
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

	SetJumpState(EPlayerJumpState::Grounded);

	SetLane(2);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	JumpedThisFrame = false;

	UpdateLaneScroll();

	UpdateSpeedFromInput();
	UpdateLaneFromInput();

	UpdateJumpState(DeltaTime);
	UpdateJumpFromInput();

	UpdateShootValues(DeltaTime);
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
		Shoot(EPlayerProjectileDirection::Left, true, false);
		return;
	}
	if (ShootRightInput_Pressed)
	{
		Shoot(EPlayerProjectileDirection::Right, true, false);
		return;
	}
	if (ShootUpInput_Pressed)
	{
		Shoot(EPlayerProjectileDirection::Up, true, false);
		return;
	}
	if (ShootForwardInput_Pressed)
	{
		Shoot(EPlayerProjectileDirection::Forward, true, false);
		return;
	}

	if (ShootLeftInput_Active)
	{
		Shoot(EPlayerProjectileDirection::Left, false, true);
		return;
	}
	if (ShootRightInput_Active)
	{
		Shoot(EPlayerProjectileDirection::Right, false, true);
		return;
	}
	if (ShootUpInput_Active)
	{
		Shoot(EPlayerProjectileDirection::Up, false, true);
		return;
	}
	if (ShootForwardInput_Active)
	{
		Shoot(EPlayerProjectileDirection::Forward, false, true);
		return;
	}

	
}

void APlayerCharacter::UpdateLaneFromInput()
{
	if (LeftInput_Pressed)
	{
		MoveLane_Left();
	}

	if (RightInput_Pressed)
	{
		MoveLane_Right();
	}
}

bool APlayerCharacter::MoveLane_Left()
{
	return (SetLane(CurrentLaneIndex - 1));
}

bool APlayerCharacter::MoveLane_Right()
{
	return (SetLane(CurrentLaneIndex + 1));
}

bool APlayerCharacter::SetLane(int laneIndex)
{
	if (!CanPlayerOccupyLane(laneIndex))
	{
		return false;
	}

	bool moveLeft = false;
	bool moveRight = false;

	if (laneIndex == CurrentLaneIndex - 1)
	{
		moveLeft = true;
	}

	if (laneIndex == CurrentLaneIndex + 1)
	{
		moveRight = true;
	}
	
	CurrentLaneIndex = laneIndex;

	if (moveLeft)
	{
		FVector offset = FVector(0, -LaneDistance, 0);
		AddActorWorldOffset(offset);

		CameraComponent->SetWorldLocation(FVector(
			CameraComponent->GetComponentLocation().X,
			0,
			CameraComponent->GetComponentLocation().Z));
	}

	if (moveRight)
	{
		FVector offset = FVector(0, LaneDistance, 0);
		AddActorWorldOffset(offset);


		CameraComponent->SetWorldLocation(FVector(
			CameraComponent->GetComponentLocation().X,
			0,
			CameraComponent->GetComponentLocation().Z));
	}

	return true;
}

bool APlayerCharacter::CanPlayerOccupyLane(int laneIndex)
{
	//cancel if outside the 5 valid lanes
	if (laneIndex < 0 || laneIndex > 4)
	{
		return false;
	}

	return true;
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
	if (JumpInput_Pressed)
	{
		if (CurrentJumpState == EPlayerJumpState::Grounded)
		{
			bPressedJump = true;
			SetJumpState(EPlayerJumpState::Rise);
			JumpedThisFrame = true;
		}
	}

	if (JumpInput_Released)
	{
		bPressedJump = false;
		SetJumpState(EPlayerJumpState::Fall);
	}
}

void APlayerCharacter::UpdateShootValues(float DeltaTime)
{
	if (TimeSinceShoot_Left < ShootHoldInputDelay)
	{
		TimeSinceShoot_Left += DeltaTime;
	}
	if (TimeSinceShoot_Right < ShootHoldInputDelay)
	{
		TimeSinceShoot_Right += DeltaTime;
	}
	if (TimeSinceShoot_Up < ShootHoldInputDelay)
	{
		TimeSinceShoot_Up += DeltaTime;
	}
	if (TimeSinceShoot_Forward < ShootHoldInputDelay)
	{
		TimeSinceShoot_Forward += DeltaTime;
	}
}

void APlayerCharacter::UpdateLaneScroll()
{
	//scroll behaviour
	AddMovementInput(FVector(GetCurrentRunSpeed(), 0.0f, 0.0f));
}

void APlayerCharacter::UpdateJumpState(float DeltaTime)
{
	bool apexToFall = false;

	if (TimeSinceJumpStateChange < JumpApexHangTime)
	{
		TimeSinceJumpStateChange += DeltaTime;
	}
	else
	{
		apexToFall = true;
	}

	switch (CurrentJumpState)
	{
	case EPlayerJumpState::Rise:
		if (!JumpedThisFrame)
		{
			if (GetVelocity().Z <= 0.01f)
			{
				SetJumpState(EPlayerJumpState::Apex);
			}
		}
		break;
	case EPlayerJumpState::Fall:
		if (GetVelocity().Z == 0.0f)
		{
			SetJumpState(EPlayerJumpState::Grounded);
		}
		break;
	case EPlayerJumpState::Apex:
		if (apexToFall)
		{
			SetJumpState(EPlayerJumpState::Fall);
		}
		break;
	}
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

void APlayerCharacter::Shoot(EPlayerProjectileDirection direction, bool bypassDelay, bool holdNotTap)
{
	if (!CanShootInDirection(direction, bypassDelay, holdNotTap))
	{
		return;
	}

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
			//GetPointer
			Projectile->InitialiseBeforeShoot(direction);
			//Projectile->LifespanComponent->OnLifetimeEnded.BindUObject(this, &)

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
				UScrollWithPlayerComponent* scrollComp = (UScrollWithPlayerComponent*)Projectile->GetComponentByClass(UScrollWithPlayerComponent::StaticClass());
				scrollComp->Enabled = false;
				UProjectileMovementComponent* projMoveComp = (UProjectileMovementComponent*)Projectile->GetComponentByClass(UProjectileMovementComponent::StaticClass());
				projMoveComp->InitialSpeed = 2000.0f;
				projMoveComp->MaxSpeed = 2000.0f;
				break;
			}

			Projectile->FireInDirection(LaunchDirection);

			switch (direction)
			{
			case EPlayerProjectileDirection::Left:
				TimeSinceShoot_Left = 0;
				break;
			case EPlayerProjectileDirection::Right:
				TimeSinceShoot_Right = 0;
				break;
			case EPlayerProjectileDirection::Up:
				TimeSinceShoot_Up = 0;
				break;
			case EPlayerProjectileDirection::Forward:
				TimeSinceShoot_Forward = 0;
				break;
			}
		}
	}
}

bool APlayerCharacter::CanShootInDirection(EPlayerProjectileDirection direction, bool bypassDelay, bool holdNotTap)
{
	if (!bypassDelay)
	{
		if (DelayPreventsShootInDirection(direction))
		{
			return false;
		}
	}

	if (holdNotTap)
	{
		if (ExceededProjCountForDirection(direction))
		{
			return false;
		}
	}

	return true;
}

bool APlayerCharacter::DelayPreventsShootInDirection(EPlayerProjectileDirection direction)
{
	switch (direction)
	{
	case EPlayerProjectileDirection::Forward:
		return TimeSinceShoot_Forward < ShootHoldInputDelay;
		break;
	case EPlayerProjectileDirection::Up:
		return TimeSinceShoot_Up < ShootHoldInputDelay;
		break;
	case EPlayerProjectileDirection::Left:
		return TimeSinceShoot_Left < ShootHoldInputDelay;
		break;
	case EPlayerProjectileDirection::Right:
		return TimeSinceShoot_Right < ShootHoldInputDelay;
		break;
	}

	return false;
}

bool APlayerCharacter::ExceededProjCountForDirection(EPlayerProjectileDirection direction)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return true;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerProjectile::StaticClass(), FoundActors);

	int activeProjectiles_Left = 0;
	int activeProjectiles_Right = 0;
	int activeProjectiles_Up = 0;
	int activeProjectiles_Forward = 0;

	for (AActor* Actor : FoundActors)
	{
		APlayerProjectile* proj = Cast<APlayerProjectile>(Actor);
		if (proj)
		{
			switch (proj->ShootInDirection)
			{
			case EPlayerProjectileDirection::Left:
				activeProjectiles_Left++;
				break;
			case EPlayerProjectileDirection::Right:
				activeProjectiles_Right++;
				break;
			case EPlayerProjectileDirection::Up:
				activeProjectiles_Up++;
				break;
			case EPlayerProjectileDirection::Forward:
				activeProjectiles_Forward++;
				break;
			}
		}
	}

	switch (direction)
	{
	case EPlayerProjectileDirection::Left:
		return activeProjectiles_Left >= HoldShoot_MaxProjectiles;
		break;
	case EPlayerProjectileDirection::Right:
		return activeProjectiles_Right >= HoldShoot_MaxProjectiles;
		break;
	case EPlayerProjectileDirection::Up:
		return activeProjectiles_Up >= HoldShoot_MaxProjectiles;
		break;
	case EPlayerProjectileDirection::Forward:
		return activeProjectiles_Forward >= HoldShoot_MaxProjectiles;
		break;
	}

	return false;
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


void APlayerCharacter::SetSpeedState(EPlayerSpeedState newState)
{
	CurrentSpeedState = newState;
}

void APlayerCharacter::SetJumpState(EPlayerJumpState newState)
{
	CurrentJumpState = newState;
	TimeSinceJumpStateChange = 0.0f;

	UCharacterMovementComponent* characterMovement = (UCharacterMovementComponent*)GetComponentByClass(UCharacterMovementComponent::StaticClass());

	switch (CurrentJumpState)
	{
	case EPlayerJumpState::Rise:
		characterMovement->GravityScale = JumpRiseGravity;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Rise."));
		break;
	case EPlayerJumpState::Apex:
		CancelVerticalSpeed();
		characterMovement->GravityScale = 0;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Apex."));
		break;
	case EPlayerJumpState::Fall:
		characterMovement->GravityScale = JumpFallGravity;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Fall."));
		break;
	case EPlayerJumpState::Grounded:
		characterMovement->GravityScale = JumpRiseGravity;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Grounded."));
		break;
	}
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

void APlayerCharacter::CancelVerticalSpeed()
{
	GetRootComponent()->ComponentVelocity = FVector(GetRootComponent()->ComponentVelocity.X, GetRootComponent()->ComponentVelocity.Y, 0);
}
