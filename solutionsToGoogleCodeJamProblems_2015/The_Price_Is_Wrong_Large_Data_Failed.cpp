#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <set>
using namespace std;

#define CMAX 70

string names[CMAX];
double prices[CMAX];
set<set<string>> minRemain;
int cItems;
int cMaxAsc;

int GetAscLen(bool* iInConsider, int cConsider) {

	int thisAscLen = 0;

	bool iConsider[CMAX];
	for (int i = 0; i < cItems; i++) {
		iConsider[i] = iInConsider[i];
	}

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
		set<string> tmpSet;
		for (int i = 0; i < cItems; i++) {
			if (!iConsider[i]) tmpSet.insert(names[i]);
		}
		minRemain.insert(tmpSet);
	}

	return thisAscLen;
}

int main() {

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

		int itIdxFin = 0;
		int itIdx = -1;
		bool firstMet = false;
		for (set<set<string>>::iterator ii = minRemain.begin(); ii != minRemain.end(); ii++) {
			itIdx++;
			if ((*ii).size() != cItems - ascLen) continue;
			else {
				if (firstMet) {
					for (int i = 0; i < cItems - ascLen; i++) {
						set<set<string>>::iterator itTmp = minRemain.begin();
						for (int j = 0; j < itIdxFin; j++) {
							itTmp++;
						}
						set<string>::iterator i1 = (*itTmp).begin();
						set<string>::iterator i2 = (*ii).begin();
						for (int j = 0; j < i; j++) {
							i1++;
							i2++;
						}
						if (*i2 < *i1) {
							itIdxFin = itIdx;
							break;
						}
						else if (*i2 > *i1) {
							break;
						}
					}
				}
				else {
					itIdxFin = itIdx;
					firstMet = true;
				}			
			}
		}

		set<set<string>>::iterator it = minRemain.begin();
		for (int i = 0; i < itIdxFin; i++) it++;
		set<string>::iterator its = (*it).begin();
		while (its != (*it).end()) {
			outfile << " " << *its;
			its++;
		}
		outfile << endl;
	}

	infile.close();
	outfile.close();
	system("pause");
	return 0;
}