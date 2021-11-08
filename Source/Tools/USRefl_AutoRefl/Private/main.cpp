#include "MetaGenerator.h"
#include "TypeInfoGenerator.h"
#include "SourceModifier.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

using namespace Ubpa::USRefl;
using namespace std;
using namespace std::filesystem;

string ReadFileIntoString(const char* filename) {
	ifstream ifile(filename);
	if (!ifile.is_open())
		return "";

	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	return buf.str();
}

void OperateFile(const std::string& inputPath)
{
	string postfix = inputPath.substr(inputPath.size() - 2, 2);
	if (postfix != ".h") return;

	string outputPath = inputPath.substr(0, inputPath.size() - 2) + "_AutoRefl.inl";

	auto code = ReadFileIntoString(inputPath.c_str());

	// Modify source .h file
	SourceModifier sourceModifier;
	bool shouldGenerate = sourceModifier.TryModify(code, outputPath);

	if (!shouldGenerate) return;

	string tempPath = inputPath + ".temp";
	ofstream out(tempPath);
	if (!out.is_open())
		cerr << "open fail : " << tempPath << endl;

	out << code;
	out.close();
	remove(inputPath.c_str());
	auto success = rename(tempPath.c_str(), inputPath.c_str());

	// Parse and generate inl
	MetaGenerator metaGenerator;
	TypeInfoGenerator typeinfoGenerator;
	auto typeMetas = metaGenerator.Parse(code);
	auto rst = typeinfoGenerator.Generate(typeMetas);
	auto curout = ReadFileIntoString(inputPath.c_str());
	if (curout == rst) return;

	out.open(outputPath);
	if (!out.is_open())
		cerr << "open fail : " << outputPath << endl;

	out << rst;
	out.close();
}

void EnterDictRecur(const std::string& dir)
{
	directory_iterator list(dir);
	for (auto& it : list) {
		auto path = it.path().string();
		if (it.status().type() == file_type::directory)
			EnterDictRecur(path);
		else if (it.status().type() == file_type::regular)
			OperateFile(path);
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "arguments error" << endl;
		return 1;
	}

	//string inputPath = argv[1];
	string inputDir = argv[1];
	char rootDir[1024];

#ifdef _WIN32
	auto rst = _fullpath(rootDir, inputDir.c_str(), 1024);
#else
	realpath(inputDir.c_str(), rootDir);
#endif
	
	if (!exists(rootDir)) {
		cerr << "root directory doesn't exist" << endl;
		return 1;
	}

	EnterDictRecur(rootDir);

	return 0;
}
