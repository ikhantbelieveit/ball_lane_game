// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class BALLGAMEPROJECT_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Make BlueprintCallable for testing
	UFUNCTION(BlueprintCallable)
	void ShowMainMenu();

	UFUNCTION(BlueprintCallable)
	void HideMainMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MainMenuClass;

	// Keep a pointer to be able to hide it
	UPROPERTY()
	UUserWidget* MainMenu;
};
