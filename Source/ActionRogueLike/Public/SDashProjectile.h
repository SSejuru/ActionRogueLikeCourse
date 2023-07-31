// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:

	ASDashProjectile();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash Data")
	UParticleSystem* ExplosionParticles;

	FTimerHandle TimerHandle_DelayedDetonation;

	void TeleportInstigator();

	void StopProjectile();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
