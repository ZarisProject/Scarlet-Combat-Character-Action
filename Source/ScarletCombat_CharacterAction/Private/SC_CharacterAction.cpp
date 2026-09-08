// Fill out your copyright notice in the Description page of Project Settings.

#include "SC_CharacterAction.h"

#include "Animation/AnimMontage.h"

#include "SC_ComboInputNotify.h"
#include "SC_CharacterActionInterface.h"

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
					// Caching combo key associated with the requestor notify
					if (ComboKeyCache.IsNone() || Requestor.Key->OverrideExistingKey)
						ComboKeyCache = Requestor.Key->ComboKey;

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
	for (auto& PlayerInput : PlayerInputBuffer)
	{
		FSC_ComboMoveData* RootMoveData = LookUpMoveData(PlayerInput.Key);
		if (RootMoveData)
		{
			StartMove(PlayerInput.Key, RootMoveData);
			break;
		}
	}
}

// Initiates move animation
void USC_CharacterAction::StartMove(const FName& MoveName, FSC_ComboMoveData* MoveData)
{
	CurrentMove = MoveName;

	// Clear cache (just in case)
	ComboKeyCache = NAME_None;

	if (GetOwner() && GetOwner()->Implements<USC_CharacterActionInterface>())
	{
		// Playing animation (through an interface call)
		ISC_CharacterActionInterface::Execute_PlayMoveAnimation(GetOwner(), MoveData->Animation);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SC CHARACTER ACTION: Owner actor does not exist or does not implement SC_CharacterActionInterface"));
	}
		
}

// Attempts to find move data in move set libraries
FSC_ComboMoveData* USC_CharacterAction::LookUpMoveData(const FName& MoveName)
{
	FSC_ComboMoveData* MoveData = nullptr;

	for (auto MoveSet : MoveSetLibraries)
	{
		FString ContextString = TEXT("SC CHARACTER ACTION : Looking up move data");
		MoveData = MoveSet->FindRow<FSC_ComboMoveData>(MoveName, ContextString, false);
		if (MoveData)
			return MoveData;
	}

	return nullptr;
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
	// Early exist if not combo key is provided
	if (ComboKeyCache.IsNone() && DefaultComboKey.IsNone())
		return;

	// Finding current move data
	FSC_ComboMoveData* CurrentMoveData = LookUpMoveData(CurrentMove);

	if (!CurrentMoveData)
	{
		UE_LOG(LogTemp, Warning, TEXT("SC CHARACTER ACTION: current move is invalid or None!"));
		return;
	}

	// Determining which combo key to use
	const FName* ComboKey = &ComboKeyCache;
	if (ComboKeyCache.IsNone() || ForceDefaultComboKey)
		ComboKey = &DefaultComboKey;

	// Checking combo key validity
	FName* NextMove = CurrentMoveData->ComboBranches.Find(*ComboKey);
	if (!NextMove)
	{
		UE_LOG(LogTemp, Warning, TEXT("SC CHARACTER ACTION: provided combo key is invalid!"));
		return;
	}

	// Looking up new move data
	FSC_ComboMoveData* NewMoveData = LookUpMoveData(*NextMove);
	if (!NewMoveData)
	{
		UE_LOG(LogTemp, Warning, TEXT("SC CHARACTER ACTION: next move is invalid!"));
		return;
	}

	// Initiating new move
	StartMove(*NextMove, NewMoveData);
}

// Resets current move and buffers at the end of the combo
void USC_CharacterAction::ResetCombo()
{
	CurrentMove = NAME_None;

	ComboKeyCache = NAME_None;

	PlayerInputBuffer.Empty();
	InputRequestBuffer.Empty(InputRequestBuffer.Num());
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
	for (auto MoveSet : MoveSetLibraries)
	{
		FString ContextString = TEXT("SC CHARACTER ACTION : Checking combo key validity");
		FSC_ComboMoveData* Row = MoveSet->FindRow<FSC_ComboMoveData>(Move, ContextString, false);
		if (Row)
			return Row->ComboBranches.Contains(ComboKey);
	}

	return false;
}

