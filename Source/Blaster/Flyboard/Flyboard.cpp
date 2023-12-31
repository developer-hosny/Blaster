// Fill out your copyright notice in the Description page of Project Settings.

#include "Flyboard.h"
#include "Blaster/Character/BlasterCharacter.h"

AFlyboard::AFlyboard()
{
	PrimaryActorTick.bCanEverTick = true;

	FlyboardMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	FlyboardMesh->SetupAttachment(RootComponent);
	SetRootComponent(FlyboardMesh);

	// DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	// SetRootComponent(RootComponent);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LeftJet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftJet"));
	LeftJet->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftJet->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RightJet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightJet"));
	RightJet->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightJet->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	JetConnector = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JetConnector"));
	JetConnector->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	JetConnector->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LeftJet->AttachToComponent(AreaSphere, FAttachmentTransformRules::KeepRelativeTransform);
	RightJet->AttachToComponent(AreaSphere, FAttachmentTransformRules::KeepRelativeTransform);
	JetConnector->AttachToComponent(AreaSphere, FAttachmentTransformRules::KeepRelativeTransform);

	ThrusterLeft = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ThrusterLeft"));
	ThrusterRight = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ThrusterRight"));

	ThrusterLeft->AttachToComponent(LeftJet, FAttachmentTransformRules::KeepRelativeTransform);
	ThrusterRight->AttachToComponent(RightJet, FAttachmentTransformRules::KeepRelativeTransform);
}

void AFlyboard::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
		AreaSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereEndOverlap);
	}
}

void AFlyboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlyboard::OnSphereOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ABlasterCharacter *BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (BlasterCharacter)
	{
		BlasterCharacter->SetOverlappingFlyboard(this);
	}
}

void AFlyboard::OnSphereEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	ABlasterCharacter *BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (BlasterCharacter)
	{
		BlasterCharacter->SetOverlappingFlyboard(nullptr);
	}
}

void AFlyboard::Dropped()
{
	ThrusterLeft->Deactivate();
	ThrusterRight->Deactivate();

	// AFlyboard::ActiveThruster(false);

	// if (HasAuthority())
	// {
	// 	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// }
	FlyboardMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FlyboardMesh->SetSimulatePhysics(true);
	FlyboardMesh->SetEnableGravity(true);

	// FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
	// FlyboardMesh->DetachFromComponent(DetachRules);
	// // AreaSphere->DetachFromComponent(DetachRules);
	// SetOwner(nullptr);
}

void AFlyboard::ActiveThruster(bool bIsActive)
{
	ThrusterLeft->Activate(bIsActive);
	ThrusterRight->Activate(bIsActive);
}
