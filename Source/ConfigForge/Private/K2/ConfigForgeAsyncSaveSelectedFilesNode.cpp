// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "K2/ConfigForgeAsyncSaveSelectedFilesNode.h"

#include "Subsystems/ConfigForgeSubsystem.h"

UConfigForgeAsyncLoadSelectedFilesNode* UConfigForgeAsyncLoadSelectedFilesNode::LoadConfigForgeSelectedFilesAsync(UObject* WorldContextObject, const TArray<FConfigForgeFileData>& InFiles)
{
	UConfigForgeAsyncLoadSelectedFilesNode* node = NewObject<UConfigForgeAsyncLoadSelectedFilesNode>();
	node->WorldContextObject = WorldContextObject;
	node->Files = InFiles;
	return node;
}

void UConfigForgeAsyncLoadSelectedFilesNode::Activate()
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
	callback.BindUObject(this, &UConfigForgeAsyncLoadSelectedFilesNode::OnLoadComplete);

	// Start async load
	configForgeSubsystem->LoadSelectedFilesAsync(Files, callback);
}

void UConfigForgeAsyncLoadSelectedFilesNode::OnLoadComplete(bool bSuccess, const TArray<UConfigForgeFileRuntime*>& InFiles)
{
	OnFinished.Broadcast(InFiles, bSuccess);
	SetReadyToDestroy();
}