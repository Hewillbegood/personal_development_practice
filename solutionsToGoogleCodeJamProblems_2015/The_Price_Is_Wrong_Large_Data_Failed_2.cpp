#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

#define CMAX 70

string names[CMAX];
double prices[CMAX];
int cItems;
int cMaxAsc;
vector<vector<string>> minRemain;

int GetAscLen(bool* iInConsider, int cConsider) {

	bool iConsider[CMAX];
	for (int i = 0; i < cItems; i++) {
		iConsider[i] = iInConsider[i];
	}

	int thisAscLen = 0;

	for (int i = 0; i < cItems; i++) {
		if (!iConsider[i]) continue;

		int currAscLen = 0;

		iConsider[i] = false;
		currAscLen += GetAscLen(iConsider, cConsider - 1);
		iConsider[i] = true;

		bool plusEle1 = true;
		bool plusEle2 = true;
		if (i > 0) {
			for (int j = i - 1; j >= 0; j--) {
				if (iConsider[j]) {
					if (prices[j] > prices[i]) {
						plusEle1 = false;
						break;
					}
				}
			}
		}
		if (i < cItems - 1) {
			for (int j = i + 1; j < cItems; j++) {
				if (iConsider[j]) {
					if (prices[j] < prices[i]) {
						plusEle2 = false;
						break;
					}
				}
			}
		}

		if (plusEle1 && plusEle2) {
			currAscLen++;
		}
		if (currAscLen > thisAscLen) {
			thisAscLen = currAscLen;
		}
	}

	if (thisAscLen > cMaxAsc) {
		minRemain.clear();
		cMaxAsc = thisAscLen;
	}
	if (thisAscLen == cMaxAsc && cMaxAsc > 0) {
		vector<string> tmpV;
		tmpV.reserve(64);
		for (int i = 0; i < cItems; i++) {
			if (!iConsider[i])  tmpV.push_back(names[i]);
		}
		minRemain.push_back(tmpV);
	}

	return thisAscLen;
}

int main() {

	minRemain.reserve(100);

	int cCases = 0;
	ifstream infile("B-large-practice.in");
	ofstream outfile("outfile.out");
	infile >> cCases;
	infile.get();

	for (int iCase = 1; iCase <= cCases; iCase++) {

		cItems = 0;
		cMaxAsc = 0;
		minRemain.clear();
		char ch;
		do {
			infile >> names[cItems];
			cItems++;
			infile.get(ch);
		} while (ch != '\n');
		for (int i = 0; i < cItems; i++) {
			infile >> prices[i];
		}

		bool iConsider[CMAX];
		for (int i = 0; i < CMAX; i++) {
			iConsider[i] = true;
		}

		int ascLen = GetAscLen(iConsider, cItems);

		outfile << "Case #" << iCase << ":";

		vector<string> tmpV;
		for (int i = 0; i < cItems - ascLen; i++) {
			tmpV.push_back("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
		}
		vector<string>* pFin = &tmpV;
		for (int i = 0; i < minRemain.size(); i++) {
			if (minRemain[i].size() != cItems - ascLen) continue;
			else {
				sort(minRemain[i].begin(), minRemain[i].end());
				for (int j = 0; j < cItems - ascLen; j++) {
					if ((*pFin)[j] > minRemain[i][j]) {
						pFin = &minRemain[i];
						break;
					}
					else if ((*pFin)[j] < minRemain[i][j]) {
						break;
					}
				}
			}
		}

		for (int i = 0; i < pFin->size(); i++) {
			outfile << " " << (*pFin)[i];
		}
		outfile << endl;
	}

	infile.close();
	outfile.close();
	system("pause");
	return 0;
}