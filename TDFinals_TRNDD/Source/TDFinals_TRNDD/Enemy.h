// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathEvent, AEnemy*, Enemy);

UCLASS()
class TDFINALS_TRNDD_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHealthComponent* Health;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDeathEvent OnDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IsFlyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GoldDrop;

	UPROPERTY(EditAnywhere)
	int CurrentWaypointIdx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> WaypointList;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void OnEnemyDeath();

	UFUNCTION(BlueprintCallable)
	void MoveToWaypoint();


};
