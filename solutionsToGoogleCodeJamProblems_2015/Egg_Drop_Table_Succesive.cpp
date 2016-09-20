#include <fstream>
#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;

#define MAX_F 4294967295

int main() {

	typedef unsigned long Bline[100001];
	Bline* table = new Bline[33];	// the indexes are real d, b values.
	for (int i = 0; i < 100001; i++) table[0][i] = 0;
	for (int i = 0; i < 33; i++) table[i][0] = 0;
	//
	// fill the table.
	//
	for (int d = 1; d <= 100000; d++) table[1][d] = d;
	for (int b = 1; b <= 32; b++) table[b][1] = 1;
	for (int b = 2; b <= 32; b++) {
		for (int d = 2; d <= 100000; d++) {
			if (table[b - 1][d - 1] == 0 || table[b][d - 1] == 0) {
				table[b][d] = 0;
			}
			else {
				table[b][d] = table[b - 1][d - 1] + table[b][d - 1] + 1;
				if (table[b][d] <= table[b - 1][d - 1] || table[b][d] <= table[b][d - 1]) {
					table[b][d] = 0;	// 0 represents: >= MAX_F
				}
			}			
		}
	}
	//
	// cases.
	//
	int cCases = 0;
	ifstream infile("C-large-practice.in");
	ofstream outfile("outfile.out");
	infile >> cCases;

	for (int iCase = 1; iCase <= cCases; iCase++) {
		unsigned long F, D, B;
		infile >> F >> D >> B;
		//
		// Results.
		//
		unsigned long Fmax, Dmin, Bmin;
		if (B > 32) {

			Fmax = 0;

			if (D > 100000) {
				if (D >= F) Bmin = 1;
				else Bmin = 2;
			}
			else {
				int candBmin = 1;
				while (table[candBmin][D] < F && table[candBmin][D] != 0) candBmin++;
				Bmin = candBmin;
			}

			int candDmin = 1;
			while (pow(2ull, candDmin) - 1 < F) candDmin++;
			Dmin = candDmin;
		}
		else {
			if (D > 100000) {
				if (B == 1) Fmax = D;
				else Fmax = 0;

				if (D >= F) {
					Bmin = 1;
				}
				else {
					Bmin = 2;
				}
			}
			else {
				Fmax = table[B][D];

				if (D <= 30) assert(table[D][D] >= F);
				int candBmin = 1;
				while (table[candBmin][D] < F && table[candBmin][D] != 0) candBmin++;
				Bmin = candBmin;
			}

			if (B == 1) Dmin = F;
			else {
				int candDmin = 1;
				while (table[B][candDmin] < F && table[B][candDmin] != 0) candDmin++;
				Dmin = candDmin;
			}
		}

		if (Fmax != 0) {
			outfile << "Case #" << iCase << ": " << Fmax << " " << Dmin << " " << Bmin << endl;
		}
		else {
			outfile << "Case #" << iCase << ": " << -1 << " " << Dmin << " " << Bmin << endl;
		}
	}


	infile.close();
	outfile.close();
	delete[] table;
	system("pause");
	return 0;
}