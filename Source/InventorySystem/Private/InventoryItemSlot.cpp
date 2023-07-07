// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemSlot.h"

#include <string>

#include "DragItemVisual.h"
#include "InventoryPanel.h"
#include "InventorySystemHUD.h"
#include "InventoryTooltip.h"
#include "ItemBase.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemDragDropOperation.h"
#include "MainMenu.h"
#include "Components/GridPanel.h"

void UInventoryItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(TooltipClass)
	{
		UInventoryTooltip* Tooltip = CreateWidget<UInventoryTooltip>(this, TooltipClass);
		Tooltip->InventorySlotBeingHovered = this;
		// 设置控件的提示文本
		SetToolTip(Tooltip);
	}
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if(ItemReference)
	{
		switch (ItemReference->ItemQuality)
		{
		case EItemQuality::Shoddy:
			ItemBorder->SetBrushColor(FLinearColor::Gray);

			break;
		case EItemQuality::Common:
			ItemBorder->SetBrushColor(FLinearColor::Blue);

			break;
		case EItemQuality::Quality:
			ItemBorder->SetBrushColor(FLinearColor(218.0f, 112.0f, 214.0f)); // purple

			break;
		case EItemQuality::Masterwork:
			ItemBorder->SetBrushColor(FLinearColor(100.0f, 65.9f, 0.0f, 1.0f)); // orange

			break;
		case EItemQuality::Grandmaster:
			ItemBorder->SetBrushColor(FLinearColor(255.0f, 51.0f, 51.0f)); // red

			break;
		default: ;
		}

		ItemIcon->SetBrushFromTexture(ItemReference->AssertData.Icon);

		if(ItemReference->NumericData.bIsStackable)
		{
			ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
		}
		else
		{
			ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Reply =  Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	// submenu on right click will happen here

	return Reply.Unhandled();
}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if(DragItemVisualClass)
	{
		const TObjectPtr<UDragItemVisual> DragVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualClass);
		DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->AssertData.Icon);
		DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());
		DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));

		UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
		DragItemOperation->SourceItem = ItemReference;
		DragItemOperation->SourceInventory = ItemReference->OwningInventory;

		DragItemOperation->SourceItemSlot = this;

		DragItemOperation->DefaultDragVisual = DragVisual;
		DragItemOperation->Pivot = EDragPivot::TopLeft;

		OutOperation = DragItemOperation;
	}
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);
	UE_LOG(LogTemp, Warning, TEXT("Drop Into ItemSlot, Source ItemSlot -> RowNum: {%d}, ColoumNum: {%d}; Aim ItemSlot -> RowNum: {%d}, ColoumNum: {%d}"), 
		ItemDragDrop->SourceItemSlot->GetRowNum(), ItemDragDrop->SourceItemSlot->GetColumnNum(),
		this->GetRowNum(), this->GetColumnNum());

	if(ItemDragDrop->SourceItemSlot == this)
	{
		return false;
	}
	
	UInventoryItemSlot* ItemSlotTemp = this;

	const int32 SourceRow = ItemDragDrop->SourceItemSlot->GetRowNum();
	const int32 SourceColumn = ItemDragDrop->SourceItemSlot->GetColumnNum();
	const int32 AimRow = this->GetRowNum();
	const int32 AimColumn = this->GetColumnNum();

	auto HUD = Cast<AInventorySystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	UInventoryPanel* InventoryPanel = HUD->GetMainMenu()->PlayerInventoryPanel;
	InventoryPanel->InventoryGridPanel->AddChildToGrid(ItemDragDrop->SourceItemSlot, AimRow, AimColumn);
	InventoryPanel->InventoryGridPanel->AddChildToGrid(ItemSlotTemp, SourceRow, SourceColumn);

	this->SetRowNum(SourceRow);
	this->SetColumnNum(SourceColumn);

	ItemDragDrop->SourceItemSlot->SetRowNum(AimRow);
	ItemDragDrop->SourceItemSlot->SetColumnNum(AimColumn);

	return true;
}
