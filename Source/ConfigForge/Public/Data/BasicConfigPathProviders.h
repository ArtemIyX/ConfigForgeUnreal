// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Data/ConfigPathProvider.h"
#include "BasicConfigPathProviders.generated.h"

UCLASS(Blueprintable, BlueprintType, DisplayName="GeneratedConfigDir")
class CONFIGFORGE_API UConfigPathProvider_GeneratedConfigDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		return FPaths::ConvertRelativePathToFull(FPaths::GeneratedConfigDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="RootDir")
class CONFIGFORGE_API UConfigPathProvider_RootDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::RootDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="DiffDir")
class CONFIGFORGE_API UConfigPathProvider_DiffDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::DiffDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="EngineDir")
class CONFIGFORGE_API UConfigPathProvider_EngineDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::EngineDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="EngineContentDir")
class CONFIGFORGE_API UConfigPathProvider_EngineContentDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::EngineContentDir());
	}
};


UCLASS(Blueprintable, BlueprintType, DisplayName="ProjectConfigDir")
class CONFIGFORGE_API UConfigPathProvider_ProjectConfigDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectConfigDir());
	}
};


UCLASS(Blueprintable, BlueprintType, DisplayName="ProjectDir")
class CONFIGFORGE_API UConfigPathProvider_ProjectDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="ProjectSavedDir")
class CONFIGFORGE_API UConfigPathProvider_ProjectSavedDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="ProjectContentDir")
class CONFIGFORGE_API UConfigPathProvider_ProjectContentDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="ProjectModsDir")
class CONFIGFORGE_API UConfigPathProvider_ProjectModsDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectModsDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="ProjectLogDir")
class CONFIGFORGE_API UConfigPathProvider_ProjectLogDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectLogDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="ProjectPluginsDir")
class CONFIGFORGE_API UConfigPathProvider_ProjectPluginsDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="ProjectIntermediateDir")
class CONFIGFORGE_API UConfigPathProvider_ProjectIntermediateDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectIntermediateDir());
	}
};

UCLASS(Blueprintable, BlueprintType, DisplayName="ProjectUserDir")
class CONFIGFORGE_API UConfigPathProvider_ProjectUserDir : public UConfigPathProvider
{
	GENERATED_BODY()

public:
	virtual FString GetPath_Implementation() const override
	{
		// Returns the root directory of the engine directory tree
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectUserDir());
	}
};

