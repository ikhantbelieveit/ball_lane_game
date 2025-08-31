// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMainMenu2.h"
#include "Components/Button.h"

void UTestMainMenu2::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UTestMainMenu2::OnStartButtonClicked);
    }
}

void UTestMainMenu2::OnStartButtonClicked()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("PRESSED START."));
}