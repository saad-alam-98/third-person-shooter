// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
		FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(
		MovementRotation,
			AimRotation).Yaw;

		if (ShooterCharacter->GetVelocity().Size() > 0.f)
		{
			LastMovementOffsetYaw = MovementOffsetYaw;
		}

		FString OffsetRotationMessage = FString::Printf(TEXT("MovementOffsetYaW: %f"), AimRotation.Yaw);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 0, FColor::White, OffsetRotationMessage);
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

