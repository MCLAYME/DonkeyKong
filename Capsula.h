// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Capsula.generated.h"

// Forward declaration de ADonkeyKongCharacter
class ADonkeyKongCharacter;

UCLASS()
class DONKEYKONG_API ACapsula : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACapsula();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Función para disparar al personaje
    UFUNCTION()
    void Disparar();

    // Función para detectar al personaje
    UFUNCTION()
    void DetectarCharacter();

    // Función para explotar y destruir la cápsula
    UFUNCTION()
    void Explote();

private:
    // Referencia al personaje del jugador
    UPROPERTY()
    ADonkeyKongCharacter* PlayerCharacter;

    // Rango de patrullaje horizontal
    UPROPERTY(EditAnywhere, Category = "Movimiento")
    float RangoPatrullaje;

    // Velocidad de patrullaje horizontal
    UPROPERTY(EditAnywhere, Category = "Movimiento")
    float VelocidadPatrullaje;

    // Dirección actual del patrullaje horizontal
    int32 DireccionPatrullaje;

    // Temporizador para disparos
    FTimerHandle TimerDisparo;

    // Tiempo entre disparos
    UPROPERTY(EditAnywhere, Category = "Disparo")
    float TiempoEntreDisparos;

    // Componente visual de la cápsula
    UPROPERTY(VisibleAnywhere, Category = "Visual")
    UStaticMeshComponent* CapsulaVisual;

    // Sistema de partículas para el efecto de explosión
    UPROPERTY(EditAnywhere, Category = "Efectos")
    UParticleSystem* ExplosionParticle;

    // Material dinámico para cambiar el color
    UPROPERTY()
    UMaterialInstanceDynamic* MaterialInstance;
};
