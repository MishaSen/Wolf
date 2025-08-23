// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WolfCharacter.h"

// Sets default values
AWolfCharacter::AWolfCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ASC = CreateDefaultSubobject<UWolfAbilitySystemComponent>(TEXT("Ability System Component"));
	AtSet = CreateDefaultSubobject<UWolfAttributeSet>(TEXT("Attribute Set"));
}

// Called when the game starts or when spawned
void AWolfCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ASC && DefaultAttributes)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		if (FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
			SpecHandle.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
		}
	}

	if (HasAuthority() && ASC)
	{
		for (TSubclassOf<UGameplayAbility>& AbilityClass : DefaultAbilities)
		{
			ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, INDEX_NONE, this));
		}
	}
}

// Called every frame
void AWolfCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWolfCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AWolfCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}
