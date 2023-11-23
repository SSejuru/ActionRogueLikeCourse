// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupBase.h"
#include "SHealthPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASHealthPowerUp : public ASPowerupBase
{
	GENERATED_BODY()

public:

	ASHealthPowerUp();

protected:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual FText GetInteractMessage_Implementation(APawn* InstigatorActor) override;

	UPROPERTY(EditDefaultsOnly)
	float HealAmmount;



};
