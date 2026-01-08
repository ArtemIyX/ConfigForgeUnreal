#pragma once

#include "CoreMinimal.h"
#include "ValueHolder.h"
#include "ValueHolderBase.h"
#include "DynamicValue.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct CONFIGFORGE_API FDynamicValue
{
	GENERATED_BODY()

private:
	TSharedPtr<FValueHolderBase> Holder;

public:
	FDynamicValue() = default;

	// Copy constructor
	FDynamicValue(const FDynamicValue& Other)
	{
		if (Other.Holder.IsValid())
		{
			Holder = MakeShareable(Other.Holder->Clone());
		}
	}

	// Copy assignment
	FDynamicValue& operator=(const FDynamicValue& Other)
	{
		if (this != &Other)
		{
			if (Other.Holder.IsValid())
			{
				Holder = MakeShareable(Other.Holder->Clone());
			}
			else
			{
				Holder.Reset();
			}
		}
		return *this;
	}

	// Move constructor
	FDynamicValue(FDynamicValue&& Other) = default;

	// Move assignment
	FDynamicValue& operator=(FDynamicValue&& Other) = default;

	// Set a value (copy)
	template <typename T>
	void Set(const T& InValue)
	{
		Holder = MakeShareable(new FValueHolder<T>(InValue));
	}

	// Set a value (move)
	template <typename T>
	void Set(T&& InValue)
	{
		Holder = MakeShareable(new FValueHolder<T>(Forward<T>(InValue)));
	}

	// Get a value with type checking
	template <typename T>
	bool Get(T& OutValue) const
	{
		if (!Holder.IsValid())
		{
			return false;
		}

		FValueHolder<T>* TypedHolder = static_cast<FValueHolder<T>*>(Holder.Get());
		if (TypedHolder)
		{
			OutValue = TypedHolder->Value;
			return true;
		}

		return false;
	}

	// Get a value (returns pointer, nullptr if wrong type or empty)
	template <typename T>
	T* GetPtr()
	{
		if (!Holder.IsValid())
		{
			return nullptr;
		}

		FValueHolder<T>* TypedHolder = static_cast<FValueHolder<T>*>(Holder.Get());
		if (TypedHolder)
		{
			return &TypedHolder->Value;
		}

		return nullptr;
	}

	// Get a value (const version)
	template <typename T>
	const T* GetPtr() const
	{
		if (!Holder.IsValid())
		{
			return nullptr;
		}

		const FValueHolder<T>* TypedHolder = static_cast<const FValueHolder<T>*>(Holder.Get());
		if (TypedHolder)
		{
			return &TypedHolder->Value;
		}

		return nullptr;
	}

	// Check if a value is stored
	bool IsSet() const
	{
		return Holder.IsValid();
	}

	// Clear the stored value
	void Reset()
	{
		Holder.Reset();
	}
	
};