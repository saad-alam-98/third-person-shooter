// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

//class UCharacterMovementComponent;

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ShooterCharacter == nullptr)
	{
		UShooterAnimInstance::AssingShooterCharacter();
	}

	if (ShooterCharacter)
	{
		FVector Velocity = ShooterCharacter->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();
		
		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

	}

}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	UShooterAnimInstance::AssingShooterCharacter();
}

void UShooterAnimInstance::AssingShooterCharacter()
{
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}

