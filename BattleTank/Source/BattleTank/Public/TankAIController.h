// Copyright Raffie


#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 4000;

private:

	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTankDeath();
};
