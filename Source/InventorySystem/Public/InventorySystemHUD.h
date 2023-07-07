// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventorySystemHUD.generated.h"


class UWorldInventoryWidget;
class AInventorySystemCharacter;
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

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> CrosshairWidgetClass;

	// new
	UPROPERTY(EditDefaultsOnly, Category = "World Widgets")
		TSubclassOf<UWorldInventoryWidget> WorldInventoryWidgetClass;

	bool bIsMenuVisible;

	// new
	bool bIsPanelVisible;
public:
	AInventorySystemHUD();

	void DisplayMenu();
	void HideMenu();

	void ToggleMenu();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

	void ShowCrosshair();
	void HideCrosshair();

	void ShowOrHidePanelWidget();

	void ShowOrHideMMInventoryVisible() const;

	FORCEINLINE UMainMenu* GetMainMenu() const { return MainMenuWidget; }
protected:
	UPROPERTY()
		UMainMenu* MainMenuWidget;

	UPROPERTY()
		UInteractionWidget* InteractionWidget;

	UPROPERTY()
		UUserWidget* CrosshairWidget;

	UPROPERTY()
		UWorldInventoryWidget* WorldInventoryWidget;

protected:
	virtual void BeginPlay() override;
};
