// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventorySystemHUD.generated.h"


class UInventoryPanel;
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

	//// new
	//UPROPERTY(EditDefaultsOnly, Category = "Inventory Widget")
	//TSubclassOf<UInventoryPanel> InventoryPanelClass;

	bool bIsMenuVisible;

	//// new
	//bool bIsInventoryPanelVisible;
public:
	AInventorySystemHUD();

	void DisplayMenu();
	void HideMenu();

	void ToggleMenu();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

	//void ShowInventorySystemWidget();
	//void HideInventorySystemWidget();
	//void ToggleInventoryMenu();

protected:
	UPROPERTY()
		UMainMenu* MainMenuWidget;

	UPROPERTY()
		UInteractionWidget* InteractionWidget;

	// new
	UPROPERTY()
		UInventoryPanel* InventoryPanel;
protected:
	virtual void BeginPlay() override;
};
