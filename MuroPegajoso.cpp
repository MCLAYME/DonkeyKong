// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroPegajoso.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"

AMuroPegajoso::AMuroPegajoso()
{
	PrimaryActorTick.bCanEverTick = true;

	// Crear el componente de malla estática
	MuroPegajosoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuroPegajosoMesh"));
	RootComponent = MuroPegajosoMesh;

	// Asignar la malla
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MuroPegajosoMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MuroPegajosoMeshAsset.Succeeded())
	{
		MuroPegajosoMesh->SetStaticMesh(MuroPegajosoMeshAsset.Object);
		FVector NewScale(2.0f, 0.25f, 3.0f);
		MuroPegajosoMesh->SetWorldScale3D(NewScale);
	}

	// Asignar el material pegajoso
	static ConstructorHelpers::FObjectFinder<UMaterial> StickyMaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Ground_Moss.M_Ground_Moss'"));
	if (StickyMaterialAsset.Succeeded())
	{
		StickyMaterial = StickyMaterialAsset.Object;
	}
}

void AMuroPegajoso::Chocar()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Chocaste con un muro pegajoso."));
}

void AMuroPegajoso::BeginPlay()
{
	Super::BeginPlay();

	if (StickyMaterial)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(StickyMaterial, this);
		if (MaterialInstance && MuroPegajosoMesh)
		{
			MuroPegajosoMesh->SetMaterial(0, MaterialInstance);
		}
	}
}

void AMuroPegajoso::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
