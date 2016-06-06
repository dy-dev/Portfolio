// File Tree Viewer by Rama
//
#include "PortfolioApp.h"
//
////This header
#include "SDDFileTree.h"
#include "SlateOptMacros.h"
#include "DirectoryVisitor.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"

//
//The Data
#include "DDFileTreeItem.h"
#include <string>


#define LOCTEXT_NAMESPACE "SStandardSlateWidget"


void SDDFileTree::Construct(const FArguments& Args/*, TWeakObjectPtr<class UDDEdEngine> IN_DDEdEngine*/)
{
	//Set DDEdEngine
	//DDEdEngine = IN_DDEdEngine;
	//~~~~~~~~~~~~~~~~~~~
	OwnerHUD = Args._OwnerHUD;

	//Build Core Data
	RebuildFileTree();

	//Build the tree view of the above core data
	DDFileTreeView =
		SNew(SDDFileTreeView)
		// For now we only support selecting a single folder in the tree
		.SelectionMode(ESelectionMode::Single)
		.ClearSelectionOnClick(false)		// Don't allow user to select nothing.

		.TreeItemsSource(&Directories)
		.OnGenerateRow(this, &SDDFileTree::DDFileTree_OnGenerateRow)
		.OnGetChildren(this, &SDDFileTree::DDFileTree_OnGetChildren)

		.OnSelectionChanged(this, &SDDFileTree::DDFileTree_OnSelectionChanged)

		;

	/*
	// Expand the root  by default
	for( auto RootDirIt( Directories.CreateConstIterator() ); RootDirIt; ++RootDirIt )
	{
	const auto& Dir = *RootDirIt;
	DDFileTreeView->SetItemExpansion( Dir, true );
	}

	// Select the first item by default
	if( Directories.Num() > 0 )
	{
	DDFileTreeView->SetSelection( Directories[ 0 ] );
	}
	*/

	ChildSlot.AttachWidget(DDFileTreeView.ToSharedRef());
}


SDDFileTree::~SDDFileTree()
{
}



void SDDFileTree::RebuildFileTree()
{
	Directories.Empty();

	//~~~~~~~~~~~~~~~~~~~
	//Root Level
//	
///*	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL, 
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::AutomationDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::AutomationDir()))) ) );
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::GameDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::GameDir())))));
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::GameSavedDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::GameSavedDir())))));
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::BugItDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::BugItDir())))));
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::CloudDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::CloudDir())))));
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::EngineDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::EngineDir())))) ) ;
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::RootDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::RootDir())))));*/
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPlatformProcess::UserSettingsDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPlatformProcess::UserSettingsDir())))));
//	/*Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::LaunchDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::LaunchDir())))));
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::EngineDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::EngineDir())))));*/
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::GameDevelopersDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::GameDevelopersDir())))));
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(TCHAR_TO_ANSI(FPlatformProcess::BaseDir())),
//		FPaths::ConvertRelativePathToFull(TCHAR_TO_ANSI(FPlatformProcess::BaseDir())))));
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPlatformProcess::GenerateApplicationPath(FPlatformProcess::ExecutableName(true), EBuildConfigurations::Debug)),
//		FPaths::ConvertRelativePathToFull(FPlatformProcess::GenerateApplicationPath(FPlatformProcess::ExecutableName(true), EBuildConfigurations::Debug)))));
//	Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::GameSavedDir())),
//		FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::GameSavedDir())) )));

		//Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
		//	FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::GameUserDir())),
		//	FPaths::ConvertRelativePathToFull(FPaths::GetCleanFilename(FPaths::GameUserDir())))));
		//Directories.Add(MakeShareable(new FDDFileTreeItem(NULL,
		//	FPaths::ConvertRelativePathToFull(TCHAR_TO_ANSI(FPlatformProcess::UserSettingsDir())),
		//	FPaths::ConvertRelativePathToFull(TCHAR_TO_ANSI(FPlatformProcess::UserSettingsDir())))));
	FString path = FPaths::Combine(*FPaths::GameSavedDir(), TEXT("DiapoAssets"));
	if (FPaths::DirectoryExists(path))
	{
		TSharedRef<FDDFileTreeItem> RootDir = MakeShareable(new FDDFileTreeItem(NULL, path, FPaths::GetCleanFilename(path)));
		Directories.Add(RootDir);
		PathsToDirectories.Add(path, RootDir);

		//~~~~~~~~~~~~~~~~~~~

		//Root Category
		FDDFileTreeItemPtr ParentCategory = RootDir;


		IFileManager& FileManager = IFileManager::Get();
		TArray<FString> DirNamesOut;
		if (path.Len() > 1)
		{
			FPaths::NormalizeDirectoryName(path);
			FString FinalPath = path;// +"/" + "*.*";
			FString Str;
			GetDirectories(FinalPath, DirNamesOut, true);
		}
		FDDFileTreeItemPtr curDir = RootDir;
		for (auto names : DirNamesOut)
		{
			std::string strdir(TCHAR_TO_ANSI(*names));
			FString cleanName = FPaths::GetBaseFilename(names);
			std::string strname(TCHAR_TO_ANSI(*cleanName));
			FString curPath = names.LeftChop(cleanName.Len() + 1);
			std::string strpath(TCHAR_TO_ANSI(*curPath));
			FDDFileTreeItemPtr EachSubDir = MakeShareable(new FDDFileTreeItem(ParentCategory, names, names));
			FDDFileTreeItemPtr* ptr = PathsToDirectories.Find(curPath);
			if (ptr != nullptr)
			{
				(*ptr)->AddSubDirectory(EachSubDir);
			}
			else
			{
				curDir->AddSubDirectory(EachSubDir);
			}
			PathsToDirectories.Add(names, EachSubDir);
			curDir = EachSubDir;
			TArray<FString> Files;
			GetFiles(names, Files, false);
			for (auto fileName : Files)
			{
				FDDFileTreeItemPtr file = MakeShareable(new FDDFileTreeItem(ParentCategory, fileName, FPaths::GetBaseFilename(fileName)));
				curDir->AddSubDirectory(file);


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
							Images.Add(UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8));
						}
					}
				}
			}
		}

		//Refresh
		if (DDFileTreeView.IsValid())
		{
			DDFileTreeView->RequestTreeRefresh();
		}
	}
	//TODO else show display message it needs a specific path to store assets for the diaporama
}

