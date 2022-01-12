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
    mDrawData->OwnerViewport = drawData->OwnerViewport;

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

void ImguiManagerDx12::Init(void* hWnd, int frameNum)
{
    ImGui_ImplWin32_Init_Shared(hWnd);

    mEditorContext = ImGui::CreateContext();
    ImGui_ImplWin32_Init_Context(mEditorContext);
    ImGui_ImplDX12_Init_Context(mEditorContext);
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
    ImGui_ImplWin32_Shutdown_Shared();
    for (auto& context : mContexts)
    {
        ImGui_ImplDX12_Shutdown_Context(context);
        ImGui_ImplWin32_Shutdown_Context(context);
        ImGui::DestroyContext(context);
    }
    
    mContexts.clear();
    free(mProxyStorage);
}

DrawDataProxy* ImguiManagerDx12::CreateContextDrawDataProxy(ImGuiContext* context, int currFrame)
{
    if (!context->Viewports[0]->DrawDataP.Valid)
        LOG_WARN("Invalid Imgui draw data, use origin data instead, may cause some unexpected error");

    int index = currFrame * mContextNum + mContext2IndexMap.at(context);

    ImDrawData* originData = &context->Viewports[0]->DrawDataP;
    //if (mProxyStorage[index].mDrawData != nullptr && mProxyStorage[index].mDrawData->CmdListsCount)
        mProxyStorage[index].~DrawDataProxy();
    new(&mProxyStorage[index])DrawDataProxy(originData);
    return &mProxyStorage[index];
}