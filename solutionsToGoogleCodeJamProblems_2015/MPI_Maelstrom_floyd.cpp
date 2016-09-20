#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

#define BLOCK 1000000000

int martrix[100][100];
int n;
int prevM[100][100];

int main() {

	cin >> n;
	string tmp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			cin >> tmp;
			if (tmp[0] != 'x') {
				// number.
				martrix[i][j] = atoi(tmp.c_str());
				martrix[j][i] = atoi(tmp.c_str());
				assert(martrix[i][j] < BLOCK);
				// record.
				prevM[i][j] = i;
				prevM[j][i] = j;
			}
			else {
				// block.
				martrix[i][j] = BLOCK;
				martrix[j][i] = BLOCK;
				// record.
				prevM[i][j] = -1;
				prevM[j][i] = -1;
			}
		}
		martrix[i][i] = 0;
		prevM[i][i] = i;
	}

	// process floyd.
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int right = martrix[i][k] + martrix[k][j];
				assert(right >= martrix[i][k]);
				assert(right >= martrix[k][j]);

				if (martrix[i][j] > right) {
					martrix[i][j] = right;
					// record.
					prevM[i][j] = prevM[k][j];
				}
			}
		}
	}

	int result = 0;
	for (int i = 0; i < n; i++) {
		if (martrix[0][i] > result) result = martrix[0][i];
	}
	cout << result<< endl;
	cout << "The Path:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << i << " to " << j << " from last:";
			int theFirst = prevM[i][j];
			cout << " " << j;
			cout << " " << theFirst;
			while (theFirst != i) {
				theFirst = prevM[i][theFirst];
				cout << " " << theFirst;
			}
			cout << endl;
		}
	}

	system("pause");
	return 0;
}