// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"


class UInventoryPanel;
class UGridWidget;
class UWorldInventoryWidget;
class AInventorySystemCharacter;

UCLASS()
class INVENTORYSYSTEM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
		AInventorySystemCharacter* PlayerCharacter;

	UPROPERTY(meta = (BindWidget))
		UWorldInventoryWidget* WorldInventoryWidget;

	UPROPERTY(meta = (BindWidget))
		UInventoryPanel* PlayerInventoryPanel;

	bool bIsWorldInventoryVisbal;

	bool bIsDragging;

public:
	void SetWorldInventoryWidgetVisibility();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void UpdateDragging();

public:
	void GetCursorPosition(FVector2D& MousePosition) const;
};
