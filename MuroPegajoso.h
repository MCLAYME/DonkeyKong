// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "MuroPegajoso.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_API AMuroPegajoso : public AMuro
{
	GENERATED_BODY()
public:
	AMuroPegajoso();

	// Sobrescribir el método Chocar
	virtual void Chocar();

protected:
	// Llamado cuando el juego comienza
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MuroPegajosoMesh;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* StickyMaterial;

public:
	virtual void Tick(float DeltaTime) override;

};
