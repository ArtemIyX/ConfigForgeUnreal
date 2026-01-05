// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Libs/ConfigForgeLibrary.h"

#include "ConfigForge.h"
#include "Subsystems/ConfigForgeSubsystem.h"


bool UConfigForgeLibrary::GetConfigForgeFile(const UObject* WorldContextObject, const FString& InFileName, FConfigForgeFileData& OutFileData)
{
	if (!WorldContextObject)
	{
		UE_LOG(LogConfigForge, Error, TEXT("%hs %d GetConfigForgeFile: WorldContextObject is null"), __FUNCTION__, __LINE__);
		return false;
	}

	// Get the world from the context object
	UWorld* world = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!world)
	{
		UE_LOG(LogConfigForge, Error, TEXT("%hs %d GetConfigForgeFile: Failed to get World from context object"), __FUNCTION__, __LINE__);
		return false;
	}

	// Get the game instance
	UGameInstance* gi = world->GetGameInstance();
	if (!gi)
	{
		UE_LOG(LogConfigForge, Error, TEXT("%hs %d GameInstance is null"), __FUNCTION__, __LINE__);
		return false;
	}

	// Get the ConfigForge subsystem
	UConfigForgeSubsystem* subsystem = gi->GetSubsystem<UConfigForgeSubsystem>();
	if (!subsystem)
	{
		UE_LOG(LogConfigForge, Error, TEXT("%hs %d GetConfigForgeFile: ConfigForgeSubsystem is null"), __FUNCTION__, __LINE__);
		return false;
	}

	// Call the actual GetFile function
	return subsystem->GetFile(InFileName, OutFileData);
}

FGuid UConfigForgeLibrary::GetForgeFileID(const FConfigForgeFileData& InData)
{
	return FConfigForgeFileData::MakeID(InData);
}