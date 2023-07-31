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


void ASDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this, &ASDashProjectile::OnComponentHit);
}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonation, this, &ASDashProjectile::StopProjectile, 0.2f);
}

void ASDashProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonation);
	StopProjectile();
}
