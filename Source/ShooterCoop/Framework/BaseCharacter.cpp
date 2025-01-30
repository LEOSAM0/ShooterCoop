// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::MoveForward(float val)
{
	if (Controller == nullptr || val == 0.f)
	{
		return;
	}
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, val);
}

void ABaseCharacter::MoveRight(float val)
{
	if (Controller == nullptr || val == 0.f)
	{
		return;
	}
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, val);
}

void ABaseCharacter::LookUp(float val)
{
	if (val == 0.f)
	{
		return;
	}
	AddControllerPitchInput(val);
}

void ABaseCharacter::Turn(float val)
{
	if (val == 0.f)
	{
		return;
	}
	AddControllerYawInput(val);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


