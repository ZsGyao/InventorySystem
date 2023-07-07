// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPanel.h"

#include "InventoryComponent.h"
#include "InventoryItemSlot.h"
#include "InventorySystemCharacter.h"
#include "ItemBase.h"
#include "ItemDragDropOperation.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

void UInventoryPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PlayerCharacter = Cast<AInventorySystemCharacter>(GetOwningPlayerPawn());
	if(PlayerCharacter)
	{
		InventoryReference = PlayerCharacter->GetInventory();
		if(InventoryReference)
		{
			InventoryReference->OnInventoryUpdated.AddUObject(this, &UInventoryPanel::RefreshInventory);
			SetInfoText();
		}
	}
}

void UInventoryPanel::SetInfoText() const
{
	WeightInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
		InventoryReference->GetInventoryTotalWeight(),
		InventoryReference->GetWeightCapacity()));

	CapacityInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
		InventoryReference->GetInventoryContents().Num(),
		InventoryReference->GetSlotsCapacity()));
}


void UInventoryPanel::RefreshInventory()
{
	if(InventoryReference && InventorySlotClass)
	{
		// InventoryPanel->ClearChildren();
		while(InventoryGridPanel->GetChildrenCount() > 0)
		{
			UWidget* ChildWidget = InventoryGridPanel->GetChildAt(0);
			InventoryGridPanel->RemoveChild(ChildWidget);
			ChildWidget->RemoveFromParent();
		}

		const int32 NumColumns = 4;

		for (int32 Index = 0; Index < InventoryReference->GetInventoryContents().Num(); Index++)
		{
			const int32 ItemNumRows = Index / NumColumns;
			const int32 ItemNumColumns = Index % NumColumns;

			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, InventorySlotClass);

			ItemSlot->SetColumnNum(ItemNumColumns);
			ItemSlot->SetRowNum(ItemNumRows);

			ItemSlot->SetItemReference(InventoryReference->GetInventoryContents()[Index]);
			InventoryGridPanel->AddChildToGrid(ItemSlot, ItemNumRows, ItemNumColumns);
		}

		//for(UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		//{
		//	UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, InventorySlotClass);
		//	ItemSlot->SetItemReference(InventoryItem);
		//	InventoryGridPanel->AddChildToGrid(ItemSlot, Ite);
		////	InventoryPanel->AddChildToWrapBox(ItemSlot);
		//}
		SetInfoText();
	}
}

bool UInventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	if(ItemDragDrop->SourceItem && InventoryReference)
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected an item drop on InventoryPanel."))

		if(ItemDragDrop->SourceInventory == PlayerCharacter->GetWorldInventory())
		{
			PlayerCharacter->DropItemFromWorldPanelToPlayPanel(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->Quantity);
		}

		return true;
	}
	return false;
}
