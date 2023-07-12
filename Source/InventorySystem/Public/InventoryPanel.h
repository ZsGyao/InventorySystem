// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPanel.generated.h"

class UGridPanel;
class UTextBlock;
class UWrapBox;
class UInventoryItemSlot;
class UInventoryComponent;
class AInventorySystemCharacter;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	// UWrapBox是线性布局容器 用于在水平或垂直方向上自动排列子控件。它按顺序放置子控件，并在空间不足时自动换行或换列
	/*UPROPERTY(meta = (BindWidget))
	UWrapBox* InventoryPanel;*/

	UPROPERTY(meta = (BindWidget))
		UGridPanel* InventoryGridPanel;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* WeightInfo;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CapacityInfo;

	UPROPERTY()
		AInventorySystemCharacter* PlayerCharacter;

	UPROPERTY()
		UInventoryComponent* InventoryReference;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UInventoryItemSlot> InventorySlotClass;

	bool bIsDragging;

	bool bIsInViewpoint;

public:
	UFUNCTION()
	void RefreshInventory();

protected:
	void SetInfoText() const;
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void GetCursorPosition(FVector2D& MousePosition) const;
	void UpdateDragging();

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;
};
