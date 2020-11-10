// Copyright Raffie


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};

//Holds barrel's properties and Elevate method.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()
			
public:	

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	EFiringStatus GetFireState() const;

	bool IsBarrelMoving();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetRoundsLeft() const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringStatus FireState = EFiringStatus::Reloading;

private:
	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;

	void MoveBarrel(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	double LastFireTime = 0;
	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Config, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 RoundsLeft = 150;
};
