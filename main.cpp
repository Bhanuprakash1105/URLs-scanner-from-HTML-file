#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <regex>
#include <fstream>
#include <string>
#include <assert.h>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

typedef long long int lli;

void printLink_count(std::unordered_map <string, lli> &hash_map)
{
	lli i = 0;
	for(auto x: hash_map) {
		printf("\n> Number of times appeared: %3lld  Link %3lld = ", x.second, i + 1);
		cout << x.first << endl;
		i += 1;
	}
	assert(i == hash_map.size());
	cout <<"\n> Printed "<< i <<" links"<< endl;
}

void printLinks(std::unordered_map <string, lli> &hash_map) {
	for(auto x: hash_map) { cout << x.first << endl; }
}

bool check(string &s) {
	if(s.length() <= 0) { return false; }
	for(int i = 0; i < s.length(); ++i) { if(!isdigit(s[i])) { return false; } }
	return true;
}

lli giveNum(string &s) {
	lli retValue = 0;
	for(int i = 0; i < s.length(); ++i) {
		retValue += ((s[i] - '0') * pow(10, s.length() - i - 1));
	}
	return retValue;
}

int main(int argc, char const *argv[])
{
	fstream fin;
	streambuf *cinbuf = cin.rdbuf();

	string fileName;
	cout <<"\n> Enter the name of file (ex: file_name.html or file_name.txt): "; cin >> fileName;

	fin.open(fileName, ios::in);
	if(fin.fail()) {
		cout <<"\n> Error: The input file is not present in the current directory\n"<< endl;
		return -1;
	}
	cin.rdbuf(fin.rdbuf());

	regex reg_expr_all("https?://[a-zA-Z0-9]+(\\.)+[^/\'\";\?]*");
	regex reg_expr_ref("href=\"https?://[a-zA-Z0-9]+(\\.)+[^/\'\";\?]*");
	smatch match;

	string html_string = "", input, store_html_string = "";
	while(cin >> input) { html_string += input; }
	store_html_string = html_string;

	cin.rdbuf(cinbuf);
	fin.close();

	unordered_map <string, lli> map_all, map_ref;
	while(regex_search(html_string, match, reg_expr_all)) {
		map_all[match[0]]++;
		html_string = match.suffix();
	}
	while(regex_search(store_html_string, match, reg_expr_ref)) {
		string temp = match[0];
		map_ref[temp.substr(6, temp.length())]++;
		store_html_string = match.suffix();
	}

	fstream fout;
	streambuf *coutbuf = cout.rdbuf();
	string outputFileName = fileName.substr(0, fileName.length() - 5) + "_links_output.txt";
	fout.open(outputFileName, ios::out);
	if(fout.fail()) {
		cout <<"\n> Error: Unable to make a output file in the current directory\n"<< endl;
	}
	cout.rdbuf(fout.rdbuf());
	printLinks(map_ref);
	cout.rdbuf(coutbuf);
	fout.close();

	cout <<"\nClosed the input file"<< endl;
	cout <<"\nSuccessfully scanned the html file"<< endl;
	cout <<"\nGenerated output file with name: \""<< outputFileName <<"\" with Referred the links"<< endl;

	printf("\n> All unique links count: %4lld", (lli)map_all.size());
	printf("  Referred unique links count: %4lld\n", (lli)map_ref.size());

	bool flag = true;
	while(flag) {
		string c = "";
		cout <<"\nPress: [1] All links with count  [2] Referred links with count  [3] Exit  -> "; cin >> c;
		int k = -1;
		if(check(c)) { k = giveNum(c); } else { k = -1; }
		switch (k) {
			case 1: cout <<"\n> All links with count" << endl; printLink_count(map_all); break;
			case 2: cout <<"\n> Referred links with count" << endl; printLink_count(map_ref); break;
			case 3: cout <<"\n> Program terminated"<< endl; flag = false; break;
			default: cout <<"\n> Error: Input is a invalid Key, try again"<< endl;
		}
	}

	map_all.clear();
	map_ref.clear();
	cout << endl;
	return 0;
}