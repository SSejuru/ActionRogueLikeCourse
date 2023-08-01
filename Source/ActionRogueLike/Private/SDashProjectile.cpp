// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


ASDashProjectile::ASDashProjectile()
{
	
}

void ASDashProjectile::TeleportInstigator()
{
	GetInstigator()->SetActorRelativeLocation(GetActorLocation());
	Destroy();
}

void ASDashProjectile::StopProjectile()
{
	MovementComp->StopMovementImmediately();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticles, SphereComp->GetRelativeLocation());

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonation, this, &ASDashProjectile::TeleportInstigator, 0.2f);
}


void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonation, this, &ASDashProjectile::StopProjectile, 0.2f);
}

void ASDashProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator()) {
		GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonation);
		StopProjectile();
	}
}


