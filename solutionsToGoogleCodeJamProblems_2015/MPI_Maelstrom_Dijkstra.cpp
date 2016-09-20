#include <iostream>
#include <string>
#include <assert.h>
#include <iomanip>
using namespace std;

#define DIST_INFI 1000000000

int main() {

	int martrix[100][100];
	int n;
	bool closed[100];
	int dist[100];
	int cClosed;
	int currNode;
	int prevN[100];

	// input.
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			string tmp;
			cin >> tmp;
			if (tmp[0] != 'x') {// number.
				martrix[i][j] = atoi(tmp.c_str());
				martrix[j][i] = martrix[i][j];
			}
			else {// 'x'.
				martrix[i][j] = DIST_INFI;
				martrix[j][i] = DIST_INFI;
			}
		}
		martrix[i][i] = 0;
	}

	// prepare.
	currNode = 0;
	cClosed = 1;
	closed[0] = true;
	for (int i = 1; i < n; i++) {
		closed[i] = false;
	}
	for (int i = 0; i < n; i++) {
		dist[i] = DIST_INFI;
	}
	dist[0] = 0;
	prevN[0] = -1;

	// process.
	while (cClosed < n) {
		for (int i = 0; i < n; i++) {
			if (closed[i]) continue;
			if (martrix[currNode][i] == DIST_INFI) continue;
			if (dist[currNode] + martrix[currNode][i] < dist[i]) {
				dist[i] = dist[currNode] + martrix[currNode][i];
				prevN[i] = currNode;
			}
		}
		int thisDist = DIST_INFI;
		for (int i = 0; i < n; i++) {
			if (closed[i]) continue;
			if (dist[i] == DIST_INFI) continue;
			if (dist[i] < thisDist) {
				thisDist = dist[i];
				currNode = i;
			}
		}
		cClosed++;
		closed[currNode] = true;
	}

	int result = 0;
	for (int i = 1; i < n; i++) {
		if (dist[i] > result) result = dist[i];
	}
	cout << result << endl;

	// shortest paths.

		for (int j = 0; j < n; j++) {
			cout << "Path from " << 0 << " to " << j << " backwards:";
			int curr = j;
			while (curr != -1) {
				cout << " " << curr;
				curr = prevN[curr];
			}
			cout << endl;
		}


	system("pause");
	return 0;
}