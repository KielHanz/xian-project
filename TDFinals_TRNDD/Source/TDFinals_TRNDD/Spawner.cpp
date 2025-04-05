// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Enemy.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameModeTD.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AEnemy* ASpawner::InitializeEnemySpawn(TSubclassOf<AEnemy> EnemyClass, int Hp)
{
	if (EnemyClass)
	{
		AEnemy* EnemyUnit = GetWorld()->SpawnActor<AEnemy>(EnemyClass, GetActorTransform());
		AGameModeTD* GameMode = Cast<AGameModeTD>(GetWorld()->GetAuthGameMode());

		if (EnemyUnit)
		{
			EnemyUnit->Health->MaxHealth = Hp;
			EnemyUnit->Health->InitializeHealth();
			EnemyUnit->Initialize();
			EnemyUnit->WaypointList = this->WaypointList;
			EnemyUnit->SpawnDefaultController();
			EnemyUnit->MoveToWaypoint();

			GameMode->EnemyAliveList.Add(EnemyUnit);
			// if (OnSpawn.IsBound()) OnSpawn.Broadcast(EnemyUnit);

			return EnemyUnit;
		}
	}

	return nullptr;
}

