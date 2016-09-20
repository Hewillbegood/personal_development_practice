#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main() {

	int cCase = 0;
	fstream inFile;
	inFile.open("A-small-practice.in");
	inFile >> cCase;

	ofstream outFile;
	outFile.open("outfile.out");

	for (int caseIdx = 1; caseIdx <= cCase; caseIdx++) {

		string inNum;
		inFile >> inNum;
		string srcDigits;
		inFile >> srcDigits;
		string tgtDigits;
		inFile >> tgtDigits;

		int inNumLen = inNum.length();
		int cBaseSrc = srcDigits.length();
		int cBaseTgt = tgtDigits.length();

		int inNumDec = 0;
		for (int digiIdx = 0; digiIdx < inNumLen; digiIdx++) {
			int exp = inNumLen - 1 - digiIdx;
			int scale = pow(cBaseSrc, exp);
			int coe = srcDigits.find(inNum[digiIdx]);
			inNumDec += coe * scale;
		}

		int reversedIdxes[100];
		int cIndxes = 0;

		do {
			int rem = inNumDec % cBaseTgt;
			reversedIdxes[cIndxes++] = rem;
		} while ((inNumDec /= cBaseTgt) != 0);

		// write.

		outFile << "Case #" << caseIdx << ": ";
		for (int i = cIndxes - 1; i >= 0; i--) {
			outFile << tgtDigits[reversedIdxes[i]];
		}
		outFile << endl;;
	}

	inFile.close();
	outFile.close();

	return 0;
}