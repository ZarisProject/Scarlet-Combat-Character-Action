// Fill out your copyright notice in the Description page of Project Settings.

#include "SC_CharacterAction.h"

#include "Animation/AnimMontage.h"

#include "SC_ComboInputNotify.h"

// Sets default values for this component's properties
USC_CharacterAction::USC_CharacterAction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USC_CharacterAction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every tick, handles PlayerInputBuffer and InputRequestBuffer
void USC_CharacterAction::ServeInput()
{
}


// Called every frame
void USC_CharacterAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Provide player input to the Character Action component
void USC_CharacterAction::Input(const FName& Input, int32 Complexity)
{
}

// Called by Combo Transition Notifies, triggers a transition to the next move, based on Combo Key and Current Move
void USC_CharacterAction::TriggerComboMove(const FName& ComboKey)
{
}

// Called by Combo Input Notifies, adds an entry to InputRequestBuffer
void USC_CharacterAction::RequestInput(const FName& Input, USC_ComboInputNotify* RequestorNotify)
{
}

// Wether the specified combo key is valid or not
bool USC_CharacterAction::IsComboKeyValid(const FName& ComboKey, const FName& Move)
{
	return false;
}

