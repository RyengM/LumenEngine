#pragma once
#include "Game/Engine/Public/EditorEngine.h"

namespace Lumen::Game
{
	// Platform independent parts, for OS related should be implemented in specific implementation inherit from this class
	class BaseFramework
	{
	public:
		BaseFramework(const char* name) : mName(name) {}
		virtual ~BaseFramework() {}

		inline void PreInit() { mEngine.PreInit(); }
		inline void Init() { mEngine.Init(); }
		inline void Tick() { mEngine.Tick(); }
		inline void Exit() { mEngine.Exit(); }

		inline const char* GetName() noexcept { return mName; }

	private:
		const char* mName;
		EditorEngine mEngine;
	};
}