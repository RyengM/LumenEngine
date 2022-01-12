#pragma once

#include "Game/Engine/Public/EditorEngine.h"

namespace Lumen::Game
{
	// Platform independent parts, for OS related should be implemented in specific implementation inherit from this class
	class BaseFramework
	{
	public:
		BaseFramework(const wchar_t* name) : mName(name) {}
		virtual ~BaseFramework() {}

		inline void PreInit() { mEngine.PreInit(); }		// Launch modules
		inline void Init() { mEngine.Init(); }				// Load assets
		inline void Tick() { mEngine.Tick(); }
		inline void Exit() { mEngine.Exit(); }

	public:
		const wchar_t* mName;
		EditorEngine mEngine;
	};
}