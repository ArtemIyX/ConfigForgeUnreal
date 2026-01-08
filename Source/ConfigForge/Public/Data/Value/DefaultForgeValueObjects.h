// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Data/Value/ConfigValueObject.h"

#include "DefaultForgeValueObjects.generated.h"

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONFIGFORGE_API UBoolConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", meta=(DisplayPriority=2), Category="Data")
	bool bValue;

public:

	virtual void SetDefaultValue(FDynamicValue& InDynamicValue) override;
	
	virtual void SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		const FDynamicValue& InDynamicValue) override;

	virtual bool GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		FDynamicValue& InDynamicValue) override;

	virtual uint32 MakeHash() const override;
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONFIGFORGE_API UFloatConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", meta=(DisplayPriority=2), Category="Data")
	float FloatValue;

public:
	virtual void SetDefaultValue(FDynamicValue& InDynamicValue) override;
	
	virtual void SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		const FDynamicValue& InDynamicValue) override;

	virtual bool GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		FDynamicValue& InDynamicValue) override;

	virtual uint32 MakeHash() const override;
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONFIGFORGE_API UDoubleConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", meta=(DisplayPriority=2), Category="Data")
	double DoubleValue;

public:
	virtual void SetDefaultValue(FDynamicValue& InDynamicValue) override;
	
	virtual void SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		const FDynamicValue& InDynamicValue) override;

	virtual bool GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		FDynamicValue& InDynamicValue) override;

	virtual uint32 MakeHash() const override;
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONFIGFORGE_API UIntConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", meta=(DisplayPriority=2), Category="Data")
	int32 IntValue;

public:
	virtual void SetDefaultValue(FDynamicValue& InDynamicValue) override;
	
	virtual void SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		const FDynamicValue& InDynamicValue) override;

	virtual bool GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		FDynamicValue& InDynamicValue) override;
	virtual uint32 MakeHash() const override;
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONFIGFORGE_API UInt64ConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", meta=(DisplayPriority=2), Category="Data")
	int64 Int64Value;

public:
	virtual void SetDefaultValue(FDynamicValue& InDynamicValue) override;
	
	virtual void SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		const FDynamicValue& InDynamicValue) override;

	virtual bool GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		FDynamicValue& InDynamicValue) override;
	virtual uint32 MakeHash() const override;
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONFIGFORGE_API UInt8ConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", meta=(DisplayPriority=2), Category="Data")
	uint8 UintValue;

public:
	virtual void SetDefaultValue(FDynamicValue& InDynamicValue) override;
	
	virtual void SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		const FDynamicValue& InDynamicValue) override;

	virtual bool GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		FDynamicValue& InDynamicValue) override;
	virtual uint32 MakeHash() const override;
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONFIGFORGE_API UStringConfigObject : public UConfigValueObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", meta=(DisplayPriority=2), Category="Data")
	FString StringValue;

public:
	virtual void SetDefaultValue(FDynamicValue& InDynamicValue) override;
	
	virtual void SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		const FDynamicValue& InDynamicValue) override;

	virtual bool GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection,
		FDynamicValue& InDynamicValue) override;
	virtual uint32 MakeHash() const override;
};