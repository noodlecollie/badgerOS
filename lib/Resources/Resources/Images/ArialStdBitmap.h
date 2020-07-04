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
			0x03, 0xFC, 0x01, 0xF0, 0x80, 0x1F, 0xF8, 0x1F,
			0x04, 0xE0, 0x0F, 0xF0, 0x3C, 0x0F, 0x3C, 0xC3,
			0x83, 0xFF, 0x07, 0x98, 0xC1, 0x3F, 0xF8, 0x1F,
			0x1F, 0xF8, 0x3F, 0xF8, 0xBD, 0x1F, 0x7E, 0xC3,
			0xC3, 0x03, 0x0F, 0x0C, 0xC3, 0x30, 0x60, 0xD8,
			0x7F, 0x3C, 0x78, 0x1C, 0xFF, 0x38, 0xC7, 0xE3,
			0xE3, 0x00, 0x1C, 0x0C, 0xC3, 0x30, 0x60, 0xF8,
			0xE4, 0x0E, 0xE0, 0x0C, 0x7E, 0xF0, 0x83, 0xFB,
			0x73, 0x3C, 0x3B, 0x06, 0xC6, 0x30, 0x78, 0x78,
			0xC4, 0x06, 0xC0, 0x06, 0x3C, 0xE0, 0x01, 0xDF,
			0x33, 0x7E, 0x33, 0x06, 0xC6, 0x30, 0x78, 0x78,
			0x04, 0x07, 0xC0, 0x07, 0x3C, 0xE0, 0x01, 0xCF,
			0x1B, 0xC7, 0x63, 0x06, 0xC6, 0x30, 0x78, 0x78,
			0x04, 0x03, 0x80, 0x07, 0x3C, 0xE0, 0x01, 0xC3,
			0x9B, 0x81, 0x61, 0x03, 0xCC, 0x30, 0x78, 0xD8,
			0x05, 0x03, 0x80, 0x07, 0x3C, 0xE0, 0x01, 0xC3,
			0x8F, 0x81, 0x61, 0x03, 0xCC, 0x30, 0x78, 0x98,
			0x0F, 0x03, 0x80, 0x07, 0x3C, 0xE0, 0x01, 0xC3,
			0xCF, 0x80, 0x61, 0x03, 0x6C, 0x60, 0x78, 0x18,
			0x3E, 0x03, 0x80, 0x0D, 0x7E, 0x30, 0x83, 0xC3,
			0xCF, 0x80, 0x61, 0x03, 0x3C, 0xC0, 0x78, 0x18,
			0x74, 0x03, 0x80, 0x1D, 0xFF, 0x38, 0xC7, 0xC3,
			0xCF, 0x80, 0x71, 0x03, 0x7C, 0xE0, 0x78, 0x18,
			0xC4, 0x07, 0xC0, 0xF9, 0xBD, 0x1F, 0x7E, 0xC3,
			0xCF, 0xC0, 0x30, 0x03, 0x6C, 0x60, 0x78, 0x18,
			0xC4, 0x06, 0xC6, 0xF0, 0x3C, 0x0F, 0x3C, 0xC3,
			0xCF, 0xE0, 0x38, 0x03, 0xCC, 0x30, 0x78, 0x78,
			0xC4, 0x0E, 0xFE, 0x00, 0x3C, 0x00, 0x00, 0xC3,
			0x8F, 0xF1, 0x1C, 0x03, 0xCC, 0x30, 0x78, 0xF8,
			0xC4, 0x3C, 0x78, 0x06, 0x3C, 0x00, 0x00, 0xC3,
			0x9B, 0xFF, 0x0F, 0x06, 0xC6, 0x30, 0x78, 0xD8,
			0x64, 0xF8, 0xFF, 0x0E, 0x37, 0x00, 0x00, 0xC3,
			0x1B, 0x8F, 0x03, 0x06, 0xC6, 0x30, 0x78, 0xD8,
			0x7F, 0xC0, 0xCF, 0xFD, 0x37, 0x00, 0x00, 0xC3,
			0x33, 0x00, 0xC0, 0x06, 0xC6, 0x30, 0x78, 0x18,
			0x1F, 0x00, 0x80, 0xF9, 0x31, 0x00, 0x00, 0x03,
			0xF3, 0x00, 0x70, 0x0C, 0xC3, 0x30, 0x78, 0x18,
			0x04, 0xFF, 0x01, 0xFC, 0xC1, 0x01, 0xF7, 0xFF,
			0xE3, 0x03, 0x3C, 0x0C, 0xC3, 0x30, 0x78, 0x18,
			0x04, 0xFF, 0x01, 0xFF, 0x87, 0x83, 0xF3, 0xFF,
			0x83, 0xFF, 0x0F, 0x98, 0xC1, 0x3F, 0xFF, 0x1F,
			0x60, 0x00, 0x9C, 0x07, 0x0F, 0xC3, 0x31, 0x00,
			0x03, 0xFC, 0x03, 0xF0, 0x80, 0x1F, 0xEF, 0x1F,
			0xC0, 0x00, 0xCE, 0x01, 0x0C, 0xC7, 0x31, 0x00,
			0x03, 0x0C, 0x70, 0x80, 0x79, 0xC0, 0x00, 0xFE,
			0x80, 0x01, 0xC6, 0x00, 0x18, 0xEE, 0x30, 0x00,
			0x03, 0x0F, 0x70, 0x80, 0xCD, 0x60, 0x80, 0xFF,
			0x03, 0x03, 0xE3, 0x00, 0x00, 0x6C, 0x30, 0x00,
			0x03, 0x1B, 0xD8, 0xC0, 0x86, 0x61, 0xC0, 0x83,
			0x07, 0x87, 0x63, 0x00, 0x00, 0x7C, 0x30, 0x00,
			0x83, 0x19, 0xD8, 0xC0, 0x86, 0x31, 0xE0, 0x00,
			0x0E, 0xCE, 0x61, 0x00, 0x00, 0x38, 0xF0, 0x7F,
			0x86, 0x19, 0xD8, 0xC0, 0x86, 0x31, 0x60, 0x00,
			0x0C, 0xCC, 0x60, 0xC0, 0x1F, 0x38, 0xF0, 0x7F,
			0x86, 0x19, 0x8C, 0xC1, 0x86, 0x19, 0x70, 0x00,
			0x1C, 0xFC, 0x60, 0xC0, 0x1F, 0x6C, 0x30, 0x00,
			0xC6, 0x30, 0x8C, 0x61, 0x86, 0x19, 0x30, 0x00,
			0x18, 0x78, 0x60, 0x00, 0x18, 0x6E, 0x30, 0x00,
			0xCC, 0x30, 0x8C, 0x61, 0xCC, 0x0C, 0x30, 0x00,
			0x18, 0x30, 0xE0, 0x00, 0x18, 0xEE, 0x30, 0x00,
			0xCC, 0x30, 0x06, 0x63, 0x78, 0xCC, 0x33, 0x00,
			0x18, 0x30, 0xC0, 0x00, 0x18, 0xC7, 0x31, 0x00,
			0xD8, 0x30, 0x06, 0x63, 0x00, 0x66, 0x36, 0x00,
			0x18, 0x30, 0xC0, 0x01, 0x98, 0x83, 0x33, 0x00,
			0x78, 0x70, 0x06, 0x73, 0x00, 0x37, 0x3C, 0x00,
			0x18, 0x30, 0x80, 0x07, 0x9E, 0x01, 0x33, 0x00,
			0x78, 0x60, 0x07, 0x37, 0x00, 0x33, 0x7C, 0x00,
			0x1C, 0x30, 0x00, 0xFF, 0xC7, 0x01, 0x37, 0x00,
			0x70, 0x60, 0x03, 0x36, 0x80, 0x33, 0x6C, 0x00,
			0x0C, 0x30, 0x00, 0xF8, 0xE1, 0x00, 0x3E, 0x00,
			0x30, 0x60, 0x03, 0x36, 0x80, 0x31, 0xEC, 0x00,
			0x0E, 0x30, 0x00, 0xFF, 0xC3, 0xFF, 0x81, 0x0F,
			0x30, 0x60, 0x03, 0x36, 0xC0, 0x31, 0xCC, 0x83,
			0x07, 0x30, 0x00, 0xFF, 0xC7, 0xFF, 0xC3, 0x1F,
			0x30, 0xC0, 0x01, 0x1C, 0xC0, 0x60, 0x86, 0xFF,
			0x03, 0xF8, 0xFF, 0x03, 0xCE, 0x00, 0xE7, 0x38,
			0x18, 0xC0, 0x01, 0x1C, 0x60, 0xC0, 0x03, 0xFE,
			0x00, 0xF8, 0xFF, 0x03, 0xDC, 0x00, 0x66, 0x30,
			0x1E, 0x00, 0xE0, 0x00, 0xF8, 0xE1, 0x00, 0x0E,
			0x0F, 0x00, 0x60, 0x03, 0xD8, 0x00, 0x36, 0x60,
			0x0E, 0x00, 0xE0, 0x00, 0xFE, 0xE7, 0x01, 0x8F,
			0x1F, 0x00, 0x30, 0x03, 0xF0, 0x00, 0x36, 0x60,
			0x03, 0x60, 0xB0, 0x01, 0x07, 0xEE, 0x01, 0xCF,
			0x39, 0x00, 0x18, 0x03, 0xF0, 0x00, 0x37, 0x60,
			0x06, 0x30, 0xB0, 0x81, 0x03, 0xEC, 0x01, 0xCF,
			0x30, 0x00, 0x1C, 0x03, 0xF0, 0xFF, 0x33, 0x60,
			0x06, 0x30, 0xB8, 0x83, 0x01, 0x78, 0x83, 0xCD,
			0x30, 0x00, 0x0E, 0x03, 0xF0, 0xFF, 0x30, 0x60,
			0x06, 0x30, 0x18, 0xC3, 0x00, 0x60, 0x83, 0x8D,
			0x19, 0x00, 0x06, 0x03, 0xF0, 0x70, 0x30, 0x60,
			0x0C, 0x18, 0x18, 0xC3, 0x00, 0x60, 0x83, 0x0D,
			0x1F, 0x00, 0x03, 0x03, 0xF0, 0xE0, 0x30, 0x60,
			0x0C, 0x18, 0x0C, 0xC6, 0x00, 0x60, 0x82, 0x8C,
			0x07, 0x80, 0x01, 0x03, 0xF0, 0xC0, 0x31, 0x60,
			0x1C, 0x1C, 0x0C, 0xC6, 0x00, 0x60, 0xC6, 0xCC,
			0x0F, 0xC0, 0x01, 0x03, 0xD8, 0xC0, 0x31, 0x60,
			0x18, 0x0C, 0x0C, 0xC6, 0x00, 0x60, 0xC6, 0xEC,
			0x8C, 0xE0, 0x00, 0x03, 0xD8, 0x80, 0x63, 0x30,
			0x18, 0x0C, 0xFE, 0xCF, 0x00, 0x60, 0xC6, 0x3C,
			0x98, 0x61, 0x00, 0x03, 0xCE, 0x00, 0xE3, 0x38,
			0x30, 0x06, 0xFE, 0xCF, 0x00, 0x78, 0x6C, 0x3C,
			0xF0, 0x30, 0x00, 0xFF, 0xC7, 0x00, 0xE7, 0x1F,
			0x30, 0x06, 0x07, 0x9C, 0x01, 0x78, 0x6C, 0x3C,
			0xF0, 0x18, 0x00, 0xFF, 0xC3, 0x00, 0x8E, 0x0F,
			0x30, 0x06, 0x03, 0x98, 0x03, 0x6C, 0x6C, 0x7C,
			0xE0, 0xFC, 0xFF, 0xC0, 0x7F, 0x18, 0xC0, 0x08,
			0x60, 0x03, 0x03, 0x18, 0x07, 0x6E, 0x28, 0x6C,
			0xF8, 0xFD, 0xFF, 0xC0, 0xFF, 0x19, 0xC0, 0x0C,
			0x60, 0x83, 0x01, 0x30, 0xFE, 0x67, 0x38, 0xEC,
			0xBF, 0x03, 0x06, 0xF0, 0x80, 0x1B, 0xC0, 0x0C,
			0xE0, 0x83, 0x01, 0x30, 0xF8, 0x61, 0x38, 0x8C,
			0x0F, 0x01, 0x06, 0xF0, 0x00, 0x1B, 0xC0, 0x0C,
			0xC0, 0x01, 0x00, 0x00, 0x7F, 0xFC, 0x0F, 0x30,
			0xF6, 0xFF, 0x07, 0xF0, 0x00, 0x1B, 0xC0, 0x7F,
			0xC0, 0x01, 0x00, 0xC0, 0xFF, 0xFC, 0x3F, 0x30,
			0xF6, 0xFF, 0x07, 0xF0, 0x00, 0x1B, 0xC0, 0x7F,
			0x03, 0xDC, 0xFF, 0xCF, 0xC0, 0x0D, 0x30, 0x18,
			0x33, 0x00, 0x06, 0xF0, 0x80, 0x19, 0xC0, 0x0C,
			0x03, 0xCE, 0xFF, 0x6F, 0x80, 0x0F, 0x60, 0x18,
			0x33, 0x00, 0x06, 0xF0, 0xFF, 0xF9, 0xFF, 0x0C,
			0x03, 0x07, 0x30, 0x60, 0x00, 0x0F, 0x60, 0x18,
			0x33, 0x00, 0x06, 0xF0, 0xFF, 0xF9, 0xFF, 0x0C,
			0x83, 0x03, 0x30, 0x60, 0x00, 0x0C, 0xE0, 0xFF,
			0x3F, 0x00, 0x06, 0xF0, 0x80, 0x1B, 0xC0, 0x0C,
			0xC3, 0x01, 0x30, 0xC0, 0x01, 0x0C, 0xE0, 0xFF,
			0x3F, 0x00, 0x06, 0xF0, 0x00, 0x1E, 0xC0, 0x0C,
			0xE3, 0x00, 0x30, 0xC0, 0x3F, 0x0C, 0x30, 0x8C,
			0xF1, 0xFF, 0x06, 0xF0, 0x00, 0x1E, 0xC0, 0x0C,
			0x73, 0x00, 0x30, 0x00, 0xFF, 0xFC, 0x3F, 0x8C,
			0xF1, 0xFF, 0x06, 0xF0, 0x00, 0x1E, 0xC0, 0x0C,
			0x7B, 0x00, 0x30, 0x00, 0xE0, 0xFD, 0x0F, 0x8C,
			0x31, 0x00, 0x06, 0xF0, 0x00, 0x1E, 0xC0, 0x0C,
			0xFF, 0x00, 0x30, 0x00, 0x80, 0x0F, 0x00, 0x8C,
			0x31, 0x00, 0x06, 0xF0, 0x00, 0x1B, 0xC0, 0x0C,
			0xEF, 0x00, 0x30, 0x30, 0x00, 0x0F, 0x80, 0xFF,
			0x3F, 0x00, 0x0C, 0xD8, 0xFF, 0x1B, 0xC0, 0x7C,
			0xC7, 0x01, 0x30, 0x30, 0x00, 0x0F, 0x80, 0xFF,
			0x3F, 0x00, 0x1C, 0xDC, 0xFF, 0x18, 0xC0, 0x78,
			0x83, 0x03, 0x30, 0x60, 0x00, 0x0F, 0x00, 0xC6,
			0x30, 0x00, 0xF8, 0x0F, 0x00, 0x3E, 0xF8, 0x78,
			0x03, 0x07, 0x30, 0xE0, 0xC1, 0x0D, 0x00, 0xC6,
			0x30, 0x00, 0xF0, 0x07, 0x80, 0x7F, 0xFC, 0x79,
			0x03, 0x07, 0x30, 0xC0, 0xFF, 0x0C, 0x00, 0x63,
			0xF0, 0xFF, 0x01, 0xF0, 0xCF, 0xE1, 0x06, 0x03,
			0x03, 0x0E, 0x30, 0x00, 0x7F, 0x0C, 0x00, 0x63,
			0xF0, 0xFF, 0x01, 0xF0, 0xCF, 0xC0, 0x07, 0x03,
			0x03, 0x1C, 0x30, 0x00, 0x00, 0x30, 0x1E, 0xF0,
			0x01, 0x18, 0x7C, 0x18, 0xC0, 0x00, 0x03, 0x1E,
			0x03, 0x38, 0x30, 0x00, 0x00, 0xB0, 0x7F, 0xF8,
			0x03, 0x1C, 0xFE, 0x19, 0x60, 0x00, 0x03, 0x1E,
			0x03, 0x18, 0x1F, 0x03, 0x00, 0xB0, 0xE1, 0x1C,
			0x07, 0x1E, 0x87, 0x19, 0x60, 0x1E, 0x03, 0x1E,
			0x07, 0xD8, 0x7F, 0x03, 0x00, 0xF0, 0xC0, 0x0C,
			0x06, 0x9E, 0x03, 0xDB, 0x63, 0x7F, 0x03, 0x1E,
			0x0F, 0xD8, 0x60, 0x03, 0xC0, 0x33, 0xC0, 0x0C,
			0x06, 0x9B, 0x01, 0xFB, 0xE7, 0x61, 0x86, 0x1F,
			0x0F, 0x78, 0xC0, 0x03, 0xE0, 0x3F, 0xC0, 0x0C,
			0x86, 0x1B, 0x00, 0x1F, 0xEC, 0xC0, 0xFE, 0x1E,
			0x1B, 0x78, 0xC0, 0xF3, 0x70, 0x3C, 0x60, 0x18,
			0x83, 0x19, 0x80, 0x0D, 0x78, 0xC0, 0x78, 0x1E,
			0x33, 0x18, 0xC0, 0xFB, 0x39, 0x38, 0x3C, 0xF0,
			0xC1, 0x18, 0xC0, 0x01, 0x78, 0xC0, 0x00, 0x7E,
			0x33, 0x18, 0xC0, 0x8F, 0x1B, 0x30, 0x7C, 0xF8,
			0xC3, 0x18, 0xE0, 0x00, 0x78, 0xC0, 0x00, 0x7B,
			0x63, 0x18, 0x60, 0x07, 0x1F, 0x30, 0xC0, 0x0C,
			0x66, 0x18, 0x30, 0x00, 0xD8, 0xC0, 0x03, 0x5B,
			0xE3, 0x18, 0x30, 0x03, 0x1E, 0x30, 0x80, 0x07,
			0x7C, 0x18, 0x18, 0x0C, 0xD8, 0x61, 0x87, 0x5B,
			0xC3, 0x18, 0x18, 0x03, 0x1E, 0x30, 0x80, 0x07,
			0xFC, 0x7F, 0x18, 0x0C, 0x88, 0x3F, 0xFE, 0x79,
			0x83, 0x19, 0x0C, 0x03, 0x1E, 0xF0, 0x80, 0x07,
			0xFC, 0x7F, 0x18, 0x18, 0x0C, 0x1F, 0x7C, 0x38,
			0x83, 0x19, 0x06, 0x03, 0x36, 0xF8, 0x81, 0x07,
			0x0C, 0x18, 0x00, 0xF0, 0x07, 0xCC, 0xF1, 0xEC,
			0x03, 0x1B, 0x03, 0x03, 0x76, 0xBC, 0xC1, 0x0C,
			0x06, 0x18, 0x00, 0xE0, 0x03, 0xFC, 0xFB, 0xFD,
			0x03, 0x9E, 0x01, 0x07, 0xE3, 0x37, 0x7F, 0xFC,
			0x07, 0x18, 0x18, 0x00, 0x00, 0x1C, 0x8F, 0x1F,
			0x03, 0xDE, 0x00, 0x8F, 0xC3, 0x33, 0x3E, 0xF0,
			0x01, 0x18, 0x18, 0x00, 0x00, 0x0C, 0x06, 0x0F,
			0x03, 0xFC, 0xFF, 0xFB, 0x01, 0x00, 0x0F, 0xF0,
			0xE0, 0xFF, 0xFF, 0x07, 0x02, 0x0F, 0x06, 0x0F,
			0x03, 0xF8, 0xFF, 0xF3, 0x00, 0x00, 0x0F, 0xF8,
			0xE0, 0x3F, 0x00, 0x07, 0x07, 0x0F, 0x06, 0x0F,
			0xFF, 0x1F, 0x60, 0x80, 0x01, 0x00, 0x1B, 0x18,
			0xB0, 0x3F, 0x00, 0x07, 0x07, 0x0F, 0x06, 0x0F,
			0xFF, 0x1F, 0x60, 0x80, 0x01, 0x00, 0x1B, 0x18,
			0xB0, 0x3F, 0x00, 0x0D, 0x85, 0x0D, 0x06, 0x0F,
			0x00, 0x1A, 0x60, 0x80, 0x01, 0x00, 0x1B, 0xFE,
			0xB0, 0x3F, 0x00, 0x8D, 0x8D, 0x0D, 0x06, 0x0F,
			0x00, 0x1B, 0x60, 0x80, 0x01, 0x00, 0x33, 0xFE,
			0x98, 0x3F, 0x00, 0x8D, 0x8D, 0x0D, 0x06, 0x0F,
			0x80, 0x19, 0x6C, 0x80, 0x79, 0x00, 0x33, 0x18,
			0x98, 0x3F, 0x00, 0xD9, 0xD8, 0x0C, 0x06, 0x0F,
			0x80, 0x18, 0x66, 0x80, 0xFD, 0x00, 0x33, 0x18,
			0x98, 0x3F, 0x00, 0xD9, 0xD8, 0x0C, 0x06, 0x0F,
			0xC0, 0x18, 0x63, 0x80, 0xC7, 0x01, 0x73, 0x18,
			0x9C, 0x3F, 0x00, 0xD9, 0xD8, 0x0C, 0x06, 0x0F,
			0x60, 0x98, 0x61, 0x80, 0x83, 0x01, 0x63, 0x18,
			0x8C, 0x3F, 0x00, 0x51, 0x50, 0x00, 0x03, 0x0C,
			0x60, 0xD8, 0x60, 0x80, 0x81, 0x01, 0x63, 0x18,
			0x8C, 0x3F, 0x00, 0x71, 0x70, 0x00, 0x03, 0x0C,
			0x60, 0xF8, 0x60, 0x80, 0x81, 0x01, 0x63, 0x18,
			0x8C, 0x3F, 0x00, 0x71, 0x70, 0x00, 0x83, 0x7F,
			0x30, 0xF8, 0x61, 0x80, 0x81, 0x07, 0xC3, 0x18,
			0x86, 0x3F, 0x00, 0x21, 0x20, 0x00, 0x03, 0x1E,
			0x30, 0x98, 0x61, 0x80, 0x81, 0x07, 0xC3, 0x18,
			0x86, 0x27, 0x00, 0x0F, 0xFF, 0x07, 0x03, 0x1E,
			0x30, 0x18, 0x63, 0x80, 0x81, 0x8F, 0xC3, 0x18,
			0x86, 0x27, 0x00, 0x0D, 0xFF, 0xFF, 0x7F, 0x33,
			0x18, 0x18, 0x67, 0x80, 0x81, 0xFD, 0x81, 0x19,
			0x83, 0xFF, 0xFF, 0x19, 0xC0, 0xF8, 0x7F, 0x12,
			0x18, 0x18, 0x66, 0x80, 0x81, 0xF9, 0x80, 0x19,
			0x83, 0x1F, 0x60, 0x60, 0xE0, 0x00, 0x03, 0x00,
			0x18, 0x18, 0xEC, 0xFF, 0x81, 0x81, 0x0F, 0x7C,
			0xE6, 0xE1, 0x67, 0x60, 0x70, 0x00, 0x03, 0x00,
			0x18, 0x18, 0xFC, 0xFF, 0x81, 0xE1, 0x1F, 0xFE,
			0xF6, 0xF3, 0x6F, 0x60, 0x38, 0x00, 0x03, 0x00,
			0xF8, 0xC0, 0xC7, 0x80, 0x0F, 0x7C, 0x38, 0xC7,
			0x1F, 0x3F, 0x7C, 0x60, 0x18, 0x00, 0x03, 0x00,
			0xFC, 0xE1, 0xCF, 0x80, 0x0D, 0x36, 0xB0, 0x83,
			0x0F, 0x1E, 0x78, 0x60, 0x0C, 0x00, 0x03, 0x00,
			0x8E, 0x73, 0x9C, 0xC1, 0x18, 0x07, 0xB0, 0x01,
			0x06, 0x3E, 0x60, 0x60, 0x0E, 0x00, 0x00, 0x06,
			0x03, 0x3F, 0xB8, 0xC1, 0x38, 0x03, 0xBE, 0x01,
			0x06, 0xF6, 0x63, 0x60, 0x07, 0x00, 0x00, 0x0F,
			0x03, 0x1E, 0xB0, 0xC1, 0xB0, 0xC1, 0xBF, 0x01,
			0x06, 0xE6, 0x6F, 0x60, 0x03, 0x00, 0x00, 0x0F,
			0xFF, 0x1F, 0x30, 0x63, 0xE0, 0xE0, 0xB1, 0x01,
			0x06, 0x06, 0x7F, 0xE0, 0xFF, 0x07, 0x80, 0x19,
			0xFF, 0x1F, 0x30, 0x63, 0xE0, 0x30, 0xB0, 0x01,
			0x06, 0x06, 0x78, 0xF0, 0xFF, 0x07, 0x80, 0x19,
			0x03, 0x18, 0x30, 0x36, 0xE0, 0x30, 0xB0, 0x83,
			0x07, 0x1E, 0xF8, 0xF8, 0x00, 0x00, 0x90, 0x19,
			0x03, 0x18, 0x30, 0x36, 0xB0, 0x71, 0x3C, 0xC3,
			0x07, 0x3E, 0xDC, 0xEF, 0x03, 0x00, 0xDC, 0x30,
			0x07, 0x3E, 0x38, 0x36, 0xB8, 0xE3, 0x3F, 0xFE,
			0x06, 0xF6, 0x8F, 0x67, 0x1F, 0x80, 0xCF, 0x30,
			0x8E, 0x73, 0x1C, 0x1C, 0x18, 0xC3, 0x63, 0x7C,
			0x06, 0xE6, 0x07, 0x00, 0x78, 0xE0, 0x61, 0x60,
			0xFC, 0xE1, 0x0F, 0x1C, 0x0C, 0x06, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0xE0, 0x79, 0xE0, 0xFF,
			0xF8, 0xC0, 0x07, 0x08, 0x0E, 0x0E, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0xFF,
			0xF3, 0x7B, 0xC0, 0xFF, 0x0F, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0xE0, 0x79, 0x00, 0x00,
			0xF3, 0xFF, 0xF1, 0xFF, 0x0F, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x78, 0xE0, 0x01, 0x00,
			0xB3, 0x8F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x0F, 0x00,
			0xB3, 0x03, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0xFC, 0xFF,
			0xF3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0xF0, 0xFF,
			0x73, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};

		static constexpr BadgerGL::BitmapMask BITMAP(WIDTH, HEIGHT, DATA);
	}
}

