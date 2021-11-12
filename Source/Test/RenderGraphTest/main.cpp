#include "Render/RenderGraph/Public/RenderGraph.h"
#include <iostream>

using namespace Lumen::Render;

int main()
{
	RenderGraph rg("TestRG");
	auto gBuffer0 = rg.RegisterResourceNode("G-Buffer0");
	auto gBuffer1 = rg.RegisterResourceNode("G-Buffer1");
	auto deferLightedRT = rg.RegisterResourceNode("DeferLightedRT");
	auto presentedRT = rg.RegisterResourceNode("PresentedRT");

	auto gPass = rg.RegisterPassNode("G-Pass", {}, { gBuffer0, gBuffer1 });
	auto deferLightPass = rg.RegisterPassNode("DeferLightPass", { gBuffer0, gBuffer1 }, { deferLightedRT });
	auto postProcessPass = rg.RegisterPassNode("PostProcessPass", { deferLightedRT }, { presentedRT });

	rg.Compile();
	rg.LogCompiledInfo();

	rg.RegisterPassFunction(
		gPass,
		[&]()
	{
		std::cout << "test g-pass func" << std::endl;
	}
	);
	rg.RegisterPassFunction(
		deferLightPass,
		[&]()
	{
		std::cout << "test defer func" << std::endl;
	}
	);
	rg.RegisterPassFunction(
		postProcessPass,
		[&]()
	{
		std::cout << "test pp func" << std::endl;
	}
	);

	std::cout << "----------------------- exec ------------------------" << std::endl;
	rg.Exec();

	return 0;
}