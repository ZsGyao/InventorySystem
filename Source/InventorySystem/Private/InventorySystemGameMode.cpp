// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventorySystemGameMode.h"
#include "InventorySystemCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include  "InventorySystem/Public/InventorySystemHUD.h"
AInventorySystemGameMode::AInventorySystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> PlayInventorySystemBPClass(TEXT("/Game/InventorySystem/Blueprints/BP_InventorySystemHUD"));
	if (PlayInventorySystemBPClass.Class != NULL)
	{
		HUDClass = PlayInventorySystemBPClass.Class;
	}
}
