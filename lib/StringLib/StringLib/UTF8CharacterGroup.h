#pragma once

#include <cstdint>

namespace StringLib
{
	enum UTF8CharacterGroup : uint32_t
	{
		LatinAndLatinSupplement = 0x000000,
		LatinExtendedA = 0x000100,
		LatinExtendedB = 0x000180,
		IPAExtensions = 0x000250,
		SpacingModifierLetters = 0x0002B0,
		CombiningDiacriticalMarks = 0x000300,
		GreekAndCoptic = 0x000370,
		Cyrillic = 0x000400,
		CyrillicSupplement = 0x000500,
		Armenian = 0x000530,
		Hebrew = 0x000590,
		Arabic = 0x000600,
		ArabicSupplement = 0x000750,
		ArabicExtendedA = 0x0008A0,
		PhoneticExtensions = 0x001D00,
		PhoneticExtensionsSupplement = 0x001D80,
		CombiningDiacriticalMarksSupplement = 0x001DC0,
		LatinExtendedAdditional = 0x001E00,
		GreekExtended = 0x001F00,
		GeneralPunctuation = 0x002000,
		SubscriptsAndSuperscripts = 0x002070,
		CurrencySymbols = 0x0020A0,
		CombiningDiacriticalMarksForSymbols = 0x0020D0,
		LetterlikeSymbols = 0x002100,
		NumberForms = 0x002150,
		Arrows = 0x002190,
		MathematicalOperators = 0x002200,
		MiscellaneousTechnical = 0x002300,
		BoxDrawing = 0x002500,
		BlockElements = 0x002580,
		GeometricShapes = 0x0025A0,
		MiscellaneousSymbols = 0x002600,
		LatinExtendedC = 0x002C60,
		SupplementalPunctuation = 0x002E00,
		ModifierToneLetters = 0x00A700,
		LatinExtendedD = 0x00A720,
		LatinExtendedE = 0x00AB30,
		PrivateUseArea = 0x00F300,
		AlphabeticalPresentationForms = 0x00FB00,
		ArabicPresentationFormsA1 = 0x00FB50,
		ArabicPresentationFormsA2 = 0x00FC50,
		ArabicPresentationFormsA3 = 0x00FD50,
		CombiningHalfMarks = 0x00FE20,
		ArabicPresentationFormsB = 0x00FE70,
		Specials = 0x00FF00
	};
}
