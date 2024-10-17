// Copyright Derrick Gennrich

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy:uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy:uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UENUM(BlueprintType)
enum class EEffectDurationType:uint8
{
	Instant,
	Duration,
	Infinite
};

USTRUCT(BlueprintType)
struct FGameplayEffectLayer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	EEffectDurationType EffectDurationType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	float EffectLevel = 1.0f;
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied Effects")
	TArray<FGameplayEffectLayer> GameplayEffects;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, int32 GameplayEffectIndex);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor, int32 GameplayEffectIndex);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor, int32 GameplayEffectIndex);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AppliedEffects")
	bool bDestroyOnEffectRemoval = false;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
};
