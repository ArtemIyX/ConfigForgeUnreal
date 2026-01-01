// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/ConfigForgeSetup.h"

#include "Data/ConfigPathProvider.h"

FConfigForgeFileData::FConfigForgeFileData()
{
	File = nullptr;
	PathProvider = UConfigPathProvider::StaticClass();

}

UConfigForgeSetup::UConfigForgeSetup(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer) {}