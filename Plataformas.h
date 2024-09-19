// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plataformas.generated.h"

UCLASS()
class DONKEYKONG_API APlataformas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlataformas();

	//UStaticMeshComponent* PlataformaMesh
	UStaticMeshComponent* mallaPlataforma;
	//void crearPlataforma();
	FVector StartPoint;
	FVector EndPoint;
	float Speed;
	float StartTime;


	bool bMoverHorizontalmente;
	bool bMoverVerticalmente;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plataformas")
//	TMap<int32, APlataformas* > PlataformaMap;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
