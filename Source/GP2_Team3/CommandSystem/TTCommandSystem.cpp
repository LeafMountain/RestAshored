#include "TTCommandSystem.h"
#include "Engine/Engine.h"
#include "TTGameMode.h"
#include "Components/Interaction/TTInteractableComponent.h"

// For debug purposes
void PrintQueue(TArray<FCommandQueueStruct>* commandQueue)
{
	FString debugOutput = "";

	for (int i = 0; i < (*commandQueue).Num(); i++)
	{
		switch ((*commandQueue)[i].type)
		{
		case CT_Verb:
			debugOutput += " Verb: ";
			debugOutput += *(*commandQueue)[i].text;			
			break;
		case CT_Object:
			debugOutput += " Object: ";
			debugOutput += *(*commandQueue)[i].text;
			break;
		}
	}

	if(debugOutput != "")
		UE_LOG(LogTemp, Log, TEXT("[CommandSystem] %s"), *debugOutput);
}

void ATTCommandSystem::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<ATTGameMode>(GetWorld()->GetAuthGameMode());

	// Add verbs
	for (FKeyDictionary dictionary : gameMode->KeyDictionary)
	{
		for (FString verb : dictionary.Keywords)
		{
			verbs.Add(verb);
		}
	}

	// Add extra words
	for (FString word : gameMode->ExtraWords)
	{
		interactableNames.Add(word);
	}
}

void ATTCommandSystem::SendCommandToUnit()
{
	if (selectedListeners.Num() <= 0)
		return;

	FCommandStruct command;
	command.Verb = FVerbEnum::CE_Unknown;

	for (int i = 0; i < commandQueue.Num(); i++)
	{
		switch (commandQueue[i].type)
		{
		case CT_Verb:
			//ClearCommand();
			command.Verb = ParseVerbToCommand(commandQueue[i].text);
			break;
		case CT_Object:
			if(command.Object1 == "")
				command.Object1 = *commandQueue[i].text;
			else
				command.Object2 = *commandQueue[i].text;
			break;
		}
	}

	commandQueue.Empty();

	for (UTTCommandListenerComponent* listener : selectedListeners)
	{
		listener->AddCommandAndClear(command);
	}
}

void ATTCommandSystem::SelectListeners(TArray<UTTCommandListenerComponent*> newListeners)
{
	for (int i = 0; i < selectedListeners.Num(); i ++)
	{
		if (!newListeners.Contains(selectedListeners[i]))
		{
			selectedListeners[i]->Deselect();
		}
	}

	selectedListeners = newListeners;
	FString logMessage = "[CommandSystem] Selecting unit";
	if (selectedListeners.Num() > 1)
		logMessage += "s";

	for (int i = 0; i < selectedListeners.Num(); i++)
	{
		selectedListeners[i]->Select();
		logMessage += selectedListeners[i]->ListenerTag.ToString();
		if (i != selectedListeners.Num() - 1)
			logMessage += " ";
	}

	UE_LOG(LogTemp, Log, TEXT("%s"), *logMessage);

	OnNewUnit.Broadcast(selectedListeners[0]->GetOwner());
	OnNewUnits.Broadcast(selectedListeners);
}

void ATTCommandSystem::BuildVoiceDictionary()
{
	// expand the array
	keywordCombinations.SetNum(verbs.Num() * interactableNames.Num() * interactableNames.Num());
	FString phrase;

	for (int i = 0; i < verbs.Num(); i++)
	{
		for (int j = 0; j < interactableNames.Num(); j++)
		{
			for (int k = 0; k < interactableNames.Num(); k++)
			{
				keywordCombinations.Add(verbs[i] + " " + interactableNames[j] + " " + interactableNames[k]);
			}
		}
	}

	int pause = 0;
}

