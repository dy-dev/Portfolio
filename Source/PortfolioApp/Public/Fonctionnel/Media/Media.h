#pragma once

#include <string>
#include "Enums.h"

#include "Media.generated.h"

UCLASS(Blueprintable)
class UMedia : public UObject
{
	GENERATED_BODY()

public:
	UMedia();
	~UMedia();
	virtual void Initializer(FString p_sPath, FString p_sFullPath, uint8 p_sExtension);


protected:
	FString m_sFullPath;
	FString m_sName;
	std::string m_sArtist;
	std::string m_sReleaseDate;
	std::string m_sType;
	uint8 m_iExtension;
};

