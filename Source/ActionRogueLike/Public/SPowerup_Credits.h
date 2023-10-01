// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupBase.h"
#include "SPowerup_Credits.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPowerup_Credits : public ASPowerupBase
{
	GENERATED_BODY()

	ASPowerup_Credits();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Credits")
	int32 Credits;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
