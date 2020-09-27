#pragma once

#include <BadgerUI/FixedDimensionLayout.h>
#include <BadgerUI/Label.h>
#include <BadgerUI/Box.h>

namespace Badge
{
	class CharacterInfoScreenLayout : public BadgerUI::FixedDimensionLayout
	{
	public:
		CharacterInfoScreenLayout(uint16_t width, uint16_t height);

	protected:
		virtual void onSetup() override;
		virtual void onActivate() override;
		virtual void onPreUpdate(const BadgerUI::UIUpdateContext& context) override;

	private:
		void setLabelCommonProperties(BadgerUI::Label& label);
		void setLabelRowPositions(uint32_t index, BadgerUI::Label& key, BadgerUI::Label& value);

		BadgerUI::Box m_Background;

		BadgerUI::Label m_NameKey;
		BadgerUI::Label m_NameValue;

		BadgerUI::Label m_SpeciesKey;
		BadgerUI::Label m_SpeciesValue;

		BadgerUI::Label m_SocialMediaKey;
		BadgerUI::Label m_SocialMediaValue;

		CoreUtil::TimevalMs m_ButtonReleaseTime = 0;
	};
}
