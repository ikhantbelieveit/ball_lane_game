// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PlayerCharacter.h"

#ifdef BALLGAMEPROJECT_PlayerCharacter_generated_h
#error "PlayerCharacter.generated.h already included, missing '#pragma once' in PlayerCharacter.h"
#endif
#define BALLGAMEPROJECT_PlayerCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class APlayerCharacter *********************************************************
BALLGAMEPROJECT_API UClass* Z_Construct_UClass_APlayerCharacter_NoRegister();

#define FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_PlayerCharacter_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPlayerCharacter(); \
	friend struct Z_Construct_UClass_APlayerCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend BALLGAMEPROJECT_API UClass* Z_Construct_UClass_APlayerCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(APlayerCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/BallGameProject"), Z_Construct_UClass_APlayerCharacter_NoRegister) \
	DECLARE_SERIALIZER(APlayerCharacter)


#define FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_PlayerCharacter_h_27_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	APlayerCharacter(APlayerCharacter&&) = delete; \
	APlayerCharacter(const APlayerCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APlayerCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APlayerCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APlayerCharacter) \
	NO_API virtual ~APlayerCharacter();


#define FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_PlayerCharacter_h_24_PROLOG
#define FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_PlayerCharacter_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_PlayerCharacter_h_27_INCLASS_NO_PURE_DECLS \
	FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_PlayerCharacter_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APlayerCharacter;

// ********** End Class APlayerCharacter ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_PlayerCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
