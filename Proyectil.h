// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proyectil.generated.h"


//class UStaticMeshComponent;
UCLASS()
class DONKEYKONG_API AProyectil : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AProyectil();
	UStaticMeshComponent* ProyectilMesh;

	void MoverProyectil(FVector direccion);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProyectilSpeed;
	// Collision component
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class USphereComponent* CollisionComp;

	// Particle system for explosion effect
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* ExplosionEffect;


	// Called when the projectile hits something
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
