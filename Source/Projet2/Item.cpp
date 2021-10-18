// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Projet2Character.h"



// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	RootComponent = Mesh;
	
	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));
	Collider->SetupAttachment(Mesh);

	FoodValue = 1;
	
	bHolding = false;
	bGravity = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AItem::OnEndOverlap);
}

void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AProjet2Character::StaticClass()))
	{
		if(((AProjet2Character*)OtherActor)->currentItem == nullptr)
		{
			((AProjet2Character*)OtherActor)->currentItem = this;
		}

	}
}

void AItem::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if(OtherActor->IsA(AProjet2Character::StaticClass()))
	{
		if(((AProjet2Character*)OtherActor)->currentItem == this){
			((AProjet2Character*)OtherActor)->currentItem = nullptr;
		}

	}
}

void AItem::PickItem()
{
	bHolding = true;
	bGravity = false;
	Mesh->SetEnableGravity(bGravity);
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	AttachToComponent(((AProjet2Character*)Player)->FP_FistLocation,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AItem::DropItem()
{
	bHolding = false;
	bGravity = true;
	Mesh->SetEnableGravity(bGravity);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}



// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bHolding==true)
	{
		Player = GetWorld()->GetFirstPlayerController()->GetPawn();
		if(Player->IsA(AProjet2Character::StaticClass()))
		{
			//TargetPosition = ((AProjet2Character*)Player)->FP_FistLocation->GetComponentLocation();
			//SetActorLocationAndRotation(TargetPosition,GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation());
			RootComponent->SetupAttachment(((AProjet2Character*)Player)->Mesh1E);
		}
	}
	
}

