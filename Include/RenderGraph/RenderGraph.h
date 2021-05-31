#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <functional>

// Refer to Utopia

namespace Lumen::RenderGraph {

	using PassFunction = std::function<void()>;

	class PassNode
	{
	public:
		PassNode(std::string name, std::vector<size_t> inputs, std::vector<size_t> outputs) :
			name{ std::move(name) }, inputs{ std::move(inputs) }, outputs{ std::move(outputs) } {}

		const std::string& GetName() const noexcept { return name; }
		const std::vector<size_t>& GetInputs() const noexcept { return inputs; }
		const std::vector<size_t>& GetOutputs() const noexcept { return outputs; }

	private:
		std::string name;
		std::vector<size_t> inputs;
		std::vector<size_t> outputs;
	};

	class ResourceNode
	{
	public:
		ResourceNode(std::string name) : name(std::move(name)) {}
		const std::string& GetName() const noexcept { return name; }

	private:
		std::string name;
	};

	class RenderGraph
	{
	public:
		// RenderGraph
		RenderGraph(std::string name) : name(std::move(name)) {}

		const std::vector<ResourceNode>& GetResourceNodes() const noexcept { return resourceNodes; }
		const std::vector<PassNode>& GetPassNodes() const noexcept { return passNodes; }

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
		std::string name;
		std::vector<ResourceNode> resourceNodes;
		std::vector<PassNode> passNodes;
		// @std::string: node name, @size_t: resource ID, index of node in origin vector
		std::unordered_map<std::string, size_t> name2resourceMap;
		std::unordered_map<std::string, size_t> name2passMap;

		// Compile
		// @size_t: current resourceNode, ResourceNodeManager: related compile data
		std::unordered_map<size_t, ResourceNodeManager> resource2managerMap;
		// @size_t: current passNode, set<size_t>: dependent passNodes
		std::unordered_map<size_t, std::set<size_t>> passDependency;
		std::vector<size_t> compiledExecutePassSequence;
		bool bCompiled = false;

		// Execute
		std::unordered_map<size_t, PassFunction> pass2functionMap;
	};

}