// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Enemy.h"

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	AEnemy* Enemy = Cast<AEnemy>(AEnemyAIController::GetPawn());

	if (Enemy && Result.IsSuccess())
	{
		Enemy->MoveToWaypoint();
	}

}
