// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FEnemyData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AEnemy> EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Hp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int AmountOfEnemies;

};

UCLASS()
class TDFINALS_TRNDD_API UWaveData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int WaveGoldDrop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEnemyData> EnemyData;
};
