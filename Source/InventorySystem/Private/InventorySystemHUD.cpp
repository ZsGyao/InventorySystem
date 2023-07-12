// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystemHUD.h"
#include "MainMenu.h"
#include "InteractionWidget.h"
#include "InteractionInterface.h"
#include "WorldInventoryWidget.h"
#include "InventorySystemCharacter.h"

//#ifdef WITH_EDITOR
//#pragma optimize("", off)
//#endif

AInventorySystemHUD::AInventorySystemHUD()
{
	
}

void AInventorySystemHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		PlayerInventoryPanel = MainMenuWidget->PlayerInventoryPanel;
	}

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (CrosshairWidgetClass)
	{
		CrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
		CrosshairWidget->AddToViewport();
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(WorldInventoryWidgetClass)
	{
		WorldInventoryWidget = CreateWidget<UWorldInventoryWidget>(GetWorld(), WorldInventoryWidgetClass);
		WorldInventoryWidget->AddToViewport(4);
		WorldInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

}

void AInventorySystemHUD::DisplayMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("In to Display Menu"));
	if (MainMenuWidget)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("Main Menu already set Visable"));
		PlayerInventoryPanel->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("The PlayerInventoryPanel in HUD already set Visable"));
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
		PlayerInventoryPanel->SetVisibility(ESlateVisibility::Collapsed);
		UE_LOG(LogTemp, Warning, TEXT("The PlayerInventoryPanel in HUD already set Collapsed"));
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

void AInventorySystemHUD::ShowCrosshair()
{
	if(CrosshairWidget)
	{
		CrosshairWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AInventorySystemHUD::HideCrosshair()
{
	if (CrosshairWidget)
	{
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AInventorySystemHUD::ShowOrHidePanelWidget()
{
	if (!bIsPanelVisible)
	{
		WorldInventoryWidget->SetVisibility(ESlateVisibility::Visible);
		bIsPanelVisible = true;
	}
	else
	{
		WorldInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		bIsPanelVisible = false;
	}
}

void AInventorySystemHUD::ShowOrHideMMInventoryVisible() const
{
	if(MainMenuWidget)
	{
		MainMenuWidget->SetWorldInventoryWidgetVisibility();
	}
}


//#ifdef WITH_EDITOR
//#pragma optimize("", on)
//#endif
