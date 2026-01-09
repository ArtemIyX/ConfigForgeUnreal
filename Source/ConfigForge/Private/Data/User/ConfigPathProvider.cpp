// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/User/ConfigPathProvider.h"

UConfigPathProvider::UConfigPathProvider(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer) {}

FString UConfigPathProvider::GetPath_Implementation() const
{
	return FPaths::ProjectConfigDir();
}