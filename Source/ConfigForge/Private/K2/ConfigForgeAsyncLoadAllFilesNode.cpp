// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "K2/ConfigForgeAsyncLoadAllFilesNode.h"

#include "K2/ConfigForgeAsyncSaveFileNode.h"
#include "Subsystems/ConfigForgeSubsystem.h"


UConfigForgeAsyncLoadAllFilesNode* UConfigForgeAsyncLoadAllFilesNode::LoadConfigForgeFilesAsync(UObject* WorldContextObject)
{
	UConfigForgeAsyncLoadAllFilesNode* node = NewObject<UConfigForgeAsyncLoadAllFilesNode>();
	node->WorldContextObject = WorldContextObject;

	return node;
}

void UConfigForgeAsyncLoadAllFilesNode::Activate()
{
	if (!WorldContextObject.IsValid())
	{
		OnFinished.Broadcast({}, false);
		SetReadyToDestroy();
		return;
	}

	UWorld* world = GEngine->GetWorldFromContextObjectChecked(WorldContextObject.Get());
	UGameInstance* gi = world->GetGameInstance();
	if (!gi)
	{
		OnFinished.Broadcast({}, false);
		SetReadyToDestroy();
		return;
	}

	UConfigForgeSubsystem* configForgeSubsystem = gi->GetSubsystem<UConfigForgeSubsystem>();
	if (!configForgeSubsystem)
	{
		OnFinished.Broadcast({}, false);
		SetReadyToDestroy();
		return;
	}

	// Create delegate for callback
	FLoadAllForgeFileDelegate callback;
	callback.BindUObject(this, &UConfigForgeAsyncLoadAllFilesNode::OnLoadComplete);

	// Start async load
	configForgeSubsystem->LoadAllFilesAsync(callback);
}

void UConfigForgeAsyncLoadAllFilesNode::OnLoadComplete(bool bSuccess, const TArray<UConfigForgeFileRuntime*>& InFiles)
{
	OnFinished.Broadcast(InFiles, bSuccess);
	SetReadyToDestroy();
}