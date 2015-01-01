// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "CharacterController.h"
#include "MyHUD.h"
#include "MosaicGameMode.h"


AMosaicGameMode::AMosaicGameMode(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/Blueprint/CharacterBP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> ControllerClassObject(TEXT("/Game/Character/Blueprint/CharacterControllerBP"));
	if (ControllerClassObject.Class != NULL)
	{
		PlayerControllerClass = ControllerClassObject.Class;
	}

	//HUDClass = AMyHUD::StaticClass();
}


