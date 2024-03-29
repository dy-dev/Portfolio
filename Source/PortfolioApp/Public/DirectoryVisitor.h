#pragma once
template <class FunctorType>
class PlatformFileFunctor : public IPlatformFile::FDirectoryVisitor	//GenericPlatformFile.h
{
public:

	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
	{
		return Functor(FilenameOrDirectory, bIsDirectory);
	}

	PlatformFileFunctor(FunctorType&& FunctorInstance)
		: Functor(MoveTemp(FunctorInstance))
	{
	}

private:
	FunctorType Functor;
};

template <class Functor>
PlatformFileFunctor<Functor> MakeDirectoryVisitor(Functor&& FunctorInstance)
{
	return PlatformFileFunctor<Functor>(MoveTemp(FunctorInstance));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Victory Get All Files
//      Optional File Extension Filter!!!  by Rama
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static FORCEINLINE  bool GetFiles(const FString& FullPathOfBaseDir, TArray<FString>& FilenamesOut, bool Recursive = false, const FString& FilterByExtension = "")
{
	//Format File Extension, remove the "." if present
	const FString FileExt = FilterByExtension.Replace(TEXT("."), TEXT("")).ToLower();

	FString Str;
	auto FilenamesVisitor = MakeDirectoryVisitor(
		[&](const TCHAR* FilenameOrDirectory, bool bIsDirectory)
	{
		//Files
		if (!bIsDirectory)
		{
			//Filter by Extension
			if (FileExt != "")
			{
				Str = FPaths::GetCleanFilename(FilenameOrDirectory);

				//Filter by Extension
				if (FPaths::GetExtension(Str).ToLower() == FileExt)
				{
					if (Recursive)
					{
						FilenamesOut.Push(FilenameOrDirectory); //need whole path for recursive
					}
					else
					{
						FilenamesOut.Push(Str);
					}
				}
			}

			//Include All Filenames!
			else
			{
				//Just the Directory
				Str = FPaths::GetCleanFilename(FilenameOrDirectory);

				if (Recursive)
				{
					FilenamesOut.Push(FilenameOrDirectory); //need whole path for recursive
				}
				else
				{
					FilenamesOut.Push(Str);
				}
			}
		}
		return true;
	}
	);
	if (Recursive)
	{
		return FPlatformFileManager::Get().GetPlatformFile().IterateDirectoryRecursively(*FullPathOfBaseDir, FilenamesVisitor);
	}
	else
	{
		return FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*FullPathOfBaseDir, FilenamesVisitor);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Victory Get Directories
//      Optional Search SubString!!!  by Rama
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Get Directories
static FORCEINLINE bool GetDirectories(const FString& FullPathOfBaseDir, TArray<FString>& DirsOut, bool Recursive = false, const FString& ContainsStr = "")
{
	FString Str;
	auto FilenamesVisitor = MakeDirectoryVisitor(
		[&](const TCHAR* FilenameOrDirectory, bool bIsDirectory)
	{
		if (bIsDirectory)
		{
			//Using a Contains Filter?
			if (ContainsStr != "")
			{
				Str = FPaths::GetCleanFilename(FilenameOrDirectory);

				//Only if Directory Contains Str
				if (Str.Contains(ContainsStr))
				{
					if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
					else DirsOut.Push(Str);
				}
			}

			//Get ALL Directories!
			else
			{
				//Just the Directory
				Str = FPaths::GetCleanFilename(FilenameOrDirectory);

				if (Recursive) DirsOut.Add(FilenameOrDirectory); //need whole path for recursive
				else DirsOut.Add(Str);
			}
		}
		return true;
	}
	);
	if (Recursive)
	{
		return FPlatformFileManager::Get().GetPlatformFile().IterateDirectoryRecursively(*FullPathOfBaseDir, FilenamesVisitor);
	}
	else
	{
		return FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*FullPathOfBaseDir, FilenamesVisitor);
	}
}
