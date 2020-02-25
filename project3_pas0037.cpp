/*
File name: project3_pas0037.cpp
AU UserID: pas0037
How to Compile: g++ -std=c++11 project3_pas0037.
Author: Patrick Spafford

Sources Used:
Cplusplus.com/reference/vector/vector
This source helped me figure out what methods were built into vector so that I could properly read, write and merge the inputs.
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool check_file(string input_file) {
	ifstream in;
	in.open(input_file.c_str());
	if (in.fail()) {
		return false;
	}
	in.close();
	return true;
	} // good. Do not modify.
vector<int> read_file(string file) {
	ifstream stream;
	vector<int> v;
	int i;
	stream.open(file.c_str());
	while (stream.good()) {
		stream >> i;
		v.push_back(i);
	}
	stream.close();
	return v;
}
void write_file(string file, vector<int> output) {
	ofstream out;
	out.open(file.c_str());
	// While stream.good()?
	for (vector<int>::iterator i = output.begin(); i != output.end(); ++i) {
		out << *i;
	}
	out.close();

}
vector<int> merge(vector<int> a, vector<int> b) {
vector<int> merged;
while (!a.empty() > 0 && !b.empty()) {
int v1 = a.front();
int v2 = b.front();
if (v1 < v2) {
merged.push_back(v1);
a.erase(a.begin());
}
else {
merged.push_back(v2);
b.erase(b.begin());
}
}
if (!a.empty()) {
		unsigned short j = 0;
		while (j < a.size()) {
			merged.push_back(a.at(j));
			j++;
		}
	}
	if (!b.empty()) {
		unsigned short k = 0;
		while (k < b.size()) {
			merged.push_back(b.at(k));
			k++;
		}
	}
	return merged;
}

string to_vector_string(vector<int> v) {
	string str;
	for (unsigned int i = 0; i < v.size(); i++) {
		string vector_entry = to_string(v.at(i));
		str += vector_entry;
		str += "\n";
	}
	return str;
}
string to_vector_string2(vector<int> v) {
	string str;
	for (unsigned int i = 0; i < v.size(); i++) {
		string vector_entry = to_string(v.at(i));
		str += vector_entry;
		str += " ";
	}
	return str;
}

int main() {
	cout << "*** Welcome to Patrick's sorting program ***" << endl;


	cout << "Enter the first input file name: ";
	string file_name_1;
	cin >> file_name_1;
	if (!check_file(file_name_1)) {
		cout << "Cannot open file 1!" << endl;
		return 1;
	}
	vector<int> v1 = read_file(file_name_1);
	cout << endl << "The list of " << v1.size() << " numbers in file " << file_name_1 << " is:" << endl;
	cout << to_vector_string(v1) << endl;



	cout << "Enter the second input file name: ";
	string file2;
	cin >> file2;
	if (!check_file(file2)) {
		cout << "Cannot open file 2!" << endl;
		return 1;
	}
	vector<int> v2 = read_file(file2);
	cout << endl << "The list of " << v2.size() << " numbers in file " << file2 << " is:" << endl;
	cout << to_vector_string(v2) << endl;

	vector<int> v3 = merge(v1, v2);
	cout << "The sorted list of " << v3.size() << " numbers is: " << to_vector_string2(v3) << endl;
	
	string output_file_name;
	cout << "Enter the output file name: ";
	cin >> output_file_name;
	write_file(output_file_name, v3);
	cout << "*** Please check the new file - " << output_file_name << " ***" << endl;
	cout << "*** Goodbye ***" << endl;


	return 0;


}

