// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTreeTask/BTTargetPointSelection.h"
#include "Actor/BotTargetPoint.h"
#include "IA/MyAIController1.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController1* AICon = Cast<AMyAIController1>(OwnerComp.GetAIOwner());
 
	/*If the Controller is valid:
	1)Get the Blackboard Component and the Current Point of the bot
	2)Search for the next point, which will be different from the Current Point*/
	if (AICon)
	{
       if(AICon->CurrentNbMove <= AICon->NbMoveMax)
       {
       	ATargetActor* CurrentPoint = Cast<ATargetActor>(AICon->GetBlackboardComp()->GetValueAsObject("LocationToGo"));
 
       	TArray<AActor*> AvailableTargetPoints = AICon->GetAvailableTargetPoints();
       
       	//This variable will contain a random index in order to determine the next possible point
       	int32 RandomIndex;
 
       	//Here, we store the possible next target point
       	ATargetActor* NextTargetPoint = nullptr;
 
       	//Find a next point which is different from the current one
       	do
       	{
       		RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num()-1);
       		//Remember that the Array provided by the Controller function contains AActor* objects so we need to cast.
       		NextTargetPoint = Cast<ATargetActor>(AvailableTargetPoints[RandomIndex]);
       	} while (CurrentPoint == NextTargetPoint);
 
       	//Update the next location in the Blackboard so the bot can move to the next Blackboard value
       	AICon->GetBlackboardComp()->SetValueAsObject("LocationToGo", NextTargetPoint);
       	AICon->CurrentPoint = NextTargetPoint;
       	AICon->CurrentNbMove++;
       	//At this point, the task has been successfully completed
       	return EBTNodeResult::Succeeded;
       }
		else
       {
       	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
			
			//Update the next location in the Blackboard so the bot can move to the next Blackboard value
       	AICon->GetBlackboardComp()->SetValueAsBool("bReturnSpawn", true);
       	//Update the next location in the Blackboard so the bot can move to the next Blackboard value
       AICon->GetBlackboardComp()->SetValueAsObject("LocationToGo", AICon->AIChar->Spawn);
       }
	}
	return EBTNodeResult::Failed;
}
