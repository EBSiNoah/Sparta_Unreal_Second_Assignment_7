// Fill out your copyright notice in the Description page of Project Settings.


#include "DronGameMode.h"

ADronGameMode::ADronGameMode()
{
	DefaultPawnClass = ADrone::StaticClass();
	PlayerControllerClass = ADronePlayerController::StaticClass();
}