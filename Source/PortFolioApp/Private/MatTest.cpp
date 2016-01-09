// Fill out your copyright notice in the Description page of Project Settings.

#include "PortFolioApp.h"
#include "MatTest.h"


#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"

// Sets default values
AMatTest::AMatTest(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshSphere(TEXT("StaticMesh'/Game/Shape_Sphere.Shape_Sphere'"));
	SolutionSphere1 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("SolutionSphere1"));
	RootComponent = SolutionSphere1;
	SolutionSphere1->SetStaticMesh(StaticMeshSphere.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> materialOb_PinkPlasma(TEXT("Material'/Game/Bats_Mat.Bats_Mat'"));
	if (materialOb_PinkPlasma.Object != NULL)
	{
		MasterMaterialRef = (UMaterial*)materialOb_PinkPlasma.Object;
	}
}

void AMatTest::GetTexture()
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	// Note: PNG format.  Other formats are supported
	IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	TArray<uint8> RawFileData;
	FString TexturePath = "D:\\Personal Dev Projects\\PortFolioApp\\Saved\\3dLoad\\Bats.png";
	if (FFileHelper::LoadFileToArray(RawFileData, *TexturePath))
	{
		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
		{
			const TArray<uint8>* UncompressedBGRA = NULL;
			if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
			{
				ModelTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
				// Fill in the source data from the file
				FTexture2DMipMap& Mip = ModelTexture->PlatformData->Mips[0];
				void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(Data, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
				Mip.BulkData.Unlock();
				ModelTexture->UpdateResource();
			}
		}
	}
}

// Called when the game starts or when spawned
void AMatTest::BeginPlay()
{
	Super::BeginPlay();
	/*UMaterialInstanceDynamic* RV_MatInst = UMaterialInstanceDynamic::Create(MasterMaterialRef, this);
	RV_MatInst->SetTextureParameterValue(FName("T2DParam"), ModelTexture);
	SolutionSphere1->SetMaterial(0, MasterMaterialRef);*/
}

// Called every frame
void AMatTest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

