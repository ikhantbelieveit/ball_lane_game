// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestMainMenu2.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BALLGAMEPROJECT_API UTestMainMenu2 : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable, Category="MyFunctions")
    void OnStartButtonClicked();

protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* StartButton;

    
};
