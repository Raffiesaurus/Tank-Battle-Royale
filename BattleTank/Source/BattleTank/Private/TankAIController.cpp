// Copyright Raffie

#include "BattleTank/Public/TankAIController.h"
#include "BattleTank/Public/TankAimingComponent.h"
#include "Tank.h"
#include "Classes/GameFramework/Pawn.h"
#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank)
		{
			return;
		}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}


void ATankAIController::OnTankDeath()
{
	if (!GetPawn())
	{
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	

	if (PlayerTank && ControlledTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if(AimingComponent->GetFireState() == EFiringStatus::Locked)
			AimingComponent->Fire();
	}
}
