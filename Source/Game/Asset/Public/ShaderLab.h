#pragma once

#include "Core/Math/Public/Vector.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

using namespace Lumen::Core;

namespace Lumen::Game
{
	using PropertyValue = std::variant<int,	float, Vec4, std::string>;

	enum class CullMode : uint8_t
	{
		Front		= 0,
		Back		= 1,
		None		= 2
	};

	enum class Comparator : uint8_t
	{
		Less		= 0,
		Greater		= 1,
		LEqual		= 2,
		GEqual		= 3,
		NotEqual	= 4,
		Always		= 5,
		Never		= 6
	};

	enum class ZWriteMode : uint8_t
	{
		On			= 0,
		Off			= 1
	};

	enum class Channel : uint8_t
	{
		Off			= 0,
		R			= 1,
		G			= 2,
		B			= 4,
		A			= 8,
	};

	enum class StateType
	{
		CullMode	= 0,
		ZTest		= 1,
		ZWriteMode	= 2,
		ColorMask	= 3
	};

	struct Property
	{
		std::string name;
		std::string displayName;
		std::vector<std::string> metas;
		std::pair<float, float> range;
		PropertyValue value;
	};

	struct CommonState
	{
		CullMode cullMode			= CullMode::Back;
		Comparator zTestMode		= Comparator::LEqual;
		ZWriteMode zWriteMode		= ZWriteMode::Off;
		Channel colorMaskChannel	= Channel::Off;
	};

	// Same as Pass in unity
	struct Kernel
	{
		std::unordered_map<std::string, std::string> tags;
		CommonState commonState;
		std::string hlsl;
	};

	// Same as SubShader in unity, we assusme there is always only one category in one shader file
	struct Category
	{
		std::unordered_map<std::string, std::string> tags;
		std::vector<Kernel> kernels;
	};

	// ShaderLab is designed like unity shaderlab
	class ShaderLab
	{
	public:

	private:
		std::string mName;
		std::unordered_map<std::string, Property> mProperties;
		Category mCategories;

		friend class ShaderLabGenerator;
	};
}