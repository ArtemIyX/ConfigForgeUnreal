// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "K2/ConfigForgeAsyncSaveAllFilesNode.h"

#include "Subsystems/ConfigForgeSubsystem.h"

UConfigForgeAsyncSaveAllFilesNode* UConfigForgeAsyncSaveAllFilesNode::SaveConfigForgeFilesAsync(UObject* WorldContextObject)
{
	UConfigForgeAsyncSaveAllFilesNode* node = NewObject<UConfigForgeAsyncSaveAllFilesNode>();
	node->WorldContextObject = WorldContextObject;
	return node;
}


void UConfigForgeAsyncSaveAllFilesNode::Activate()
{
	if (!WorldContextObject.IsValid())
	{
		OnFinished.Broadcast(false);
		SetReadyToDestroy();
		return;
	}

	UWorld* world = GEngine->GetWorldFromContextObjectChecked(WorldContextObject.Get());
	UGameInstance* gi = world->GetGameInstance();
	if (!gi)
	{
		OnFinished.Broadcast(false);
		SetReadyToDestroy();
		return;
	}

	UConfigForgeSubsystem* configForgeSubsystem = gi->GetSubsystem<UConfigForgeSubsystem>();
	if (!configForgeSubsystem)
	{
		OnFinished.Broadcast(false);
		SetReadyToDestroy();
		return;
	}

	// Create delegate for callback
	FSaveAllForgeFileDelegate callback;
	callback.BindUObject(this, &UConfigForgeAsyncSaveAllFilesNode::OnSaveComplete);

	// Start async load
	configForgeSubsystem->SaveAllFilesAsync(callback);
}

void UConfigForgeAsyncSaveAllFilesNode::OnSaveComplete(bool bSuccess)
{
	OnFinished.Broadcast(bSuccess);
	SetReadyToDestroy();
}