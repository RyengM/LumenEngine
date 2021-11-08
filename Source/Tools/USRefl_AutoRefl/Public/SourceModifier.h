#pragma once

#include <string>

namespace Ubpa::USRefl {
	class SourceModifier
	{
	public:
		SourceModifier() {};
		~SourceModifier() = default;
		SourceModifier(SourceModifier&&) noexcept = default;
		SourceModifier& operator=(SourceModifier&&) noexcept = default;

		bool TryModify(std::string& code, const std::string& inlPath);
	};
}