// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GridWidget.generated.h"

class UBorder;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UGridWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere, Category = "Grid | GridBroder", meta=(BindWidget))
		UBorder* GridBorder;
};
