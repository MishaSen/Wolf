// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WolfCharacter.h"

#include "Presage/PresageAbilityRequest.h"
#include "Presage/PresageSubsystem.h"

// Sets default values
AWolfCharacter::AWolfCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ASC = CreateDefaultSubobject<UWolfAbilitySystemComponent>(TEXT("Ability System Component"));
	AtSet = CreateDefaultSubobject<UWolfAttributeSet>(TEXT("Attribute Set"));

	/* Multiplayer would need to replicate ASC. Replication Mode either Mixed or Full.
	 * 
	 * ASC = CreateDefaultSubobject<UWolfAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	 * ASC->SetIsReplicated(true);
	 * ASC->SetReplicationMode(EGameplayEffect ReplicationMode::Mixed);
	 */
}

void AWolfCharacter::QueueAbility(FGameplayAbilitySpecHandle SpecHandle, float ScheduledTime)
{
	if (!ASC) return;

	// Get ability spec from handle
	const FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromHandle(SpecHandle);
	if (!Spec || !Spec->Ability)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Ability or Spec Handle"));
		return;
	}
	const FPresageAbilityRequest Request(ASC, SpecHandle, ScheduledTime);

	// Send Request to PresageSubsystem
	if (UWorld* World = GetWorld())
	{
		if (UPresageSubsystem* Presage = UPresageSubsystem::Get(World))
		{
			Presage->QueueAbilityRequest(Request);
			UE_LOG(LogTemp, Log, TEXT("Queued ability at %s at time %f"),
				*Spec->Ability.GetClass()->GetName(),
				ScheduledTime)
		}
	}
}

// Called when the game starts or when spawned
void AWolfCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ASC && DefaultAttributes)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
		}
	}

	if (HasAuthority() && ASC)
	{
		for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
		{
			ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, 0, this));
		}
	}

	/* Input Binding (maybe future use)
	 *
	 * FGameplayAbilityInputBinds(
	 * "Confirm",
	 * "Cancel",
	 * "EAbilityInputID",
	 * static_cast<int32>(EAbilityInputID::Confirm),
	 * static_cast<int32(EAbilityInputID::Cancel)));
	 */
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
