#pragma once

#include <string>
#include "Enums.h"

class Media
{
public:
	Media();
	~Media();

protected:
	FString m_sFullPath;
	std::string m_sName;
	std::string m_sArtist;
	std::string m_sReleaseDate;
	std::string m_sType;
	uint8 m_iExtension;
};

