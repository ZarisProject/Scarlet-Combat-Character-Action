// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SC_ComboTransitionNotify.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETCOMBAT_CHARACTERACTION_API USC_ComboTransitionNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	// If a value different to "None" is specified, then this transition point will trigger even with no inputs from the player
	// And will use the DefaultComboKey
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FName DefaultComboKey;

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
		const FAnimNotifyEventReference& EventReference) override;
};


UCLASS()
class SCARLETCOMBAT_CHARACTERACTION_API USC_ComboTransitionStateNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:

	// If a value different to "None" is specified, then this transition point will trigger even with no inputs from the player
	// And will use the DefaultComboKey
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FName DefaultComboKey;

protected:
	class USC_CharacterAction* Cached_CharacterAction = nullptr;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};