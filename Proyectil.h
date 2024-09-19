#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proyectil.generated.h"

UCLASS()
class DONKEYKONG_API AProyectil : public AActor
{
	GENERATED_BODY()

public:
	// Constructor
	AProyectil();

	// Malla del proyectil
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProyectilMesh;

	// Función para mover el proyectil manualmente
	void MoverProyectil(FVector Direccion);

protected:
	// Se llama cuando el juego comienza
	virtual void BeginPlay() override;

public:
	// Se llama cada frame
	virtual void Tick(float DeltaTime) override;

	// Componente de movimiento
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProyectilMovimiento;

	// Velocidad del proyectil
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProyectilSpeed;

	// Componente de colisión
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class USphereComponent* CollisionComp;

	// Sistema de partículas para el efecto de explosión
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* ExplosionEffect;

	// Función para manejar colisiones
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
