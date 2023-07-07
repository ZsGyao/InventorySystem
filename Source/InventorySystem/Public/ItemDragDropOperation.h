// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

class UInventoryItemSlot;
class UInventoryComponent;
class UItemBase;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY()
		UItemBase* SourceItem;

	UPROPERTY()
		UInventoryComponent* SourceInventory;

	UPROPERTY()
		UInventoryItemSlot* SourceItemSlot;
};
