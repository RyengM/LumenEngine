//#pragma once
//
//#include "Core/Common/Public/RingQueue.h"
//#include "Core/Memory/Public/MemoryPool.h"
//#include "Render/RenderCore/Public/RenderProxy.h"
//#include <vector>
//
//using namespace Lumen::Core;
//
//namespace Lumen::Render
//{
//    // Include all render proxy in one frame
//    struct FrameRenderContext
//    {
//        // GUI context proxy, the number of context is limited
//        // We do not wanna transport platform dependent data in engine, so we do not take special care for the resource
//        // This proxy resource is created in ImguiManagerDx12
//        std::vector<void*> guiProxies;
//
//        // Scene proxies, use pool to manage resource
//    };
//
//    // Include all render proxy and help functions, one and only one instance in the whole program
//    // It is like a singleton, which is shared by game thread and render thread
//    class RenderContext
//    {
//    public:
//        RenderContext(int frameNum);
//        ~RenderContext() = default;
//
//        // Forbid copy and move
//        RenderContext(const RenderContext& context) = delete;
//        RenderContext& operator=(const RenderContext& context) = delete;
//        RenderContext(RenderContext&& context) = delete;
//        RenderContext& operator=(RenderContext&& context) = delete;
//
//        // Important: because render thread will call run each frame and try fetch render context
//        // There must be EnqueueFrameRenderContext call between RenderCommandQueue::GetInstance().BeginEnqueue() and EndQueue()
//        // Invoked from game thread and enqueue render context
//        void EnqueueFrameRenderContext(FrameRenderContext&& context);
//        // Invoked from render thread and enqueue render context
//        void FetchFrameRenderContext(FrameRenderContext& out);
//
//    private:
//        RingQueue<FrameRenderContext> mRenderContext;
//    };
//
//    // Store proxy memory resource
//    struct RenderContextResourceContainer
//    {
//
//    };
//}