// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USActionComponent;
class USAttributeComponent;
class ASProjectileBase;
class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()



public:
	// Sets default values for this character's properties
	ASCharacter();

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ASProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ASProjectileBase> PrimarySkillProjectile;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ASProjectileBase> SecondarySkillProjectile;

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USActionComponent* ActionComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);

	void MoveRight(float value);

	void SprintStart();

	void SprintStop();

	void PrimaryAttack();

	void PrimarySkill();

	void SecondarySkill();

	void PrimaryInteract();

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual FVector GetPawnViewLocation() const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);

	UFUNCTION(Exec)
	void KillSelf();

};
