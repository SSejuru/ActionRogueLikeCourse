// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


USBTService_CheckHealth::USBTService_CheckHealth()
{
	LowHealthFraction = 0.4f;
}

void USBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* MyPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(ensure(MyPawn))
	{
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(MyPawn);
		if(AttributeComp)
		{
			bool bIsLowHealth = (AttributeComp->GetHealth() / AttributeComp->GetMaxHealth()) < LowHealthFraction;

			OwnerComp.GetBlackboardComponent()->SetValueAsBool(LowHealthKey.SelectedKeyName, bIsLowHealth);
		}
	}
}


