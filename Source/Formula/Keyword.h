#pragma once

#include "FormulaCore.h"

class FKeyword
{
public:
	FKeyword(const FKeyword&) = delete;

	FKeyword(const char* StringPtr, uint8 Length)
		: StringPtr(StringPtr), Length(Length)
	{}

	template<uint8 StringSize>
	bool operator == (const char(&String)[StringSize]) const
	{
        if (Length != StringSize - 1)
            return false;

        for (size_t i = 0; i < Length; i++)
        {
			if (StringPtr[i] != String[i])
				return false;
        }

        return true;
	}

	const uint8 Length;

private:
	const char* const StringPtr;
};