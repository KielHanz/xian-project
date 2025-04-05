// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "GameModeTD.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetupAttachment(RootComponent);

	Health = CreateDefaultSubobject<UHealthComponent>("Health");
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
	MoveToWaypoint();

	if (Health)
	{
		Health->OnDeath.AddDynamic(this, &AEnemy::OnEnemyDeath);
	}
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::Initialize()
{
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

void AEnemy::OnEnemyDeath()
{
	//OnDeath.Broadcast(this);
	AGameModeTD* GameMode = Cast<AGameModeTD>(GetWorld()->GetAuthGameMode());
	GameMode->EnemyAliveList.Remove(this);
	this->Destroy();
}

void AEnemy::MoveToWaypoint()
{
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(GetController());

	if (CurrentWaypointIdx < WaypointList.Num())
	{
		if (EnemyAIController && WaypointList[CurrentWaypointIdx])
		{
			EnemyAIController->MoveToActor(WaypointList[CurrentWaypointIdx], 50, true);
			CurrentWaypointIdx++;
		}
	}
}

