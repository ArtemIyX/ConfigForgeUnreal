// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "K2/ConfigForgeAsyncSaveFileNode.h"

#include "Subsystems/ConfigForgeSubsystem.h"

UConfigForgeAsyncSaveFileNode* UConfigForgeAsyncSaveFileNode::SaveConfigForgeFileAsync(UObject* WorldContextObject, const FGuid& InFileUniqueID)
{
	UConfigForgeAsyncSaveFileNode* Node = NewObject<UConfigForgeAsyncSaveFileNode>();
	Node->WorldContextObject = WorldContextObject;
	Node->FileID = InFileUniqueID;
	return Node;
}

void UConfigForgeAsyncSaveFileNode::Activate()
{
	if (!WorldContextObject.IsValid())
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		return;
	}

	UWorld* world = GEngine->GetWorldFromContextObjectChecked(WorldContextObject.Get());
	UGameInstance* gi = world->GetGameInstance();
	if (!gi)
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		return;
	}

	UConfigForgeSubsystem* configForgeSubsystem = gi->GetSubsystem<UConfigForgeSubsystem>();
	if (!configForgeSubsystem)
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		return;
	}

	// Create delegate for callback
	FSaveForgeFileDelegate callback;
	callback.BindUObject(this, &UConfigForgeAsyncSaveFileNode::OnSaveComplete);

	// Start async load
	configForgeSubsystem->SaveSingleFileAsync(FileID, callback);
}

void UConfigForgeAsyncSaveFileNode::OnSaveComplete(bool bSuccess)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFailure.Broadcast();
	}
	SetReadyToDestroy();
}