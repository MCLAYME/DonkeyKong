#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Nave.generated.h"



UCLASS()
class DONKEYKONG_API ANave : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANave();

	// Componente de malla estática para la nave
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* NaveMesh;

	// Variables para el movimiento entre dos puntos
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nave")
	FVector PuntoA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nave")
	FVector PuntoB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nave")
	bool bMoviendoHaciaPuntoA;

	// Variables para controlar el tiempo de movimiento
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nave")
	float TiempoMovido;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nave")
	float TiempoMaximo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nave")
	FRotator RotacionInicial;
	FTimerHandle Temporizador;

	void DispararBombas();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Velocidad de movimiento
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nave")
	float MovimientoNave;

	// Rotación en 180 grados
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nave")
	FRotator RotacionCambio;
};
