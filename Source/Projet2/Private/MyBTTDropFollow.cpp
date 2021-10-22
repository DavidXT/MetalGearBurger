// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTDropFollow.h"

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTDropItem.h"
#include "MyAIController1.h"

EBTNodeResult::Type UMyBTTDropFollow::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController1* AICon = Cast<AMyAIController1>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		if(AICon->AIChar)
		{
			if(AICon->CurrentPoint->IsA(ATargetActor::StaticClass()))
			{
				if(((ATargetActor*)AICon->CurrentPoint)->bHasItem == false)
				{
					AICon->AIChar->Drop();
					AICon->SetItemPosition(AICon->AIChar->CurrentItem->GetActorLocation());
				}
			}
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}