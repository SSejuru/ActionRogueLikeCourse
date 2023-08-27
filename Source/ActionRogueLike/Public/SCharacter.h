// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USAttributeComponent;
class ASProjectileBase;
class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	FTimerHandle TimerHandle_PrimaryAttack;

public:
	// Sets default values for this character's properties
	ASCharacter();

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ASProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ASProjectileBase> PrimarySkillProjectile;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ASProjectileBase> SecondarySkillProjectile;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	USAttributeComponent* AttributeComp;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);

	void MoveRight(float value);

	void PrimaryAttack();

	void PrimaryAttack_TimeElapsed();

	void PrimarySkill();

	void PrimarySkill_TimeElapsed();

	void SecondarySkill();

	void SecondarySkill_TimeElapsed();

	void PrimaryInteract();

	void ShootProjectile(TSubclassOf<ASProjectileBase> Projectile);

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

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
