// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataformas.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlataformas::APlataformas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Content/Geometry/Meshes/Escenario/Donkey_Kong_Level_1_Platform001.Donkey_Kong_Level_1_Platform001'"));

	mallaPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mallaPlataforma->SetStaticMesh(MeshAsset.Object);
	RootComponent = mallaPlataforma;

	FVector NewScale(4.0f, 6.0f, 2.5f); // Cambia estos valores según tus necesidades
	SetActorScale3D(NewScale);
	bMoverHorizontalmente = false;
	bMoverVerticalmente = false;

	StartPoint = FVector(0.0f, 0.0f, 0.0f);
	EndPoint = FVector(1000.0f, 0.0f, 0.0f);
	Speed = 100.0f;
}

/*void APlataformas::crearPlataforma()
{
    //crear las pltafoormas de 5 pisos y que este compuesto cada piso de 5 plataformas
	if (GetWorld())
	{
		FVector ubicacion1(-0.80f, 1200.0f, 140.0f);
		FRotator rotacion1(0.0f, 90.0f, 0.0f);
		FTransform SpawnLocationNP;

		for (int i = 0; i < 5; i++)
		{

			for (int j = 0; j < 3; j++)
			{
				//SpawnLocationNP.SetLocation(FVector(ubicacion1.X, ubicacion1.Y, ubicacion1.Z));
				APlataformas* plataforma1 = GetWorld()->SpawnActor<APlataformas>(ubicacion1, rotacion1);
				PlataformaMap.Add(1, plataforma1);
				ubicacion1.Z += 90.0f;
				ubicacion1.Y -= 367.0f;
				//rotacion1.Roll = rotacion1.Roll * -1;
			}
			ubicacion1.Y += 1000.0f;
			ubicacion1.Z += 700.0f;

		}


		FVector ubicacion2(0.50f, 1300.0f, 180.0f);
		FRotator rotacion2(0.0f, 90.0f, 0.0f);

		for (int i = 0; i < 5; i++)
		{

			for (int j = 0; j < 3; j++)
			{
				//SpawnLocationNP.SetLocation(FVector(ubicacion2.X, ubicacion2.Y, ubicacion2.Z));
				APlataformas* plataforma2 = GetWorld()->SpawnActor<APlataformas>(ubicacion2, rotacion2);
				PlataformaMap.Add(2, plataforma2);
				ubicacion2.Z += 90.0f;
				ubicacion2.Y += 367.0f;
				//rotacion2.Roll = rotacion2.Roll * -1;
			}
			ubicacion2.Y -= 1150.0f;
			ubicacion2.Z += 700.0f;

		}

	}

}*/

// Called when the game starts or when spawned
void APlataformas::BeginPlay()
{
	Super::BeginPlay();



	
}

// Called every frame
void APlataformas::Tick(float DeltaTime)
{

	// Verificamos si la plataforma debe moverse verticalmente
	if (bMoverVerticalmente)
	{
		// Movimiento entre StartPoint y EndPoint verticalmente
		FVector CurrentLocation = GetActorLocation();
		float DistanceCovered = (GetWorld()->TimeSeconds - StartTime) * Speed;
		float JourneyLength = (EndPoint - StartPoint).Size();
		float FractionOfJourney = DistanceCovered / JourneyLength;
		FVector NewLocation = FMath::Lerp(StartPoint, EndPoint, FractionOfJourney);
		SetActorLocation(NewLocation);

		// Intercambiamos StartPoint y EndPoint cuando llega al destino
		if (FractionOfJourney >= 1.0f)
		{
			FVector Temp = StartPoint;
			StartPoint = EndPoint;
			EndPoint = Temp;
			StartTime = GetWorld()->TimeSeconds;
		}
	}

	// Verificamos si la plataforma debe moverse horizontalmente
	if (bMoverHorizontalmente)
	{
		// Movimiento entre StartPoint y EndPoint horizontalmente
		FVector CurrentLocation = GetActorLocation();
		float DistanceCovered = (GetWorld()->TimeSeconds - StartTime) * Speed;
		float JourneyLength = (EndPoint - StartPoint).Size();
		float FractionOfJourney = DistanceCovered / JourneyLength;
		FVector NewLocation = FMath::Lerp(StartPoint, EndPoint, FractionOfJourney);
		SetActorLocation(NewLocation);

		// Intercambiamos StartPoint y EndPoint cuando llega al destino
		if (FractionOfJourney >= 1.0f)
		{
			FVector Temp = StartPoint;
			StartPoint = EndPoint;
			EndPoint = Temp;
			StartTime = GetWorld()->TimeSeconds;
		}
	}

}

