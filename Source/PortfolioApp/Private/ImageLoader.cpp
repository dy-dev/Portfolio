// Fill out your copyright notice in the Description page of Project Settings.

#include "PortfolioApp.h"
#include "ImageLoader.h"
#include "ImagesHolder.h"
#include "Runtime/Engine/Public/DDSLoader.h"

#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"

#include "DirectoryVisitor.h"

#include <string>

UImageLoader::UImageLoader()
    :ImagesPaths("")
{
}

UImageLoader::~UImageLoader()
{
}

void UImageLoader::CreateSearchPaths(FString p_sPath, UImagesHolder* p_pHolder )
{
    ImagesPaths = p_sPath;
    if (FPaths::DirectoryExists( p_sPath ))//If the folder exists
    {
    	IFileManager& FileManager = IFileManager::Get();
    	TArray<FString> DirNamesOut;
    	if ( p_sPath.Len() > 1)//Minimum count of letters of the folder must be 2
    	{
    		FPaths::NormalizeDirectoryName( p_sPath );
    		FString FinalPath = p_sPath;// +"/" + "*.*";
    		FString Str;
    	/*	GetDirectories(FinalPath, DirNamesOut, true);
    	}

    	for (auto names : DirNamesOut)
    	{
    		std::string strdir(TCHAR_TO_ANSI(*names));
    		FString cleanName = FPaths::GetBaseFilename(names);
    		std::string strname(TCHAR_TO_ANSI(*cleanName));
    		FString curPath = names.LeftChop(cleanName.Len() + 1);
    		std::string strpath(TCHAR_TO_ANSI(*curPath));
           */
    		TArray<FString> Files;
    		GetFiles( p_sPath, Files, false); //We put all the files in Files
                                                          
    		for (auto fileName : Files) //For each file 
    		{
    			if (FPaths::GetExtension(fileName).ToLower() != "db") //if the extension isn't .db
    			{
    				TArray<uint8> RawFileData;
                   // FString filePath = FPaths::Combine( *names, *fileName );
                    FString filePath = FPaths::Combine(*FinalPath, *fileName); //create the full path of the file
    				std::string strfileName(TCHAR_TO_ANSI(*filePath));

    				if (FFileHelper::LoadFileToArray(RawFileData, *filePath)) //put all the data in RawFileData
    				{
    					IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper")); 
    					// Note: PNG format.  Other formats are supported
    					IImageWrapperPtr ImageWrapper;
    					if (FPaths::GetExtension(fileName).ToLower() == "jpg" ||
    						FPaths::GetExtension(fileName).ToLower() == "jpeg")
    					{
    						ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
    					}
    					else if (FPaths::GetExtension(fileName).ToLower() == "png")
    					{
    						ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
    					}
    					else if (FPaths::GetExtension(fileName).ToLower() == "bmp")
    					{
    						ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP);
    					}

    					if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
    					{
    						const TArray<uint8>* UncompressedBGRA = NULL;
    						if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
    						{
    							ImagesPaths.Append(filePath + TEXT("\n"));
    							// Create the UTexture for rendering
    							UTexture2D* MyTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

    							// Fill in the source data from the file
    							FTexture2DMipMap& Mip = MyTexture->PlatformData->Mips[0];
    							void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
    							FMemory::Memcpy(Data, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
    							Mip.BulkData.Unlock();
    							MyTexture->UpdateResource();

                                p_pHolder->Images.Add(MyTexture);
    						}
    					}
    				}
    			}
    		}
    	}
    }
}



UTexture2D* UImageLoader::LoadTexture( FString TextureFilename )
{
    UTexture2D* Texture = nullptr;
    std::string strpath(TCHAR_TO_ANSI(*TextureFilename));
    FString TexturePath = TextureFilename;// FPaths::GameContentDir() + TEXT("../Data/") + TextureFilename;
    TArray<uint8> FileData;

    /* Load DDS texture */
    if (FFileHelper::LoadFileToArray(FileData, *TexturePath))
    {
    	FDDSLoadHelper DDSLoadHelper(&FileData[0], FileData.Num());
    	if (DDSLoadHelper.IsValid2DTexture())
    	{
    		int32 NumMips = DDSLoadHelper.ComputeMipMapCount();
    		EPixelFormat Format = DDSLoadHelper.ComputePixelFormat();
    		int32 BlockSize = 16;

    		if (NumMips == 0)
    		{
    			NumMips = 1;
    		}

    		if (Format == PF_DXT1)
    		{
    			BlockSize = 8;
    		}

    		/* Create transient texture */
    		Texture = UTexture2D::CreateTransient(DDSLoadHelper.DDSHeader->dwWidth, DDSLoadHelper.DDSHeader->dwHeight, Format);
    		//Texture->MipGenSettings = TMGS_LeaveExistingMips;
    		Texture->PlatformData->NumSlices = 1;
    		Texture->NeverStream = true;
    		Texture->Rename(*TextureFilename);

    		/* Get pointer to actual data */
    		uint8* DataPtr = (uint8*)DDSLoadHelper.GetDDSDataPointer();

    		uint32 CurrentWidth = DDSLoadHelper.DDSHeader->dwWidth;
    		uint32 CurrentHeight = DDSLoadHelper.DDSHeader->dwHeight;

    		/* Iterate through mips */
    		for (int32 i = 0; i < NumMips; i++)
    		{
    			/* Lock to 1x1 as smallest size */
    			CurrentWidth = (CurrentWidth < 1) ? 1 : CurrentWidth;
    			CurrentHeight = (CurrentHeight < 1) ? 1 : CurrentHeight;

    			/* Get number of bytes to read */
    			int32 NumBytes = CurrentWidth * CurrentHeight * 4;
    			if (Format == PF_DXT1 || Format == PF_DXT3 || Format == PF_DXT5)
    			{
    				/* Compressed formats */
    				NumBytes = ((CurrentWidth + 3) / 4) * ((CurrentHeight + 3) / 4) * BlockSize;
    			}

    			/* Write to existing mip */
    			if (i < Texture->PlatformData->Mips.Num())
    			{
    				FTexture2DMipMap& Mip = Texture->PlatformData->Mips[i];

    				void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
    				FMemory::Memcpy(Data, DataPtr, NumBytes);
    				Mip.BulkData.Unlock();
    			}

    			/* Add new mip */
    			else
    			{
    				FTexture2DMipMap* Mip = new(Texture->PlatformData->Mips) FTexture2DMipMap();
    				Mip->SizeX = CurrentWidth;
    				Mip->SizeY = CurrentHeight;

    				Mip->BulkData.Lock(LOCK_READ_WRITE);
    				Mip->BulkData.Realloc(NumBytes);
    				Mip->BulkData.Unlock();

    				void* Data = Mip->BulkData.Lock(LOCK_READ_WRITE);
    				FMemory::Memcpy(Data, DataPtr, NumBytes);
    				Mip->BulkData.Unlock();
    			}

    			/* Set next mip level */
    			CurrentWidth /= 2;
    			CurrentHeight /= 2;

    			DataPtr += NumBytes;
    		}

    		Texture->UpdateResource();
    	}
    }

    return Texture;
}