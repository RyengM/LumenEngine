#include "RenderGraph.h"
#include <queue>
#include <iostream>
#include <cassert>

bool RenderGraph::IsRegisteredPassNode(const std::string& name) const
{
	return name2passMap.find(name) != name2passMap.end();
}

bool RenderGraph::IsRegisteredResourceNode(const std::string& name) const
{
	return name2resourceMap.find(name) != name2resourceMap.end();
}

size_t RenderGraph::GetPassNodeIndex(const std::string& name) const
{
	assert(IsRegisteredPassNode(name));
	return name2passMap.find(name)->second;
}

size_t RenderGraph::GetResourceNodeIndex(const std::string& name) const
{
	assert(IsRegisteredResourceNode(name));
	return name2resourceMap.find(name)->second;
}

size_t RenderGraph::RegisterPassNode(PassNode node)
{
	assert(!IsRegisteredPassNode(node.GetName()));
	size_t id = passNodes.size();
	name2passMap.emplace(node.GetName(), id);
	passNodes.push_back(std::move(node));
	return id;
}

size_t RenderGraph::RegisterPassNode(std::string name, std::vector<size_t> inputs, std::vector<size_t> outputs)
{
	return RegisterPassNode(PassNode(std::move(name), std::move(inputs), std::move(outputs)));
}

size_t RenderGraph::RegisterResourceNode(ResourceNode node)
{
	assert(!IsRegisteredResourceNode(node.GetName()));
	size_t id = resourceNodes.size();
	name2resourceMap.emplace(node.GetName(), id);
	resourceNodes.push_back(std::move(node));
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
	pass2functionMap.emplace(std::move(passNode), std::move(function));
}

bool RenderGraph::CompileGraphWithDependency()
{
	// BFS, @sizt_t: passNode
	std::queue<size_t> zeroIndegreeNodes;

	// Do not destroy passDependency, use indegree map instead
	// @size_t: current passNode, @size_t: dependent passNode
	std::unordered_map<size_t, size_t> indegreeMap;
	
	for (const auto& [node, dependency] : passDependency)
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
		compiledExecutePassSequence.push_back(selectedNode);
		indegreeMap.erase(selectedNode);
		for (auto& [node, dependencyNum] : indegreeMap)
		{
			auto dependency = passDependency.find(node)->second;
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
	for (int id = 0; id < passNodes.size(); ++id)
	{
		const auto pass = passNodes[id];
		for (const auto& input : pass.GetInputs())
			resource2managerMap[input].readers.push_back(id);
		for (const auto& output : pass.GetOutputs())
			resource2managerMap[output].writer = id;
	}
	// Construct pass node dependencies
	// Ensure that each pass node has its dependency, even though the value is zero
	for (int idx = 0; idx < passNodes.size(); ++idx)
		passDependency.try_emplace(idx);
	for (const auto& [resourceNode, resourceData] : resource2managerMap)
	{
		for (const auto reader : resourceData.readers)
			passDependency[reader].insert(resourceData.writer);
	}
	// Sort graph into vector with dependency
	assert(CompileGraphWithDependency());

	// Check resource lifetime, from writer to last reader
	for (auto& [node, resourceData] : resource2managerMap)
	{
		resourceData.lifeStartPass = resourceData.writer;
		resourceData.lifeEndPass = resourceData.writer;
		int curIndex = 0;
		// This value must can be found, so init value of curIndex is not important
		for (int i = compiledExecutePassSequence.size() - 1; i >= 0; --i)
			if (compiledExecutePassSequence[i] == resourceData.lifeStartPass)
				curIndex = i;
		for (auto& reader : resourceData.readers)
			for (int i = compiledExecutePassSequence.size() - 1; i >= 0; --i)
				if (compiledExecutePassSequence[i] == reader && i > curIndex)
					resourceData.lifeEndPass = compiledExecutePassSequence[i];
	}

	bCompiled = true;
}

void RenderGraph::Exec()
{
	for (const auto& node : compiledExecutePassSequence)
	{
		assert(pass2functionMap.find(node) != pass2functionMap.end());
		pass2functionMap.find(node)->second();
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
	for (int i = 0; i < passNodes.size(); ++i)
		std::cout << i << ": " + passNodes[i].GetName() << std::endl;
	std::cout << std::endl;
	std::cout << "------------------- resource info -------------------" << std::endl;
	for (int i = 0; i < resourceNodes.size(); ++i)
	{
		std::cout << i << ": " + resourceNodes[i].GetName() << std::endl;
		auto resource = resource2managerMap.find(i)->second;
		std::cout << "  - writer :" << passNodes[resource.writer].GetName() << std::endl;
		std::cout << "  - reader :" << std::endl;
		for (const auto& reader : resource.readers)
			std::cout << "    * " << passNodes[reader].GetName() << std::endl;
		std::cout << "  - lifetime :" << passNodes[resource.lifeStartPass].GetName() << " -> " << passNodes[resource.lifeEndPass].GetName() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "---------- ------- pass dependency ------------------" << std::endl;
	for (const auto& [node, dependency] : passDependency)
		for (const auto& dependencyNode : dependency)
			std::cout << passNodes[dependencyNode].GetName() << " -> " << passNodes[node].GetName() << std::endl;
	std::cout << std::endl;
	std::cout << "---------------- compiled pass order ----------------" << std::endl;
	for (int i = 0; i < compiledExecutePassSequence.size(); ++i)
		std::cout << i << ": " + passNodes[compiledExecutePassSequence[i]].GetName() << std::endl;
	std::cout << std::endl;
}