void ATTCommandSystem::StringToCommand(FString text)
{
	// Exit function since there's no command listeners
	if (listeners.Num() < 1 || !listeners[0])
		return;

	// Remove the spaces in the beginning of the string
	text.TrimStartInline();

	// Check if the first word is a name (Special check on the first word)
	TArray<UTTCommandListenerComponent*> commandListeners;

	// Check if the word is everyone
	FString listenerName = "everyone";
	if (text.StartsWith(listenerName))
	{
		// Add all the listeners
		for (UTTCommandListenerComponent* listener : listeners)
		{
			commandListeners.Add(listener);
		}
	}
	// Or check which listeners the player tried to select
	else
	{
		int listenersNum = listeners.Num();
		for (int i = 0; i < listenersNum; i++)
		{
			text.TrimStartInline();

			FString listenerName = listeners[i]->ListenerTag.ToString();
			bool wordsMatched = text.RemoveFromStart(listenerName);
			if (wordsMatched)
			{
				if(!commandListeners.Contains(listeners[i]))
					commandListeners.Add(listeners[i]);
	
				i = -1;
			}
		}
	}

	// Select the listeners if any has been found
	if(commandListeners.Num() > 0)
		SelectListeners(commandListeners);

	int verbsNum = verbs.Num();
	int interactablesNum = interactableNames.Num();

	while(text.Len() > 2)
	{
		bool wordsMatched = false;

		// loop through all the words
		for (int i = 0; i < verbsNum + interactablesNum; i++)
		{
			// Clean up the text
			text.TrimStartInline();

			// Flag to check if within verbs arrays range
			bool withinVerbsRange = i < verbsNum;
			// Calculate the correct index to use depending on array
			int correctIndex = withinVerbsRange ? i : i - verbsNum;
			// Get the word we want to compare
			FString wordToCompare = withinVerbsRange ? verbs[correctIndex] : interactableNames[correctIndex];

			wordsMatched = text.RemoveFromStart(wordToCompare) ;
			if (wordsMatched)
			{
				// add the command as well
				FCommandQueueStruct newCommand;
				newCommand.type = withinVerbsRange ? CT_Verb : CT_Object;
				newCommand.text = wordToCompare;

				commandQueue.Add(newCommand);

				break;
			}
		}

		// Remove the first word since it's not recognized
		if (!wordsMatched)
		{
			// Remove first word
			int spaceIndex;
			text.FindChar(' ', spaceIndex);

			if (spaceIndex < 0)
				text.Empty();
			else
				text.RemoveAt(0, spaceIndex + 1);
		}
	}

	PrintQueue(&commandQueue);
	SendCommandToUnit();
}

// IMPLEMENT A BETTER WAY OF SORTING IF WE ARE GOING TO USE THIS!!!!!!!!!!!!!!!!!
void SortListByFStringLength(TArray<FString>& array)
{
	for (int i = 1; i < array.Num(); i++)
	{
		if (array[i].Len() > array[i - 1].Len())
		{
			FString temp = array[i];
			array[i] = array[i - 1];
			array[i - 1] = temp;
			i = 0;
		}
	}
}

void ATTCommandSystem::AddInteractable(FName Command)
{
	interactableNames.AddUnique(Command.ToString());
	SortListByFStringLength(interactableNames);
}

void ATTCommandSystem::AddUnit(UTTCommandListenerComponent* listener)
{
	UE_LOG(LogTemp, Log, TEXT("[CommandSystem] Adding %s to listeners."), *listener->ListenerTag.ToString());
	listeners.Add(listener);
}

void ATTCommandSystem::RemoveUnit(class UTTCommandListenerComponent* unit)
{
	listeners.Remove(unit);
}

UTTCommandListenerComponent* ATTCommandSystem::GetListener(FString name)
{
	for (int i = 0; i < listeners.Num(); i++)
	{
		if (listeners[i]->ListenerTag == FName(*name))
		{
			return listeners[i];
		}
	}

	return nullptr;
}

FVerbEnum ATTCommandSystem::ParseVerbToCommand(FString verb)
{
	for (FKeyDictionary dictionary : gameMode->KeyDictionary)
	{
		if (dictionary.ContainsKey(verb))
		{
			return dictionary.Verb;
		}
	}

	return FVerbEnum::CE_Unknown;
}
