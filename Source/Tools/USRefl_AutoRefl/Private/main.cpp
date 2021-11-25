// Forked from USRefl, the following changes have been made
// 1. Specialize for the project structure
// 2. The output form is connected to RTTR

// Way to use this tool
// 1. Add LumenEngine/Bin/Release to user environment path
// 2. USRefl [directory to be reflected]
// 3. This tool will search recursive to reflect the files had been marked by macro

#include "MetaGenerator.h"
#include "TypeInfoGenerator.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <regex>

using namespace Ubpa::USRefl;
using namespace std;
using namespace std::filesystem;

static vector<string> gRecognizedMacroList = { "RTTR_REGISTRATION_FRIEND", "RTTR_ENABLE" };

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

bool Preprocess(std::string& code) {
	bool bMacroExist = false;
	for (const auto& macro : gRecognizedMacroList)
		while (regex_search(code, regex(macro))) {
			code = regex_replace(code, regex(macro + "\\(\\w*\\)"), "");
			code = regex_replace(code, regex(macro), "");
			bMacroExist = true;
		}
	return bMacroExist;
}

void OperateFile(const std::string& inputPath, const std::string& filename, const std::string& curDirectory) {
	string postfix = inputPath.substr(inputPath.size() - 2, 2);
	if (postfix != ".h") return;

	string cppName = filename.substr(0, filename.size() - 2) + ".cpp";

	auto code = ReadFileIntoString(inputPath.c_str());

	// Preprocess file to delete macro, our parser do not need macro
	if (!Preprocess(code)) return;

	// Parse and generate inl
	MetaGenerator metaGenerator;
	TypeInfoGenerator typeinfoGenerator;
	auto typeMetas = metaGenerator.Parse(code);
	auto rst = typeinfoGenerator.Generate(typeMetas);
	auto curout = ReadFileIntoString(inputPath.c_str());
	if (curout == rst) return;

	// Check if cpp file is existed, if not exist, create one
	auto cppFilename = curDirectory + "/../Private/" + cppName;
	const path cppPath = cppFilename;
	if (!exists(cppPath)) {
		ofstream out(cppPath);
		if (!out.is_open())
			cerr << "open fail : " << cppPath << endl;
		out << "#include \"../Public/" + filename + "\"\n\n" << rst;
		out.close();
	}
	else {
		path tempPath = cppFilename + ".temp";
		ofstream out(tempPath);
		if (!out.is_open())
			cerr << "open fail : " << tempPath << endl;
		auto cppCode = ReadFileIntoString(cppFilename.c_str());

		// Check header include
		if (!regex_search(cppCode, regex("#include (\"|<).*/?(\\w.?/?)*(\"|>)\\n")))
			cppCode += "#include \"../Public/" + filename + "\"";
		// Check if reflection is generated, if not, append
		if (cppCode.find("RTTR_REGISTRATION") == cppCode.npos) 
			cppCode += "\n\n" + rst;
		// Else, replace content
		else {
			smatch replaceStr;
			regex_search(rst, replaceStr, regex("RTTR_REGISTRATION[^\\}]*\\}"));
			cppCode = regex_replace(cppCode, regex("RTTR_REGISTRATION[^\\}]*\\}"), replaceStr.str());
		}

		out << cppCode;
		out.close();
		remove(cppPath.c_str());
		rename(tempPath.c_str(), cppPath.c_str());
	}
}

void EnterDictRecur(const std::string& dir) {
	directory_iterator list(dir);
	for (auto& it : list) {
		auto path = it.path().string();
		if (it.status().type() == file_type::directory)
			EnterDictRecur(path);
		else if (it.status().type() == file_type::regular)
			OperateFile(it.path().string(), it.path().filename().string(), dir.c_str());
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "arguments error" << endl;
		return 1;
	}

	string inputDir = argv[1];
	char rootDir[1024];

#ifdef _WIN32
	auto rst = _fullpath(rootDir, inputDir.c_str(), 1024);
#else
	realpath(inputDir.c_str(), rootDir);
#endif
	
	if (!exists(rootDir)) {
		cerr << "file or directory doesn't exist" << endl;
		return 1;
	}
	directory_entry entry(rootDir);

	// File
	std::string fileFullPath = std::string(rootDir);
	if (fileFullPath.substr(fileFullPath.length() - 2, fileFullPath.length()) == ".h" ||
		fileFullPath.substr(fileFullPath.length() - 4, fileFullPath.length()) == ".hpp")
	{
		auto idx = inputDir.find_last_of('/');
		if (idx == std::string::npos) idx = inputDir.find_last_of('\\');
		inputDir = inputDir.substr(idx + 1, inputDir.length());
		OperateFile(fileFullPath, inputDir, std::filesystem::current_path().string());
		return 0;
	}

	// Directory
	if (entry.status().type() != file_type::directory) {
		cerr << "arguments error, input should be a directory or header file" << endl;
		return 1;
	}

	EnterDictRecur(rootDir);

	return 0;
}
