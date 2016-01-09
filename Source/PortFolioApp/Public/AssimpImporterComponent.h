// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
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

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3DLoader")
		TArray<FVector> Vertices;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3DLoader")
		TArray<FVector> Normals;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3DLoader")
		TArray<int32> Triangles;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3DLoader")
		TArray<FVector2D> UVs;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3DLoader")
		bool inverseNormals;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3DLoader")
		int32 swapCoords;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "3DLoader")
		FString InternalFilePath;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "3DLoader")
		UTexture2D* ModelTexture;

	//~~~ BP Referenced Materials ~~~
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "3DLoader")
		UMaterialInterface* MasterMaterialRef;

	UFUNCTION(BlueprintCallable, Category = "File Loader")
		bool Load(const FString& FilePath);

};
