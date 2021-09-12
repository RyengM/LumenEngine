#pragma once

namespace Lumen::Game
{
	class BaseFramework
	{
	public:
		BaseFramework(const char* name) : mName(name) {}
		virtual ~BaseFramework() {}

		virtual const char* GetName() noexcept
		{
			return mName;
		}

	private:
		const char* mName;
	};
}