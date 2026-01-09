// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Libs/ConfigForgeLibrary.h"

#include "ConfigForge.h"
#include "Data/Asset/ConfigForgeSetup.h"
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

FDynamicValue UConfigForgeLibrary::MakeDynamicValue_Int(int32 InValue)
{
	FDynamicValue res;
	res.Set<int32>(InValue);
	return res;
}

FDynamicValue UConfigForgeLibrary::MakeDynamicValue_Float(float InValue)
{
	FDynamicValue res;
	res.Set<float>(InValue);
	return res;
}

FDynamicValue UConfigForgeLibrary::MakeDynamicValue_Double(double InValue)
{
	FDynamicValue res;
	res.Set<double>(InValue);
	return res;
}

FDynamicValue UConfigForgeLibrary::MakeDynamicValue_Bool(bool InValue)
{
	FDynamicValue res;
	res.Set<bool>(InValue);
	return res;
}

FDynamicValue UConfigForgeLibrary::MakeDynamicValue_Byte(uint8 InValue)
{
	FDynamicValue res;
	res.Set<uint8>(InValue);
	return res;
}

FDynamicValue UConfigForgeLibrary::MakeDynamicValue_Int64(int64 InValue)
{
	FDynamicValue res;
	res.Set<int64>(InValue);
	return res;
}

FDynamicValue UConfigForgeLibrary::MakeDynamicValue_String(const FString& InValue)
{
	FDynamicValue res;
	res.Set<FString>(InValue);
	return res;
}

void UConfigForgeLibrary::ParseDynamicValue_Int(const FDynamicValue& InDynamicValue, int32& OutInt, bool& bSuccess)
{
	bSuccess = InDynamicValue.Get<int32>(OutInt);
}

void UConfigForgeLibrary::ParseDynamicValue_Float(const FDynamicValue& InDynamicValue, float& OutFloat, bool& bSuccess)
{
	bSuccess = InDynamicValue.Get<float>(OutFloat);
}

void UConfigForgeLibrary::ParseDynamicValue_Double(const FDynamicValue& InDynamicValue, double& OutDouble, bool& bSuccess)
{
	bSuccess = InDynamicValue.Get<double>(OutDouble);
}

void UConfigForgeLibrary::ParseDynamicValue_Bool(const FDynamicValue& InDynamicValue, bool& OutBool, bool& bSuccess)
{
	bSuccess = InDynamicValue.Get<bool>(OutBool);
}

void UConfigForgeLibrary::ParseDynamicValue_Byte(const FDynamicValue& InDynamicValue, uint8& OutByte, bool& bSuccess)
{
	bSuccess = InDynamicValue.Get<uint8>(OutByte);
}

void UConfigForgeLibrary::ParseDynamicValue_Int64(const FDynamicValue& InDynamicValue, int64& OutInt64, bool& bSuccess)
{
	bSuccess = InDynamicValue.Get<int64>(OutInt64);
}

void UConfigForgeLibrary::ParseDynamicValue_String(const FDynamicValue& InDynamicValue, FString& OutString, bool& bSuccess)
{
	bSuccess = InDynamicValue.Get<FString>(OutString);
}