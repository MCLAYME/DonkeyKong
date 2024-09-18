#include "Nave.h"
#include "BombaNave.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
// Sets default values
ANave::ANave()
{
    PrimaryActorTick.bCanEverTick = true;

    NaveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NaveMesh"));
    RootComponent = NaveMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> NaveMeshAsset(TEXT("StaticMesh'/Game/Meshes/Nodriza5.Nodriza5'"));
    if (NaveMeshAsset.Succeeded()) {
        NaveMesh->SetStaticMesh(NaveMeshAsset.Object);
    }

    MovimientoNave = 500.0f;
    PuntoA = FVector(100.0f, 1200.0f, 4600.0f);  
    PuntoB = FVector(140.0f, -1400.0f, 4340.0f);  
    bMoviendoHaciaPuntoA = true;  

    RotacionInicial = FRotator(0.0f, 90.0f, 0.0f); 
    RotacionCambio = FRotator(0.0f, 90.0f, 0.0f);

    TiempoMovido = 0.0f;
    TiempoMaximo = 60.0f;  
}
void ANave::DispararBombas()
{

    // Verificar si el mundo es válido
    UWorld* Mundo = GetWorld();
    if (Mundo)
    {
        // Establecer la ubicación de la bomba en la posición de la nave
        FVector UbicacionBombaNave = GetActorLocation();

        // Establecer la rotación de la bomba
        FRotator RotacionBombaNave = FRotator::ZeroRotator;
        ABombaNave* Bomba = Mundo->SpawnActor<ABombaNave>(ABombaNave::StaticClass(), UbicacionBombaNave, RotacionBombaNave);


        // Instanciar la bomba
        Mundo->SpawnActor<ABombaNave>(ABombaNave::StaticClass(), UbicacionBombaNave, RotacionBombaNave);


        if (Bomba)
        {
            // Destruir la bomba después de 10 segundos
            Bomba->SetLifeSpan(0.10f);
        }
    }

}

void ANave::BeginPlay()
{
    Super::BeginPlay();

    SetActorRotation(RotacionInicial);

    GetWorld()->GetTimerManager().SetTimer(Temporizador, this, &ANave::DispararBombas, 1.0f, true);

}

void ANave::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector PosicionActual = GetActorLocation();
    FVector Objetivo = bMoviendoHaciaPuntoA ? PuntoB : PuntoA;

    FVector NuevaPosicion = FMath::VInterpConstantTo(PosicionActual, Objetivo, DeltaTime, MovimientoNave);
    SetActorLocation(NuevaPosicion);

    if (FVector::Dist(NuevaPosicion, Objetivo) < 10.0f)
    {
		DispararBombas();

        FRotator NuevaRotacion = GetActorRotation() + RotacionCambio;
        SetActorRotation(NuevaRotacion);

        bMoviendoHaciaPuntoA = !bMoviendoHaciaPuntoA;
    }

    TiempoMovido += DeltaTime;

    if (TiempoMovido >= TiempoMaximo)
    {
        PrimaryActorTick.bCanEverTick = false;
    }
}
