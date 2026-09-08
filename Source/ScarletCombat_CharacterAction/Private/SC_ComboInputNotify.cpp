// Fill out your copyright notice in the Description page of Project Settings.


#include "SC_ComboInputNotify.h"

#include "SC_CharacterAction.h"
#include "SC_CharacterActionInterface.h"

// Serving input to the input notify
// Returns the result of ADDITIONAL checks (if such are present)
bool USC_ComboInputNotify::ServeInput(const FName& Input)
{
    return CheckAdditionalConditions(Cached_MeshComp, Cached_Animation, Cached_OwnerActor, Cached_CharacterAction, Input);
}

void USC_ComboInputNotify::NotifyBegin( USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
                                        float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Duration = TotalDuration;
    CurrentTime = 0.0f;

    // Caching data
    Cached_MeshComp = MeshComp;
    Cached_Animation = Animation;
    Cached_OwnerActor = MeshComp->GetOwner();

    if (Cached_OwnerActor && Cached_OwnerActor->Implements<USC_CharacterActionInterface>())
    {
        USC_CharacterAction* CharacterAction = ISC_CharacterActionInterface::Execute_GetCharacterActionComponent(Cached_OwnerActor);
        Cached_CharacterAction = CharacterAction;
    }
}

void USC_ComboInputNotify::NotifyTick(  USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    CurrentTime += FrameDeltaTime;

    if (Cached_CharacterAction)
    {
        for (auto& Input : Inputs)
            Cached_CharacterAction->RequestInput(Input, this, Priority);
    }
}

void USC_ComboInputNotify::NotifyEnd(   USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
                                        const FAnimNotifyEventReference& EventReference)
{
}
