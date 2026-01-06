// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "K2/ConfigForgeAsyncLoadFileNode.h"
#include "Engine/GameInstance.h"

UConfigForgeAsyncLoadFileNode* UConfigForgeAsyncLoadFileNode::LoadConfigForgeFileAsync(UObject* WorldContextObject, const FConfigForgeFileData& FileData)
{
	UConfigForgeAsyncLoadFileNode* Node = NewObject<UConfigForgeAsyncLoadFileNode>();
	Node->WorldContextObject = WorldContextObject;
	Node->FileData = FileData;
	return Node;
}

void UConfigForgeAsyncLoadFileNode::Activate()
{
	if (!WorldContextObject.IsValid())
	{
		OnFailure.Broadcast(nullptr);
		SetReadyToDestroy();
		return;
	}

	UWorld* world = GEngine->GetWorldFromContextObjectChecked(WorldContextObject.Get());
	UGameInstance* gi = world->GetGameInstance();
	if (!gi)
	{
		OnFailure.Broadcast(nullptr);
		SetReadyToDestroy();
		return;
	}

	UConfigForgeSubsystem* configForgeSubsystem = gi->GetSubsystem<UConfigForgeSubsystem>();
	if (!configForgeSubsystem)
	{
		OnFailure.Broadcast(nullptr);
		SetReadyToDestroy();
		return;
	}

	// Create delegate for callback
	FLoadForgeFileDelegate callback;
	callback.BindUObject(this, &UConfigForgeAsyncLoadFileNode::OnLoadComplete);

	// Start async load
	configForgeSubsystem->LoadSingleFileAsync(FileData, callback);
}

void UConfigForgeAsyncLoadFileNode::OnLoadComplete(bool bSuccess, UConfigForgeFileRuntime* LoadedFile)
{
	if (bSuccess && LoadedFile)
	{
		OnSuccess.Broadcast(LoadedFile);
	}
	else
	{
		OnFailure.Broadcast(nullptr);
	}

	SetReadyToDestroy();
}