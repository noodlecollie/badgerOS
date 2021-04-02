#pragma once

#include <cstdint>

namespace BadgerBLE
{
	// For generating UUIDs, use https://www.uuidgenerator.net/

	struct ServiceDef
	{
		const char* name;
		const char* uuid;
	};

	struct CharacteristicDef
	{
		const char* name;
		const char* uuid;
		uint32_t attributes;
	};
}
