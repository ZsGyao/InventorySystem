// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataStructs.h"
#include "InventorySystemCharacter.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	/*UPROPERTY()
		UInventoryComponent* OwningInventory;*/

	UPROPERTY(VisibleAnywhere, Category = "Item")
		int32 Quantity;

	UPROPERTY(EditAnywhere, Category = "Item")
		FName ID;

	UPROPERTY(EditAnywhere, Category = "Item")
		EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item")
		EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item")
		FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category = "Item")
		FItemNumericData NumericData;

	UPROPERTY(EditAnywhere, Category = "Item")
		FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Item")
		FItemAssertData AssertData;

public:
	UItemBase();

	UItemBase* CreateItemCopy() const;

	UFUNCTION(Category="Item")
	FORCEINLINE float GetItemStackWeight() const
	{
		return Quantity * NumericData.Weight;
	}

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const
	{
		return NumericData.Weight;
	}

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const
	{
		return Quantity == NumericData.MaxStackSize;
	}

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(AInventorySystemCharacter* Character);

protected:
	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}
};
