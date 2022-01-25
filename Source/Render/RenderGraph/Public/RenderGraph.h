#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <functional>

// Refer to Utopia

namespace Lumen::Render 
{
    using PassFunction = std::function<void()>;

    class PassNode
    {
    public:
        PassNode(std::string name, std::vector<size_t> inputs, std::vector<size_t> outputs) :
            mName{ std::move(name) }, mInputs{ std::move(inputs) }, mOutputs{ std::move(outputs) } {}

        const std::string& GetName() const noexcept { return mName; }
        const std::vector<size_t>& GetInputs() const noexcept { return mInputs; }
        const std::vector<size_t>& GetOutputs() const noexcept { return mOutputs; }

    private:
        std::string mName;
        std::vector<size_t> mInputs;
        std::vector<size_t> mOutputs;
    };

    class ResourceNode
    {
    public:
        ResourceNode(std::string name) : mName(std::move(name)) {}
        const std::string& GetName() const noexcept { return mName; }

    private:
        std::string mName;
    };

    class RenderGraph
    {
    public:
        // RenderGraph
        RenderGraph(std::string name) : mName(std::move(name)) {}

        const std::vector<ResourceNode>& GetResourceNodes() const noexcept { return mResourceNodes; }
        const std::vector<PassNode>& GetPassNodes() const noexcept { return mPassNodes; }

        size_t GetResourceNodeIndex(const std::string& name) const;
        size_t GetPassNodeIndex(const std::string& name) const;

        size_t RegisterResourceNode(ResourceNode node);
        size_t RegisterResourceNode(std::string name);
        size_t RegisterPassNode(PassNode node);
        size_t RegisterPassNode(std::string name, std::vector<size_t> inputs, std::vector<size_t> outputs);

        void RegisterPassFunction(size_t passNode, PassFunction function);

        bool IsRegisteredResourceNode(const std::string& name) const;
        bool IsRegisteredPassNode(const std::string& name) const;

        // Compile
        bool IsRenderGraphCompiled() const;

        void Compile();

        struct ResourceNodeManager
        {
            // Lifetime management, unit: pass
            size_t lifeStartPass = -1;
            size_t lifeEndPass = -1;
            // There can only have one writer for a resouce node but can have several readers
            std::vector<size_t> readers;
            size_t writer;
        };

        void LogCompiledInfo() const;

        // Exec
        void Exec();

    private:
        bool CompileGraphWithDependency();

    private:
        // Render Graph
        std::string mName;
        std::vector<ResourceNode> mResourceNodes;
        std::vector<PassNode> mPassNodes;
        // @std::string: node mName, @size_t: resource ID, index of node in origin vector
        std::unordered_map<std::string, size_t> mName2resourceMap;
        std::unordered_map<std::string, size_t> mName2passMap;

        // Compile
        // @size_t: current resourceNode, ResourceNodeManager: related compile data
        std::unordered_map<size_t, ResourceNodeManager> mResource2managerMap;
        // @size_t: current passNode, set<size_t>: dependent passNodes
        std::unordered_map<size_t, std::set<size_t>> mPassDependency;
        std::vector<size_t> mCompiledExecutePassSequence;
        bool bCompiled = false;

        // Execute
        std::unordered_map<size_t, PassFunction> mPass2functionMap;
    };
}