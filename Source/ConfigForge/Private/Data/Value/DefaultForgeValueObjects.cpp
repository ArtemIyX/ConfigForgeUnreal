#include "Data/Value/DefaultForgeValueObjects.h"

void UBoolConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	if (!InConfigFile.IsValid())
		return;
	InConfigFile->SetBool(InSection, Key, bValue);
}

bool UBoolConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	if (!InConfigFile.IsValid())
		return false;
	bool temp;
	if (InConfigFile->GetBool(InSection, Key, temp))
	{
		bValue = temp;
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

void UFloatConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	InConfigFile->SetFloat(InSection, Key, FloatValue);
}

bool UFloatConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	if (!InConfigFile.IsValid())
		return false;
	float temp;
	if (InConfigFile->GetFloat(InSection, Key, temp))
	{
		FloatValue = temp;
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

void UDoubleConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	InConfigFile->SetDouble(InSection, Key, DoubleValue);
}

bool UDoubleConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	if (!InConfigFile.IsValid())
		return false;
	double temp;
	if (InConfigFile->GetDouble(InSection, Key, temp))
	{
		DoubleValue = temp;
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

void UIntConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	InConfigFile->SetInt32(InSection, Key, IntValue);
}

bool UIntConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	if (!InConfigFile.IsValid())
		return false;
	int32 temp;
	if (InConfigFile->GetInt32(InSection, Key, temp))
	{
		IntValue = temp;
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

void UInt64ConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	InConfigFile->SetInt64(InSection, Key, Int64Value);
}

bool UInt64ConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	if (!InConfigFile.IsValid())
		return false;
	int64 temp;
	if (InConfigFile->GetInt64(InSection, Key, temp))
	{
		Int64Value = temp;
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

void UInt8ConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	InConfigFile->SetInt64(InSection, Key, UintValue);
}

bool UInt8ConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	if (!InConfigFile.IsValid())
		return false;
	int32 temp;
	if (InConfigFile->GetInt32(InSection, Key, temp))
	{
		UintValue = static_cast<uint8>(FMath::Clamp(temp, TNumericLimits<uint8>::Min(), TNumericLimits<uint8>::Max()));
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

void UStringConfigObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	InConfigFile->SetString(InSection, Key, StringValue);
}

bool UStringConfigObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection)
{
	if (!InConfigFile.IsValid())
		return false;
	FString temp;
	if (InConfigFile->GetString(InSection, Key, temp))
	{
		StringValue = temp;
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