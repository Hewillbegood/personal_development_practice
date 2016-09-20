#include <iostream>
#include <assert.h>
#include <memory.h>
#include <vector>
#include <iomanip>
#include <stdio.h>
using namespace std;

#define INT_INFI 1000000000

int cOrders, cFacs;

int equalSub[50][2500];

struct Line {
	Line(int a, int b) {
		left = a;
		right = b;
	}
	int left;
	int right;
};

int load[50][2500];
int leftLabel[50];
int rightLabel[2500];

int match[50][2500];
bool leftMatched[50], rightMatched[2500];
bool treeLeft[50], treeRight[2500];

int d;

int dfs(int theLeft, vector<Line> inRoad, bool leftSearched[], bool rightSearched[]) {
	// return 1 for successive searching for an extended path.
	treeLeft[theLeft] = true;
	leftSearched[theLeft] = true;
	for (int i = 0; i < cFacs * cOrders; i++) {

		if (equalSub[theLeft][i] == 0) {
                  int tobe = leftLabel[theLeft] + rightLabel[i] - load[theLeft][i];
                  if (tobe < d) d = tobe;
                  continue;
		}
		if (rightSearched[i] == true) continue;
		if (match[theLeft][i]) continue;

            // cout << " " << theLeft << "x" << i << endl;

		treeRight[i] = true;
		rightSearched[i] = true;
		inRoad.push_back(Line(theLeft, i));
		if (rightMatched[i]) {
			// continue the crossroad.
			for (int j = 0; j < cOrders; j++) {

				if (equalSub[j][i] == 0) continue;
				if (leftSearched[j] == true) continue;
				if (match[j][i] == 0) continue;

				// cout << " " << j << "-" << i << endl;

				// continue searching.
				inRoad.push_back(Line(j, i));
				bool newLeftSearched[50];
				bool newRightSearched[2500];
				for (int k = 0; k < cOrders; k++) {
					newLeftSearched[k] = leftSearched[k];
				}
				for (int k = 0; k < cFacs * cOrders; k++) {
					newRightSearched[k] = rightSearched[k];
				}
				if (dfs(j, inRoad, newLeftSearched, newRightSearched) == 1) {
					return 1;
				}
			}
		}
		else {
			// an extended road found.
			bool good = true;
			for (int j = 0; j < inRoad.size(); j++) {

				// update the match.
				int theLeft = inRoad[j].left;
				int theRight = inRoad[j].right;
				if (good == true) {
					match[theLeft][theRight] = 1;
					rightMatched[theRight] = 1;
					leftMatched[theLeft] = 1;
					good = false;
				}
				else {
					match[theLeft][theRight] = 0;
					rightMatched[theRight] = 1;
					leftMatched[theLeft] = 1;
					good = true;
				}
			}
			return 1;
		}
	}
	return 0;
}

int main() {

	int cCases = 0;
	scanf("%d", &cCases);

	for (int iCase = 0; iCase < cCases; iCase++) {
		int input[50][50];
		scanf("%d%d", &cOrders, &cFacs);
		for (int i = 0; i < cOrders; i++) {
			for (int j = 0; j < cFacs; j++) {
				scanf("%d", &input[i][j]);
			}
		}

		// real martrix for 2-graph.
		for (int i = 0; i < cOrders; i++) {
			for (int j = 0; j < cFacs; j++) {
				for (int k = 0; k < cOrders; k++) {
					load[i][j * cOrders + k] = -input[i][j] * (k + 1);
				}
			}
		}

		// KM process.

		// init label.
		for (int i = 0; i < cOrders; i++) {
			int theMax = -INT_INFI;
			for (int j = 0; j < cOrders * cFacs; j++) {
				assert(load[i][j] > -INT_INFI);
				if (load[i][j] > theMax) theMax = load[i][j];
			}
			leftLabel[i] = theMax;
		}
		for (int i = 0; i < cFacs * cOrders; i++) {
			rightLabel[i] = 0;
		}

		// init the equalSub.
		for (int i = 0; i < cOrders; i++) {
			for (int j = 0; j < cFacs * cOrders; j++) {
				if (load[i][j] == leftLabel[i] + rightLabel[j]) {
					equalSub[i][j] = 1;
				}
				else {
					equalSub[i][j] = 0;
				}
			}
		}
//            cout << "equalSub" << endl;
//            for (int i = 0; i < cOrders; i++) {
//                  for (int j = 0; j < cFacs * cOrders; j++) {
//                        if (equalSub[i][j]) cout << i << " " << j << endl;
//                  }
//            }

		// init the match for equalSub.
		for (int i = 0; i < cOrders; i++) {
			leftMatched[i] = 0;
			for (int j = 0; j < cFacs * cOrders; j++) {
				match[i][j] = 0;
				rightMatched[j] = 0;
			}
		}

		// for all left nodes.
		for (int i = 0; i < cOrders; i++) {
			if (leftMatched[i] == 0) {

				// init the tree.
				for (int i = 0; i < cOrders; i++) {
					treeLeft[i] = false;
				}
				memset(treeRight, 0, sizeof(treeRight));

				int result = 0;
				while (result != 1) {

					// compute d.
//					int d = INT_INFI;
//					for (int j = 0; j < cOrders; j++) {
//						if (!treeLeft[j]) continue;
//						for (int k = 0; k < cOrders * cFacs; k++) {
//							if (treeRight[k]) continue;
//							int waiting = leftLabel[j] + rightLabel[k] - load[j][k];
//							if (waiting < d) d = waiting;
//						}
//					}
					// cout << "d == " << d << endl;

					// update labels.
					for (int j = 0; j < cOrders; j++) {
						if (!treeLeft[j]) continue;
						leftLabel[j] -= d;
					}
					for (int j = 0; j < cFacs; j++) {
						if (!treeRight[j]) continue;
						rightLabel[j] += d;
					}

					// update equalSub.
					for (int j = 0; j < cOrders; j++) {
						if (!treeLeft[j]) continue;
						for (int k = 0; k < cOrders * cFacs; k++) {
							if (treeRight[j]) continue;
							if (load[j][k] == leftLabel[j] + rightLabel[k]) {
								equalSub[j][k] = 1;
							}
						}
					}
//					cout << "equalSub" << endl;
//					for (int i = 0; i < cOrders; i++) {
//						for (int j = 0; j < cFacs * cOrders; j++) {
//							if (equalSub[i][j]) cout << i << " " << j << endl;
//						}
//					}

					memset(treeLeft, 0, sizeof(treeLeft));
					memset(treeRight, 0, sizeof(treeRight));

					bool leftSearched[50], rightSearched[2500];
					memset(leftSearched, 0, sizeof(leftSearched));
					memset(rightSearched, 0, sizeof(rightSearched));
					vector<Line> tmpV;
                              d = INT_INFI;
					result = dfs(i, tmpV, leftSearched, rightSearched);
                              // cout << endl;
				}
			}
		}

		// output.
		int sum = 0;
		for (int i = 0; i < cOrders; i++) {
			for (int j = 0; j < cOrders * cFacs; j++) {
				if (match[i][j]) {
					sum += load[i][j];
				}
			}
		}
		cout << fixed << setprecision(6) << double(0 - sum) / cOrders << endl;
	}

	return 0;
}
