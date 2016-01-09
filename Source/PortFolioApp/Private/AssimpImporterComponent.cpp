// Fill out your copyright notice in the Description page of Project Settings.

#include "PortFolioApp.h"
#include "AssimpImporterComponent.h"
#include "assimp/importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"

namespace Assimp
{
	class Importer;
}


// Sets default values for this component's properties
UAssimpImporterComponent::UAssimpImporterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> materialOb_PinkPlasma(TEXT("Material'/Game/Bats_Mat.Bats_Mat'"));
	if (materialOb_PinkPlasma.Object != NULL)
	{
		MasterMaterialRef = (UMaterial*)materialOb_PinkPlasma.Object;
	}
}


// Called when the game starts
void UAssimpImporterComponent::BeginPlay()
{
	Super::BeginPlay();
	inverseNormals = false;
	swapCoords = 0;
	InternalFilePath = FPaths::Combine(*FPaths::GameSavedDir(), TEXT("DiapoAssets/Bird/BeeBird.obj"));
	// ...
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	// Note: PNG format.  Other formats are supported
	IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	TArray<uint8> RawFileData;
	FString TexturePath = FPaths::GetPath(InternalFilePath) / FPaths::GetBaseFilename(InternalFilePath) + FString(".png");
	std::string strname(TCHAR_TO_ANSI(*TexturePath));
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

				UMaterialInstanceDynamic* RV_MatInst = UMaterialInstanceDynamic::Create(MasterMaterialRef, this);
				RV_MatInst->SetTextureParameterValue(FName("T2DParam"), ModelTexture);
			}
		}
	}
}


// Called every frame
void UAssimpImporterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UAssimpImporterComponent::Load(const FString& FilePath)
{
	
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(TCHAR_TO_ANSI(*FilePath), aiProcessPreset_TargetRealtime_Quality);
	/*aiProcess_GenNormals |
	 |
	aiProcess_CalcTangentSpace |
	aiProcess_Triangulate |
	aiProcess_JoinIdenticalVertices |
	aiProcess_SortByPType);*/

	if (!scene) return false;

	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* currentMesh = scene->mMeshes[i];
		for (unsigned int j = 0; j < currentMesh->mNumVertices; j++)
		{
			aiVector3D vertex = currentMesh->mVertices[j];
			Vertices.Add(FVector(vertex.x, vertex.y, vertex.z));
			if (currentMesh->HasNormals())
			{
				aiVector3D normal = currentMesh->mNormals[j].Normalize();
				float tmp = 0;
				switch (swapCoords)
				{
				case 1:
					tmp = normal.z;
					normal.z = normal.y;
					normal.y = tmp;
					break;
				case 2:
					tmp = normal.x;
					normal.x = normal.z;
					normal.z = normal.y;
					normal.y = tmp;
					break;
				case 3:
					tmp = normal.x;
					normal.x = normal.y;
					normal.y = tmp;
					break;
				case 4:
					tmp = normal.x;
					normal.x = normal.y;
					normal.y = normal.z;
					normal.z = tmp;
					break;
				case 5:
					tmp = normal.x;
					normal.x = normal.z;
					normal.z = tmp;
					break;
				}
				int inverse = inverseNormals ? -1 : 1;
				Normals.Add(FVector(inverse*normal.x, inverse*normal.y, inverse*normal.z));
			}
		}

		if (currentMesh->HasTextureCoords(0))
		{
			for (unsigned int j = 0; j < currentMesh->mNumVertices; j++)
			{
				UVs.Add(FVector2D(currentMesh->mTextureCoords[0][j].x, 1 - currentMesh->mTextureCoords[0][j].y));
			}
		}

		for (unsigned int k = 0; k < currentMesh->mNumFaces; k++)
		{
			if (currentMesh->mFaces != 0x0)
			{
				aiFace face = currentMesh->mFaces[k];
				for (unsigned int l = 0; l < face.mNumIndices; l++)
				{
					Triangles.Add(face.mIndices[l]);
				}
			}
		}
	}

	return true;
}