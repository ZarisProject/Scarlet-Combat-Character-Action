// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SC_CharacterActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USC_CharacterActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SCARLETCOMBAT_CHARACTERACTION_API ISC_CharacterActionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Implement this method in your character class. It must return your character action component
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ScarletCombat|CharacterAction|Character")
	class USC_CharacterAction* GetCharacterActionComponent();
	virtual class USC_CharacterAction* GetCharacterActionComponent_Implementation() { return nullptr; }

	// Implement this method in your character class. It is supposed to play the specify animation montage on your character mesh
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ScarletCombat|CharacterAction|Character")
	void PlayMoveAnimation(class UAnimMontage* Animation);
	virtual void PlayMoveAnimation_Implementation(class UAnimMontage* Animation) {}
};
