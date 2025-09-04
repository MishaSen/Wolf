// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetManager/WolfAssetManager.h"

#include "AbilitySystem/WolfGameplayTags.h"
#include "AbilitySystemGlobals.h"

UWolfAssetManager& UWolfAssetManager::Get()
{
	check(GEngine)
	if (UWolfAssetManager* AssetManager = Cast<UWolfAssetManager>(GEngine->AssetManager))
	{
		return *AssetManager;
	}

	UE_LOG(LogTemp, Fatal, TEXT(
		       "Error: Asset Manager not found. You had ONE job... "
		       "Set 'AssetManagerClassName' in DefaultEngine.ini to '/Script/Wolf.WolfAssetManager'."));
	return *NewObject<UWolfAssetManager>();
}

void UWolfAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FWolfGameplayTags::InitializeNativeGameplayTags();

	// Initializes global data required for using GAS' targeting features (e.g., FGameplayAbilityTargetData).
	UAbilitySystemGlobals::Get().InitGlobalData();
}