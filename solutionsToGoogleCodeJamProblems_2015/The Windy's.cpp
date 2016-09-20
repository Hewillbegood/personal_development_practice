#include <memory.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;

#define max(x, y) ((x)>(y)?(x):(y))

// *** need modifying.
#define KM
#define MIN_INFI -1000000000		// meanwhile for blocked.
#define MAX_INFI 1000000000
#define TYPE int

#define C_LEFT_MAX 50
#define C_RIGHT_MAX 2500

int cLeft, cRight;
// *** end.

TYPE load[C_LEFT_MAX][C_RIGHT_MAX];
int maty[C_RIGHT_MAX];
bool treeLeft[C_LEFT_MAX];
bool treeRight[C_RIGHT_MAX];

#ifdef KM
TYPE leftLabel[C_LEFT_MAX];
TYPE rightLabel[C_RIGHT_MAX];
TYPE d;

void initLabels() {

      for (int i = 0; i < cLeft; i++) {
            TYPE maxForI = MIN_INFI;
            for (int j = 0; j < cRight; j++) {
                  if (load[i][j] > maxForI) maxForI = load[i][j];
            }
            leftLabel[i] = maxForI;
      }

	memset(rightLabel, 0, sizeof(rightLabel));
}
#endif

void initMatch() {

      for (int i = 0; i < cRight; i++) {
            maty[i] = -1;
      }

}

bool dfs(int theLeft) {

      treeLeft[theLeft] = true;
      for (int i = 0; i < cRight; i++) {
            if (!treeRight[i]) {
                  #ifdef KM
                  TYPE t = leftLabel[theLeft] + rightLabel[i] - load[theLeft][i];
                  if (t == 0) { // equalsub.
                        treeRight[i] = true;
                        if (maty[i] == -1 || dfs(maty[i])) {
                              maty[i] = theLeft;
                              return true;
                        }
                  }
                  else if (d > t) {
                        d = t;
                  }
			#else
                  if (load[theLeft][i] != MIN_INFI) {	// in the graph.
                        treeRight[i] = true;
                        if (maty[i] == -1 || dfs(maty[i])) {
                              maty[i] = theLeft;
                              return true;
                        }
                  }
			#endif
            }
      }
      return false;

}

int process() { // return count of DFSSucc.

      #ifdef KM
      initLabels();
      #endif // KM
      initMatch();

      int cDFSSucc  = 0;
      for (int i = 0; i < cLeft; i++) {
		memset(treeLeft, 0, sizeof(treeLeft));
            memset(treeRight, 0, sizeof(treeRight));
		#ifdef KM
            d = MAX_INFI;
            while (!dfs(i)) {
                  // update labels.
                  for (int j = 0; j < cLeft; j++) {
                        if (!treeLeft[j]) continue;

                        leftLabel[j] -= d;
                  }
                  for (int k = 0; k < cRight; k++) {
                              if (!treeRight[k]) continue;

                              rightLabel[k] += d;
                  }

			d = MAX_INFI;
			memset(treeLeft, 0, sizeof(treeLeft));
			memset(treeRight, 0, sizeof(treeRight));
            }
            #else
            if (dfs(i)) cDFSSucc++;
            #endif
      }
	return cDFSSucc;

}

int main() {

	int cCases = 0;
	scanf("%d", &cCases);

	for (int iCase = 0; iCase < cCases; iCase++) {
		int input[50][50];
		int cOrders, cFacs;
		scanf("%d%d", &cOrders, &cFacs);
		for (int i = 0; i < cOrders; i++) {
			for (int j = 0; j < cFacs; j++) {
				scanf("%d", &input[i][j]);
			}
		}

            cLeft = cOrders;
            cRight = cOrders * cFacs;
		// real martrix for 2-graph.
		for (int i = 0; i < cOrders; i++) {
			for (int j = 0; j < cFacs; j++) {
				for (int k = 0; k < cOrders; k++) {
					load[i][j * cOrders + k] = -input[i][j] * (k + 1);
				}
			}
		}

            process();

		// output.
		int sum = 0;
		for (int i = 0; i < cRight; i++) {
                  if (maty[i] != -1) {
                        sum += load[maty[i]][i];
                  }
		}
            printf("%0.6f\n", double(0 - sum) / cOrders);
	}
	return 0;

}
