#include "engine.h"

using namespace std;

Offsets defs;

ansi_fn Decrypt_ANSI = nullptr;
wide_fn Decrypt_WIDE = nullptr;

struct DeadByDaylight {
	uint16_t Stride = 4;
	struct {
		uint16_t Size = 24;
	} FUObjectItem;
	struct {
		uint16_t Number = 8;
	} FName;
	struct {
		uint16_t Info = 4;
		uint16_t WideBit = 0;
		uint16_t LenBit = 1;
		uint16_t HeaderSize = 6;
	} FNameEntry;
	struct {
		uint16_t Index = 0xC;
		uint16_t Class = 0x10;
		uint16_t Name = 0x18;
		uint16_t Outer = 0x28;
	} UObject;
	struct {
		uint16_t Next = 0x30;
	} UField;
	struct {
		uint16_t SuperStruct = 0x48;
		uint16_t Children = 0x50;
		uint16_t ChildProperties = 0x58;
		uint16_t PropertiesSize = 0x60;
	} UStruct;
	struct {
		uint16_t Names = 0x48;
	} UEnum;
	struct {
		uint16_t FunctionFlags = 0xB8;
		uint16_t Func = 0xB8 + 0x28; // ue3-ue4, always +0x28 from flags location.
	} UFunction;
	struct {
		uint16_t Class = 0x8;
		uint16_t Next = 0x20;
		uint16_t Name = 0x28;
	} FField;
	struct {
		uint16_t ArrayDim = 0x38;
		uint16_t ElementSize = 0x3C;
		uint16_t PropertyFlags = 0x40;
		uint16_t Offset = 0x4C;
		uint16_t Size = 0x80;
	} FProperty;
};
static_assert(sizeof(DeadByDaylight) == sizeof(Offsets));

struct RogueCompany {
	uint16_t Stride = 2;
	struct {
		uint16_t Size = 24;
	} FUObjectItem;
	struct {
		uint16_t Number = 4;
	} FName;
	struct {
		uint16_t Info = 0;
		uint16_t WideBit = 0;
		uint16_t LenBit = 6;
		uint16_t HeaderSize = 2;
	} FNameEntry;
	struct {
		uint16_t Index = 0xC;
		uint16_t Class = 0x10;
		uint16_t Name = 0x18;
		uint16_t Outer = 0x20;
	} UObject;
	struct {
		uint16_t Next = 0x28;
	} UField;
	struct {
		uint16_t SuperStruct = 0x40;
		uint16_t Children = 0x48;
		uint16_t ChildProperties = 0x50;
		uint16_t PropertiesSize = 0x58;
	} UStruct;
	struct {
		uint16_t Names = 0x40;
	} UEnum;
	struct {
		uint16_t FunctionFlags = 0xB0;
		uint16_t Func = 0xB0 + 0x28;
	} UFunction;
	struct {
		uint16_t Class = 0x8;
		uint16_t Next = 0x20;
		uint16_t Name = 0x28;
	} FField;
	struct {
		uint16_t ArrayDim = 0x38;
		uint16_t ElementSize = 0x3C;
		uint16_t PropertyFlags = 0x40;
		uint16_t Offset = 0x4C;
		uint16_t Size = 0x78;
	} FProperty;
};
static_assert(sizeof(RogueCompany) == sizeof(Offsets));

