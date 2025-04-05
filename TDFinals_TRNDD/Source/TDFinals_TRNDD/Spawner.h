// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"


//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnEvent, AEnemy*, Enemy);

UCLASS()
class TDFINALS_TRNDD_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(BlueprintAssignable, BlueprintCallable)
	//FOnSpawnEvent OnSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemy> Enemy;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> WaypointList;

	UFUNCTION(BlueprintCallable)
	AEnemy* InitializeEnemySpawn(TSubclassOf<AEnemy> EnemyClass, int Hp);

};
