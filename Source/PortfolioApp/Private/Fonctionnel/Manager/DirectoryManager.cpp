#include "PortfolioApp.h"

#include "DirectoryManager.h"
#include "DirectoryVisitor.h"
#include "FileSort.h"

#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"
#include "Runtime/UMG/Public/Components/Button.h" 

#include <string>


DirectoryManager::DirectoryManager()
{

}


DirectoryManager::~DirectoryManager()
{
}


TArray<FString> DirectoryManager::GetSubDirectories()
{
	TArray<FString> DirNamesOut;
	if (FPaths::DirectoryExists(RootPath))
	{
		//IFileManager& FileManager = IFileManager::Get();
		
		TArray<FString> Files;
		if (RootPath.Len() > 1)
		{
			FPaths::NormalizeDirectoryName(RootPath);
			FString FinalPath = RootPath;// +"/" + "*.*";
			GetDirectories(FinalPath, DirNamesOut, false);
			GetFiles(FinalPath, Files, false);
		}
		if ((Files.Num() == 1 && Files[0] == "Thumbs.db") ||
			(Files.Num() == 0 && DirNamesOut.Num() > 0))
		{
			for (auto name : DirNamesOut)
			{
				FString fullPath = FPaths::Combine(*RootPath, *name);
				std::string strdir(TCHAR_TO_ANSI(*fullPath));
				FString cleanName = FPaths::GetBaseFilename(name);
				std::string strname(TCHAR_TO_ANSI(*cleanName));
				FString curPath = name.LeftChop(cleanName.Len() + 1);
				std::string strpath(TCHAR_TO_ANSI(*curPath));
			}
		}
		else
		{
			//FileSort::ListImagesToDisplay();
		}
	}
	return DirNamesOut;
}
