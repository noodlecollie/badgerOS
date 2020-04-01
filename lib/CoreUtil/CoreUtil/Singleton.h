#pragma once

namespace BadgeOS
{
	// Only supports default-initialisable objects.
	template<typename T>
	class Singleton
	{
	public:
		static T& staticInstance()
		{
			static T instance;
			return instance;
		}
	};
}
