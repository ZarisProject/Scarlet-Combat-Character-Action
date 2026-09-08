// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SC_ComboInputNotify.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETCOMBAT_CHARACTERACTION_API USC_ComboInputNotify : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:

	// List of inputs that sattisfy the input request
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TSet<FName> Inputs;

	// Combo Key used to look up the next Combo Branch of the current move in Move Set Library
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FName ComboKey;

	// Used to sort same input requests from different notifies, the bigger the value - the higher the priority
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int32 Priority = 0;

	// Whether this input window shall override results of previous yet untransitioned input windows
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool OverrideExistingKey = false;

protected:

	// Runtime context data
	float Duration = 0.f;
	float CurrentTime = 0.f;

	// Cache
	USkeletalMeshComponent* Cached_MeshComp;
	UAnimSequenceBase* Cached_Animation;
	AActor* Cached_OwnerActor;
	class USC_CharacterAction* Cached_CharacterAction;

public:

	// Serving input to the input notify
	// Returns the result of ADDITIONAL checks (if such are present)
	bool ServeInput(const FName& Input);


	virtual void NotifyBegin(	USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
								float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyTick(	USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
								float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(		USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
								const FAnimNotifyEventReference& EventReference) override;


	// Returns notify's duration in seconds (works correctly after NotifyBegin)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ScarletCombat|CharacterAction|ComboInputNotify")
	float GetDuration() const { return Duration; }

	// Returns time since last NotifyBegin in seconds
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ScarletCombat|CharacterAction|ComboInputNotify")
	float GeCurrentTime() const { return CurrentTime; }


	// Override this function to add additional conditions
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent, Category = "ScarletCombat|CharacterAction|ComboInputNotify")
	bool CheckAdditionalConditions(	USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
									AActor* OwnerActor, class USC_CharacterAction* CharacterAction,
									const FName& Input) const;

	virtual bool CheckAdditionalConditions_Implementation(
		USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		AActor* OwnerActor, class USC_CharacterAction* CharacterAction, const FName& Input) const
	{
		return true;
	}
};
