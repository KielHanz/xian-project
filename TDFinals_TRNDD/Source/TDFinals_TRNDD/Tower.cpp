// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(root);

	TowerBottom = CreateDefaultSubobject<UStaticMeshComponent>("Turret Bottom");
	TowerBottom->SetupAttachment(root);

	TowerTop = CreateDefaultSubobject<UStaticMeshComponent>("Turret Top");
	TowerTop->SetupAttachment(TowerBottom);

	EnemyDetectCollision = CreateDefaultSubobject<USphereComponent>("Enemy Detect Collision");
	EnemyDetectCollision->SetupAttachment(TowerBottom);

	Muzzle = CreateDefaultSubobject<UArrowComponent>("Nozzle Point");
	Muzzle->SetupAttachment(TowerTop);
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	EnemyDetectCollision->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnBeginOverlap);
	EnemyDetectCollision->OnComponentEndOverlap.AddDynamic(this, &ATower::OnEndOverlap);
	
	FireRate = DefaultFireRate;
	DelayFireRate = FireRate;
	
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TowerTop)
	{
		if (EnemyInRangeList.Num() > 0)
		{
			UpdateTurretRotation(DeltaTime);
			Shoot(projectileType, DeltaTime);
		}
	}

}

void ATower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);

	if (Enemy && !EnemyInRangeList.Contains(Enemy))
	{
		EnemyInRangeList.Add(Enemy);
	}
}

void ATower::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		EnemyInRangeList.Remove(Enemy);
	}

	AProjectile* Projectile = Cast<AProjectile>(OtherActor);
	if (Projectile && Projectile->ProjectileOwner == this)
	{
		Projectile->Destroy();
	}
}

void ATower::Shoot(TSubclassOf<class AProjectile> projectile, float deltaTime)
{
	if (DelayFireRate > 0)
	{
		DelayFireRate -= deltaTime;
	}

	if (DelayFireRate <= 0)
	{
		AProjectile* projectileActor = GetWorld()->SpawnActor<AProjectile>(projectile, Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation());

		if (projectileActor)
		{
			projectileActor->ProjectileOwner = this;
			projectileActor->BaseDamage = this->Damage;
		}

		OnShoot.Broadcast(projectileActor);
		DelayFireRate = FireRate;
	}
}

void ATower::UpdateTurretRotation(float deltaSeconds)
{

	if (EnemyInRangeList.Num() > 0)
	{
		FVector ActorLocation = TowerTop->GetComponentLocation();
		FVector TargetLocation = EnemyInRangeList[0]->StaticMesh->GetComponentLocation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, TargetLocation);

		FRotator NewRotation = FMath::RInterpConstantTo(TowerTop->GetComponentRotation(), LookAtRotation, deltaSeconds, 500);

		TowerTop->SetWorldRotation(NewRotation);
	}
}

