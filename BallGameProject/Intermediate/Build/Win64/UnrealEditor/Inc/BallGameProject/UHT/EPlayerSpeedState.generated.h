// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "EPlayerSpeedState.h"

#ifdef BALLGAMEPROJECT_EPlayerSpeedState_generated_h
#error "EPlayerSpeedState.generated.h already included, missing '#pragma once' in EPlayerSpeedState.h"
#endif
#define BALLGAMEPROJECT_EPlayerSpeedState_generated_h

#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_EPlayerSpeedState_h

// ********** Begin Enum EPlayerSpeedState *********************************************************
#define FOREACH_ENUM_EPLAYERSPEEDSTATE(op) \
	op(EPlayerSpeedState::Default) \
	op(EPlayerSpeedState::Fast) \
	op(EPlayerSpeedState::Slow) 

enum class EPlayerSpeedState : uint8;
template<> struct TIsUEnumClass<EPlayerSpeedState> { enum { Value = true }; };
template<> BALLGAMEPROJECT_API UEnum* StaticEnum<EPlayerSpeedState>();
// ********** End Enum EPlayerSpeedState ***********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
