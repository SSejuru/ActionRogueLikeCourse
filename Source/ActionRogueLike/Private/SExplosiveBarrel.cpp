// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "DrawDebugHelpers.h"
#include "PhysicsEngine/RadialForceComponent.h"

/**
 * Sets default values
*/
ASExplosiveBarrel::ASExplosiveBarrel()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = MeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->SetupAttachment(MeshComp);

	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->Radius = 750.0f;
	RadialForceComp->ImpulseStrength = 2000.0f;
	RadialForceComp->bImpulseVelChange = true;

	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

/**
 * Called when the game starts or when spawned
*/
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnComponentHit);
}

void ASExplosiveBarrel::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();

	// Log Example
	// %s = string, %f = float.
	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel!"));
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);


	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);

}



