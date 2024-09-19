#include "MuroLadrillo.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"

AMuroLadrillo::AMuroLadrillo()
{
	PrimaryActorTick.bCanEverTick = true;

	// Crear el componente de malla estática
	MuroLadrilloMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuroLadrilloMesh"));
	RootComponent = MuroLadrilloMesh;

	// Buscar y asignar la malla al componente
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MuroLadrilloMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MuroLadrilloMeshAsset.Succeeded())
	{
		MuroLadrilloMesh->SetStaticMesh(MuroLadrilloMeshAsset.Object);
		FVector NewScale(2.0f, 0.25f, 3.0f);
		MuroLadrilloMesh->SetWorldScale3D(NewScale);
	}

	// Buscar el material
	static ConstructorHelpers::FObjectFinder<UMaterial> BrickMaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'"));
	if (BrickMaterialAsset.Succeeded())
	{
		BrickMaterial = BrickMaterialAsset.Object;
	}
}

void AMuroLadrillo::Chocar()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Chocaste con un muro de ladrillo."));
}

void AMuroLadrillo::BeginPlay()
{
	Super::BeginPlay();

	if (BrickMaterial) // Asegurarse de que el material esté asignado
	{
		// Crear una instancia dinámica del material basado en BrickMaterial
		MaterialInstance = UMaterialInstanceDynamic::Create(BrickMaterial, this);

		if (MaterialInstance && MuroLadrilloMesh)
		{
			// Asignar el material a la malla estática
			MuroLadrilloMesh->SetMaterial(0, MaterialInstance);
		}
	}
}

void AMuroLadrillo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
