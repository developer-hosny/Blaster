// Fill out your copyright notice in the Description page of Project Settings.

#include "BlasterPlayerState.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"

void ABlasterPlayerState::OnRep_Score()
{
    Super::OnRep_Score();

    Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;

    if (GetCharacter())
    {
        Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;

        if (Controller)
        {
            Controller->SetHUDScore(GetScore());
        }
    }
}

void ABlasterPlayerState::AddToScore(int32 ScoreAmount)
{
    SetScore(GetScore() + ScoreAmount);
    // Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
    if (GetCharacter())
    {
        Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
        if (Controller)
        {
            Controller->SetHUDScore(GetScore());
        }
    }
}
