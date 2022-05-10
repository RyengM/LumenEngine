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
    LoadStyle();
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

void ImguiManagerDx12::LoadStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    style->WindowPadding = ImVec2(5, 5);
    style->WindowRounding = 0.0f;
    style->WindowBorderSize = 0.0f;

    style->FramePadding = ImVec2(5, 5);
    style->FrameRounding = 0.0f;
    style->ItemInnerSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;
    style->ScrollbarRounding = 0.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.07f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.00f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.6f, 0.2f, 0.2f, 0.2f);
    style->Colors[ImGuiCol_Tab] = ImVec4(0.32f, 0.33f, 0.30f, 1.00f);
    style->Colors[ImGuiCol_TabHovered] = ImVec4(0.43f, 0.45f, 0.45f, 1.00f);
    style->Colors[ImGuiCol_TabActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.40f);
    style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.40f);
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