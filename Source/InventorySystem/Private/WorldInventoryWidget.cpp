// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldInventoryWidget.h"


#include "InventoryComponent.h"
#include "InventoryItemSlot.h"
#include "InventorySystemCharacter.h"
#include "ItemBase.h"
#include "ItemDragDropOperation.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

void UWorldInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PlayerCharacter = Cast<AInventorySystemCharacter>(GetOwningPlayerPawn());
	if (PlayerCharacter)
	{
		InventoryReference = PlayerCharacter->GetWorldInventory();
		if (InventoryReference)
		{
			InventoryReference->OnInventoryUpdated.AddUObject(this, &UWorldInventoryWidget::RefreshInventory);
			SetInfoText();
		}
	}
}

void UWorldInventoryWidget::SetInfoText() const
{
	WeightInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
		InventoryReference->GetInventoryTotalWeight(),
		InventoryReference->GetWeightCapacity()));

	CapacityInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
		InventoryReference->GetInventoryContents().Num(),
		InventoryReference->GetSlotsCapacity()));
}


void UWorldInventoryWidget::RefreshInventory()
{
	if (InventoryReference && InventorySlotClass)
	{
		InventoryPanel->ClearChildren();

		for (UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		{
			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, InventorySlotClass);
			ItemSlot->SetItemReference(InventoryItem);

			InventoryPanel->AddChildToWrapBox(ItemSlot);
		}
		SetInfoText();
	}
}

bool UWorldInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	if (ItemDragDrop->SourceItem && InventoryReference)
	{
		// todo  move the item slot
		UE_LOG(LogTemp, Warning, TEXT("Detected an item drop on World Inventory Panel, which means the Item slot should move."))

		//todo 增加在WorldInventory中增加Slot的功能，同时需要减少另一个的Slot,实际上只要完成对Inventory数量的修改。
		if(ItemDragDrop->SourceInventory == PlayerCharacter->GetInventory())
		{
			PlayerCharacter->DropItemFromPlayPanelToWorldPanel(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->Quantity);
		}

		return true;
	}
	return false;
}