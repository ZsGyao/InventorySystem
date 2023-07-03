// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystemHUD.h"
#include "MainMenu.h"
#include "InteractionWidget.h"
#include "InteractionInterface.h"

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
}

void AInventorySystemHUD::DisplayMenu()
{
	if(MainMenuWidget)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AInventorySystemHUD::HideMenu()
{
	if(MainMenuWidget)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
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


//#ifdef WITH_EDITOR
//#pragma optimize("", on)
//#endif