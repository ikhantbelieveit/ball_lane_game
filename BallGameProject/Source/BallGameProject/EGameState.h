#pragma once

#include "CoreMinimal.h"
#include "EGameState.generated.h"

/**
 * Custom enum to demonstrate how to expose enums to Blueprints.
 */
UENUM(BlueprintType)
enum class EGameState : uint8
{
    Active UMETA(DisplayName = "Active"),  //during gameplay
    Lose UMETA(DisplayName = "Lose"), //player dies
    Win UMETA(DisplayName = "Win"), //player reaches win condition
    Dormant UMETA(DisplayName = "Dormant"), //outside game (e.g. in menus)
};