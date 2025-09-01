// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMainMenu2.h"
#include "Components/Button.h"

void UTestMainMenu2::NativeConstruct()
{
    Super::NativeConstruct();

    /*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("HELLO."));


    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UTestMainMenu2::OnStartButtonClicked);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("WE DA BEST."));
    }*/
}

void UTestMainMenu2::OnStartButtonClicked()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("PRESSED START."));
}