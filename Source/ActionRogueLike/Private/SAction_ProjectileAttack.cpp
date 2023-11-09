// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"

#include "SProjectileBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	AttackAnimDelay = 0.2f;
	HandSocketName = "Muzzle_01";
}


void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(AttackAnim);

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		if (Character->HasAuthority())
		{
			FTimerHandle TimerHandle_AttackDelay;
			FTimerDelegate Delegate;
			Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
		}
	}
}

void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensureAlways(ProjectileClass))
	{
		//Projectile Spawn location
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation("Muzzle_01");

		//Line trace from camera to world to find hit location
		FHitResult Hit;
		FVector Start = InstigatorCharacter->GetPawnViewLocation();
		FVector Forward = InstigatorCharacter->GetControlRotation().Vector();
		FVector End = Start + (Forward * 2500.0f);

		FCollisionShape Shape;
		Shape.SetSphere(15.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FCollisionObjectQueryParams CollisionObjectParams;

		CollisionObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		CollisionObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);
		CollisionObjectParams.AddObjectTypesToQuery(ECC_Pawn);

		bool bBlockingHit = GetWorld()->SweepSingleByObjectType(Hit, Start, End, FQuat::Identity, CollisionObjectParams, Shape, Params);

		//FColor lineColor = bBlockingHit ? FColor::Green : FColor::Red;
		//DrawDebugLine(GetWorld(), Start, End, lineColor, false, 2, 0, 2.0f);

		FVector HitPosition = bBlockingHit ? Hit.ImpactPoint : End;

		//Spawn Projectile in hand location with rotation to line trace hit position
		FVector TargetDirection = HitPosition - HandLocation;
		FRotator ProjectileRotation = FRotationMatrix::MakeFromX(TargetDirection).Rotator();

		FTransform SpawnTM = FTransform(ProjectileRotation, HandLocation);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		GetWorld()->SpawnActor<ASProjectileBase>(ProjectileClass, SpawnTM, SpawnParams);
	}

	StopAction(InstigatorCharacter);
}


