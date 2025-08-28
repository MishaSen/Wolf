// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PresageManager.generated.h"

class UGameplayAbility;
struct FGameplayAbilitySpecHandle;
class UAbilitySystemComponent;
struct FActorState;
struct FPresageAbilityRequest;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WOLF_API UPresageManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPresageManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Presage")
	TArray<FActorState> OriginalCharacterStates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Presage", meta=(ClampMin = "0.0", UIMin = "0.0"))
	float FlowTime = 3.f;

	UPROPERTY()
	TArray<FPresageAbilityRequest> AbilityQueue;

	FTimerHandle FlowTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Presage")
	void CaptureCharacterStates();

	UFUNCTION(BlueprintCallable, Category = "Presage")
	void RevertCharacterStates();

	UFUNCTION(BlueprintCallable, Category = "Presage")
	void StartLoop();

	UFUNCTION(BlueprintCallable, Category = "Presage")
	void StopLoop();

	UFUNCTION(BlueprintCallable, Category = "Presage")
	void PauseLoop();

	UFUNCTION(BlueprintCallable, Category = "Presage")
	void ResumeLoop();

	UFUNCTION(BlueprintCallable, Category = "Presage")
	void OnFlowTimerTick();

	UFUNCTION(BlueprintCallable, Category = "Presage")
	void QueueAbilityRequest(UAbilitySystemComponent* ASC, FGameplayAbilitySpecHandle SpecHandle, float DesiredTime, TSubclassOf<UGameplayAbility> AbilityClass);
};
