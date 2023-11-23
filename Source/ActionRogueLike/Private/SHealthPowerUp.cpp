// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPowerUp.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"

ASHealthPowerUp::ASHealthPowerUp()
{
	HealAmmount = 20.0f;
	CreditCost = 50;
}

void ASHealthPowerUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!InstigatorPawn) return;

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (AttributeComp && !AttributeComp->IsMaxHealth())
	{
		if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{
			if(PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChange(this, HealAmmount))
			{
				Super::Interact_Implementation(InstigatorPawn);
			}
		}
	}

}

FText ASHealthPowerUp::GetInteractMessage_Implementation(APawn* InstigatorActor)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorActor->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (AttributeComp && AttributeComp->IsMaxHealth())
	{
		return NSLOCTEXT("InteractableActors", "HealthPotion_FullHealthWarning", "Already at full health");
	}

	return FText::Format(NSLOCTEXT("InteractableActors", "HealthPotion_InteractMessage", "Cost: {0} Credits."), CreditCost);
}
