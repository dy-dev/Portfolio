#pragma once

#include <string>

class Media;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EMedia : uint8
{
	EPicture 	    UMETA(DisplayName = "Picture"),
	EAnim 			UMETA(DisplayName = "Anim"),
	ESound 			UMETA(DisplayName = "Sound"),
	EObject3D 	    UMETA(DisplayName = "Object3D"),
	EUndefined		UMETA(DisplayName = "Undefined")
};

class MediaFactory
{
public:
	static MediaFactory* getInstance();

	Media* createMedia(FString p_sPath);
	EMedia returnType(FString p_sPath);

private :
	MediaFactory();
	~MediaFactory();

	static MediaFactory* uniqueInstance;
};

