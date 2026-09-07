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
};