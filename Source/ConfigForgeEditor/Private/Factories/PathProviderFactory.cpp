// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Factories/PathProviderFactory.h"
#include "AssetToolsModule.h"
#include "Data/ConfigPathProvider.h"

UPathProviderFactory::UPathProviderFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UConfigPathProvider::StaticClass();
}