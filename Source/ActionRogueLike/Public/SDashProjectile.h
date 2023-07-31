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

	virtual void BeginPlay() override;

private:

	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
