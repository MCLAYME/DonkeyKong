// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "MuroCongelado.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_API AMuroCongelado : public AMuro
{
	GENERATED_BODY()
public:
	AMuroCongelado();

	// Sobrescribir el método Chocar
	virtual void Chocar();
	

protected:
	// Llamado cuando el juego comienza
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MuroCongeladoMesh;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* FrozenMaterial;

public:
	virtual void Tick(float DeltaTime) override;

};
