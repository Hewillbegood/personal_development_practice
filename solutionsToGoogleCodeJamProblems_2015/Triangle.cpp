#include <fstream>
#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;

void Decide(int iCase, int sq12, int sq13, int sq23, ofstream* outfile) {

	if (sq12 == sq13 || sq12 == sq23 || sq13 == sq23) {
		*outfile << "Case #" << iCase << ": isosceles ";
	}
	else {
		*outfile << "Case #" << iCase << ": scalene ";
	}

	if (sq12 + sq13 > sq23 && sq12 + sq23 > sq13 && sq13 + sq23 > sq12) {
		*outfile << "acute triangle" << endl;
	}
	else if (sq12 + sq13 == sq23 || sq12 + sq23 == sq13 || sq13 + sq23 == sq12) {
		*outfile << "right triangle" << endl;
	}
	else {
		*outfile << "obtuse triangle" << endl;
	}

}

int main() {

	int cCases = 0;
	ifstream infile("A-large-practice.in");
	ofstream outfile("outfile.out");
	infile >> cCases;

	for (int iCase = 1; iCase <= cCases; iCase++) {
		int x1, y1, x2, y2, x3, y3;
		infile >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		int sq12 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
		int sq13 = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);
		int sq23 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);
		if (x1 == x2 && y1 == y2) {
			outfile << "Case #" << iCase << ": not a triangle" << endl;
		}
		else {
			if (x1 == x2) {
				if (x3 != x1) {
					Decide(iCase, sq12, sq13, sq23, &outfile);
				}
				else {
					outfile << "Case #" << iCase << ": not a triangle" << endl;
				}
			}
			else {
				if ((x3 == x1 && y3 != y1) || (x3 == x2 && y3 != y2)) {
					Decide(iCase, sq12, sq13, sq23, &outfile);
				}
				else {
					if ((y3 - y2) * (x3 - x1) == (y3 - y1) * (x3 - x2)) {
						outfile << "Case #" << iCase << ": not a triangle" << endl;
					}
					else {
						Decide(iCase, sq12, sq13, sq23, &outfile);
					}
				}
			}
		}
	}

	infile.close();
	outfile.close();
	system("pause");
	return 0;
}