TSharedRef<ITableRow> SDDFileTree::DDFileTree_OnGenerateRow(FDDFileTreeItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (!Item.IsValid())
	{
		return SNew(STableRow< FDDFileTreeItemPtr >, OwnerTable)
			[
				SNew(STextBlock).Text(FText::FromString("THIS WAS NULL SOMEHOW"))
			];
	}
	return SNew(STableRow< FDDFileTreeItemPtr >, OwnerTable)
		[
			SNew(STextBlock)
		//	.Text(Item->GetDisplayName())
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("/Slate/Fonts/Roboto-Bold.ttf"), 24))
		.ColorAndOpacity(FLinearColor(1, 0, 1, 1))
		.ShadowColorAndOpacity(FLinearColor::Black)
		.ShadowOffset(FIntPoint(-2, 2))
		];
}


void SDDFileTree::DDFileTree_OnGetChildren(FDDFileTreeItemPtr Item, TArray< FDDFileTreeItemPtr >& OutChildren)
{
	const auto& SubCategories = Item->GetSubDirectories();
	OutChildren.Append(SubCategories);
}


//Key function for interaction with user!
void SDDFileTree::DDFileTree_OnSelectionChanged(FDDFileTreeItemPtr Item, ESelectInfo::Type SelectInfo)
{
	//Selection Changed! Tell DDEdEngine!
	UE_LOG(LogDebug, Warning, TEXT("Item Selected: %s"), *Item->GetDisplayName());
}


FDDFileTreeItemPtr SDDFileTree::GetSelectedDirectory() const
{
	if (DDFileTreeView.IsValid())
	{
		auto SelectedItems = DDFileTreeView->GetSelectedItems();
		if (SelectedItems.Num() > 0)
		{
			const auto& SelectedCategoryItem = SelectedItems[0];
			return SelectedCategoryItem;
		}
	}

	return NULL;
}


void SDDFileTree::SelectDirectory(const FDDFileTreeItemPtr& CategoryToSelect)
{
	if (ensure(DDFileTreeView.IsValid()))
	{
		DDFileTreeView->SetSelection(CategoryToSelect);
	}
}

//is the tree item expanded to show children?
bool SDDFileTree::IsItemExpanded(const FDDFileTreeItemPtr Item) const
{
	return DDFileTreeView->IsItemExpanded(Item);
}



void SDDFileTree::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	// Call parent implementation
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	//can do things here every tick
}


bool SDDFileTree::PortFolio_GetFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext)
{
	if (RootFolderFullPath.Len() < 1) return false;

	FPaths::NormalizeDirectoryName(RootFolderFullPath);

	IFileManager& FileManager = IFileManager::Get();

	if (Ext == "")
	{
		Ext = "*.*";
	}
	else
	{
		Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
	}

	FString FinalPath = RootFolderFullPath + "/" + Ext;
	FileManager.FindFiles(Files, *FinalPath, true, false);
	return true;
}