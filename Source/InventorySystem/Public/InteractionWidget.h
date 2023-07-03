// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

struct FInteractableData;
class AInventorySystemCharacter;
class UTextBlock;
class UProgressBar;

UCLASS()
class INVENTORYSYSTEM_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Player Reference")
		AInventorySystemCharacter* PlayerReference;

	void UpdateWidget(const FInteractableData* InteractableData) const;

protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = "Interaction Widget | Interaction Data")
	UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	UTextBlock* ActionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	UTextBlock* QuantityText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	UTextBlock* KeyPressText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	UProgressBar* InteractionProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	float CurrentInteractionDuration;

	UFUNCTION(Category = "Interaction Widget | Interaction Data")
	float UpdateInteractionProgress();

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
};
