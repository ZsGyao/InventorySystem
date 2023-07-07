// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "ItemBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

UItemBase* UInventoryComponent::FindMatchingItem(UItemBase* ItemIn) const
{
	 if(ItemIn)
	 {
		 if(InventoryContents.Contains(ItemIn))
		 {
			 return ItemIn;
		 }
	 }
	 return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(UItemBase* ItemIn) const
{
	if(ItemIn)
	{
		if(const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}
	return  nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(UItemBase* ItemIn) const
{
	if(const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByPredicate([&ItemIn](const UItemBase* InventoryItem)
	{
			return InventoryItem->ID == ItemIn->ID && !InventoryItem->IsFullItemStack();
	}))
	{
		return *Result;
	}
	return nullptr;
}	

int32 UInventoryComponent::CalculateWeightAddAmount(UItemBase* ItemIn, const int32 RequestedAddAmount) const
{
	const int32 WeightMaxAddAmount = FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) / ItemIn->GetItemSingleWeight());
	if (WeightMaxAddAmount >= RequestedAddAmount)
	{
		return RequestedAddAmount;
	}
	return WeightMaxAddAmount;
}

int32 UInventoryComponent::CalculateNumberForFullStack(UItemBase* ItemIn, int32 InitialRequestedAddAmount) const
{
	const int32 AddAmountToMakeFullStack = ItemIn->NumericData.MaxStackSize - ItemIn->Quantity;

	return FMath::Min(InitialRequestedAddAmount, AddAmountToMakeFullStack);
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemIn)
{
	InventoryContents.RemoveSingle(ItemIn);
	OnInventoryUpdated.Broadcast();
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* ItemIn, const int32 DesiredAmountToRemove)
{
	const int32 ActualAmountToRemove = FMath::Min(DesiredAmountToRemove, ItemIn->Quantity);

	ItemIn->SetQuantity(ItemIn->Quantity - ActualAmountToRemove);

	InventoryTotalWeight -= ActualAmountToRemove * ItemIn->GetItemSingleWeight();

	OnInventoryUpdated.Broadcast();

	return ActualAmountToRemove;
}

void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
	if(InventoryContents.Num() + 1 <= InventorySoltsCapacity)
	{
		RemoveAmountOfItem(ItemIn, AmountToSplit);
		AddNewItem(ItemIn, AmountToSplit);
	}
}

FItemAddResult UInventoryComponent::HandleNonStackableItems(UItemBase* ItemIn)
{
	UE_LOG(LogTemp, Warning, TEXT("HandleNonStackableItems"));
	// check if in the input item has valid weight
	if(FMath::IsNearlyZero(ItemIn->GetItemSingleWeight()) || ItemIn->GetItemSingleWeight() < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not add {0} to the inventory. Item is invalid weight value."));
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to the inventory. Item is invalid weight value."), ItemIn->TextData.Name));
	}

	// will the item weight overflow weight capacity
	if(InventoryTotalWeight + ItemIn->GetItemSingleWeight() > GetWeightCapacity())
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not add {0} to the inventory. Item weight is overflow weight capacity."));
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to the inventory. Item weight is overflow weight capacity."), ItemIn->TextData.Name));
	}

	if(InventoryContents.Num() + 1 > InventorySoltsCapacity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not add {0} to the inventory. Inventory slot is full."));
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to the inventory. Inventory slot is full."), ItemIn->TextData.Name));
	}

	AddNewItem(ItemIn, 1);
	return FItemAddResult::AddedAll(1, FText::Format(
		FText::FromString("Successful add 1 {0} to the inventory.") ,ItemIn->TextData.Name));
}

