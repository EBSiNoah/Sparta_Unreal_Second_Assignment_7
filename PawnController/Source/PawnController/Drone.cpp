// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	springArmComp->SetupAttachment(RootComponent);

	springArmComp->TargetArmLength = 300.0f;

	springArmComp->bUsePawnControlRotation = true;


	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	cameraComp->SetupAttachment(springArmComp, USpringArmComponent::SocketName);

	cameraComp->bUsePawnControlRotation = false;

	normalSpeed = 600.0f;
	boostMultiply = 1.5f;
	boostSpeed = normalSpeed * boostMultiply;

	GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ADronePlayerController* droneController = Cast<ADronePlayerController>(GetController()))
		{
			if (droneController->flyingAction)
			{
				enhancedInput->BindAction(
					droneController->flyingAction,
					ETriggerEvent::Triggered,
					this,
					&ADrone::Fly
				);
			}

			if (droneController->hoveringAction)
			{
				enhancedInput->BindAction(
					droneController->hoveringAction,
					ETriggerEvent::Triggered,
					this,
					&ADrone::StartHover
				);

				enhancedInput->BindAction(
					droneController->hoveringAction,
					ETriggerEvent::Completed,
					this,
					&ADrone::StopHover
				);
			}

			if (droneController->lookAction)
			{
				enhancedInput->BindAction(
					droneController->lookAction,
					ETriggerEvent::Triggered,
					this,
					&ADrone::Look
				);
			}

			if (droneController->boosterAction)
			{
				enhancedInput->BindAction(
					droneController->boosterAction,
					ETriggerEvent::Triggered,
					this,
					&ADrone::StartBoost
				);

				enhancedInput->BindAction(
					droneController->boosterAction,
					ETriggerEvent::Completed,
					this,
					&ADrone::StopBoost
				);
			}
		}
	}
}

void ADrone::Fly(const FInputActionValue& value)
{
	if (!Controller)return;

	const FVector2D flyInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(flyInput.X))
	{
		AddMovementInput(GetActorForwardVector(), flyInput.X);
	}

	if (!FMath::IsNearlyZero(flyInput.Y))
	{
		AddMovementInput(GetActorRightVector(), flyInput.Y);
	}
}

void ADrone::StartHover(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
	}
}

void ADrone::StopHover(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}

void ADrone::Look(const FInputActionValue& value)
{
	FVector2D lookInput = value.Get<FVector2D>();

	AddControllerYawInput(lookInput.X);
	AddControllerPitchInput(lookInput.Y);	
}

void ADrone::StartBoost(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = boostSpeed;
	}
}

void ADrone::StopBoost(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
	}
}