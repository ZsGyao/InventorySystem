// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystemHUD.h"
#include "MainMenu.h"
#include "InteractionWidget.h"
#include "InteractionInterface.h"
#include "InventoryPanel.h"

//#ifdef WITH_EDITOR
//#pragma optimize("", off)
//#endif

AInventorySystemHUD::AInventorySystemHUD()
{
	//if(MainMenuClass)
	//{
	//	MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
	//	MainMenuWidget->AddToViewport(5);
	//	MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	//}

	//if(InteractionWidgetClass)
	//{
	//	InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
	//	InteractionWidget->AddToViewport(-1);
	//	InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	//}
}

void AInventorySystemHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	//// new
	//if(InventoryPanelClass)
	//{
	//	InventoryPanel = CreateWidget<UInventoryPanel>(GetWorld(), InventoryPanelClass);
	//	InventoryPanel->AddToViewport(-1);
	//	InventoryPanel->SetVisibility(ESlateVisibility::Collapsed);
	//}
}

void AInventorySystemHUD::DisplayMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("In to Display Menu"));
	if (MainMenuWidget)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("Main Menu already set Visable"));
	}

}

void AInventorySystemHUD::HideMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("In to Hide Menu"));
	if(MainMenuWidget)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		UE_LOG(LogTemp, Warning, TEXT("Main Menu already set Collapsed"));
	}

}

void AInventorySystemHUD::ToggleMenu()
{
	if(bIsMenuVisible)
	{
		 HideMenu();
		
		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisplayMenu();
		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void AInventorySystemHUD::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AInventorySystemHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AInventorySystemHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if(IsValid((InteractionWidget)))
	{
		if(InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractableData);
	}
}

//void AInventorySystemHUD::ShowInventorySystemWidget() 
//{
//	// new
//	if (InventoryPanel)
//	{
//		bIsInventoryPanelVisible = true;
//		InventoryPanel->SetVisibility(ESlateVisibility::Visible);
//	}
//}
//
//void AInventorySystemHUD::HideInventorySystemWidget()
//{
//	// new
//	if (InventoryPanel)
//	{
//		bIsInventoryPanelVisible = false;
//		InventoryPanel->SetVisibility(ESlateVisibility::Collapsed);
//	}
//}
//
//void AInventorySystemHUD::ToggleInventoryMenu()
//{
//	if (bIsInventoryPanelVisible)
//	{
//		HideInventorySystemWidget();
//
//		const FInputModeGameOnly InputMode;
//		GetOwningPlayerController()->SetInputMode(InputMode);
//		GetOwningPlayerController()->SetShowMouseCursor(false);
//	}
//	else
//	{
//		ShowInventorySystemWidget();
//		const FInputModeGameAndUI InputMode;
//		GetOwningPlayerController()->SetInputMode(InputMode);
//		GetOwningPlayerController()->SetShowMouseCursor(true);
//	}
//}


//#ifdef WITH_EDITOR
//#pragma optimize("", on)
//#endif