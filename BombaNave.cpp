// Fill out your copyright notice in the Description page of Project Settings.


#include "BombaNave.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "Nave.h"
// Sets default values
ABombaNave::ABombaNave()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Crea el componente de malla para la bomba
	BombaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombaMesh"));
	RootComponent = BombaMesh;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BombaMeshAsset(TEXT("StaticMesh'/Game/Meshes/Missile.Missile'"));
	if (BombaMeshAsset.Succeeded()) {
		BombaMesh->SetStaticMesh(BombaMeshAsset.Object);
	}

	Velocidad = 300.0f;
	DireccionMovimiento = FVector(0.0f, 0.0f, -1.0f);  // La bomba cae hacia abajo por defecto
	
}

// Called when the game starts or when spawned
void ABombaNave::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABombaNave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Mueve la bomba en la dirección del movimiento
	FVector NuevaPosicion = GetActorLocation() + (DireccionMovimiento * Velocidad * DeltaTime);
	SetActorLocation(NuevaPosicion);

}

