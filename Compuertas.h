// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Compuertas.generated.h"

class UBoxComponent;

UCLASS()
class DONKEYKONG_API ACompuertas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACompuertas();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void InicializarTamanio();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Compuerta")
    UStaticMeshComponent* CompuertaMesh;
    // Tamaño personalizado para la compuerta
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compuerta")
    FVector TamanioCompuerta;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Compuerta")
    UBoxComponent* TeleportBox;

    // Posiciones de las compuertas
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compuerta")
    FVector PosicionCompuerta;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compuerta")
    ACompuertas* CompuertaDestino;

    UFUNCTION()
    void TeletransportarJugador(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    // Función para configurar la posición de la compuerta
    void ConfigurarPosicion(FVector NuevaPosicion);
};
