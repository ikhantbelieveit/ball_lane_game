// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BallGameProject/EPlayerSpeedState.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeEPlayerSpeedState() {}

// ********** Begin Cross Module References ********************************************************
BALLGAMEPROJECT_API UEnum* Z_Construct_UEnum_BallGameProject_EPlayerSpeedState();
UPackage* Z_Construct_UPackage__Script_BallGameProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EPlayerSpeedState *********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EPlayerSpeedState;
static UEnum* EPlayerSpeedState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EPlayerSpeedState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EPlayerSpeedState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_BallGameProject_EPlayerSpeedState, (UObject*)Z_Construct_UPackage__Script_BallGameProject(), TEXT("EPlayerSpeedState"));
	}
	return Z_Registration_Info_UEnum_EPlayerSpeedState.OuterSingleton;
}
template<> BALLGAMEPROJECT_API UEnum* StaticEnum<EPlayerSpeedState>()
{
	return EPlayerSpeedState_StaticEnum();
}
struct Z_Construct_UEnum_BallGameProject_EPlayerSpeedState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Custom enum to demonstrate how to expose enums to Blueprints.\n */" },
#endif
		{ "Default.DisplayName", "Default" },
		{ "Default.Name", "EPlayerSpeedState::Default" },
		{ "Fast.DisplayName", "Fast" },
		{ "Fast.Name", "EPlayerSpeedState::Fast" },
		{ "ModuleRelativePath", "EPlayerSpeedState.h" },
		{ "Slow.DisplayName", "Slow" },
		{ "Slow.Name", "EPlayerSpeedState::Slow" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Custom enum to demonstrate how to expose enums to Blueprints." },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EPlayerSpeedState::Default", (int64)EPlayerSpeedState::Default },
		{ "EPlayerSpeedState::Fast", (int64)EPlayerSpeedState::Fast },
		{ "EPlayerSpeedState::Slow", (int64)EPlayerSpeedState::Slow },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_BallGameProject_EPlayerSpeedState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_BallGameProject,
	nullptr,
	"EPlayerSpeedState",
	"EPlayerSpeedState",
	Z_Construct_UEnum_BallGameProject_EPlayerSpeedState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_BallGameProject_EPlayerSpeedState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_BallGameProject_EPlayerSpeedState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_BallGameProject_EPlayerSpeedState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_BallGameProject_EPlayerSpeedState()
{
	if (!Z_Registration_Info_UEnum_EPlayerSpeedState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EPlayerSpeedState.InnerSingleton, Z_Construct_UEnum_BallGameProject_EPlayerSpeedState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EPlayerSpeedState.InnerSingleton;
}
// ********** End Enum EPlayerSpeedState ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_EPlayerSpeedState_h__Script_BallGameProject_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EPlayerSpeedState_StaticEnum, TEXT("EPlayerSpeedState"), &Z_Registration_Info_UEnum_EPlayerSpeedState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 72051231U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_EPlayerSpeedState_h__Script_BallGameProject_1732965469(TEXT("/Script/BallGameProject"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_EPlayerSpeedState_h__Script_BallGameProject_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Joseph_Documents_GitHub_ball_lane_game_BallGameProject_Source_BallGameProject_EPlayerSpeedState_h__Script_BallGameProject_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
