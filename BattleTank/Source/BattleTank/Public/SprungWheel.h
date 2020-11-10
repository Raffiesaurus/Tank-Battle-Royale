// Copyright Raffie

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitutde);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void SetupConstraint();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

	float TotalForceMagnitudeThisFrame = 0;
};
