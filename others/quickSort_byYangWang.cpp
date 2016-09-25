// the quick sort algorithm by Yang Wang

#include <cstdio>
#include <cstdlib>

void QuickSort(int *list, int totalLen, int begin /*inclusive*/, int end /*exclusive*/) {
	// base cases
	if (begin >= end - 1) return;

	// sort: the key is list[begin]; begin < end - 1; at least two elements in the range
	int left = begin, right = end;
	bool keyIsLeft = true;
	while (left < right - 1) {
		if (keyIsLeft) {
			if (list[left] <= list[right-1]) {
				right--;
			}
			else { // need swap
				int temp = list[left];
				list[left] = list[right-1];
				list[right-1] = temp;
				keyIsLeft = false;
				left++;
			}
		}
		else { // key is right
			if (list[left] <= list[right-1]) {
				left++;
			}
			else { // need swap
				int temp = list[left];
				list[left] = list[right-1];
				list[right-1] = temp;
				keyIsLeft = true;
				right--;
			}
		} // if (keyIsLeft)
	}

	// recursive calls: the key is now at left
	QuickSort(list, totalLen, begin, left);
	QuickSort(list, totalLen, left + 1, end);
}

int main() {
	// prepare the list
	int list[] = { 7, 20, 3, 4, 5, 3, 5, 76,5,69, 2039 ,3, 8, 9, 9, 8, 3, 7, 10, 3, 9, 9 };
	int totalLen = 22;
	printf("before sort:\n");
	for (int i = 0; i < totalLen; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");

	// sort
	QuickSort(list, totalLen, 0, totalLen);

	// output
	printf("after sort:\n");
	for (int i = 0; i < totalLen; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");

	system("pause");
	return 0;
}