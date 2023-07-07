// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InteractionInterface.h"
#include "InventorySystemCharacter.generated.h"

class UTimelineComponent;
class UItemBase;
class UInventoryComponent;
class AInventorySystemHUD;

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f)
	{
		
	}

	UPROPERTY()
		AActor* CurrentInteractable;

	UPROPERTY()
		float LastInteractionCheckTime;
};

UCLASS(config=Game)
class AInventorySystemCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	bool bAiming;

protected:
	UPROPERTY()
		AInventorySystemHUD* HUD;

	// 可以保存所有实现了IInteractionInterface接口的实例
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
		TScriptInterface<IInteractionInterface> TargetInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Character | Inventory")
		UInventoryComponent* PlayerInventory;

	// new the Inventory in world, Inventory Actor
	UPROPERTY(VisibleAnywhere, Category = "Character | Inventory In World Actor")
		UInventoryComponent* WorldInventory;

	// interaction properties
	float InteractionCheckFrequency;
	float InteractionCheckDistance;
	//管理和控制计时器的结构体
	FTimerHandle TimerHandle_Interaction;
	FInteractionData InteractionData;

	// timeline properties used for camera aiming transiting
	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
		FVector DefaultCameraLocation;
	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
		FVector AimingCameraLocation;

	TObjectPtr<UTimelineComponent> AimingCameraTimeline;

	UPROPERTY(EditDefaultsOnly, Category = "Character | Aim Timeline")
		UCurveFloat* AimingCameraCurve;

public:
	AInventorySystemCharacter();
	
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); }

	FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory;  }
	FORCEINLINE UInventoryComponent* GetWorldInventory() const { return WorldInventory; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void UpdateInteractionWidget() const;

	void DropItem(UItemBase* ItemToDrop, const int32 Quantity);

	void DropItemFromPlayPanelToWorldPanel(UItemBase* ItemDrop, const int32 Quantity);

	void DropItemFromWorldPanelToPlayPanel(UItemBase* ItemDrop, const int32 Quantity);
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void ToggleMenu();

	void Aim();
	void StopAiming();
	UFUNCTION()
	void UpdateCameraTimeline(float TimelineValue) const;
	UFUNCTION()
	void CameraTimelineEnd();

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();
	
};

