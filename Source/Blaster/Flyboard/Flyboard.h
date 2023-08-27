// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"

#include "Flyboard.generated.h"

UCLASS()
class BLASTER_API AFlyboard : public AActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	AFlyboard();
	void Dropped();

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	class USphereComponent *AreaSphere;

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent *OverlappedComponent,
		AActor *OtherActor,
		UPrimitiveComponent *OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult &SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(
		UPrimitiveComponent *OverlappedComponent,
		AActor *OtherActor,
		UPrimitiveComponent *OtherComp,
		int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsOnFlyingBoard;

	// UPROPERTY(BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	// bool bActiveThrusters = false;

	// FORCEINLINE void SetThrusters(bool bIsActive) { bActiveThrusters = bIsActive; }
	FORCEINLINE bool IsOnFlyingBoard() const { return bIsOnFlyingBoard; }
};
