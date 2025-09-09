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

void UWolfAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& Tag)
{
	if (!Tag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (AbilitySpec.IsActive())
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed,
				                      AbilitySpec.Handle,
				                      AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
		}
	}
}

void UWolfAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& Tag)
{
	if (!Tag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tag) && AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased,
								  AbilitySpec.Handle,
								  AbilitySpec.ActivationInfo.GetActivationPredictionKey());
		}
	}
}

void UWolfAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& Tag)
{
	if (!Tag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}
