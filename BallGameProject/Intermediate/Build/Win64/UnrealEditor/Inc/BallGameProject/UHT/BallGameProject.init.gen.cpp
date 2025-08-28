// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBallGameProject_init() {}
	BALLGAMEPROJECT_API UFunction* Z_Construct_UDelegateFunction_BallGameProject_OnPlayerEnter__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_BallGameProject;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_BallGameProject()
	{
		if (!Z_Registration_Info_UPackage__Script_BallGameProject.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_BallGameProject_OnPlayerEnter__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/BallGameProject",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x563712FB,
				0x9A04799C,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_BallGameProject.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_BallGameProject.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_BallGameProject(Z_Construct_UPackage__Script_BallGameProject, TEXT("/Script/BallGameProject"), Z_Registration_Info_UPackage__Script_BallGameProject, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x563712FB, 0x9A04799C));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
