// Fill out your copyright notice in the Description page of Project Settings.

#include "PortfolioApp.h"
#include "DirectoryVisitor.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"
#include "Runtime/UMG/Public/Components/Button.h" 
#include "Category_Button.h"
#include "Categories_ScrollBox.h"
#include "PortfolioPlayerController.h"
#include <assert.h>
#include <string>


UCategories_ScrollBox::UCategories_ScrollBox(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
	, CurrentPath(FPaths::Combine(*FPaths::GameSavedDir(), TEXT("DiapoAssets")))
{
	//Default Values Set Here, see above
	//this->Slot()->SlotPadding( FMargin( 5 ) );
}

TSharedRef<SWidget> UCategories_ScrollBox::RebuildWidget()
{
	TSharedRef<SWidget> OurWidget = Super::RebuildWidget();
	return OurWidget;
}

void UCategories_ScrollBox::SetCurrentPath(FString p_sCurrentName)
{
	CurrentPath = p_sCurrentName;
}

FString UCategories_ScrollBox::GetCurrentPath()
{
	return CurrentPath;
}

void UCategories_ScrollBox::FillCatButtons(APortFolioPlayerController* p_pController)
{
	assert(p_pController != nullptr);
	TArray<FString> m_sSubDirectories = p_pController->GetSubDirectoriesFromController();

	for (auto name : m_sSubDirectories)
	{
		FString fullPath = FPaths::Combine(*CurrentPath, *name);
		FString cleanName = FPaths::GetBaseFilename(name);
		FString curPath = name.LeftChop(cleanName.Len() + 1);

		UCategory_Button* subCategoryButton = NewObject<UCategory_Button>(this, UCategory_Button::StaticClass());
		UTextBlock* subCategoryText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		subCategoryText->SetText(FText::FromString(cleanName));
		subCategoryButton->AddChild(subCategoryText);
		subCategoryButton->SetScrollBox(this);
		subCategoryButton->SetController(p_pController);
		subCategoryButton->SetSubCategoryPath(fullPath);
		this->AddChild(subCategoryButton);
		m_tmButtonToDir.Add(subCategoryButton, name);

		subCategoryButton->OnClicked.AddDynamic(subCategoryButton, &UCategory_Button::exploreSubCategory);

		subCategoryButton->WidgetStyle = ButtonStyle;

	}
	for (UPanelSlot* Slot : Slots)
	{
		if (UScrollBoxSlot* TypedSlot = Cast<UScrollBoxSlot>(Slot))
		{
			TypedSlot->SetPadding(FMargin(10));
		}
	}
}

void UCategories_ScrollBox::ListImagesToDisplay()
{
	TArray<FString> Files;
	GetFiles(CurrentPath, Files, false);
	for (auto fileName : Files)
	{
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		// Note: PNG format.  Other formats are supported
		IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
		TArray<uint8> RawFileData;

		if (FFileHelper::LoadFileToArray(RawFileData, *fileName))
		{
			if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
			{
				const TArray<uint8>* UncompressedBGRA = NULL;
				if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
				{
					m_aTextures.Add(UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8));
				}
			}
		}
	}
	DisplayImages.Broadcast();
}
