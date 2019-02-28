#pragma once

#include "GameFramework/Actor.h"
#include "TTCommandListenerComponent.h"
#include "TTCommandData.h"
#include "TTCommandSystem.generated.h"

// Deprecate these
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewUnit, const AActor*, unit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommandEvent_SelectedUnits, const TArray<class UTTCommandListenerComponent*>, commandListeners);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCommandEvent, const FString, verb, const FString, object);



UENUM()
enum FCommandTypeEnum
{
	CT_Error,
	CT_Verb,
	CT_Object
};

USTRUCT()
struct FCommandQueueStruct
{
	GENERATED_BODY()

	FCommandTypeEnum type;
	FString text;
};

UCLASS()
class GP2_TEAM3_API ATTCommandSystem : public AActor
{
	GENERATED_BODY()

protected:
	void virtual BeginPlay() override;
	
private:	
	// Collections of stuff
	TArray<FString> interactableNames;
	TArray<FString> verbs;
	TArray<FString> specialCommands;

	TArray<UTTCommandListenerComponent*> listeners;
	UTTCommandListenerComponent* SelectedListener;
	TArray<UTTCommandListenerComponent*> selectedListeners;

	// Analyze command and send enum to listener
	FVerbEnum ParseVerbToCommand(FString verb);
	UTTCommandListenerComponent* GetListener(FString name);

	// Send Command to unit
	void SendCommandToUnit();

	//void SelectListener(UTTCommandListenerComponent* newListener, bool clearSelected = true);
	void SelectListeners(TArray<UTTCommandListenerComponent*> listeners);

	TArray<FCommandQueueStruct> commandQueue;

	class ATTGameMode* gameMode;

	TArray<FString> keywordCombinations;


public:
	UFUNCTION(BlueprintCallable)
	void BuildVoiceDictionary();
	// Relays the text to the text to command system
	UFUNCTION(BlueprintCallable)
	void StringToCommand(FString text);

	void AddInteractable(FName Command);

	void AddUnit(class UTTCommandListenerComponent* unit);
	void RemoveUnit(class UTTCommandListenerComponent* unit);

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FOnNewUnit OnNewUnit;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent OnCommand;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_SelectedUnits OnNewUnits;
	
};