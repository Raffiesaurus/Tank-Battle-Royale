// Copyright Raffie


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h" 
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	static ConstructorHelpers::FClassFinder<AProjectile> ProjectileBP(TEXT("Blueprint'/Game/Tank/Projectile_BP.Projectile_BP_C'"));
	ProjectileBlueprint = ProjectileBP.Class;
	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FireState = EFiringStatus::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		FireState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FireState = EFiringStatus::Aiming;
	}
	else
	{
		FireState = EFiringStatus::Locked;
	}

}


EFiringStatus UTankAimingComponent::GetFireState() const
{
	
	return FireState;
}


void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))
		return;
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}

}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
		return;
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	if (FMath::Abs(DeltaRotation.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotation.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotation.Yaw);
	}
	Barrel->Elevate(DeltaRotation.Pitch);
}

void UTankAimingComponent::Fire()
{
	if (FireState == EFiringStatus::Locked || FireState == EFiringStatus::Aiming)
	{
		if (!ensure(Barrel))
			return;
		if (!ensure(ProjectileBlueprint))
			return;
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
		return false;
	auto CurrentDirection = Barrel->GetForwardVector();
	return !(CurrentDirection.Equals(AimDirection, 0.01));
}