#pragma once

#include "TTCommandData.generated.h"

UENUM(BlueprintType)
enum class FVerbEnum : uint8
{
	CE_Unknown,

	// Universal verb
	CE_Go,			// Used for a lot of things (go north, go fish)

	CE_PickUp	UMETA(DisplayName = "Pick Up"),		// Pick something up
	CE_Drop,		// Drop something
	CE_Throw,		// Throw what's equipped
	CE_Use,			// Use something
	CE_Eat,			// Eat something
	CE_Stop,		// Stop what you are doing
	CE_Craft,		// Combine two things
	CE_Build,		// Build something in the world


	// Move
	CE_GoTo,		// Go to a position
	CE_Turn,		// Turn

	// Harvest
	CE_Harvest,		// Try to harvest something

	CE_Store,		// Store stuff in inventory
	//CE_Withdraw,

	// Utility
	CE_WhatsUp,		// Ask character how it feels?
	CE_ScanArea,	// Return what the character sees

	// Social
	CE_Hug,
	CE_Hit,
	CE_Speak,
	CE_Assist,
	CE_Highfive,
	CE_Pat,
	CE_Call,
	CE_Annoy,
	CE_Kill,

	CE_Equip,

	CE_Special
};

USTRUCT()
struct FCommandStruct
{
	GENERATED_BODY()

	FVerbEnum Verb;
	FString Object1;
	FString Object2;
};

USTRUCT(BlueprintType)
struct FKeyDictionary
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FVerbEnum Verb;

	UPROPERTY(EditAnywhere)
	TArray<FString> Keywords;

	bool ContainsKey(FString key)
	{
		return Keywords.Contains(key);
	}
};
