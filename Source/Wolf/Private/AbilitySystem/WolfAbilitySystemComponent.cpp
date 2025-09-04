// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf/Public/AbilitySystem/WolfAbilitySystemComponent.h"

void UWolfAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant,
                                                        TMap<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle>&
                                                        OutHandles)
{
	if (!GetOwner()) return;
	for (auto AbilityClass : AbilitiesToGrant)
	{
		FGameplayAbilitySpecHandle NewHandle = GiveAbility(FGameplayAbilitySpec(
			AbilityClass,
			1,
			0,
			GetOwner()));
		if (NewHandle.IsValid())
		{
			OutHandles.Add(AbilityClass, NewHandle);
		}
	}
}
