// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShootEvent, AProjectile*, Projectile);

UCLASS()
class TDFINALS_TRNDD_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* TowerBottom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* TowerTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* EnemyDetectCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* Muzzle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void Shoot(TSubclassOf<class AProjectile> projectile, float deltaTime);

	UFUNCTION(BlueprintCallable)
	void UpdateTurretRotation(float deltaSeconds);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnShootEvent OnShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AEnemy*> EnemyInRangeList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AProjectile> projectileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultFireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere)
	float DelayFireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsBuffed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SellCost;
};
