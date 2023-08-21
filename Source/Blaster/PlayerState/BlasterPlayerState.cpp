// Fill out your copyright notice in the Description page of Project Settings.

#include "BlasterPlayerState.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Net/UnrealNetwork.h"

void ABlasterPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ABlasterPlayerState, Defeats);
}

void ABlasterPlayerState::AddToDefeats(int32 DefeatsAmount)
{
    Defeats += DefeatsAmount;
    Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
    if (GetCharacter())
    {
        Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(GetCharacter()->Controller) : Controller;
        if (Controller)
        {
            Controller->SetHUDDefeats(Defeats);
        }
    }
}

void ABlasterPlayerState::OnRep_Defeats()
{
    if (GetCharacter())
    {
        Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(GetCharacter()->Controller) : Controller;
        if (Controller)
        {
            Controller->SetHUDDefeats(Defeats);
        }
    }
}

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