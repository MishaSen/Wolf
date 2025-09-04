// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WolfAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class WOLF_API UWolfAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant,
	                           TMap<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle>& OutHandles);
};
