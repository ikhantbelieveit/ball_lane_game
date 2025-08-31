// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMyHUD::BeginPlay()
{
	Initialise();
	ShowMainMenu();
}

void AMyHUD::Initialise()
{
	// Make widget owned by our PlayerController
	APlayerController* PC = Cast<APlayerController>(GetOwner());

	if (PC)
	{
		MainMenu = CreateWidget<UUserWidget>(PC, MainMenuClass);

		MainMenu->AddToViewport();
	}
}

void AMyHUD::ShowMainMenu()
{
	if (MainMenu)
	{
		MainMenu->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMyHUD::HideMainMenu()
{
	if (MainMenu)
	{
		MainMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

