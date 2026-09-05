// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "SC_CharacterAction.generated.h"


USTRUCT(BlueprintType)
struct FSC_ComboMoveData : public FTableRowBase
{
	GENERATED_BODY()

	// Move animation montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* Animation;

	// Branch map: Combo Key -> New Move
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FName> ComboBranches;

	// ...
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCARLETCOMBAT_CHARACTERACTION_API USC_CharacterAction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USC_CharacterAction();


protected:

	// Name (ID) of the currently playing move
	FName CurrentMove;

	// Buffer of player inputs that happened during the last tick
	TMap<FName, int32> PlayerInputBuffer;

	// Buffer of input requests from Combo Input Notifies that were created during the last tick
	TArray<TPair<FName, class USC_ComboInputNotify*>> InputRequestBuffer;

public:
	// Array of move set libraries, which are used for combo look ups
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TArray<UDataTable*> MoveSetLibraries;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every tick, handles PlayerInputBuffer and InputRequestBuffer
	void ServeInput();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Provide player input to the Character Action component
	UFUNCTION(BlueprintCallable, Category = "ScarletCombat|CharacterAction")
	void Input(const FName& Input, int32 Complexity);

	// Called by Combo Transition Notifies, triggers a transition to the next move, based on Combo Key and Current Move
	// Call manually to force a transition
	UFUNCTION(BlueprintCallable, Category = "ScarletCombat|CharacterAction")
	void TriggerComboMove(const FName& ComboKey);

	// Called by Combo Input Notifies, adds an entry to InputRequestBuffer
	void RequestInput(const FName& Input, class USC_ComboInputNotify* RequestorNotify);

	// Wether the specified combo key is valid or not
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ScarletCombat|CharacterAction")
	bool IsComboKeyValid(const FName& ComboKey, const FName& Move = "SC_CURRENT");
};
