// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/MyGameState.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "AnimInstance1.generated.h"
/**
 * 
 */
UCLASS(Transient, Blueprintable, HideCategories=AnimInstance, Blueprintable)
class UAnimInstance1: public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnimInstance1();

	AMyGameState* MyGameState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Generic")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Generic")
	bool bIsHoldingItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Generic")
	bool bIsWin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Generic")
	bool bIsLose;
	
	UPROPERTY(EditDefaultsOnly, Category = animation)
	UAnimSequence* animPickUp;



	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
