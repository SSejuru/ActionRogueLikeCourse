// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"

/**
 *
*/
UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;


public:

	ASItemChest();

	UPROPERTY(EditAnywhere, Category = "Animation")
	float TargetPitch;

protected:

	UPROPERTY(ReplicatedUsing = "OnRep_LidOpened") //RepNotify
	bool bLidOpened;

	UFUNCTION(BlueprintCallable)
	void OnRep_LidOpened();

	UFUNCTION(BlueprintNativeEvent, Category = "Animation")
	void AnimateLid(bool bOpenChest);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;


};
