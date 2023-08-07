// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


ASDashProjectile::ASDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MovementComp->InitialSpeed = 6000.f;
}

void ASDashProjectile::Explode_Implementation()
{
	// Clear timer if the Explode was already called through another source like OnActorHit
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonation);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	//UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());

	ParticleSystemComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ASDashProjectile::TeleportInstigator, TeleportDelay);

	// Skip base implementation as it will destroy actor (we need to stay alive a bit longer to finish the 2nd timer)
	//Super::Explode_Implementation();
}

void ASDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if(ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);

		// Play shake on the player we teleported
		//APawn* InstigatorPawn = Cast<APawn>(ActorToTeleport);
		//APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
		//if (PC && PC->IsLocalController())
		//{
		//	PC->ClientStartCameraShake(ImpactShake);
		//}
	}

	Destroy();
}


void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonation, this, &ASDashProjectile::Explode, DetonateDelay);
}



