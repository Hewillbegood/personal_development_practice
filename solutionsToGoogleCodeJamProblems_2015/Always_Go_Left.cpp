#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

typedef char Room[4];	// integer, 0-blocked, 1-open, 2-undecided. Room[0-3]: N, E, S W.
enum ED { N = 0, E, S, W };

ED IntToED(int in) {
	if (in == 0) return ED::N;
	else if (in == 1) return ED::E;
	else if (in == 2) return ED::S;
	else if (in == 3) return ED::W;
	else
		cout << "IntToED error.\n";
}

void Turn(ED& inDir, char which) {
	switch (which) {
	case 'R': 
	inDir = IntToED((inDir + 1) % 4);
		break;
	case 'L': 
	inDir = IntToED((inDir + 3) % 4);
		break;
	case 'B':
		inDir = IntToED((inDir + 2) % 4);
		break;
	default:
		cout << "Turn error.\n";
	}
}

int main() {

	int cCases = 0;
	ifstream inFile("B-large-practice.in");
	inFile >> cCases;
	inFile.get();
	ofstream outFile("outFile.out");

	for (int iCase = 1; iCase <= cCases; iCase++) {

		Room rooms[500][500];
		for (int i = 0; i < 500; i++) {
			for (int j = 0; j < 500; j++) {
				rooms[i][j][0] = 2;
				rooms[i][j][1] = 2;
				rooms[i][j][2] = 2;
				rooms[i][j][3] = 2;
			}
		}
		int cooXmin = 250, cooXmax = 250, cooYmin = 250, cooYmax = 250;
		int cuCooX = 250, cuCooY = 249;
		ED cuDir = ED::S;
		bool Wpassed = false, Rpassed = false, RRpassed = false;
		//
		// process
		//
		char currChar = '\0';
		bool fstDone = false;

		for (int i = 0; i < 2; i++) {

			inFile.get(currChar);
			do {
				switch (currChar) {

				case 'W': {

					if (Wpassed) {
						ED tmpDir = cuDir;
						Turn(tmpDir, 'L');
						rooms[cuCooY][cuCooX][tmpDir] = 0;
					}
					else if (Rpassed) {
						ED tmpDir = cuDir;

						Turn(tmpDir, 'L');
						rooms[cuCooY][cuCooX][tmpDir] = 0;

						Turn(tmpDir, 'L');
						rooms[cuCooY][cuCooX][tmpDir] = 0;

						// RRpassed.
						if (RRpassed) {
							Turn(tmpDir, 'L');
							rooms[cuCooY][cuCooX][tmpDir] = 0;
						}
					}

					rooms[cuCooY][cuCooX][cuDir] = 1;

					Wpassed = true;
					Rpassed = false;
					RRpassed = false;
					//
					// change Coordinate and Direction.
					//
					switch (cuDir) {
					case ED::N: if ((--cuCooY) < cooYmin) cooYmin = cuCooY; break;
					case ED::S: if ((++cuCooY) > cooYmax) cooYmax = cuCooY; break;
					case ED::W: if ((--cuCooX) < cooXmin) cooXmin = cuCooX; break;
					case ED::E: if ((++cuCooX) > cooXmax) cooXmax = cuCooX; break;
					default:
						;
					}
					break;
				}

				case 'R':

					if (Rpassed) RRpassed = true;
					Rpassed = true;
					Wpassed = false;
					//
					// change Coordinate and Direction.
					//
					Turn(cuDir, 'R');
					break;

				case 'L':

					RRpassed = false;
					Rpassed = false;
					Wpassed = false;
					//
					// change Coordinate and Direction.
					//
					Turn(cuDir, 'L');
					break;

				default:
					cout << "process error.\n";
				}

				inFile.get(currChar);
			} while (currChar == 'W' || currChar == 'L' || currChar == 'R');
			//
			// repair the min max.
			//
			switch (cuDir) {
			case ED::N: cooYmin++; break;
			case ED::E: cooXmax--; break;
			case ED::S: cooYmax--; break;
			case ED::W: cooXmin++; break;
			default:
				cout << "error.\n";
			}
			//
			if (!fstDone) {
				Turn(cuDir, 'B');
				Wpassed = false;
				Rpassed = false;
				RRpassed = false;
			}
			fstDone = true;
		}
		//
		// output.
		//
		outFile << "Case #" << dec << iCase << ":\n";
		for (int i = cooYmin; i <= cooYmax; i++) {
			for (int j = cooXmin; j <= cooXmax; j++) {
				if (rooms[i][j][ED::N] == 2 || rooms[i][j][ED::E] == 2 || rooms[i][j][ED::S] == 2 || rooms[i][j][ED::W] == 2) cout << iCase << ": 2 present: " << i << " " << j << " " << endl;
				outFile << hex << 1 * rooms[i][j][ED::N] + 2 * rooms[i][j][ED::S] + 4 * rooms[i][j][ED::W] + 8 * rooms[i][j][ED::E];
			}
			outFile << endl;
		}
	}

	inFile.close();
	outFile.close();
	system("pause");
	return 0;
}