int32 UInventoryComponent::HandleStackableItem(UItemBase* ItemIn, int32 RequestedAddAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("try to Handle StackanleItem"));

	if (RequestedAddAmount <= 0 || FMath::IsNearlyZero(ItemIn->GetItemStackWeight()))
	{
		// invalid item data
		return 0;
	}

	int32 AmountToDistribute = RequestedAddAmount;

	UItemBase* ExistingItem = FindNextPartialStack(ItemIn);

	// distribute item stack over existing stacks
	while(ExistingItem)
	{
		const int32 AmountToMakeFullStack = CalculateNumberForFullStack(ExistingItem, AmountToDistribute);
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount(ExistingItem, AmountToMakeFullStack);

		if (WeightLimitAddAmount > 0)
		{
			ExistingItem->SetQuantity(ExistingItem->Quantity + WeightLimitAddAmount);
			InventoryTotalWeight += (ExistingItem->GetItemSingleWeight() * WeightLimitAddAmount);

			AmountToDistribute -= WeightLimitAddAmount;

			ItemIn->SetQuantity(AmountToDistribute);

			// Refine this logic since going over weight capacity should not ever be possible
			if(InventoryTotalWeight >= InventoryWeightCapacity)
			{
				OnInventoryUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}
		}
		else if (WeightLimitAddAmount <= 0)
		{
			if (AmountToDistribute != RequestedAddAmount)
			{
				OnInventoryUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}
			return 0;
		}

		if(AmountToDistribute <= 0)
		{
			OnInventoryUpdated.Broadcast();
			return RequestedAddAmount;
		}

		ExistingItem = FindNextPartialStack(ItemIn);
	}

	// no more partial stacks found, check if a new stack can be added
	if(InventoryContents.Num() + 1 <= InventorySoltsCapacity)
	{
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount(ItemIn, AmountToDistribute);

		if(WeightLimitAddAmount > 0)
		{
			if(WeightLimitAddAmount < AmountToDistribute)
			{
				AmountToDistribute -= WeightLimitAddAmount;
				ItemIn->SetQuantity(AmountToDistribute);

				AddNewItem(ItemIn->CreateItemCopy(), WeightLimitAddAmount);
				return RequestedAddAmount - AmountToDistribute;
			}

			AddNewItem(ItemIn, AmountToDistribute);
			return  RequestedAddAmount;
		}
	}

	OnInventoryUpdated.Broadcast();
	return RequestedAddAmount - AmountToDistribute;
}

FItemAddResult UInventoryComponent::HandleAddItem(UItemBase* InputItem)
{
	UE_LOG(LogTemp, Error, TEXT("X"));
	if (GetOwner())
	{
		const int32 InitialRequestedAddAmount = InputItem->Quantity;

		// handle non-stackable items
		if (!InputItem->NumericData.bIsStackable)
		{
			return HandleNonStackableItems(InputItem);
		}

		// handle stackable
		const int32 StackableAmountAdded = HandleStackableItem(InputItem, InitialRequestedAddAmount);

		if (StackableAmountAdded == InitialRequestedAddAmount)
		{
			return FItemAddResult::AddedAll(InitialRequestedAddAmount, FText::Format(
				FText::FromString(" Add {0} {1} to the inventory."), InitialRequestedAddAmount, InputItem->TextData.Name));

		}

		if (StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
		{
			// return added partial result
			return FItemAddResult::AddedPartial(StackableAmountAdded, FText::Format(
				FText::FromString("Partial amount of {0} added to the inventory. Number added = {1}"), InputItem->TextData.Name, InitialRequestedAddAmount));
		}

		if (StackableAmountAdded <= 0)
		{
			//return added none result
			return FItemAddResult::AddedNone(FText::Format(
				FText::FromString("Could not add {0} to the inventory. No remaining inventory slots, or invalid item"), InputItem->TextData.Name));
		}
	}

	check(false);
	return FItemAddResult::AddedNone(FText::Format(
		FText::FromString("Could not add {0} to the inventory. No remaining inventory slots, or invalid item."), InputItem->TextData.Name));
}

void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("AddNewItem"));
	UItemBase* NewItem;

	if(Item->bIsCopy || Item->bIsPickup)
	{
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		// used when splitting or dragging to/from another inventory
		NewItem = Item->CreateItemCopy();
	}

	NewItem->OwningInventory = this;
	NewItem->SetQuantity(Amount);

	InventoryContents.Add(NewItem);
	InventoryTotalWeight += NewItem->GetItemStackWeight();
	OnInventoryUpdated.Broadcast();
}




