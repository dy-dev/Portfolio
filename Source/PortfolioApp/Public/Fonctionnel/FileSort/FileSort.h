#pragma once

#include <Runtime/Core/Public/Containers/Map.h>
#include <utility>

class UMedia;

class FileSort
{
public:
	FileSort();
	~FileSort();

	//bool sortArray(FString p_sPath);

	TArray<TPair < FString, UMedia* >>& PrepareFiles(FString p_sPath);

private :
	TArray<TPair < FString, UMedia* >> m_vSortedAssociateNameToMedia;
	TArray<FString> m_asSortedFiles;

};
