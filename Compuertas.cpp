// Fill out your copyright notice in the Description page of Project Settings.


#include "Compuertas.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACompuertas::ACompuertas()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Crear y configurar el BoxComponent
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	// Crear el componente visual de la compuerta
	CompuertaVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CompuertaVisual"));
	CompuertaVisual->SetupAttachment(RootComponent);

	// Usar ConstructorHelpers para encontrar una malla en los assets
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (MeshAsset.Succeeded())
	{
		CompuertaVisual->SetStaticMesh(MeshAsset.Object);
	}

	// Registrar la función para detectar colisiones
	void Teletransportar(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
}

/*void ACompuertas::crearCompuerta(FVector Location, FRotator Rotation)
{
	// Crear el objeto Compuerta en el mundo
	GetWorld()->SpawnActor<ACompuertas>(ACompuertas::StaticClass(), Location, Rotation);


}
*/

// Called when the game starts or when spawned
void ACompuertas::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACompuertas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Función que maneja el teletransporte cuando Donkey Kong entra en la colisión
void ACompuertas::Teletransportar(AActor* ActorATeletransportar)
{
	if (ActorATeletransportar && DestinoTeletransporte != FVector::ZeroVector)
	{
		ActorATeletransportar->SetActorLocation(DestinoTeletransporte);
	}
}