#pragma once



class DirectoryManager
{
public:
	DirectoryManager();
	~DirectoryManager();

	FString RootPath;

	TArray<FString> GetSubDirectories();
};

