// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "MuroElectrico.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_API AMuroElectrico : public AMuro
{
	GENERATED_BODY()
public:
	AMuroElectrico();

	// Sobrescribir el método Chocar
	virtual void Chocar();


protected:
	// Llamado cuando el juego comienza
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MuroElectricoMesh;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* ElectricMaterial;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ElectricParticleSystemAsset;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



public:
	virtual void Tick(float DeltaTime) override;
	
	
};
