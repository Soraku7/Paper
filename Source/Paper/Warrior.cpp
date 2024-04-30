// Fill out your copyright notice in the Description page of Project Settings.


#include "Warrior.h"

#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AWarrior::AWarrior()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera"));
	SpringArmComponent -> SetupAttachment(RootComponent);
	SpringArmComponent -> TargetArmLength = 900.0f;
	SpringArmComponent -> SetRelativeLocation(FVector(0.0f , 0.0f , 40.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Boom"));
	CameraComponent -> SetupAttachment(SpringArmComponent);
	
	GetSprite() -> SetCastShadow(true);
}

bool AWarrior::IsRunning() const
{
	return GetCharacterMovement() -> IsMovingOnGround() && GetVelocity().X != 0.0f;
}

void AWarrior::Move(const float InputActionValue)
{
	AddMovementInput(FVector::ForwardVector , InputActionValue);
}
