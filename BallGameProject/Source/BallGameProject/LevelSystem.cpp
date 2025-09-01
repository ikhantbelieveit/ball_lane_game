// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "LevelSystem.h"

// Sets default values
ALevelSystem::ALevelSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALevelSystem::InitialiseOnPlay()
{
	if (Initialised)
	{
		return;
	}

	//get player ref
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerCharacter* PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));

	if (PlayerRef)
	{
		Player = PlayerRef;
	}

	SetGameState(EGameState::Dormant);

	Initialised = true;

	// Get all actors in the level
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

	for (AActor* Actor : AllActors)
	{
		if (!Actor) continue;

		// Find death collision component
		if (UDeathCollisionComponent* DeathComp = Actor->FindComponentByClass<UDeathCollisionComponent>())
		{
			// Bind this component’s event to our function
			DeathComp->OnPlayerEnter.AddDynamic(this, &ALevelSystem::KillPlayer);

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("registered kill event to level system."));
		}
	}
}

// Called when the game starts or when spawned
void ALevelSystem::BeginPlay()
{
	Super::BeginPlay();
	InitialiseOnPlay();
	
	
}

// Called every frame
void ALevelSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSystem::KillPlayer()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	SetGameState(EGameState::Lose);

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (controller)
	{
		// Set input to UI only, so player can still use menus
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		//InputMode.SetWidgetToFocus(MyWidget->TakeWidget()); // <-- replace with your UUserWidget*
		controller->SetInputMode(InputMode);

		controller->bShowMouseCursor = true; // Make cursor visible
	}

	//Widget->SetTickableWhenPaused(true);
}

void ALevelSystem::SetGameState(EGameState newState)
{
	CurrentState = newState;

	if (Player)
	{
		Player->UpdateOnGameStateChange(newState);
	}
}

EGameState ALevelSystem::GetGameState()
{
	return CurrentState;
}

void ALevelSystem::StartLevel()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("start."));

	SetGameState(EGameState::Active);
}
