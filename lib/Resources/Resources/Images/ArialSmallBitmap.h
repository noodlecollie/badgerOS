#pragma once

#include <cstddef>
#include <cstdint>
#include <BadgerGL/BitmapMask.h>
#include <BadgerGL/Defs.h>

namespace Resources
{
	namespace ArialSmallBitmap
	{
		static constexpr size_t WIDTH = 128;
		static constexpr size_t HEIGHT = 59;
		static constexpr size_t DATA_LENGTH = BadgerGL::maskedDataSizeForDimensions(WIDTH, HEIGHT);

		static constexpr uint8_t DATA[DATA_LENGTH] =
		{
			0x28, 0x08, 0x01, 0x81, 0x80, 0xA0, 0x08, 0x10,
			0x82, 0x42, 0x08, 0x0E, 0x09, 0x82, 0x94, 0x94,
			0x14, 0x04, 0x82, 0x42, 0x41, 0x50, 0x10, 0x08,
			0x44, 0x21, 0x14, 0x91, 0x10, 0x45, 0x6A, 0x80,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x9C,
			0x9C, 0x20, 0x82, 0x83, 0xE0, 0x20, 0x38, 0x88,
			0x30, 0x0C, 0xC3, 0xE0, 0xFF, 0x1F, 0x65, 0xA2,
			0x22, 0x11, 0x45, 0x44, 0x11, 0x51, 0x44, 0x94,
			0x70, 0x0C, 0xC3, 0x20, 0x84, 0x10, 0x65, 0xC1,
			0x41, 0x11, 0x25, 0x48, 0x09, 0x52, 0x82, 0x94,
			0xB0, 0x0C, 0xC3, 0x20, 0x84, 0xA0, 0x64, 0xC1,
			0x41, 0x0A, 0x25, 0x48, 0x09, 0x52, 0x82, 0x94,
			0xB0, 0x0C, 0x43, 0xF1, 0xFF, 0xAF, 0x64, 0xC1,
			0x41, 0x84, 0x28, 0x28, 0x0A, 0x8A, 0x82, 0xA2,
			0x30, 0x0D, 0x43, 0x2E, 0x84, 0x40, 0x64, 0xC1,
			0x41, 0x84, 0x2F, 0xE8, 0x0B, 0xFA, 0x82, 0xBE,
			0x30, 0x0D, 0x43, 0x24, 0x84, 0x40, 0x64, 0xA2,
			0x22, 0x44, 0x50, 0x14, 0x14, 0x05, 0x45, 0xC1,
			0x30, 0x0E, 0x43, 0x28, 0x84, 0x40, 0x64, 0x9C,
			0x1C, 0x44, 0x90, 0x13, 0xE4, 0x04, 0x39, 0x41,
			0x2F, 0xF4, 0x3C, 0xEC, 0xFF, 0x2F, 0x64, 0x91,
			0xF8, 0x70, 0x28, 0x94, 0x72, 0x48, 0x05, 0x32,
			0xCD, 0x4E, 0x04, 0x75, 0xC4, 0x21, 0x42, 0x49,
			0x06, 0x51, 0x00, 0x00, 0x50, 0x08, 0x04, 0x49,
			0x50, 0xA8, 0x88, 0xAA, 0x28, 0x12, 0xA5, 0x00,
			0xB2, 0x72, 0x10, 0xE1, 0x77, 0x2E, 0x3E, 0x85,
			0x52, 0x0A, 0x00, 0x28, 0x20, 0x00, 0x00, 0x5C,
			0xC9, 0x52, 0x28, 0x61, 0x00, 0x35, 0x46, 0x85,
			0x52, 0xEA, 0x9C, 0x73, 0x2E, 0x38, 0xF7, 0x62,
			0x45, 0x52, 0x28, 0x61, 0x70, 0x45, 0xC5, 0x84,
			0x62, 0x1A, 0x63, 0xA4, 0x31, 0xC6, 0x18, 0x63,
			0x45, 0x52, 0x28, 0xE1, 0x8F, 0x45, 0x45, 0x85,
			0x52, 0xEA, 0xA3, 0xA7, 0xDE, 0xFD, 0x1F, 0x63,
			0x65, 0x89, 0x44, 0x61, 0xF0, 0x95, 0x44, 0x85,
			0x52, 0x1A, 0x63, 0xAC, 0x91, 0x84, 0x10, 0x63,
			0xD9, 0xF8, 0x7C, 0x61, 0x88, 0x8E, 0x3C, 0x85,
			0x52, 0x9A, 0x63, 0x76, 0x19, 0xC5, 0x18, 0x5D,
			0x02, 0x06, 0x83, 0x61, 0xC8, 0x82, 0x04, 0x49,
			0x52, 0x6A, 0x9D, 0x25, 0x96, 0x39, 0x17, 0x7D,
			0xFC, 0x05, 0x83, 0xDE, 0xB7, 0x42, 0x04, 0x32,
			0xCA, 0x0D, 0x1E, 0x6E, 0x90, 0xC3, 0xE1, 0x84,
			0x82, 0x0A, 0x44, 0x10, 0x51, 0x21, 0xC4, 0xDF,
			0x7D, 0x23, 0x22, 0xF1, 0x58, 0x24, 0x12, 0x85,
			0x44, 0x11, 0xA2, 0x88, 0xAA, 0x51, 0x44, 0x21,
			0x86, 0x14, 0xC2, 0xE8, 0x38, 0x18, 0x0C, 0xFE,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x22, 0x21,
			0x84, 0x14, 0xCF, 0x64, 0x35, 0x18, 0x0C, 0x84,
			0xCE, 0xC5, 0x18, 0x9D, 0x8B, 0x52, 0x22, 0x3F,
			0x7C, 0x0B, 0xC2, 0x64, 0x35, 0x18, 0x8C, 0x87,
			0x31, 0xC6, 0x18, 0x63, 0x8C, 0x8A, 0x12, 0x21,
			0x04, 0x68, 0xC2, 0x62, 0x35, 0x98, 0x0D, 0x86,
			0x3F, 0xC6, 0x18, 0x7D, 0x8C, 0x8A, 0xF2, 0x21,
			0x04, 0x94, 0x22, 0x51, 0x52, 0x24, 0x12, 0x7D,
			0x21, 0xC6, 0x18, 0x63, 0x8C, 0x04, 0x09, 0x21,
			0x06, 0x94, 0x9E, 0x4E, 0x92, 0xC3, 0xE5, 0x80,
			0x31, 0xE6, 0x9C, 0x73, 0x8C, 0x04, 0x09, 0xDF,
			0x7D, 0x62, 0xFC, 0x87, 0xFB, 0x9D, 0x73, 0xDE,
			0xCE, 0x59, 0x6B, 0xAD, 0x8B, 0x27, 0x0C, 0x3F,
			0x2F, 0x0C, 0xA1, 0x48, 0x0C, 0x63, 0x8C, 0xA2,
			0x41, 0x44, 0x30, 0x70, 0x42, 0x66, 0x8C, 0xC2,
			0x30, 0x94, 0x90, 0x30, 0x08, 0x23, 0x84, 0x81,
			0x41, 0x8A, 0x28, 0x88, 0x42, 0xA9, 0x4C, 0xC2,
			0x20, 0x94, 0x90, 0x30, 0x08, 0x23, 0x64, 0x8F,
			0x22, 0x8A, 0xE8, 0x8B, 0x42, 0xA9, 0x6C, 0x3E,
			0x23, 0x64, 0x88, 0x30, 0x08, 0x23, 0x82, 0x90,
			0x22, 0x0A, 0x25, 0x4C, 0x7E, 0x26, 0x5D, 0x12,
			0x2C, 0x64, 0x88, 0x30, 0x08, 0x23, 0x81, 0x90,
			0x14, 0x11, 0x22, 0xCC, 0x42, 0x25, 0x8D, 0x22,
			0x30, 0x94, 0x84, 0x48, 0x0C, 0xA3, 0x88, 0x91,
			0x14, 0x1F, 0xE2, 0x0B, 0xC3, 0x38, 0x8E, 0xA2,
			0x30, 0x94, 0xFE, 0x87, 0xFB, 0xDD, 0x77, 0x8E,
			0x88, 0x20, 0x22, 0x28, 0xC3, 0x28, 0x0C, 0x43,
			0xCF, 0x0B, 0x21, 0x34, 0xAB, 0x50, 0x64, 0x84,
			0x88, 0x20, 0x22, 0xC8, 0x42, 0x37, 0xF0, 0xF7,
			0x03, 0xB4, 0x2A, 0xCC, 0x0C, 0x58, 0x94, 0x40,
			0x4E, 0x7D, 0xE7, 0xDC, 0x57, 0x3F, 0xA8, 0x48,
			0x02, 0xCC, 0xA0, 0xC5, 0x18, 0x95, 0x12, 0x44,
			0x11, 0xA0, 0x18, 0x63, 0x00, 0x21, 0xA0, 0x48,
			0x9A, 0x8D, 0x6E, 0xC6, 0x18, 0x95, 0x12, 0x44,
			0xC1, 0xA1, 0x18, 0x61, 0x70, 0x21, 0xF8, 0x48,
			0x66, 0x8E, 0x31, 0xCE, 0x1C, 0x13, 0x39, 0x42,
			0x2F, 0x12, 0x17, 0xD1, 0x8F, 0x2F, 0xC4, 0x47,
			0x62, 0xCC, 0x31, 0x36, 0x1B, 0x3F, 0x11, 0x21,
			0xD1, 0x93, 0xE8, 0x49, 0xF8, 0x21, 0xC4, 0x40,
			0x62, 0xB4, 0x31, 0x06, 0x98, 0x11, 0x31, 0x31,
			0x31, 0x8A, 0x08, 0x49, 0x08, 0x21, 0xC4, 0x40,
			0x66, 0x86, 0x31, 0x06, 0x68, 0x91, 0xC8, 0x8E,
			0x31, 0x8B, 0x18, 0x41, 0x88, 0xE1, 0xBB, 0x40,
			0x9A, 0x7D, 0xCE, 0xC5, 0x17, 0x9D, 0x73, 0xAD,
			0xCE, 0x0A, 0xE7, 0xC8, 0x77, 0x01, 0xDC, 0xF5,
			0xAC, 0x8B, 0x3F, 0xC6, 0x18, 0x63, 0x8C, 0xF3,
			0x34, 0x30, 0x54, 0x7F, 0x77, 0x11, 0x23, 0x2E,
			0x73, 0x54, 0x28, 0xC6, 0xA8, 0xCC, 0xF7, 0x21,
			0x34, 0x30, 0x12, 0x9C, 0x88, 0x29, 0xFD, 0x27,
			0x6B, 0x20, 0x24, 0xC6, 0xA8, 0x50, 0x88, 0x51,
			0x3F, 0x51, 0xBF, 0xFC, 0xF8, 0xAA, 0x22, 0x24,
			0x6B, 0x20, 0x24, 0xE6, 0x48, 0x62, 0xCC, 0x01,
			0xAA, 0x50, 0x92, 0xFC, 0x08, 0xAA, 0x22, 0x26,
			0x67, 0x54, 0xC2, 0xD9, 0x48, 0x9C, 0xB3, 0x09,
			0x6A, 0x50, 0x92, 0xFC, 0x88, 0x44, 0xDC, 0x25,
			0x9B, 0x8B, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00,
			0xBF, 0x52, 0x92, 0x7E, 0x77, 0x44, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0xA5, 0x92, 0x92, 0x6E, 0xE8, 0xDB, 0x0F, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x25, 0x8D, 0xB2, 0x7E, 0xE8, 0x26, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x85, 0x92, 0x00, 0xC9, 0x6F, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x4A, 0x11, 0xE7, 0x14, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0xB4, 0x7C, 0x18, 0xD4, 0x07, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x4A, 0x11, 0xE7, 0x22, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x85, 0x92, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};

		static constexpr BadgerGL::BitmapMask BITMAP(WIDTH, HEIGHT, DATA);
	}
}

