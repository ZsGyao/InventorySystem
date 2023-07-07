// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldInventoryWidget.generated.h"

class UInventoryItemSlot;
class UInventoryComponent;
class AInventorySystemCharacter;
class UTextBlock;
class UWrapBox;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UWorldInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		UWrapBox* InventoryPanel;

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
public:
	UFUNCTION()
		void RefreshInventory();

protected:
	void SetInfoText() const;
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
