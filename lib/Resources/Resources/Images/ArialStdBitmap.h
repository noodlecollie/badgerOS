#pragma once

#include <cstddef>
#include <cstdint>
#include <BadgerGL/BitmapMask.h>
#include <BadgerGL/Defs.h>

namespace Resources
{
	namespace ArialStdBitmap
	{
		static constexpr size_t WIDTH = 128;
		static constexpr size_t HEIGHT = 128;
		static constexpr size_t DATA_LENGTH = BadgerGL::maskedDataSizeForDimensions(WIDTH, HEIGHT);

		static constexpr uint8_t DATA[DATA_LENGTH] =
		{
			0xC0, 0x1F, 0xE0, 0x07, 0x0C, 0xFF, 0x3C, 0x04,
			0xF8, 0x61, 0xE0, 0xC0, 0x1C, 0x18, 0x07, 0xF8,
			0xF0, 0x7F, 0xF0, 0x0F, 0x12, 0xFF, 0x3C, 0x1F,
			0xFC, 0x67, 0xE0, 0xC0, 0x36, 0x0C, 0x06, 0xD8,
			0x78, 0xF0, 0x30, 0x0C, 0x33, 0x3C, 0xB0, 0x3F,
			0x0E, 0x6F, 0xB0, 0xC1, 0x63, 0x0C, 0x0C, 0x0C,
			0x1C, 0xC0, 0x31, 0x0C, 0x21, 0x3C, 0xF0, 0x75,
			0x03, 0xCC, 0xB0, 0x61, 0x63, 0x06, 0x1C, 0x0E,
			0x8E, 0xB3, 0x31, 0x8C, 0x61, 0x3C, 0xFC, 0xE4,
			0x03, 0xDC, 0xB0, 0x61, 0x63, 0x06, 0x38, 0xC7,
			0xC6, 0x37, 0x33, 0x8C, 0x61, 0x3C, 0xFC, 0x84,
			0x01, 0xD8, 0x10, 0x61, 0x63, 0x03, 0x30, 0xC3,
			0xE6, 0x1C, 0x33, 0xCC, 0xC0, 0x3C, 0xFC, 0x85,
			0x01, 0xD8, 0x18, 0x63, 0x36, 0x03, 0xE0, 0xC1,
			0x63, 0x18, 0x3B, 0xDC, 0xC0, 0x3C, 0xBC, 0x8F,
			0x01, 0xD8, 0x18, 0x63, 0x9C, 0x39, 0xE0, 0xC1,
			0x33, 0x18, 0x1F, 0xF8, 0xC0, 0x3C, 0x3C, 0xBE,
			0x01, 0x98, 0x19, 0x33, 0x80, 0x6D, 0xC0, 0xC0,
			0x33, 0x18, 0x1F, 0xF8, 0xC0, 0x3C, 0x3C, 0xF4,
			0x01, 0x98, 0x0D, 0x36, 0xC0, 0xC6, 0xC0, 0xC0,
			0x33, 0x88, 0x1B, 0xDC, 0xC0, 0x3C, 0x3C, 0xE4,
			0x03, 0x8C, 0x0D, 0x36, 0xC0, 0xC6, 0xC0, 0xC0,
			0x33, 0x8C, 0x31, 0xCC, 0xC0, 0x3C, 0x3C, 0x64,
			0xC3, 0x8D, 0x0D, 0x36, 0x60, 0xC6, 0xC0, 0xC0,
			0x73, 0xCE, 0x30, 0xCC, 0xC0, 0x3C, 0xFC, 0x64,
			0x0E, 0x87, 0x0D, 0x36, 0x60, 0xC6, 0xC0, 0xC0,
			0xE6, 0x7F, 0x30, 0x8C, 0x61, 0x3C, 0xFC, 0x75,
			0xFC, 0x0F, 0x07, 0x1C, 0x30, 0x6C, 0xC0, 0xC0,
			0xC6, 0x3D, 0x33, 0x8C, 0x61, 0x3C, 0xBC, 0x3F,
			0xF8, 0x1D, 0x07, 0x1C, 0x30, 0x38, 0xC0, 0xC0,
			0x0C, 0x80, 0x31, 0x0C, 0x21, 0x3C, 0x3C, 0x1F,
			0x00, 0x10, 0x70, 0x00, 0x0F, 0xFF, 0x0F, 0x33,
			0x3C, 0xE0, 0x30, 0x0C, 0x33, 0x3C, 0x3C, 0x04,
			0x18, 0xC0, 0xF8, 0xC0, 0x3F, 0xFF, 0x0F, 0x33,
			0xF0, 0x7F, 0xF0, 0x0F, 0x12, 0xFF, 0x3F, 0x04,
			0x18, 0xC0, 0x8C, 0xE1, 0x70, 0x60, 0x00, 0x3B,
			0xC0, 0x1F, 0xE0, 0x07, 0x0C, 0xFF, 0xF7, 0x01,
			0x3F, 0xE0, 0x8C, 0x61, 0xE0, 0x60, 0x80, 0x19,
			0xF0, 0x07, 0xFC, 0xE0, 0xE0, 0xC0, 0xC1, 0x83,
			0x37, 0x60, 0x8C, 0x71, 0xC0, 0x60, 0xF0, 0x7F,
			0xF8, 0x0F, 0xFE, 0xC1, 0x61, 0xC0, 0xC1, 0x83,
			0x37, 0x60, 0xC8, 0x30, 0x00, 0x60, 0xF0, 0x7F,
			0x1C, 0x1C, 0x87, 0x83, 0x31, 0x60, 0xC3, 0x83,
			0x67, 0x30, 0x78, 0x30, 0x00, 0x60, 0x80, 0x19,
			0x06, 0xB8, 0x01, 0x86, 0x3B, 0x60, 0xC3, 0xC6,
			0x66, 0x30, 0x3C, 0x30, 0x00, 0x60, 0xC0, 0x0C,
			0x06, 0xD0, 0x01, 0x0E, 0x1B, 0x60, 0xC3, 0xC6,
			0x66, 0x30, 0x66, 0x30, 0x00, 0x60, 0xC0, 0x0C,
			0x03, 0xC0, 0x00, 0x0C, 0x0E, 0x30, 0xC6, 0xC6,
			0xC6, 0x18, 0x63, 0x36, 0x00, 0x60, 0xF0, 0x7F,
			0x03, 0xC0, 0x00, 0x0C, 0x0E, 0x30, 0xC6, 0xC6,
			0xC6, 0x18, 0xC3, 0x76, 0xC0, 0x60, 0xF0, 0x7F,
			0x83, 0xFF, 0x00, 0x0C, 0x0E, 0x30, 0xC6, 0x6C,
			0x86, 0x0D, 0x83, 0x63, 0xE0, 0x60, 0xC0, 0x0C,
			0x83, 0xFF, 0x00, 0x0C, 0x1B, 0x18, 0xCC, 0x6C,
			0x86, 0x0D, 0x87, 0xE3, 0x70, 0x60, 0xE0, 0x06,
			0x03, 0xF0, 0x00, 0x0C, 0x1B, 0xF8, 0xCF, 0x6C,
			0x86, 0x0D, 0xFE, 0xCE, 0x3F, 0x60, 0x60, 0x06,
			0x06, 0xF0, 0x01, 0x8E, 0x39, 0xFC, 0xDF, 0x6C,
			0x06, 0x07, 0x7C, 0x04, 0x0F, 0x60, 0x60, 0x06,
			0x06, 0xB0, 0x01, 0xC6, 0x71, 0x0C, 0xD8, 0x38,
			0x06, 0x07, 0x00, 0xFF, 0xFF, 0x03, 0xC8, 0xC0,
			0x1C, 0x3C, 0x87, 0xC3, 0x60, 0x0C, 0xD8, 0x38,
			0xFE, 0xE7, 0x1F, 0xFF, 0xFF, 0x07, 0xCC, 0xC0,
			0xF8, 0x1F, 0xFE, 0x61, 0xE0, 0x06, 0xF0, 0x38,
			0xFE, 0xE7, 0x3F, 0x03, 0x0C, 0x0E, 0x8E, 0x61,
			0xE0, 0x07, 0xFC, 0x70, 0xC0, 0x07, 0xB0, 0xC1,
			0x0D, 0x78, 0x70, 0x03, 0x0C, 0x0C, 0x8E, 0x61,
			0xFE, 0xC7, 0xCF, 0x3F, 0x06, 0x3C, 0xE0, 0xE1,
			0x1C, 0x78, 0x60, 0x03, 0x0C, 0x0C, 0x8F, 0x63,
			0xFE, 0xE7, 0xDF, 0x7F, 0x06, 0x3C, 0xE0, 0x71,
			0x3C, 0x78, 0xC0, 0x03, 0x0C, 0x8C, 0x0D, 0x33,
			0x00, 0x73, 0xF8, 0xE0, 0x06, 0x3C, 0xE0, 0x39,
			0x3C, 0x78, 0xC0, 0xFF, 0x0D, 0xCE, 0x0C, 0x33,
			0x80, 0x31, 0xF0, 0xC0, 0x06, 0x3C, 0xE0, 0x19,
			0x6C, 0x78, 0xC0, 0xFF, 0xFD, 0xC7, 0x0C, 0x36,
			0x80, 0x31, 0xC0, 0xC0, 0x06, 0x3C, 0xE0, 0x1D,
			0x6C, 0x78, 0xC0, 0x03, 0xFC, 0x63, 0x0C, 0x1E,
			0xC0, 0x70, 0xC0, 0xE0, 0x06, 0x3C, 0xE0, 0x0F,
			0xCC, 0x78, 0xC0, 0x03, 0x0C, 0x30, 0x0C, 0x1C,
			0x60, 0xE0, 0xC3, 0x7F, 0x06, 0xFC, 0xFF, 0x1F,
			0xCC, 0x79, 0xC0, 0x03, 0x0C, 0xF0, 0x3F, 0x1C,
			0x70, 0x80, 0xCF, 0x3F, 0x06, 0xFC, 0xFF, 0x1B,
			0x8C, 0x79, 0xC0, 0x03, 0x0C, 0xF0, 0x3F, 0x0C,
			0x30, 0x00, 0xDC, 0x18, 0x06, 0x3C, 0xE0, 0x39,
			0x0C, 0x7B, 0x60, 0x03, 0x0C, 0x00, 0x0C, 0x0E,
			0x18, 0x00, 0xF0, 0x30, 0x06, 0x3C, 0xE0, 0x71,
			0x0C, 0x7B, 0x70, 0xFF, 0x0F, 0x00, 0x8C, 0x07,
			0x0C, 0x18, 0xF0, 0x70, 0x06, 0x3C, 0xE0, 0xE1,
			0x0C, 0xFE, 0x3F, 0xFF, 0x0F, 0x00, 0x8C, 0x03,
			0x0C, 0x18, 0xF0, 0x60, 0x06, 0x3C, 0xE0, 0xC1,
			0x0C, 0xFE, 0x1F, 0xE0, 0xB1, 0x87, 0xF7, 0x7F,
			0x06, 0x70, 0xF8, 0xE0, 0x0C, 0x36, 0xE0, 0xC1,
			0x0D, 0x1C, 0xF0, 0xF1, 0xF7, 0xCF, 0xFF, 0x7F,
			0xFF, 0xF7, 0xDF, 0xC0, 0xFC, 0x37, 0xE0, 0x81,
			0x0F, 0x18, 0xF8, 0x33, 0x76, 0xCC, 0xF8, 0x00,
			0xFF, 0xC7, 0xC7, 0xC0, 0xF1, 0x31, 0xE0, 0x01,
			0x80, 0x79, 0x1F, 0x1F, 0x3C, 0x78, 0xF0, 0x00,
			0x7F, 0xF0, 0xF0, 0x87, 0xE7, 0x3F, 0x9F, 0x01,
			0x80, 0xFD, 0x0F, 0x1E, 0x3C, 0x78, 0xF0, 0x00,
			0xFF, 0xF8, 0xF1, 0xC7, 0xEF, 0xBF, 0xBF, 0x01,
			0x80, 0x8D, 0x0F, 0x1E, 0x3C, 0x78, 0xF0, 0x00,
			0xC3, 0x9D, 0x33, 0x60, 0x1C, 0xD0, 0xF1, 0x01,
			0x80, 0x07, 0x1F, 0x1F, 0x3C, 0x78, 0xF0, 0x3F,
			0x83, 0x0D, 0x33, 0x60, 0x18, 0xD8, 0xE0, 0x3D,
			0xBC, 0x07, 0xFB, 0x3B, 0x3E, 0x78, 0xF0, 0x3F,
			0x83, 0x01, 0x1B, 0x30, 0x00, 0x0C, 0xE0, 0x7F,
			0xFE, 0x07, 0xFB, 0xF3, 0x7F, 0xCC, 0xF8, 0x00,
			0xC3, 0x81, 0xDB, 0xB3, 0x07, 0x0C, 0xB0, 0x63,
			0xC6, 0x07, 0x1F, 0xE7, 0xFD, 0xCF, 0xFF, 0x00,
			0xFF, 0xC0, 0xF8, 0xF7, 0x0F, 0x06, 0xB8, 0xC1,
			0x83, 0x07, 0x0F, 0x06, 0xBC, 0x87, 0xF7, 0x00,
			0xFF, 0xC0, 0x1B, 0x7E, 0x1C, 0x06, 0x9C, 0xC1,
			0x83, 0x8D, 0x0F, 0x1E, 0x3C, 0x00, 0xF0, 0x00,
			0x83, 0x01, 0x07, 0x3C, 0x18, 0x03, 0x8E, 0xC1,
			0x83, 0xFD, 0x0F, 0x3E, 0x36, 0x00, 0xF0, 0x00,
			0x03, 0x03, 0x06, 0x3C, 0x18, 0x03, 0x86, 0xC1,
			0x83, 0x79, 0x1F, 0xF7, 0x37, 0x00, 0xF0, 0x00,
			0x03, 0x03, 0x06, 0x3C, 0x18, 0x03, 0x86, 0xC1,
			0x83, 0x01, 0xFB, 0xE3, 0x31, 0x00, 0xF0, 0x00,
			0x03, 0x0F, 0x1E, 0x3C, 0x98, 0x01, 0x80, 0x63,
			0xC6, 0x87, 0xF3, 0x01, 0x06, 0xC1, 0x7B, 0xDE,
			0x83, 0x1F, 0x3F, 0x66, 0x8C, 0x01, 0x80, 0x7F,
			0xFE, 0xFF, 0xE1, 0xFF, 0x87, 0xC3, 0x7F, 0xFF,
			0xFF, 0xF9, 0xF3, 0xE7, 0x8F, 0x01, 0x86, 0x3D,
			0xBC, 0xF9, 0xE0, 0x00, 0x87, 0xC3, 0xC7, 0x31,
			0xFF, 0xF0, 0xE1, 0x81, 0x87, 0x01, 0x06, 0xE0,
			0x01, 0xFF, 0x86, 0x00, 0x8D, 0x62, 0xC3, 0x30,
			0x7C, 0xF8, 0x0C, 0x18, 0x18, 0x00, 0xE3, 0xE1,
			0x01, 0xFF, 0x86, 0x00, 0xCD, 0x66, 0xC3, 0x30,
			0xFE, 0xFC, 0x0D, 0x18, 0x18, 0x00, 0xF3, 0x31,
			0x83, 0xFF, 0x86, 0x00, 0xD9, 0x36, 0xC3, 0x30,
			0xC6, 0x0C, 0x0F, 0x18, 0x18, 0x00, 0x33, 0x30,
			0xE3, 0xFF, 0x9F, 0x00, 0xD9, 0x36, 0xC3, 0x30,
			0x83, 0x07, 0x0F, 0x18, 0x18, 0x00, 0x33, 0x30,
			0x63, 0xFF, 0x9F, 0x00, 0x59, 0x34, 0xC3, 0x30,
			0x83, 0x01, 0x0F, 0x1F, 0xD8, 0x03, 0xFF, 0x30,
			0x03, 0xFF, 0x86, 0x00, 0x71, 0x1C, 0xC3, 0x30,
			0x83, 0x01, 0x8F, 0x1B, 0xF8, 0x07, 0xFF, 0x18,
			0x06, 0xFF, 0x86, 0x00, 0x71, 0x1C, 0xC3, 0xF0,
			0x83, 0x01, 0xCD, 0x19, 0x38, 0x06, 0x33, 0x18,
			0x06, 0xFF, 0xE6, 0x00, 0x71, 0x1C, 0xC3, 0xF0,
			0x83, 0x81, 0xED, 0x18, 0x18, 0x06, 0x33, 0x18,
			0x06, 0xFF, 0xE6, 0x00, 0x47, 0x00, 0x00, 0x6E,
			0x83, 0xC1, 0x7C, 0x18, 0x18, 0x06, 0x33, 0x0C,
			0x0C, 0xFF, 0xC6, 0x00, 0xCD, 0x03, 0xC0, 0x6F,
			0x83, 0x61, 0xFC, 0x18, 0x18, 0x06, 0x33, 0x0C,
			0x0C, 0xFF, 0xC6, 0xFF, 0x09, 0x0F, 0xF0, 0x6C,
			0x83, 0x31, 0xCC, 0x18, 0x18, 0x1E, 0x33, 0x0C,
			0x0C, 0x3F, 0x26, 0x00, 0x03, 0x78, 0x1E, 0x6C,
			0x83, 0x19, 0xCC, 0x19, 0x18, 0x1E, 0x33, 0x0C,
			0x0C, 0x3F, 0xDE, 0x0E, 0x03, 0xC0, 0x03, 0x6C,
			0xC6, 0x0C, 0x8C, 0x1B, 0x18, 0x3E, 0x33, 0x06,
			0x18, 0xFF, 0xDC, 0x0F, 0x03, 0x78, 0x1E, 0x00,
			0xFE, 0xFE, 0x0F, 0xFB, 0x1F, 0xF6, 0x31, 0x06,
			0x18, 0xFF, 0xC0, 0x01, 0x03, 0x0F, 0xF0, 0x00,
			0x7C, 0xFE, 0x0F, 0xFF, 0x1F, 0xE6, 0x30, 0xC0,
			0xDE, 0x30, 0xCF, 0xF0, 0xFF, 0x03, 0xC0, 0x03,
			0x7C, 0xF8, 0x0C, 0x1E, 0xEC, 0x9F, 0x0F, 0xCF,
			0xFF, 0xF0, 0xDF, 0xF0, 0x7F, 0x00, 0x00, 0x02,
			0xFE, 0xFC, 0x0D, 0x36, 0xE6, 0xFF, 0x9F, 0xDF,
			0xF1, 0xF0, 0xF0, 0x00, 0x03, 0x00, 0x00, 0x00,
			0xC6, 0x8C, 0x19, 0x63, 0x03, 0x7C, 0x98, 0xF9,
			0xF0, 0xF0, 0xC0, 0x00, 0x03, 0x00, 0x00, 0x00,
			0x83, 0x07, 0x1B, 0x63, 0x03, 0x0E, 0xD8, 0xF0,
			0xF0, 0xF0, 0xC3, 0x00, 0x03, 0x00, 0x00, 0x00,
			0xFF, 0x07, 0x1B, 0xC3, 0x01, 0x07, 0xDE, 0xC0,
			0xF0, 0xB0, 0xDF, 0x00, 0x03, 0x00, 0x00, 0x00,
			0xFF, 0x07, 0xB3, 0xC1, 0x81, 0xC3, 0xDF, 0xC0,
			0xF0, 0x30, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x03, 0x06, 0xB3, 0xC1, 0xC1, 0xE1, 0xD9, 0xC0,
			0xF0, 0x30, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x03, 0x06, 0xB3, 0x61, 0xE3, 0x60, 0xD8, 0xF0,
			0xF0, 0xF8, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x86, 0x8D, 0xE1, 0x60, 0x73, 0x60, 0x9C, 0xF9,
			0xF0, 0xBF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00,
			0xFE, 0xFC, 0xE1, 0x30, 0xF6, 0xFF, 0x9F, 0xDF,
			0xB0, 0x37, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x7C, 0xF8, 0x40, 0x18, 0xFC, 0xDF, 0x33, 0x0F,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x18, 0xFF, 0x23, 0xDE, 0x81, 0xFF, 0x03, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x3C, 0xFF, 0x23, 0xFE, 0xC7, 0xFF, 0x03, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x3C, 0x00, 0xFC, 0x37, 0x7E, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x3C, 0x00, 0x20, 0x16, 0x38, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x66, 0xFF, 0x53, 0x0E, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x66, 0xFF, 0xDB, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};

		static constexpr BadgerGL::BitmapMask BITMAP(WIDTH, HEIGHT, DATA);
	}
}

