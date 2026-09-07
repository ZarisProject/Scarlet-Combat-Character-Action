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

	// Whether this input window shall override results of previous yet untransitioned input windows
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool OverrideExistingKey = false;

public:

	// Serving input to the input notify
	// Returns the result of ADDITIONAL checks (if such are present)
	bool ServeInput(const FName& Input);
};
