// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPowerUp.h"

#include "SAttributeComponent.h"

ASHealthPowerUp::ASHealthPowerUp()
{
	HealAmmount = 20.0f;
}

void ASHealthPowerUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!InstigatorPawn) return;

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (AttributeComp && !AttributeComp->IsMaxHealth())
	{
		Super::Interact_Implementation(InstigatorPawn);
		AttributeComp->ApplyHealthChange(this, HealAmmount);
	}

}
