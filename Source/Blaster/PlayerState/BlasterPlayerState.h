// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BlasterPlayerState.generated.h"

/**
 *
 */
UCLASS()
class BLASTER_API ABlasterPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void OnRep_Score() override;
	void AddToScore(int32 ScoreAmount);

private:
	class ABlasterCharacter *Character;
	class ABlasterPlayerController *Controller;

public:
	FORCEINLINE ABlasterCharacter *GetCharacter() { return Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character; }
};
