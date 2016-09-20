#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <memory.h>
#include <vector>
#include <set>
using namespace std;

int main() {

	int cCases;
	scanf("%d", &cCases);
	for (int i = 0; i < cCases; i++) {
		int n;
		scanf("%d", &n);

		int xor1[31];
		int xor2[31];
		memset(xor1, 0, sizeof(xor1));
		memset(xor2, 0, sizeof(xor2));
		int sum = 0;

		for (int j = 0; j < 2 * (n - 1); j++) {
			int a;
			scanf("%d", &a);

			sum += a;

			int procInt = a;
			for (int k = 0; k < 31; k++) {
			    if (procInt % 2 == 0) xor2[k] ^= a;
			    else xor1[k] ^= a;
			    procInt >>= 1;
			}
		}

        for (int j = 0; j < 31; j++) {
		if (xor1[j] == 0 && xor2[j] == 0) {
			int result = (1 + n) * n / 2 - sum / 2;
                  printf("%d %d\n", result, result);
			break;
		}
            if (xor1[j] == 0 || xor2[j] == 0) continue;
            int smaller = xor1[j] < xor2[j] ? xor1[j] : xor2[j];
            int larger = xor1[j] < xor2[j] ? xor2[j] : xor1[j];
		printf("%d %d\n", smaller, larger);
            break;
        }
	}
	return 0;
}
