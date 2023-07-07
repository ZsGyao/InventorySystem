// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemSlot.generated.h"

class UImage;
class UTextBlock;
class UBorder;
class UInventoryTooltip;
class UDragItemVisual;
class UItemBase;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Inventory Slot")
		TSubclassOf<UDragItemVisual> DragItemVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
		TSubclassOf<UInventoryTooltip> TooltipClass;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
		UItemBase* ItemReference;

	UPROPERTY(EditAnywhere, Category = "Inventory Slot", meta = (BindWidget))
		UBorder* ItemBorder;

	UPROPERTY(EditAnywhere, Category = "Inventory Slot", meta=(BindWidget))
		UImage* ItemIcon;

	UPROPERTY(EditAnywhere, Category = "Inventory Slot", meta = (BindWidget))
		UTextBlock* ItemQuantity;

	int32 RowNum;
	int32 ColumnNum;
public:
	FORCEINLINE void SetItemReference(UItemBase* ItemIn) { ItemReference = ItemIn; }
	FORCEINLINE UItemBase* GetItemReference() const { return ItemReference; }

	FORCEINLINE int32 GetRowNum() const { return RowNum; }
	FORCEINLINE int32 GetColumnNum() const { return ColumnNum; }
	FORCEINLINE void SetRowNum(const int32 RowNum1) { this->RowNum = RowNum1; }
	FORCEINLINE void SetColumnNum(const int32 ColumnNum1) { this->ColumnNum = ColumnNum1; }

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;
};
