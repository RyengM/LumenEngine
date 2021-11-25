#include "TypeInfoGenerator.h"

#include <sstream>
#include <unordered_map>

using namespace Ubpa::USRefl;
using namespace std;

string GetAccessLevel(AccessSpecifier acc) {
	if (acc == AccessSpecifier::DEFAULT || acc == AccessSpecifier::PUBLIC) return "";
	if (acc == AccessSpecifier::PROTECTED) return "registration::protected_access";
	else return "registration::private_access";
}

string TypeInfoGenerator::Generate(const vector<TypeMeta>& typeMetas) {
	stringstream ss;

	ss	<< "// This following is generated by Ubpa::USRefl::AutoRefl" << endl
		<< endl;
	unordered_map<string, int> namespaces;
	bool bExtraLine = false;
	for (const auto& typeMeta : typeMetas) {
		if (typeMeta.namespaces.size()) {
			bExtraLine = true;
			string namespaceString = "using namespace " + typeMeta.namespaces[0];
			//ss << "using namespace " << typeMeta.namespaces[0];
			for (int i = 1; i < typeMeta.namespaces.size(); i++)
				namespaceString += "::" + typeMeta.namespaces[i];
				//ss << "::" + typeMeta.namespaces[i];
			if (namespaces.find(namespaceString) == namespaces.end()) {
				ss << namespaceString << ";\n";
				namespaces[namespaceString]++;
			}
		}
	}
	if (bExtraLine) ss << endl;
	ss << "RTTR_REGISTRATION" << endl
		<< "{" << endl;		

	for (const auto& typeMeta : typeMetas) {
		string objectName = typeMeta.GenerateNsName().substr(typeMeta.GenerateNsName().find_last_of(':') + 1, -1);
		ss << "\tregistration::class_<" + typeMeta.GenerateFullName() + ">(\"" + objectName + "\")" << endl;
		if (typeMeta.HaveAnyOutputField()) {

			bool bAbstract = false;

			// Counter to check if method is overload
			unordered_map<string, int> fieldNameCount;
			for (const auto& field : typeMeta.fields) {
				fieldNameCount[field.name]++;
				if (field.mode == Field::Mode::Function && field.initializer == "0")
					bAbstract = true;
			}
				

			for (const auto& field : typeMeta.fields) {
				if (field.isTemplate || field.IsFriendFunction() || field.IsDeletedFunction() || field.name == "")
					continue;
				// Constructor
				if (field.name == typeMeta.name) {
					ss << "\t\t.constructor<";
					for (int i = 0; i < field.parameters.size(); i++) {
						if (i > 0) ss << ", ";
						ss << field.parameters[i].type;
					}
					ss << ">(" + GetAccessLevel(field.accessSpecifier) + ")" << endl;
					continue;
				}
				// Method
				if (field.mode == Field::Mode::Function && field.name != typeMeta.name) {
					ss << "\t\t.method(\"" + field.name + "\", ";
					if (fieldNameCount.at(field.name) > 1) {
						ss << "select_overload<" + field.declSpecifiers[0];
						for (int i = 1; i < field.declSpecifiers.size(); i++)
							ss << " " + field.declSpecifiers[i];
						ss << "(";
						for (int i = 0; i < field.parameters.size(); i++) {
							if (i > 0) ss << ", ";
							ss << field.parameters[i].type;
						}
						ss << ")";
						for (int i = 0; i < field.qualifiers.size(); i++)
							ss << " " + field.qualifiers[i];
						ss << ">(&" + objectName + "::" + field.name + ")";
					}
					else {
						ss << "&" + objectName + "::" + field.name;
					}
					if (field.accessSpecifier != AccessSpecifier::DEFAULT && field.accessSpecifier != AccessSpecifier::PUBLIC)
						ss << ", " + GetAccessLevel(field.accessSpecifier);
					ss << ")";
					if (field.attrs.size()) {
						ss << endl << "\t\t(" << endl;
						for (int i = 0; i < field.attrs.size(); i++) {
							if (i > 0) ss << "," << endl;
							ss << "\t\t\tmetadata(\"" + field.attrs[i].name + "\", " + field.attrs[i].value + ")";
						}
						ss << endl << "\t\t)";
					}
					ss << endl;
				}
				// Property
				if (field.mode == Field::Mode::Variable) {
					ss << "\t\t.property(\"" + field.name + "\", &" + objectName + "::" + field.name;
					if (field.accessSpecifier != AccessSpecifier::DEFAULT && field.accessSpecifier != AccessSpecifier::PUBLIC)
						ss << ", " + GetAccessLevel(field.accessSpecifier);
					ss << ")";
					if (field.attrs.size()) {
						ss << endl << "\t\t(" << endl;
						for (int i = 0; i < field.attrs.size(); i++) {
							if (i > 0) ss << "," << endl;
							ss << "\t\t\tmetadata(\"" + field.attrs[i].name + "\", " + field.attrs[i].value + ")";
						}
						ss << endl << "\t\t)";
					}
					ss << endl;
				}
			}
			if (!bAbstract && fieldNameCount.find(typeMeta.name) == fieldNameCount.end())
				ss << "\t\t.constructor<>()" << endl;
		}
		ss << "\t;\n";
	}

	ss << "}";

	return ss.str();
}
