// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroCongelado.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"

AMuroCongelado::AMuroCongelado()
{
	PrimaryActorTick.bCanEverTick = true;

	// Crear el componente de malla estática
	MuroCongeladoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuroCongeladoMesh"));
	RootComponent = MuroCongeladoMesh;

	// Asignar la malla
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MuroCongeladoMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MuroCongeladoMeshAsset.Succeeded())
	{
		MuroCongeladoMesh->SetStaticMesh(MuroCongeladoMeshAsset.Object);
		FVector NewScale(2.0f, 0.25f, 3.0f);
		MuroCongeladoMesh->SetWorldScale3D(NewScale);
	}

	// Asignar el material congelado
	static ConstructorHelpers::FObjectFinder<UMaterial> FrozenMaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Panel.M_Tech_Panel'"));
	if (FrozenMaterialAsset.Succeeded())
	{
		FrozenMaterial = FrozenMaterialAsset.Object;
	}
}

void AMuroCongelado::Chocar()
{
	// Llama a los efectos definidos en AMuro

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Chocaste con un muro congelado."));
}

void AMuroCongelado::BeginPlay()
{
	Super::BeginPlay();

	if (FrozenMaterial)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(FrozenMaterial, this);
		if (MaterialInstance && MuroCongeladoMesh)
		{
			MuroCongeladoMesh->SetMaterial(0, MaterialInstance);
		}
	}
}

void AMuroCongelado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
