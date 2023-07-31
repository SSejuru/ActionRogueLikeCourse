// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "DrawDebugHelpers.h"
#include "SInteractionComponent.h"
#include "SProjectileBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Character Movement Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	//Camera Rotation Axis
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//Action Binds
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction("PrimarySkill", IE_Pressed, this, &ASCharacter::PrimarySkill);
	PlayerInputComponent->BindAction("SecondarySkill", IE_Pressed, this, &ASCharacter::SecondarySkill);

}


void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// In unreal engine:
	// X = Forward
	// Y = Right
	// Z = Up

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	if (ensureAlways(ProjectileClass)) 
	{
		ShootProjectile(ProjectileClass);
	}
}

void ASCharacter::PrimarySkill()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimarySkill_TimeElapsed, 0.2f);
}

void ASCharacter::PrimarySkill_TimeElapsed()
{
	if (ensureAlways(PrimarySkillProjectile))
	{
		ShootProjectile(PrimarySkillProjectile);
	}
}

void ASCharacter::SecondarySkill()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::SecondarySkill_TimeElapsed, 0.2f);
}

void ASCharacter::SecondarySkill_TimeElapsed()
{
	if (ensureAlways(SecondarySkillProjectile))
	{
		ShootProjectile(SecondarySkillProjectile);
	}
}

void ASCharacter::ShootProjectile(TSubclassOf<ASProjectileBase> Projectile)
{
	//Projectile Spawn location
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	//Line trace from camera to world to find hit location
	FHitResult Hit;
	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + (CameraComp->GetForwardVector() * 1500.0f);

	FCollisionObjectQueryParams CollisionObjectParams;
	CollisionObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	CollisionObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, CollisionObjectParams);

	//FColor lineColor = bBlockingHit ? FColor::Green : FColor::Red;
	//DrawDebugLine(GetWorld(), Start, End, lineColor, false, 2, 0, 2.0f);

	FVector HitPosition = bBlockingHit ? Hit.ImpactPoint : End;

	//Spawn Projectile in hand location with rotation to line trace hit position
	FVector TargetDirection = HitPosition - HandLocation;
	FRotator ProjectileRotation = FRotationMatrix::MakeFromX(TargetDirection).Rotator();

	FTransform SpawnTM = FTransform(ProjectileRotation, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(Projectile, SpawnTM, SpawnParams);
}
