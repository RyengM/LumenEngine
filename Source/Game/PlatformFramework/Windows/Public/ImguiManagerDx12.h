#pragma once

#include "ThirdParty/Imgui/imgui.h"
#include "ThirdParty/Imgui/imgui_internal.h"
#include "Game/PlatformFramework/Windows/Public/imgui_impl_win32.h"
#include "Game/PlatformFramework/Windows/Public/imgui_impl_dx12.h"
#include "Core/Logger/Public/Logger.h"
#include <vector>

namespace Lumen::Game
{
	struct DrawDataProxy
	{
		ImDrawData* mDrawData;
		ImVector<ImDrawList*> mDrawLists;

		DrawDataProxy();
		// Deep copy, we assume do not use OwnerViewport in render thread
		DrawDataProxy(const ImDrawData* drawData);
		~DrawDataProxy();
	};

	class ImguiManagerDx12
	{
	public:
		void Init(void* hWnd, int frameNum);
		void Clear();

		DrawDataProxy* CreateContextDrawDataProxy(ImGuiContext* context, int currFrame);

		inline std::vector<ImGuiContext*>& GetContexts() noexcept { return mContexts; }

	private:
		int mFrameNum = 0;

		// Collection of all contexts
		std::vector<ImGuiContext*> mContexts;
		ImGuiContext* mEditorContext;
		std::unordered_map<ImGuiContext*, int> mContext2IndexMap;

		// Real place to store proxy memory
		DrawDataProxy* mProxyStorage;
		
		static int const mContextNum = 1;
	};
}