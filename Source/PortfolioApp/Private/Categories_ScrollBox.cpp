// Fill out your copyright notice in the Description page of Project Settings.

#include "PortfolioApp.h"
#include "DirectoryVisitor.h"
#include "Runtime/UMG/Public/Components/Button.h" 
#include "Category_Button.h"
#include "Categories_ScrollBox.h"


UCategories_ScrollBox::UCategories_ScrollBox( class FObjectInitializer const & ObjectInitializer )
    : Super( ObjectInitializer )
    , RootPath( FPaths::Combine( *FPaths::GameSavedDir(), TEXT( "DiapoAssets" ) ) )
{
    //Default Values Set Here, see above
    //this->Slot()->SlotPadding( FMargin( 5 ) );
}

TSharedRef<SWidget> UCategories_ScrollBox::RebuildWidget()
{
    TSharedRef<SWidget> OurWidget = Super::RebuildWidget();
    return OurWidget;
}



void UCategories_ScrollBox::FillButtons()
{
    if ( FPaths::DirectoryExists( RootPath ) )
    {
        IFileManager& FileManager = IFileManager::Get();
        TArray<FString> DirNamesOut;
        TArray<FString> Files;
        if ( RootPath.Len() > 1 )
        {
            FPaths::NormalizeDirectoryName( RootPath );
            FString FinalPath = RootPath;// +"/" + "*.*";
            GetDirectories( FinalPath, DirNamesOut, false );
            GetFiles( FinalPath, Files, false );
        }
        if ( (Files.Num() == 1 && Files[0] == "Thumbs.db" )||
             ( Files.Num() == 0 && DirNamesOut.Num() > 0 ) )
        {
            for ( auto name : DirNamesOut )
            {
                FString fullPath = FPaths::Combine( *RootPath, *name );
                std::string strdir( TCHAR_TO_ANSI( *fullPath ) );
                FString cleanName = FPaths::GetBaseFilename( name );
                std::string strname( TCHAR_TO_ANSI( *cleanName ) );
                FString curPath = name.LeftChop( cleanName.Len() + 1 );
                std::string strpath( TCHAR_TO_ANSI( *curPath ) );
                UCategory_Button* subCategoryButton = NewObject<UCategory_Button>( this, UCategory_Button::StaticClass() );

                UTextBlock* subCategoryText = NewObject<UTextBlock>( this, UTextBlock::StaticClass() );
                subCategoryText->SetText( FText::FromString( cleanName ) );
                subCategoryButton->AddChild( subCategoryText );
                subCategoryButton->SetScrollBox( this );
                subCategoryButton->SetSubCategoryPath( fullPath );
                this->AddChild( subCategoryButton );
                
                m_tmButtonToDir.Add( subCategoryButton, name );

                subCategoryButton->OnClicked.AddDynamic( subCategoryButton, &UCategory_Button::exploreSubCategory );

                subCategoryButton->WidgetStyle = ButtonStyle;
                
            }
            for ( UPanelSlot* Slot : Slots )
            {
                if ( UScrollBoxSlot* TypedSlot = Cast<UScrollBoxSlot>( Slot ) )
                {
                    TypedSlot->SetPadding( FMargin(10) );
                }
            }
        }
        else
        {
            ListImagesToDisplay();
        }
    }
}

void UCategories_ScrollBox::ListImagesToDisplay()
{
    TArray<FString> Files;
    GetFiles( RootPath, Files, false );
    for ( auto fileName : Files )
    {
        IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>( FName( "ImageWrapper" ) );
        // Note: PNG format.  Other formats are supported
        IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper( EImageFormat::PNG );
        TArray<uint8> RawFileData;

        if ( FFileHelper::LoadFileToArray( RawFileData, *fileName ) )
        {
            if ( ImageWrapper.IsValid() && ImageWrapper->SetCompressed( RawFileData.GetData(), RawFileData.Num() ) )
            {
                const TArray<uint8>* UncompressedBGRA = NULL;
                if ( ImageWrapper->GetRaw( ERGBFormat::BGRA, 8, UncompressedBGRA ) )
                {
                    m_aTextures.Add( UTexture2D::CreateTransient( ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8 ) );
                }
            }
        }
    }
    DisplayImages.Broadcast();
}
