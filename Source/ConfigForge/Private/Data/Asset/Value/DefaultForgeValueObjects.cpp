

#include "Data/Asset/Value/DefaultForgeValueObjects.h"

void UBoolConfigObject::SetDefaultValue(FDynamicValue& InDynamicValue)
{
	InDynamicValue.Set<bool>(bValue);
}

void UBoolConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, const FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return;
	bool bTemp;
	if (InDynamicValue.Get<bool>(bTemp))
	{
		InConfigFile->SetBool(InSection, Key, bTemp);
	}
	else
	{
		// Default value (if dynamic value doesnt have)
		InConfigFile->SetBool(InSection, Key, bValue);
	}
}

bool UBoolConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return false;
	bool temp;
	if (InConfigFile->GetBool(InSection, Key, temp))
	{
		InDynamicValue.Set<bool>(temp);
		return true;
	}

	return false;
}

uint32 UBoolConfigObject::MakeHash() const
{
	uint32 hash = Super::MakeHash();
	hash = HashCombine(hash, GetTypeHash(FString("BoolConfigObject")));
	hash = HashCombine(hash, GetTypeHash(bValue));
	return hash;
}

void UFloatConfigObject::SetDefaultValue(FDynamicValue& InDynamicValue)
{
	InDynamicValue.Set<float>(FloatValue);
}

void UFloatConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, const FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return;

	float temp;
	if (InDynamicValue.Get<float>(temp))
	{
		InConfigFile->SetFloat(InSection, Key, temp);
	}
	else
	{
		InConfigFile->SetFloat(InSection, Key, FloatValue);
	}
}

bool UFloatConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return false;
	float temp;
	if (InConfigFile->GetFloat(InSection, Key, temp))
	{
		InDynamicValue.Set<float>(temp);
		return true;
	}
	return false;
}

uint32 UFloatConfigObject::MakeHash() const
{
	uint32 hash = Super::MakeHash();
	hash = HashCombine(hash, GetTypeHash(FString("FloatConfigObject")));
	hash = HashCombine(hash, GetTypeHash(FloatValue));
	return hash;
}

void UDoubleConfigObject::SetDefaultValue(FDynamicValue& InDynamicValue)
{
	InDynamicValue.Set<double>(DoubleValue);
}

void UDoubleConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, const FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return;

	double temp;
	if (InDynamicValue.Get<double>(temp))
	{
		InConfigFile->SetDouble(InSection, Key, temp);
	}
	else
	{
		InConfigFile->SetDouble(InSection, Key, DoubleValue);
	}
}

bool UDoubleConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return false;
	double temp;
	if (InConfigFile->GetDouble(InSection, Key, temp))
	{
		InDynamicValue.Set<double>(temp);
		return true;
	}
	return false;
}

uint32 UDoubleConfigObject::MakeHash() const
{
	uint32 hash = Super::MakeHash();
	hash = HashCombine(hash, GetTypeHash(FString("DoubleConfigObject")));
	hash = HashCombine(hash, GetTypeHash(DoubleValue));
	return hash;
}

void UIntConfigObject::SetDefaultValue(FDynamicValue& InDynamicValue)
{
	InDynamicValue.Set<int32>(IntValue);
}

void UIntConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, const FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return;

	int32 temp;
	if (InDynamicValue.Get<int32>(temp))
	{
		InConfigFile->SetInt32(InSection, Key, temp);
	}
	else
	{
		InConfigFile->SetInt32(InSection, Key, IntValue);
	}
}

bool UIntConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return false;
	int32 temp;
	if (InConfigFile->GetInt32(InSection, Key, temp))
	{
		InDynamicValue.Set<int32>(temp);
		return true;
	}
	return false;
}

uint32 UIntConfigObject::MakeHash() const
{
	uint32 hash = Super::MakeHash();
	hash = HashCombine(hash, GetTypeHash(FString("IntConfigObject")));
	hash = HashCombine(hash, GetTypeHash(IntValue));
	return hash;
}

void UInt64ConfigObject::SetDefaultValue(FDynamicValue& InDynamicValue)
{
	InDynamicValue.Set<int64>(Int64Value);
}

void UInt64ConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, const FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return;

	int64 temp;
	if (InDynamicValue.Get<int64>(temp))
	{
		InConfigFile->SetInt64(InSection, Key, temp);
	}
	else
	{
		InConfigFile->SetInt64(InSection, Key, Int64Value);
	}
}

bool UInt64ConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return false;
	int64 temp;
	if (InConfigFile->GetInt64(InSection, Key, temp))
	{
		InDynamicValue.Set<int64>(temp);
		return true;
	}
	return false;
}

uint32 UInt64ConfigObject::MakeHash() const
{
	uint32 hash = Super::MakeHash();
	hash = HashCombine(hash, GetTypeHash(FString("Int64ConfigObject")));
	hash = HashCombine(hash, GetTypeHash(Int64Value));
	return hash;
}

void UInt8ConfigObject::SetDefaultValue(FDynamicValue& InDynamicValue)
{
	InDynamicValue.Set<uint8>(UintValue);
}

void UInt8ConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, const FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return;

	uint8 temp;
	if (InDynamicValue.Get<uint8>(temp))
	{
		InConfigFile->SetInt32(InSection, Key, temp);
	}
	else
	{
		InConfigFile->SetInt32(InSection, Key, UintValue);
	}
}

bool UInt8ConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return false;
	int32 temp;
	if (InConfigFile->GetInt32(InSection, Key, temp))
	{
		uint8 byteValue = static_cast<uint8>(FMath::Clamp(temp, TNumericLimits<uint8>::Min(), TNumericLimits<uint8>::Max()));
		InDynamicValue.Set<uint8>(byteValue);
		return true;
	}
	return false;
}

uint32 UInt8ConfigObject::MakeHash() const
{
	uint32 hash = Super::MakeHash();
	hash = HashCombine(hash, GetTypeHash(FString("Int8ConfigObject")));
	hash = HashCombine(hash, GetTypeHash(UintValue));
	return hash;
}

void UStringConfigObject::SetDefaultValue(FDynamicValue& InDynamicValue)
{
	InDynamicValue.Set<FString>(StringValue);
}

void UStringConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, const FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return;

	FString temp;
	if (InDynamicValue.Get<FString>(temp))
	{
		InConfigFile->SetString(InSection, Key, temp);
	}
	else
	{
		InConfigFile->SetString(InSection, Key, StringValue);
	}
}

bool UStringConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection, FDynamicValue& InDynamicValue)
{
	if (!InConfigFile.IsValid())
		return false;
	FString temp;
	if (InConfigFile->GetString(InSection, Key, temp))
	{
		InDynamicValue.Set<FString>(temp);
		return true;
	}
	return false;
}

uint32 UStringConfigObject::MakeHash() const
{
	uint32 hash = Super::MakeHash();
	hash = HashCombine(hash, GetTypeHash(FString("StringConfigObject")));
	hash = HashCombine(hash, GetTypeHash(StringValue));
	return hash;
}