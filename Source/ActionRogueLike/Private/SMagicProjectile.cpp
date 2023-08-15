// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets Default Values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp->SetSphereRadius(20.0f);
	InitialLifeSpan = 10.0f;
	ProjectileDamage = 20;
}


// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	ASCharacter* CharacterOwner = Cast<ASCharacter>(GetInstigator());

	if(CharacterOwner)
		UGameplayStatics::SpawnEmitterAttached(SpawnParticles, CharacterOwner->GetMesh(), "Muzzle_01");
}

void ASMagicProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-ProjectileDamage);
			Explode();
		}
	}
}

void ASMagicProjectile::Explode_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation(), GetActorRotation());

	AActor* InstigatorActor = GetInstigator();

	if (InstigatorActor)
	{
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake, InstigatorActor->GetActorLocation(), 0.0f, 500.0f);
	}

	Super::Explode_Implementation();
}


void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnComponentBeginOverlap);
}


//Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

