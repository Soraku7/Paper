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

	UFUNCTION(BlueprintPure , Category = "Anim Parameters")
	bool IsRunning() const;
private:
	UPROPERTY(VisibleAnywhere , Category = "Components" , meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere , Category = "Components" , meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UFUNCTION(BlueprintCallable , Category = "Movement")
	void Move(const float InputActionValue);
};
