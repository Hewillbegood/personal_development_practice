#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

#define MAX_F 4294967295

unsigned long long Fmax = 0, Dmin = 0, Bmin = 0;
unsigned long long F = 0, D = 0, B = 0;

unsigned long long Getf(unsigned long long d, unsigned long long b) {

	if (d > 32 && b >= 32) {
		return 0;
	}
	else if (b >= d) {
		return pow(2, d) - 1;
	}
	else if (b == 1) {
		return d;
	}
	else if (b == 2) {
		if (d * (d + 1) / 2 > MAX_F) {
			return 0;
		}
		else {
			return d * (d + 1) / 2;
		}
	}
	else if (b == 3) {
		if ((d - 1) * d * (d + 1) / 6 + d > MAX_F) {
			return 0;
		}
		else {
			return (d - 1) * d * (d + 1) / 6 + d;
		}
	}
	else {
		if ((d - 1) * d * (d + 1) / 6 + d > MAX_F) {
			return 0;
		}
		else {
			unsigned long long term1 = Getf(d - 1, b - 1);
			unsigned long long term2 = Getf(d - 1, b);

			if (term1 == 0 || term2 == 0) {
				return 0;
			}
			else {
				if (term1 + term2 + 1 > MAX_F) {
					return 0;
				}
				else {
					return term1 + term2 + 1;
				}
			}
		}
	}
}

//void SeeIf(unsigned long long d, unsigned long long b) {
//
//	cout << "SeeIf-1: " << d << "," << b << endl;
//
//	unsigned long long f = Getf(d, b);
//	if (d == D && b == B) {
//		Fmax = f;
//	}
//
//	cout << "SeeIf-2: " << f << "," << d << "," << b << endl;
//
//	if (f == 0) f = MAX_F;
//
//	if (d == D) {
//		if (f < F) Bmin = b + 1;
//		else if (b == 1) Bmin = 1;
//		else SeeIf(d, b - 1);
//	}
//
//	if (b == B) {
//		if (f < F) Dmin = d + 1;
//		else if (d == 1) Dmin = 1;
//		else SeeIf(d - 1, b);
//	}
//}

void SeeIf(unsigned long long d, unsigned long long b) {

	cout << "SeeIf-1: " << d << "," << b << endl;

	unsigned long long f = Getf(d, b);

	cout << "SeeIf-2: " << f << "," << d << "," << b << endl;

	if (f == 0) f = MAX_F + 1;

	if (d == D) {
		if (f >= F) Bmin = b;
		else SeeIf(d, b + 1);
	}

	if (b == B) {
		if (f >= F) Dmin = d;
		else SeeIf(d + 1, b);
	}
}

int main() {

	int cCases = 0;
	ifstream infile("C-small-practice.in");
	ofstream outfile("outfile.out");
	infile >> cCases;

	for (int iCase = 1; iCase <= cCases; iCase++) {
		
		cout << "iCase == " << iCase << endl;

		infile >> F >> D >> B;

		Fmax = Getf(D, B);
		SeeIf(D, 1);
		SeeIf(1, B);

		if (Fmax != 0) {
			outfile << "Case #" << iCase << ": " << Fmax << " " << Dmin << " " << Bmin << endl;
		}
		else {
			outfile << "Case #" << iCase << ": " << -1 << " " << Dmin << " " << Bmin << endl;
		}
	}

	infile.close();
	outfile.close();
	system("pause");
	return 0;
}