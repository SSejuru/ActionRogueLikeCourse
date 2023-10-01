// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"
#include "SActionComponent.h"



void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));

	USActionComponent* Comp = GetOwningComponent();
	
	Comp->ActiveGameplayTags.AppendTags(GrantsTag);

	bIsRunning = true;
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));

	ensureAlways(bIsRunning);

	USActionComponent* Comp = GetOwningComponent();

	Comp->ActiveGameplayTags.RemoveTags(GrantsTag);

	bIsRunning = false;
}



bool USAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning()) return false;

	USActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags)) {
		return false;
	}

	return true;
}


UWorld* USAction::GetWorld() const
{
	//Outer is set when creating action via NewObject<T>
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if(Comp)
	{
		return Comp->GetWorld();
	}

	return nullptr;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}


bool USAction::IsRunning() const
{
	return bIsRunning;
} 
