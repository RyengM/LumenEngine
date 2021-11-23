#include "Core/Common/Public/Archive.h"

using namespace Lumen::Core;

Archive::Archive()
{
	writer.Reset(buffer);
}

Archive& Archive::operator<<(int v)
{
	writer.Int(v);
	return *this;
}

Archive& Archive::operator<<(unsigned int v)
{
	writer.Uint(v);
	return *this;
}

Archive& Archive::operator<<(float v)
{
	writer.Double(v);
	return *this;
}

Archive& Archive::operator<<(double v)
{
	writer.Double(v);
	return *this;
}

Archive& Archive::operator<<(bool v)
{
	writer.Bool(v);
	return *this;
}

Archive& Archive::operator<<(const char* v)
{
	writer.String(v);
	return *this;
}

Archive& Archive::operator<<(std::string_view v)
{
	writer.String(v.data());
	return *this;
}