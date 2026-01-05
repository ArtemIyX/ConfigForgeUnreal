// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/ConfigForgeSetup.h"

#include "Data/ConfigForgeFile.h"
#include "Data/ConfigPathProvider.h"

FConfigForgeFileData::FConfigForgeFileData()
{
	File = nullptr;
	PathProvider = UConfigPathProvider::StaticClass();

}

FGuid FConfigForgeFileData::ID() const
{
	return FConfigForgeFileData::MakeID(*this);
}

FGuid FConfigForgeFileData::MakeID(const FConfigForgeFileData& InFileData)
{
	uint32 hash = GetTypeHash(FString(TEXT("FConfigForgeFileData")));
	hash = HashCombine(hash, GetTypeHash(GetNameSafe(InFileData.PathProvider)));
	if (InFileData.File)
	{
		hash = HashCombine(hash, GetTypeHash(InFileData.File->GetName()));
	}
	
	FRandomStream stream(hash);

	FGuid guid(
		stream.GetUnsignedInt(),
		stream.GetUnsignedInt(),
		stream.GetUnsignedInt(),
		stream.GetUnsignedInt()
		);

	return guid;
}

UConfigForgeSetup::UConfigForgeSetup(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer) {}