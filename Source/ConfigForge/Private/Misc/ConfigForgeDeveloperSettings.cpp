// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Misc/ConfigForgeDeveloperSettings.h"

const UConfigForgeDeveloperSettings* UConfigForgeDeveloperSettings::Get()
{
	return GetDefault<UConfigForgeDeveloperSettings>();
}