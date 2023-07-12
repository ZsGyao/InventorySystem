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

FReply UInventoryPanel::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Warning, TEXT("Into InventoryPanel NativeOnMouseButtonDown"));

	// 如果鼠标按下的位置在InventoryPanel内
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("Start Dragging, the pisition from Butten down"));
		// 按下确定拖拽
		bIsDragging = true;

		return FReply::Handled();
	}

	return  FReply::Unhandled();
}

FReply UInventoryPanel::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("Into Inventory NativeOnMouseButton UP UP UP"));

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		 //UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonUp, the Mouse Butten will up soon"));

		bIsDragging = false;
		UE_LOG(LogTemp, Warning, TEXT("Stop Dragging,the bIsDragging is: {%d} "), bIsDragging);
		Reply = FReply::Handled();
	}

	return Reply;
}

FReply UInventoryPanel::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// todo 只有在InventoryPanel中才更新坐标？
	FVector2D MousePosition = FVector2D();
	GetCursorPosition(MousePosition);

	if (bIsDragging && this->IsHovered())
	{
		UE_LOG(LogTemp, Warning, TEXT("Into Main Menu NativeOnMouseMove, bIsDragging is {%d};"), bIsDragging);

		UpdateDragging();
		return FReply::Handled();
	 }
	return FReply::Unhandled();
}

void UInventoryPanel::GetCursorPosition(FVector2D& MousePosition) const
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc)
	{
		ULocalPlayer* LocalPlayer = pc->GetLocalPlayer();
		if (LocalPlayer && LocalPlayer->ViewportClient)
		{
			if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
			{
				UE_LOG(LogTemp, Warning, TEXT("Cursor.position X :  %f , Y : %f"), MousePosition.X, MousePosition.Y);
			}
		}
	}
}

void UInventoryPanel::UpdateDragging()
{
	FVector2D MousePosition = FVector2D();
	GetCursorPosition(MousePosition);
	if(!bIsInViewpoint)
	{
		this->RemoveFromParent();
		this->AddToViewport(300);
		bIsInViewpoint = true;
	}

	this->SetPositionInViewport(MousePosition);
	//this->SetPositionInViewport(PlayerCharacter->CursorMousePosition);
	UE_LOG(LogTemp, Warning, TEXT("SetPositionInViewport in X: {%f}, Y: {%f}"), PlayerCharacter->CursorMousePosition.X, PlayerCharacter->CursorMousePosition.Y);
}

void UInventoryPanel::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);


}
