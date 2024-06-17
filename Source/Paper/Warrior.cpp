// Fill out your copyright notice in the Description page of Project Settings.


#include "Warrior.h"

#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AWarrior::AWarrior()
{
	JumpMaxHoldTime = 0.3f;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera"));
	SpringArmComponent -> SetupAttachment(RootComponent);
	SpringArmComponent -> TargetArmLength = 900.0f;
	SpringArmComponent -> SetRelativeLocation(FVector(0.0f , 0.0f , 40.f));
	SpringArmComponent ->bInheritYaw = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Boom"));
	CameraComponent -> SetupAttachment(SpringArmComponent);
	
	GetSprite() -> SetCastShadow(true);
	GetSprite() -> SetRelativeLocation(DefaultSpriteOffset);
	GetSprite() -> SetRelativeScale3D(FVector(5.0f));

	GetCharacterMovement() -> bOrientRotationToMovement = true;
	GetCharacterMovement() -> RotationRate = FRotator(0.0f , 10000.0f , 0.0f);
	GetCharacterMovement() -> SetCrouchedHalfHeight(50.f);
	GetCharacterMovement() -> GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AWarrior::BeginPlay()
{
	Super::BeginPlay();

	CrouchSpriteOffset = FVector(DefaultSpriteOffset.X , DefaultSpriteOffset.Y , CrouchSpriteHeight);
}

void AWarrior::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsSliding)
	{
		AddMovementInput(GetActorForwardVector());
	}
}

bool AWarrior::IsGrounded() const
{
	return GetCharacterMovement()->IsMovingOnGround();
}

bool AWarrior::IsCorouching() const
{
	return GetCharacterMovement() -> IsCrouching();
}

void AWarrior::Move(const float InputActionValue)
{
	if(IsCorouching())
	{
		if(InputActionValue < 0.0f)
		{
			SetActorRotation(FRotator(0.0f , 180.0f , 0.0f));
		}
		else if(InputActionValue > 0.0f)
		{
			SetActorRotation(FRotator(0.0f , 0.0f , 0.0f));
		}
		return;
	}
	
	AddMovementInput(FVector::ForwardVector , InputActionValue);

	SetMoveInputValue(InputActionValue);
}

void AWarrior::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);
	GetSprite() -> SetRelativeLocation(CrouchSpriteOffset);
}

void AWarrior::UnCrouch(bool bClientSimulation)
{
	Super::UnCrouch(bClientSimulation);
	GetSprite() -> SetRelativeLocation(DefaultSpriteOffset);
}

void AWarrior::Slide()
{
	IsSliding = true;

	FTimerHandle SlideTimerHandle;
	GetWorldTimerManager().SetTimer(SlideTimerHandle , this , &AWarrior::StopSlide , SlideDuration);
}

void AWarrior::StopSlide()
{
	IsSliding = false;
}

void AWarrior::OnJumpInput()
{
	if(bIsCrouched)
	{
		Slide();
		return;
	}
	Jump();
}
