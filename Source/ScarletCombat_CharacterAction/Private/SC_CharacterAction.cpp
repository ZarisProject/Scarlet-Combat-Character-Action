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
}


// Called when the game starts
void USC_CharacterAction::BeginPlay()
{
	Super::BeginPlay();
}

// Called every tick, handles PlayerInputBuffer and InputRequestBuffer
void USC_CharacterAction::ServeInput()
{
	for (auto& PlayerInput : PlayerInputBuffer)
	{
		auto* Found = InputRequestBuffer.Find(PlayerInput.Key);
		if (Found)
		{
			bool WasInputServed = false;

			auto Requestors = (*Found);
			for (auto& Requestor : Requestors)
				if (Requestor.Key->ServeInput(PlayerInput.Key))
				{
					WasInputServed = true;
					break;
				}

			if (WasInputServed)
				break;
		}
	}

	PlayerInputBuffer.Empty();
	InputRequestBuffer.Empty(InputRequestBuffer.Num());
}

// Called every tick when no combo is active (CurrentMove is None), attempts to start a Root move from the player input
void USC_CharacterAction::StartCombo()
{
}


// Called every frame
void USC_CharacterAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentMove.IsNone())
		StartCombo();

	else
		ServeInput();
}

// Provide player input to the Character Action component
void USC_CharacterAction::Input(const FName& Input, int32 Complexity)
{
	// Inserting input into the buffer
	int32 InsertionIndex = 0;
	while (PlayerInputBuffer[InsertionIndex].Value > Complexity)
		InsertionIndex++;

	PlayerInputBuffer.Insert({ Input, Complexity }, InsertionIndex);
}

// Called by Combo Transition Notifies, triggers a transition to the next move, based on Combo Key and Current Move
void USC_CharacterAction::TriggerComboMove(const FName& DefaultComboKey, bool ForceDefaultComboKey)
{
}

// Resets current move and buffers at the end of the combo
void USC_CharacterAction::ResetCombo()
{
	CurrentMove = FName();
}

// Called by Combo Input Notifies, adds an entry to InputRequestBuffer
void USC_CharacterAction::RequestInput(const FName& Input, USC_ComboInputNotify* RequestorNotify, int32 Priority)
{
	auto* Requestors = InputRequestBuffer.Find(Input);
	if (Requestors)
	{
		int32 InsertionIndex = 0;
		while ((*Requestors)[InsertionIndex].Value > Priority)
			InsertionIndex++;

		Requestors->Insert({ RequestorNotify, Priority }, InsertionIndex);
	}

	else
		InputRequestBuffer.Add(Input, { { RequestorNotify, Priority } });
}

// Wether the specified combo key is valid or not
bool USC_CharacterAction::IsComboKeyValid(const FName& ComboKey, const FName& Move)
{
	return false;
}

