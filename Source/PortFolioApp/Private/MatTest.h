// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MatTest.generated.h"

UCLASS()
class AMatTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMatTest(const class FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class UStaticMeshComponent* SolutionSphere1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
		UTexture2D* ModelTexture;

	//~~~ BP Referenced Materials ~~~
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
		UMaterialInterface* MasterMaterialRef;

	UFUNCTION(BlueprintCallable, Category = "Light")
		void GetTexture();
};
