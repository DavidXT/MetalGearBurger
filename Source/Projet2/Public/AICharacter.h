// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "MyAIController1.h"
#include "Perception/PawnSensingComponent.h"
#include "AICharacter.generated.h"

UCLASS()
class PROJET2_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

	UFUNCTION()
void OnSeePlayer(APawn* InPawn);
	
public:
	
	/*The Behavior Tree of the Character*/
	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviorTree;

	/*The Component which is used for the "seeing" sense of the AI*/
	UPROPERTY(VisibleAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComp;
	
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};