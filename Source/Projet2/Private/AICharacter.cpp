// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "MyAIController1.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Initializing the pawn sensing component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degrees
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

	//Create socket to getItem
	FP_FistLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FistLocation"));
	FP_FistLocation->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	//Register the function that is going to fire when the character sees a Pawn
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnSeePlayer);
	}
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AMyAIController1* AIController = Cast<AMyAIController1>(GetController());
	
	if(bAIVisible == true)
	{
		if((GetWorld()->TimeSeconds - LastSeenTime) > TimeOut)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Je te vois PAS"));
			AIController->SetNotSeenTarget();
		}
	}

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::OnSeePlayer(APawn* InPawn)
{
	AMyAIController1* AIController = Cast<AMyAIController1>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{
		AIController->StopMovement();
		LastSeenTime = GetWorld()->GetTimeSeconds();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Je te vois"));
		AIController->SetSeenTarget(InPawn);
	}
}

void AAICharacter::Pick()
{
	if(!bHolding)
	{
		if(CurrentItem != nullptr)
		{
			CurrentItem->PickItem(this);
			GetCharacterMovement()->MaxWalkSpeed = 300;
			bHolding = true;
		}
	}
}

void AAICharacter::Drop()
{
	AMyAIController1* AIController = Cast<AMyAIController1>(GetController());

	if(bHolding)
	{
		if(CurrentItem != nullptr)
		{
			CurrentItem->DropItem();
			GetCharacterMovement()->MaxWalkSpeed = 600;
			bHolding = false;
		}
	}
}

void AAICharacter::ReturnItem()
{
	AMyAIController1* AIController = Cast<AMyAIController1>(GetController());
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();

	float Distance = GetDistanceTo(CurrentItem);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Distance: %f"), Distance));

	if (Distance <= 1500.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Je return item"));
		BlackboardComp->SetValueAsObject("LocationToGo", CurrentItem);
		BlackboardComp->SetValueAsBool("bCanPick", true);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Je return spawn"));
		BlackboardComp->SetValueAsObject("LocationToGo", Spawn);
		BlackboardComp->SetValueAsBool("bCanPick", false);
		Destroy();
	}
}