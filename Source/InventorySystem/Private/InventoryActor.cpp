// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryActor.h"

#include "InventoryPanel.h"
#include "InventorySystemHUD.h"

// Sets default values
AInventoryActor::AInventoryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void AInventoryActor::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AInventorySystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	InteractableData = InventoryInstanceData;
	
}

void AInventoryActor::BeginFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void AInventoryActor::EndFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void AInventoryActor::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory Actor begin interact --------"));
	// todo bind the press E to interact 
	// HUD->ShowOrHidePanelWidget();
	// todo 现在调用这个函数，只能在MainMenu存在的时候显示和关闭WorldInventory，后续要在MainMenu不存在的情况也能开关
	HUD->ShowOrHideMMInventoryVisible();
}

void AInventoryActor::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory Actor end interact --------"));
}

void AInventoryActor::Interact(AInventorySystemCharacter* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory Actor is interacting --------"));
}


