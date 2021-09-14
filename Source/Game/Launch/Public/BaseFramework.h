#pragma once
#include "Game/Launch/Public/Launcher.h"

namespace Lumen::Game
{
	// Platform independent parts, for OS related should be implemented in specific implementation inherit from this class
	class BaseFramework
	{
	public:
		BaseFramework(const char* name) : mName(name) {}
		virtual ~BaseFramework() {}

		inline void PreInit() { mLauncher.PreInit(); }
		inline void Init() { mLauncher.Init(); }
		inline void Tick() { mLauncher.Tick(); }
		inline void Exit() { mLauncher.Exit(); }

		inline const char* GetName() noexcept { return mName; }

	private:
		const char* mName;
		Launcher mLauncher;
	};
}