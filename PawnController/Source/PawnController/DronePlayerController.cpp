// Fill out your copyright notice in the Description page of Project Settings.


#include "DronePlayerController.h"

ADronePlayerController::ADronePlayerController()
	: inputMappingContext(nullptr),
	flyingAction(nullptr),
	hoveringAction(nullptr),
	lookAction(nullptr),
	boosterAction(nullptr)
{

}

void ADronePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* localPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* subSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (inputMappingContext)
			{
				subSystem->AddMappingContext(inputMappingContext, 0);
			}
		}
	}
}