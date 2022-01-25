#include "Render/RenderGraph/Public/RenderGraph.h"
#include <queue>
#include <iostream>
#include <cassert>

using namespace Lumen::Render;

bool RenderGraph::IsRegisteredPassNode(const std::string& name) const
{
    return mName2passMap.find(name) != mName2passMap.end();
}

bool RenderGraph::IsRegisteredResourceNode(const std::string& name) const
{
    return mName2resourceMap.find(name) != mName2resourceMap.end();
}

size_t RenderGraph::GetPassNodeIndex(const std::string& name) const
{
    assert(IsRegisteredPassNode(name));
    return mName2passMap.find(name)->second;
}

size_t RenderGraph::GetResourceNodeIndex(const std::string& name) const
{
    assert(IsRegisteredResourceNode(name));
    return mName2resourceMap.find(name)->second;
}

size_t RenderGraph::RegisterPassNode(PassNode node)
{
    assert(!IsRegisteredPassNode(node.GetName()));
    size_t id = mPassNodes.size();
    mName2passMap.emplace(node.GetName(), id);
    mPassNodes.push_back(std::move(node));
    return id;
}

size_t RenderGraph::RegisterPassNode(std::string name, std::vector<size_t> inputs, std::vector<size_t> outputs)
{
    return RegisterPassNode(PassNode(std::move(name), std::move(inputs), std::move(outputs)));
}

size_t RenderGraph::RegisterResourceNode(ResourceNode node)
{
    assert(!IsRegisteredResourceNode(node.GetName()));
    size_t id = mResourceNodes.size();
    mName2resourceMap.emplace(node.GetName(), id);
    mResourceNodes.push_back(std::move(node));
    return id;
}

size_t RenderGraph::RegisterResourceNode(std::string name)
{
    return RegisterResourceNode(ResourceNode(std::move(name)));
}

bool RenderGraph::IsRenderGraphCompiled() const
{
    return bCompiled;
}

void RenderGraph::RegisterPassFunction(size_t passNode, PassFunction function)
{
    mPass2functionMap.emplace(std::move(passNode), std::move(function));
}

bool RenderGraph::CompileGraphWithDependency()
{
    // BFS, @sizt_t: passNode
    std::queue<size_t> zeroIndegreeNodes;

    // Do not destroy passDependency, use indegree map instead
    // @size_t: current passNode, @size_t: dependent passNode
    std::unordered_map<size_t, size_t> indegreeMap;
    
    for (const auto& [node, dependency] : mPassDependency)
    {
        // Push nodes whose in-degree equals to zero
        if (!dependency.size())
            zeroIndegreeNodes.push(node);
        // Fill nodes whose in-degree not equals to zero
        else
            indegreeMap[node] = dependency.size();
    }
    // Sort graph
    while (!zeroIndegreeNodes.empty())
    {
        auto selectedNode = zeroIndegreeNodes.front();
        zeroIndegreeNodes.pop();
        mCompiledExecutePassSequence.push_back(selectedNode);
        indegreeMap.erase(selectedNode);
        for (auto& [node, dependencyNum] : indegreeMap)
        {
            auto dependency = mPassDependency.find(node)->second;
            if (dependency.find(selectedNode) != dependency.end())
                dependencyNum--;
            if (dependencyNum == 0)
                zeroIndegreeNodes.push(node);
        }
    }
    // Circle exist
    assert(indegreeMap.empty());
    return true;
}

void RenderGraph::Compile()
{
    // Construct readers and writer for resource nodes, useless resource node will be ignored automatically
    for (int id = 0; id < mPassNodes.size(); ++id)
    {
        const auto pass = mPassNodes[id];
        for (const auto& input : pass.GetInputs())
            mResource2managerMap[input].readers.push_back(id);
        for (const auto& output : pass.GetOutputs())
            mResource2managerMap[output].writer = id;
    }
    // Construct pass node dependencies
    // Ensure that each pass node has its dependency, even though the value is zero
    for (int idx = 0; idx < mPassNodes.size(); ++idx)
        mPassDependency.try_emplace(idx);
    for (const auto& [resourceNode, resourceData] : mResource2managerMap)
    {
        for (const auto reader : resourceData.readers)
            mPassDependency[reader].insert(resourceData.writer);
    }
    // Sort graph into vector with dependency
    bool result = CompileGraphWithDependency();
    assert(result);

    // Check resource lifetime, from writer to last reader
    for (auto& [node, resourceData] : mResource2managerMap)
    {
        resourceData.lifeStartPass = resourceData.writer;
        resourceData.lifeEndPass = resourceData.writer;
        int curIndex = 0;
        // This value must can be found, so init value of curIndex is not important
        for (int i = mCompiledExecutePassSequence.size() - 1; i >= 0; --i)
            if (mCompiledExecutePassSequence[i] == resourceData.lifeStartPass)
                curIndex = i;
        for (auto& reader : resourceData.readers)
            for (int i = mCompiledExecutePassSequence.size() - 1; i >= 0; --i)
                if (mCompiledExecutePassSequence[i] == reader && i > curIndex)
                    resourceData.lifeEndPass = mCompiledExecutePassSequence[i];
    }

    bCompiled = true;
}

void RenderGraph::Exec()
{
    for (const auto& node : mCompiledExecutePassSequence)
    {
        assert(mPass2functionMap.find(node) != mPass2functionMap.end());
        mPass2functionMap.find(node)->second();
    }
}

void RenderGraph::LogCompiledInfo() const
{
    if (!bCompiled) 
    {
        std::cout << "Render graph not compiled yet" << std::endl;
        return;
    }
    std::cout << "--------------------- pass info ---------------------" << std::endl;
    for (int i = 0; i < mPassNodes.size(); ++i)
        std::cout << i << ": " + mPassNodes[i].GetName() << std::endl;
    std::cout << std::endl;
    std::cout << "------------------- resource info -------------------" << std::endl;
    for (int i = 0; i < mResourceNodes.size(); ++i)
    {
        std::cout << i << ": " + mResourceNodes[i].GetName() << std::endl;
        auto resource = mResource2managerMap.find(i)->second;
        std::cout << "  - writer :" << mPassNodes[resource.writer].GetName() << std::endl;
        std::cout << "  - reader :" << std::endl;
        for (const auto& reader : resource.readers)
            std::cout << "    * " << mPassNodes[reader].GetName() << std::endl;
        std::cout << "  - lifetime :" << mPassNodes[resource.lifeStartPass].GetName() << " -> " << mPassNodes[resource.lifeEndPass].GetName() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "---------- ------- pass dependency ------------------" << std::endl;
    for (const auto& [node, dependency] : mPassDependency)
        for (const auto& dependencyNode : dependency)
            std::cout << mPassNodes[dependencyNode].GetName() << " -> " << mPassNodes[node].GetName() << std::endl;
    std::cout << std::endl;
    std::cout << "---------------- compiled pass order ----------------" << std::endl;
    for (int i = 0; i < mCompiledExecutePassSequence.size(); ++i)
        std::cout << i << ": " + mPassNodes[mCompiledExecutePassSequence[i]].GetName() << std::endl;
    std::cout << std::endl;
}