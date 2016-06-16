#pragma once
class Loader
{
public:
	Loader();
	~Loader();

	//string ImagesPaths;
	//todo declare Load function
	void Load(FString p_sPath, UImagesHolder* p_pHolder);


	virtual FString CreateSearchPaths(FString p_sPath, UImagesHolder* p_pHolder) = 0;
};

