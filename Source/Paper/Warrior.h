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
 
private:
	UPROPERTY(VisibleAnywhere , Category = "Components" , meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere , Category = "Components" , meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	float MoveInputValue;
	
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
	
	UFUNCTION(BlueprintCallable , Category = "Movement")
	FORCEINLINE void SetMoveInputValue(const float InValue) {MoveInputValue = InValue;}
};
