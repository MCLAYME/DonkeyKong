// Fill out your copyright notice in the Description page of Project Settings.


#include "Compuertas.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DonkeyKongCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACompuertas::ACompuertas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Crear el mesh de la compuerta
    CompuertaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CompuertaMesh"));
    RootComponent = CompuertaMesh;
    TamanioCompuerta = FVector(0.10f, 0.10f, 0.10f);
    InicializarTamanio();

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CompuertaMeshAsset(TEXT("StaticMesh'/Game/Meshes/CaveWall.CaveWall'"));
	if (CompuertaMeshAsset.Succeeded())
	{   
		CompuertaMesh->SetStaticMesh(CompuertaMeshAsset.Object);
	}

    // Crear el componente de colisión
    TeleportBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportBox"));
    TeleportBox->SetupAttachment(RootComponent);
    TeleportBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
    TeleportBox->OnComponentBeginOverlap.AddDynamic(this, &ACompuertas::TeletransportarJugador);
    // Inicialización del componente de colisiSION  ;
    // Configuración inicial
    PosicionCompuerta = FVector::ZeroVector;
}

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
void ACompuertas::InicializarTamanio()
{
    if (CompuertaMesh)
    {
        CompuertaMesh->SetRelativeScale3D(TamanioCompuerta);
    }

}
void ACompuertas::TeletransportarJugador(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (ACharacter* Jugador = Cast<ACharacter>(OtherActor))
    {
        if (Jugador && CompuertaDestino)
        {
            Jugador->SetActorLocation(CompuertaDestino->GetActorLocation());
        }
    }
}

void ACompuertas::ConfigurarPosicion(FVector NuevaPosicion)
{
    PosicionCompuerta = NuevaPosicion;
}

