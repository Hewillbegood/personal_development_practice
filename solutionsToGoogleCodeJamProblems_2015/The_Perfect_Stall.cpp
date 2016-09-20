#include <memory.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define max(x, y) ((x)>(y)?(x):(y))

// *** need modifying.
// #define KM
#define MIN_INFI -1000000000		// meanwhile for blocked.
#define MAX_INFI 1000000000
#define TYPE int

#define C_LEFT_MAX 210
#define C_RIGHT_MAX 210

int cLeft, cRight;
TYPE load[C_LEFT_MAX][C_RIGHT_MAX];
// *** then just process().

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

      int N, M;
      while (scanf("%d%d", &N, &M) != EOF) {
		// input.
		for (int i = 0; i < C_LEFT_MAX; i++) {
			for (int j = 0; j < C_RIGHT_MAX; j++) {
				load[i][j] = MIN_INFI;
			}
		}
            for (int i = 0; i < N; i++) {
                  int cAble = 0;
                  scanf("%d", &cAble);
                  for (int j = 0; j < cAble; j++) {
				int rIdx = 0;
				scanf("%d", &rIdx);
                        rIdx --;	// optimize to 0-starting.
				load[i][rIdx] = 1;
                  }
            }

            cLeft = N;
            cRight = M;

            int result = process();

		// output.
            printf("%d\n", result);
      }

	return 0;

}
