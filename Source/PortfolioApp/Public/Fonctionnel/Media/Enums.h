#pragma once

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EMedia : uint8
{
	EPicture 	    UMETA(DisplayName = "Picture"),
	EAnim 			UMETA(DisplayName = "Anim"),
	ESound 			UMETA(DisplayName = "Sound"),
	EObject3D 	    UMETA(DisplayName = "Object3D"),
	EUndefined		UMETA(DisplayName = "Undefined")
};

UENUM(BlueprintType)
enum class EExtension : uint8
{
	EJPG 			UMETA(DisplayName = "JPG"),
	EPNG 			UMETA(DisplayName = "PNG"),
	EBMP			UMETA(DisplayName = "BMP"),
	EAVI			UMETA(DisplayName = "AVI"),
	EMP4			UMETA(DisplayName = "MP4"),
	EWMV			UMETA(DisplayName = "WMV"),
	EMP3			UMETA(DisplayName = "MP3"),
	EWAV			UMETA(DisplayName = "WAV"),
	EOBJ			UMETA(DisplayName = "OBJ"),
	EFBX			UMETA(DisplayName = "FBX"),
	E3DS			UMETA(DisplayName = "3DS"),
	EUndefined		UMETA(DisplayName = "Undefined")
};

