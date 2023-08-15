// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupBase.h"

// Sets default values
ASPowerupBase::ASPowerupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	MeshComp->SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = MeshComp;

	ReactivationTime = 10.0f;
	bIsPowerupActive = false;
}

void ASPowerupBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		APawn* Pawn = Cast<APawn>(OtherActor);
		if(Pawn)
		{
			Execute_Interact(this, Pawn);
		}
	}
}


void ASPowerupBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &ASPowerupBase::OnComponentBeginOverlap);
}

void ASPowerupBase::Interact_Implementation(APawn* InstigatorPawn)
{
	if (bIsPowerupActive) return;

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetVisibility(false);
	GetWorldTimerManager().SetTimer(Restart_TimerHandle, this, &ASPowerupBase::RestartPowerUp, ReactivationTime);
	bIsPowerupActive = true;
}

void ASPowerupBase::RestartPowerUp()
{
	bIsPowerupActive = false;
	MeshComp->SetVisibility(true);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}


