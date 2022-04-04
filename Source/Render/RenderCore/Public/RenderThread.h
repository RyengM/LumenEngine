#pragma once

#include "Core/Thread/Public/RunnableThread.h"
#include "Core/Logger/Public/Logger.h"
#include "Render/RHI/Common/Public/RHIContext.h"
#include "RenderPipeline.h"

using namespace Lumen::Core;

namespace Lumen::Render
{
    class RenderRunnable : public Runnable
    {
    public:
        RenderRunnable(const WindowInfo& windowInfo, ProfileData* profileData);

        virtual bool Init() override;
        // Consume command and execute them
        virtual void Run() override;
        virtual void Stop() override;
        virtual void Exit() override;
        virtual ~RenderRunnable() override {}

    private:
        ProfileData* profileData;
        std::unique_ptr<RHIContext> mGraphicsContext;
    };
}