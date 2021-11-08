#include "Tools/USRefl_AutoRefl/Public/SourceModifier.h"
#include <fstream>

using namespace Ubpa::USRefl;

bool SourceModifier::TryModify(std::string& code, const std::string& inlPath)
{
	// Only object with macro mark will be reflected
	if (code.find("REFLECTION_REGISTRATION") == code.npos)
		return false;

	// Add include for this file
	if (code.substr(code.size() - 5, 4) != ".inl")
		code += "\n\n// Code generate tool will generate this file by code gen tool\n#include \"" + inlPath + "\"";

	return true;
}