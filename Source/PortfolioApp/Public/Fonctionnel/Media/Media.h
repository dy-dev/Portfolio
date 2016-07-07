#pragma once

#include <string>

class Media
{
public:
	Media();
	~Media();

protected:
	std::string m_sFullPath;
	std::string m_sName;
	std::string m_sArtist;
	std::string m_sReleaseDate;
	std::string m_sType;
	std::string m_sExtension;
};

