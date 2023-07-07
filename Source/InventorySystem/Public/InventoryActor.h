// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "InventoryActor.generated.h"

class AInventorySystemHUD;
class UInventoryPanel;

UCLASS()
class INVENTORYSYSTEM_API AInventoryActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Inventory Actor")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, Category = "Inventory Actor")
		FInteractableData InventoryInstanceData;

	UPROPERTY()
		AInventorySystemHUD* HUD;

public:	
	// Sets default values for this actor's properties
	AInventoryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;
	virtual void Interact(AInventorySystemCharacter* PlayerCharacter) override;

};
