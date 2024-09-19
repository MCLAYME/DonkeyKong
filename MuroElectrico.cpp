// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroElectrico.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "DonkeyKongCharacter.h"

AMuroElectrico::AMuroElectrico()
{
	PrimaryActorTick.bCanEverTick = true;

	MuroElectricoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuroElectricoMesh"));
	RootComponent = MuroElectricoMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MuroElectricoMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MuroElectricoMeshAsset.Succeeded())
	{
		MuroElectricoMesh->SetStaticMesh(MuroElectricoMeshAsset.Object);
		FVector NewScale(2.0f, 0.25f, 3.0f);
		MuroElectricoMesh->SetWorldScale3D(NewScale);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> ElectricMaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse'"));
	if (ElectricMaterialAsset.Succeeded())
	{
		ElectricMaterial = ElectricMaterialAsset.Object;
	}
	// Configurar la colisión
	MuroElectricoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MuroElectricoMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	MuroElectricoMesh->OnComponentBeginOverlap.AddDynamic(this, &AMuroElectrico::OnBeginOverlap);


}

void AMuroElectrico::Chocar()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Chocaste con un muro eléctrico."));
	if (MuroElectricoMesh)
	{
		UParticleSystemComponent* ParticleSystem = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ElectricParticleSystemAsset, GetActorLocation());
	}
}

void AMuroElectrico::BeginPlay()
{
	Super::BeginPlay();

	if (ElectricMaterial)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(ElectricMaterial, this);
		if (MaterialInstance && MuroElectricoMesh)
		{
			MuroElectricoMesh->SetMaterial(0, MaterialInstance);
		}
	}
}

void AMuroElectrico::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADonkeyKongCharacter* Character = Cast<ADonkeyKongCharacter>(OtherActor);
	if (Character)
	{
		// Llama al método Chocar() del muro
		Chocar();

		// Puedes agregar efectos adicionales aquí
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("¡Personaje chocó con un muro eléctrico!"));

		// Aplicar efectos adicionales
		if (MuroElectricoMesh)
		{
			UMaterialInstanceDynamic* DynamicMaterial = MuroElectricoMesh->CreateAndSetMaterialInstanceDynamic(0);
			if (DynamicMaterial)
			{
				DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor::Yellow);
				GetWorld()->GetTimerManager().SetTimerForNextTick([this, DynamicMaterial]() {
					DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor::White);
					});
			}
		}
	}
}

void AMuroElectrico::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}