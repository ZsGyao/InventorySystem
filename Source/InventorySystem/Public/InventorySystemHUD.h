// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventorySystemHUD.generated.h"


class UMainMenu;
class UInteractionWidget;
struct FInteractableData;

UCLASS()
class INVENTORYSYSTEM_API AInventorySystemHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	bool bIsMenuVisible;

public:
	AInventorySystemHUD();

	void DisplayMenu();
	void HideMenu();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

protected:
	UPROPERTY()
		UMainMenu* MainMenuWidget;

	UPROPERTY()
		UInteractionWidget* InteractionWidget;

protected:
	virtual void BeginPlay() override;
};
