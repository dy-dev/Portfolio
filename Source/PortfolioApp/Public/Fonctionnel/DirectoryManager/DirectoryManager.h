#pragma once



class DirectoryManager
{
public:
	DirectoryManager();
	~DirectoryManager();

	FString GetCurrentPath() { return m_sCurrentPath; };

	FString RootPath;

	TArray<FString> GetSubDirectories();

private:
	FString m_sCurrentPath;
};

