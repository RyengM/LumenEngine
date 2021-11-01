#include "MetaGenerator.h"
#include "TypeInfoGenerator.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace Ubpa::USRefl;
using namespace std;

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

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "arguments error" << endl;
		return 1;
	}

	string inputPath = argv[1];
	string postfix = inputPath.substr(inputPath.size() - 2, 2);
	if (postfix != ".h") {
		cerr << "input file error" << endl;
	}
	string outputPath = inputPath.substr(0, inputPath.size() - 2) + "_AutoRefl.inl";

	auto code = ReadFileIntoString(inputPath.c_str());

	MetaGenerator metaGenerator;
	TypeInfoGenerator typeinfoGenerator;
	auto typeMetas = metaGenerator.Parse(code);
	auto rst = typeinfoGenerator.Generate(typeMetas);
	auto curout = ReadFileIntoString(inputPath.c_str());
	if (curout == rst)
		return 0;

	ofstream out(outputPath);
	if (!out.is_open()) {
		cerr << "open fail : " << outputPath << endl;
		return 1;
	}

	out << rst;
	out.close();

	return 0;
}
