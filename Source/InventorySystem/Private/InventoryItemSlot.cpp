// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemSlot.h"

#include "InventoryTooltip.h"
#include "ItemBase.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

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
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
