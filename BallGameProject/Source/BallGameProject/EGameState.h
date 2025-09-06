#pragma once

#include "CoreMinimal.h"
#include "EGameState.generated.h"

/**
 * Custom enum to demonstrate how to expose enums to Blueprints.
 */
UENUM(BlueprintType)
enum class EGameState : uint8
{
    Active UMETA(DisplayName = "Active"),       //in gameplay
    Win UMETA(DisplayName = "Win"),             //in gameplay - win
    Lose UMETA(DisplayName = "Lose"),           //in gameplay - lose
    Dormant UMETA(DisplayName = "Dormant")      //out of gameplay (in main menu)
};