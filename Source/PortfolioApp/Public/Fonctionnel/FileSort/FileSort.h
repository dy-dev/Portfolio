#pragma once
#include <utility>

class Media;

class FileSort
{
public:
	FileSort();
	~FileSort();

	//bool sortArray(FString p_sPath);

	TArray<std::pair < FString, Media* >>& PrepareFiles(FString p_sPath);

private :
	TArray<std::pair < FString, Media* >> m_vSortedAssociateNameToMedia;
	TArray<FString> m_asSortedFiles;

};
