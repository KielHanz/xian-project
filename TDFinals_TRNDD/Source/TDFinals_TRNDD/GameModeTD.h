// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeTD.generated.h"

/**
 * 
 */
UCLASS()
class TDFINALS_TRNDD_API AGameModeTD : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay()override;

public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UWaveData*> WaveData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AEnemy*> EnemyAliveList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Waves;
};
