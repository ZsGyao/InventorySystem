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

FReply UMainMenu::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	// UE_LOG(LogTemp, Warning, TEXT("Into Main Menu NativeOnMouseMove"));

	// 不管在哪都可以检测到位置
	FVector2D MousePosition = FVector2D();
	GetCursorPosition(MousePosition);

	if (PlayerInventoryPanel->bIsDragging)
	{
		UE_LOG(LogTemp, Warning, TEXT("Into Main Menu NativeOnMouseMove, bIsDragging is {%d};"), PlayerInventoryPanel->bIsDragging);

		UpdateDragging();
		// return FReply::Handled();
		return FReply::Unhandled();
	}
	return FReply::Unhandled();
}


void UMainMenu::UpdateDragging()
{

	FVector2D MousePosition = FVector2D();
	GetCursorPosition(MousePosition);

	PlayerCharacter->CursorMousePosition = MousePosition;

	UE_LOG(LogTemp, Warning, TEXT("Save MousePosition to Character， the MousePosition.X: {%f}, Y: {%f}"), MousePosition.X, MousePosition.Y);

	if(!PlayerInventoryPanel->bIsInViewpoint) 
	{
		PlayerInventoryPanel->RemoveFromParent();
		PlayerInventoryPanel->AddToViewport(300);
		PlayerInventoryPanel->bIsInViewpoint = true;
	}

	PlayerInventoryPanel->SetPositionInViewport(MousePosition);
	UE_LOG(LogTemp, Warning, TEXT("PlayerInventoryPanel is in {%p} --- should in Viewport"), PlayerInventoryPanel->GetParent());
}
//
void UMainMenu::GetCursorPosition(FVector2D& MousePosition) const
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

