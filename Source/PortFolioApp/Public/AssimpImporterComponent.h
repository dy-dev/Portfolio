// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ProceduralMeshComponent.h"
#include "AssimpImporterComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PORTFOLIOAPP_API UAssimpImporterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAssimpImporterComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	Normals, Vertices, triangles and UVs describing the 3D model we want to import
	*/
	UPROPERTY(Transient, BlueprintReadWrite, Category = "3D Loader")
		TArray<FVector> Vertices;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3D Loader")
		TArray<FVector> Normals;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3D Loader")
		TArray<int32> Triangles;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3D Loader")
		TArray<FVector2D> UVs;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3D Loader")
		bool InverseNormals;

	//UPROPERTY(Transient, BlueprintReadWrite, Category = "3D Loader")
	//	int32 swapCoords;

	//Texture for the model
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "3D Loader")
		UTexture2D* ModelTexture;

	//Interface to the material we need to modify
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "3D Loader")
		UMaterialInterface* InterfaceToMainMaterial;

	//Path to the 3D model
	UPROPERTY(Transient, BlueprintReadWrite, Category = "3D Loader")
		FString MeshPath;

	//Useful for Debug
	UPROPERTY(Transient, BlueprintReadWrite, Category = "3D Loader")
		FString InternalFilePath;

	UFUNCTION(BlueprintCallable, Category = "3D Loader")
		bool Load3DModel(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "3D Loader")
		void SetMaterialToProceduralMeshComp(UProceduralMeshComponent* procMeshComp);

private:
	void CreateInterfaceToMainMaterial();
	void LoadTexture(const FString& FilePath);
};
