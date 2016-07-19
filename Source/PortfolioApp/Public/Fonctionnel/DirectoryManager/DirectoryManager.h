#pragma once



class DirectoryManager
{
public:
	DirectoryManager();
	~DirectoryManager();

	void SetCurrentPath(FString p_sPath);

	FString GetCurrentPath() { return m_sCurrentPath; };

	FString RootPath;

	TArray<FString> GetSubDirectories();

private:
	FString m_sCurrentPath;
};