struct Brickadia {
	uint16_t Stride = 2;
	struct {
		uint16_t Size = 32;
	} FUObjectItem;
	struct {
		uint16_t Number = 4;
	} FName;
	struct {
		uint16_t Info = 0;
		uint16_t WideBit = 0;
		uint16_t LenBit = 6;
		uint16_t HeaderSize = 2;
	} FNameEntry;
	struct {
		uint16_t Index = 0xC;
		uint16_t Class = 0x10;
		uint16_t Name = 0x18;
		uint16_t Outer = 0x20;
	} UObject;
	struct {
		uint16_t Next = 0x28;
	} UField;
	struct {
		uint16_t SuperStruct = 0x40;
		uint16_t Children = 0x48;
		uint16_t ChildProperties = 0x50;
		uint16_t PropertiesSize = 0x58;
	} UStruct;
	struct {
		uint16_t Names = 0x40;
	} UEnum;
	struct {
		uint16_t FunctionFlags = 0xB0;
		uint16_t Func = 0xB0 + 0x28;
	} UFunction;
	struct {
		uint16_t Class = 0x8;
		uint16_t Next = 0x20;
		uint16_t Name = 0x28;
	} FField;
	struct {
		uint16_t ArrayDim = 0x38;
		uint16_t ElementSize = 0x3C;
		uint16_t PropertyFlags = 0x40;
		uint16_t Offset = 0x4C;
		uint16_t Size = 0x78;
	} FProperty;
};
static_assert(sizeof(Brickadia) == sizeof(Offsets));

struct Fortnite {
	uint16_t Stride = 2;
	struct {
		uint16_t Size = 24;
	} FUObjectItem;
	struct {
		uint16_t Number = 4;
	} FName;
	struct {
		uint16_t Info = 0;
		uint16_t WideBit = 0;
		uint16_t LenBit = 6;
		uint16_t HeaderSize = 2;
	} FNameEntry;
	struct {
		uint16_t Index = 0xC;
		uint16_t Class = 0x10;
		uint16_t Name = 0x18;
		uint16_t Outer = 0x20;
	} UObject;
	struct {
		uint16_t Next = 0x28;
	} UField;
	struct {
		uint16_t SuperStruct = 0x40;
		uint16_t Children = 0x48;
		uint16_t ChildProperties = 0x50;
		uint16_t PropertiesSize = 0x58;
	} UStruct;
	struct {
		uint16_t Names = 0x40;
	} UEnum;
	struct {
		uint16_t FunctionFlags = 0xB0;
		uint16_t Func = 0xB0 + 0x28;
	} UFunction;
	struct {
		uint16_t Class = 0x8;
		uint16_t Next = 0x20;
		uint16_t Name = 0x28;
	} FField;
	struct {
		uint16_t ArrayDim = 0x38;
		uint16_t ElementSize = 0x3C;
		uint16_t PropertyFlags = 0x40;
		uint16_t Offset = 0x4C;
		uint16_t Size = 0x78;
	} FProperty;
};
static_assert(sizeof(Fortnite) == sizeof(Offsets));

unordered_map<string, function<void()>> games = {
	{
		{
			"DeadByDaylight-Win64-Shipping",
			[]() {
				DeadByDaylight buf{};
				defs = *reinterpret_cast<Offsets*>(&buf);
			}
		},
		{
			"RogueCompany",
			[]() {
				RogueCompany buf{};
				defs = *reinterpret_cast<Offsets*>(&buf);
			}
		},
		{
			"PropWitchHuntModule-Win64-Shipping",
			[]() {
				RogueCompany buf{};
				defs = *reinterpret_cast<Offsets*>(&buf);
			}
		},
		{
			"POLYGON-Win64-Shipping",
			[]() {
				RogueCompany buf{};
				defs = *reinterpret_cast<Offsets*>(&buf);
			}
		},
		{
			"Brickadia-Win64-Shipping",
			[]() {
				Brickadia buf{};
				defs = *reinterpret_cast<Offsets*>(&buf);
			}
		},
		{
			"FortniteClient-Win64-Shipping",
			[]() {
				Fortnite buf{};
				defs = *reinterpret_cast<Offsets*>(&buf);

				Decrypt_ANSI = [](char* a1, int a2) {
				
					char result;
					int v5;
					__int64 v6;
					char v7;

					result = 0;
					v5 = 9;

					if (a2 > 0)
					{
						v6 = (unsigned int)a2;
						do
						{
							v7 = *a1++; // first character
							result = v5 + ~v7; // 9 + bitwise not
							v5 += 7947;
							*(a1 - 1) = result;
							--v6;
						} while (v6);
					}

					return result;
				};
			}
		}
	}

};

bool EngineInit(string game)
{
	auto& fn = games[game];
	if (!fn) { return false; }
	fn();
	return true;
}