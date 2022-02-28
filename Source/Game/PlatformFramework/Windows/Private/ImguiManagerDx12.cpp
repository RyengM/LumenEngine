#include "Game/PlatformFramework/Windows/Public/ImguiManagerDx12.h"

using namespace Lumen::Game;
using namespace Lumen::Core;

DrawDataProxy::DrawDataProxy()
{
    mDrawData = new ImDrawData();
}

DrawDataProxy::DrawDataProxy(const ImDrawData* drawData)
{
    mDrawData = new ImDrawData();

    mDrawData->Valid = drawData->Valid;
    mDrawData->CmdListsCount = drawData->CmdListsCount;
    mDrawData->TotalIdxCount = drawData->TotalIdxCount;
    mDrawData->TotalVtxCount = drawData->TotalVtxCount;
    mDrawData->DisplayPos = drawData->DisplayPos;
    mDrawData->DisplaySize = drawData->DisplaySize;
    mDrawData->FramebufferScale = drawData->FramebufferScale;

    for (int i = 0; i < drawData->CmdListsCount; i++)
        mDrawLists.push_back(drawData->CmdLists[i]->CloneOutput());
    if (drawData->CmdListsCount > 0)
        mDrawData->CmdLists = mDrawLists.Data;
}

DrawDataProxy::~DrawDataProxy()
{
    for (int i = 0; i < mDrawData->CmdListsCount; i++)
        mDrawData->CmdLists[i]->~ImDrawList();
    for (auto list : mDrawLists)
        IM_FREE(list);
    mDrawLists.clear();
    delete mDrawData;
}

void ImguiManagerDx12::Init(int frameNum)
{
    mEditorContext = ImGui::CreateContext();
    ImGui::StyleColorsDark();
    mContexts.emplace_back(mEditorContext);
    mContext2IndexMap[mEditorContext] = 0;
    mFrameNum = frameNum;
    
    mProxyStorage = (DrawDataProxy*)malloc(mContextNum * frameNum * sizeof(DrawDataProxy));
    // Create default memory to ensure memory is legal
    for (int i = 0; i < mContextNum * frameNum; i++)
        new(&mProxyStorage[i])DrawDataProxy();
}

void ImguiManagerDx12::Clear()
{
    for (auto& context : mContexts)
    {
        ImGui::SetCurrentContext(context);
        ImGui_ImplDX12_Shutdown();
        ImGui::DestroyContext(context);
    }
    mContexts.clear();
    free(mProxyStorage);
}

DrawDataProxy* ImguiManagerDx12::CreateContextDrawDataProxy(ImGuiContext* context)
{
    if (!context->Viewports[0]->DrawDataP.Valid)
        LOG_WARN("Invalid Imgui draw data, use origin data instead, may cause some unexpected error");

    int index = mCurrentFrameNum * mContextNum + mContext2IndexMap.at(context);
    mCurrentFrameNum = (mCurrentFrameNum + 1) % mFrameNum;

    ImDrawData* originData = &context->Viewports[0]->DrawDataP;
    mProxyStorage[index].~DrawDataProxy();
    new(&mProxyStorage[index])DrawDataProxy(originData);
    return &mProxyStorage[index];
}