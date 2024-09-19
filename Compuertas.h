// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Compuertas.generated.h"

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
	// Función para teletransportar al jugador
	UFUNCTION()
	void Teletransportar(AActor* ActorATeletransportar);

	// BoxComponent para detectar la colisión
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

	// Componente visual (malla estática)
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CompuertaVisual;

	// Lugar de destino de teletransporte
	UPROPERTY(EditAnywhere, Category = "Teletransporte")
	FVector DestinoTeletransporte;

};

