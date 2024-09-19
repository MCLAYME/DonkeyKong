// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Muro.generated.h"

UCLASS()
class DONKEYKONG_API AMuro : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMuro();

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual void Chocar();

protected:
	UMaterialInstanceDynamic* MaterialInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Efecto de partículas a aplicar cuando el muro sea chocado
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ImpactParticles;

	// Efecto de sonido a reproducir cuando el muro sea chocado
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* ImpactSound;
	void PlayEffects();


};
