// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Actor/Item.h"
#include "GameMode/MyGameInstance.h"
#include "Components/SceneComponent.h"
#include "Projet2Character.generated.h"

USTRUCT()
struct FZoomData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Config)
		float MinCameraLen;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		float MaxCameraLen;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		float ZoomStepLen;
};

UCLASS(config=Game)
class AProjet2Character : public ACharacter
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FZoomData ZoomConfig;

public:
	AProjet2Character();
	
	UPROPERTY(EditAnywhere)
	USceneComponent* FP_FistLocation;
	
	UMyGameInstance* MyGameInstance;
	
	UPROPERTY(VisibleAnywhere)
	class AItem* CurrentItem;

	UPROPERTY(VisibleAnywhere)
	bool bIsHoldingItem;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	
protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Pick and Drop Item **/
	UFUNCTION()
	void PickItem();
	UFUNCTION()
	void DropItem();
	
	UFUNCTION(BlueprintCallable, Category = Camera)
	void ZoomIn();

	UFUNCTION(BlueprintCallable, Category = Camera)
	void ZoomOut();
	
	UFUNCTION(BlueprintCallable, Category = Menu)
	void Pause();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//OnBeginOverlap
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

