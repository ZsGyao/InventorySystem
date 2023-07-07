// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "InventorySystemCharacter.h"
#include "ItemBase.h"
#include "ItemDragDropOperation.h"
#include "WorldInventoryWidget.h"
#include "GridWidget.h"

void UMainMenu::SetWorldInventoryWidgetVisibility()
{
	if(WorldInventoryWidget)
	{
		if(bIsWorldInventoryVisbal)
		{
			WorldInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
			bIsWorldInventoryVisbal = false;
		}
		else
		{
			WorldInventoryWidget->SetVisibility(ESlateVisibility::Visible);
			bIsWorldInventoryVisbal = true;
		}
	}
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = Cast<AInventorySystemCharacter>(GetOwningPlayerPawn());

	if(WorldInventoryWidget)
	{
		WorldInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		bIsWorldInventoryVisbal = false;
	}
}

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

bool UMainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	// cast operation to item drag drop, ensure player is valid, call drop item on player
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	if (PlayerCharacter && ItemDragDrop->SourceItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected an item drop on MainMenu"));

		PlayerCharacter->DropItem(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->Quantity);
		return true;
	}
	return false;
}
