#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <assert.h>
using namespace std;

int main() {

	int cCase = 0;
	fstream inFile;
	inFile.open("A-small-practice.in");
	inFile >> cCase;

	ofstream outFile;
	outFile.open("outfile.out");

	for (int caseIdx = 1; caseIdx <= cCase; caseIdx++) {

		cout << endl;

		int s = 0, q = 0;
		inFile >> s;
		inFile.get();
		map<string, int> mapSI;
		for (int i = 0; i < s; i++) {
			string tmp;
			getline(inFile, tmp);
			mapSI.insert(pair<string, int>(tmp, i));
		}
		map<string, int>::iterator it = mapSI.begin();
		do {
			cout << it->first << " " << it->second << endl;
		} while ((++it) != mapSI.end());

		int result = 0;
		bool* iUsed = new bool[s];
		for (int i = 0; i < s; i++) {
			iUsed[i] = false;
		}
		int cUsed = 0;
		inFile >> q;
		inFile.get();
		for (int i = 0; i < q; i++) {

			// get index.
			int idx = 0;
			string tmp;
			getline(inFile, tmp);
			map<string, int>::iterator iFind = mapSI.find(tmp);
			assert(iFind != mapSI.end());
			idx = iFind->second;

			if (!iUsed[idx]) {
				if (cUsed == s - 1) {
					cUsed = 1;
					for (int j = 0; j < s; j++) {
						iUsed[j] = false;
					}
					result++;
				}
				else {
					cUsed++;
				}
				iUsed[idx] = true;				
			}

		}

		outFile << "Case #" << caseIdx << ": " << result << endl;
		delete[] iUsed;
	}

	inFile.close();
	outFile.close();

	system("pause");
	return 0;
}