// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/WolfInputConfig.h"

const UInputAction* UWolfInputConfig::FindAbilityInputActionForTag(const FGameplayTag& Tag,
                                                                   const bool bLogNotFound) const
{
	for (const FTaggedInputAction& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(Tag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT(
			       "Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"),
		       *Tag.ToString(),
		       *GetNameSafe(this));
	}

	return nullptr;
}
