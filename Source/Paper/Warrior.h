// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Warrior.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class PAPER_API AWarrior : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	AWarrior();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
 
private:
	UPROPERTY(VisibleAnywhere , Category = "Components" , meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere , Category = "Components" , meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	float MoveInputValue;

	UPROPERTY(EditAnywhere , meta = (AllowPrivateAccess = " true"))
	float CrouchSpriteHeight = 40.0f;

	const FVector DefaultSpriteOffset = FVector(25.0f , 0.0f , 18.0f);

	FVector CrouchSpriteOffset;

	UPROPERTY(BlueprintReadOnly , Category = "Anim Parameters" , meta = (AllowPrivateAccess = "true"))
	bool IsSliding;
	
	UPROPERTY(BlueprintReadOnly , Category = "Anim Parameters" , meta = (AllowPrivateAccess = "true"))
	bool IsJumping;

	UPROPERTY(EditAnywhere , Category = "Movement|Slide" , meta = (AllowPrivateAccess = "true"))
	float SlideDuration = 0.5f;

	UPROPERTY(EditAnywhere , Category = "Movement|Crouch" , meta = (AllowPrivateAccess = "true"))
	float CrouchedSpriteHeight = 50.0f;
	
	UFUNCTION(BlueprintPure , Category = "Anim Parameters")
	FORCEINLINE bool IsRunning() const{ return IsGrounded() && MoveInputValue != 0.0f; }

	UFUNCTION(BlueprintPure , Category = "Anim Parameters")
	FORCEINLINE bool IsFalling() const{return !IsGrounded() && GetVelocity().Z <= 0.0f ;}

	UFUNCTION(BlueprintPure , Category = "Anim Parameters")
	FORCEINLINE bool IsLanding() const{return IsGrounded() && MoveInputValue == 0.0f ;}

	UFUNCTION(BlueprintPure , Category = "Anim Parameters")
	bool IsCorouching() const;
	
	UFUNCTION(BlueprintPure , Category = "Anim Parameters")
	bool IsGrounded() const;
	
	UFUNCTION(BlueprintCallable , Category = "Movement")
	void Move(const float InputActionValue);
	
	virtual void Crouch(bool bClientSimulation) override;
	
	virtual void UnCrouch(bool bClientSimulation) override;

	void Slide();

	void StopSlide();
	
	UFUNCTION(BlueprintCallable , Category = "Movement")
	FORCEINLINE void SetMoveInputValue(const float InValue) {MoveInputValue = InValue;}

	UFUNCTION(BlueprintCallable , Category = "Movement")
	void OnJumpInput();

	UFUNCTION()
	void OnCharacterLanded(const FHitResult& Hit);
};
