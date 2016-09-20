#include <memory.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define max(x, y) ((x)>(y)?(x):(y))

// *** need modifying.
#define KM
#define MIN_INFI -1000000000		// meanwhile for blocked.
#define MAX_INFI 1000000000
#define TYPE int

#define C_LEFT_MAX 100
#define C_RIGHT_MAX 100

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

	// input.
      int N, M;
      int manX[100];	// X -> row.
      int manY[100];
      int houseX[100];
      int houseY[100];
      scanf("%d%d", &N, &M);
      while(N > 0) {
            char sb;
		int manIdx = 0;
		int houseIdx = 0;
            for (int i = 0; i < N; i++) {
                  scanf("%c", &sb);
                  for (int j = 0; j < M; j++) {
                        scanf("%c", &sb);
                        if (sb == 'm') {
                              manX[manIdx] = i;
                              manY[manIdx] = j;
                              manIdx++;
                        }
                        else if (sb == 'H') {
                              houseX[houseIdx] = i;
                              houseY[houseIdx] = j;
                              houseIdx++;
                        }
                  }
            }
            // init KM.
            int ct = manIdx;
		cLeft = ct;
		cRight = ct;
            for (int i = 0; i < ct; i++) {	// the i-th man.
                  for (int j = 0; j < ct; j++) {	// the j-th house.
                        load[i][j] = -(abs(manX[i] - houseX[j]) + abs(manY[i] - houseY[j]));
                  }
            }

            // process.
            process();

            // output.
            int negaSum = 0;
            for (int i = 0; i < ct; i++) {
                  negaSum += load[maty[i]][i];
            }
            printf("%d\n", 0 - negaSum);

		// next case.
		scanf("%d%d", &N, &M);
      }

	return 0;

}
