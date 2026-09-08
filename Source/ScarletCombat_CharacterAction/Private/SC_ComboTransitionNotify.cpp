// Fill out your copyright notice in the Description page of Project Settings.


#include "SC_ComboTransitionNotify.h"

#include "SC_CharacterAction.h"
#include "SC_CharacterActionInterface.h"


// POINT

void USC_ComboTransitionNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
	const FAnimNotifyEventReference& EventReference)
{
    // Fetching character action component
    AActor* Owner = MeshComp->GetOwner();
    USC_CharacterAction* CharacterAction = nullptr;

    if (Owner && Owner->Implements<USC_CharacterActionInterface>())
        CharacterAction = ISC_CharacterActionInterface::Execute_GetCharacterActionComponent(Owner);

    if (!CharacterAction) return;

    // Triggering new move
    CharacterAction->TriggerComboMove(DefaultComboKey);
}



// STATE

void USC_ComboTransitionStateNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
    float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    // Fetching character action component
    AActor* Owner = MeshComp->GetOwner();

    if (Owner && Owner->Implements<USC_CharacterActionInterface>())
        Cached_CharacterAction = ISC_CharacterActionInterface::Execute_GetCharacterActionComponent(Owner);
}

void USC_ComboTransitionStateNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
    float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (Cached_CharacterAction)
        Cached_CharacterAction->TriggerComboMove(NAME_None);
}

void USC_ComboTransitionStateNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
    const FAnimNotifyEventReference& EventReference)
{
    if (Cached_CharacterAction)
        Cached_CharacterAction->TriggerComboMove(DefaultComboKey);
}
