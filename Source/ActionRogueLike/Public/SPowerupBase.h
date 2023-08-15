// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPowerupBase.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASPowerupBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupBase();

protected:

	bool bIsPowerupActive;

	UPROPERTY(EditDefaultsOnly, Category = "Power Up")
	float ReactivationTime;

	FTimerHandle Restart_TimerHandle;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	virtual	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PostInitializeComponents() override;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual void RestartPowerUp();

};
