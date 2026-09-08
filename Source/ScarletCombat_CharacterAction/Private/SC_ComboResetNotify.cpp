// Fill out your copyright notice in the Description page of Project Settings.


#include "SC_ComboResetNotify.h"

#include "SC_CharacterAction.h"
#include "SC_CharacterActionInterface.h"

void USC_ComboResetNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
	const FAnimNotifyEventReference& EventReference)
{
    // Fetching character action component
    AActor* Owner = MeshComp->GetOwner();
    USC_CharacterAction* CharacterAction = nullptr;

    if (Owner && Owner->Implements<USC_CharacterActionInterface>())
    {
        USC_CharacterAction* CharacterAction = ISC_CharacterActionInterface::Execute_GetCharacterActionComponent(Owner);
        CharacterAction = CharacterAction;
    }

    if (!CharacterAction) return;

    // Resetting combo
    CharacterAction->ResetCombo();
}
