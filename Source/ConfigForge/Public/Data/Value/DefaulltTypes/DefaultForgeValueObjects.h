// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Data/Value/ConfigValueObject.h"

#include "DefaultForgeValueObjects.generated.h"

UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UBoolConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category = "Data")
	bool bValue;

public:

};

UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UFloatConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category = "Data")
	float FloatValue;

public:

};

UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UDoubleConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category = "Data")
	double DoubleValue;

public:

};

UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UIntConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category = "Data")
	int32 IntValue;


};

UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UInt64ConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category = "Data")
	int64 Int64Value;
};

UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UInt8ConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category = "Data")
	uint8 UintValue;


};

UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UStringConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category = "Data")
	FString StringValue;


};