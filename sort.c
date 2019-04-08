//201503564 한민지
#include<stdio.h>
#include<stdlib.h> //random함수
#include<time.h>
#include<string.h> //memset함수 (메모리 초기화함수)

//각 정렬의 비교, 이동 array (1000 ~ 10000개 - 10개 배열에 해당되는 비교, 교환값을 저장하기 위함)
int selection_compare[11] = { 0 };
int selection_move[11] = { 0 };
int bubble_compare[11] = { 0 };
int bubble_move[11] = { 0 };
int insert_compare[11] = { 0 };
int insert_move[11] = { 0 };
int shell_compare[11] = { 0 };
int shell_move[11] = { 0 };
int merge_compare[11] = { 0 };
int merge_move[11] = { 0 };
int quick_compare[11] = { 0 };
int quick_move[11] = { 0 };

//선택정렬
int selectionSort(int *arr, int n) {
	int i, j;
	int least;
	for (i = 0; i < (n*1000) - 1; i++) { //n은 1~10까지만 넘어옴, 그 값으로 1000을 곱하면 sort의 크기가 된다.
		least = arr[i];
		for (j = i + 1; j < (n*1000); j++) {
			//두번째 for문 비교 횟수 증가
			selection_compare[n] += 1;
			if (least > arr[j]) {
				least = arr[j];
				arr[j] = arr[i];
				arr[i] = least;
				selection_move[n] += 2;
			}
		}
	}
	return 0;
}

//버블정렬
int BubbleSort(int *arr, int n) {
	int i, j;
	int min;

	for (i = (n*1000) - 1; i >= 0; i--) {
		for (j = 0; j < i; j++) {
			bubble_compare[n] += 1;
			if (arr[j] > arr[j + 1]) {
				min = arr[j];
				arr[j + 1] = min;
				arr[j] = min;
				bubble_move[n] += 2;
			}
		}
	}
	return 0;
}

//삽입정렬
int InsertSort(int *arr, int n) {
	int i, j;
	int min;
	for (i = 1; i < n*1000; i++) {
		min = arr[i]; //최소값을 저장한 후 
		for (j = i - 1; j >= 0; j--) { //해당 인덱스 전부터 0번 인덱스까지 비교
			insert_compare[n] += 1;
			if (min < arr[j]) {
				arr[j + 1] = arr[j];
				insert_move[n] += 1;
			}
			else {
				break;
			}
		}
		arr[j + 1] = min;
		insert_move[n] += 1;
	}
	return 0;
}

//쉘정렬
void InsertionSort2(int *arr, int size, int h, int n) {
	int i, j, tmp;
	for (i = h; i < size; i += h) {
		for (j = i; j > 0; j -= h) {
			shell_compare[n] += 1;
			if (arr[j - h] > arr[j]) {
				tmp = arr[j - h];
				arr[j - h] = arr[j];
				arr[j] = tmp;
				shell_move[n] += 2;
			}
			else {
				break;
			}
		}
	}
}

void ShellSort(int *arr, int n)
{
	int i, h;
	for (h = (n*1000) / 2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++) //간격 안에 있는 배열들 정렬
		{
			InsertionSort2(arr + i, (n*1000) - i, h, n);
		}
	}
}

//합병정렬
void merge(int arr[], int m, int d, int n, int num) {
	int i = m;
	int j = d + 1;
	int k = m;
	int *tmp = (int*)malloc(sizeof(int) * (num * 1000));
	while (i <= d && j <= n) {
		merge_compare[num] += 2; //while 비교와 if문 비교까지
		if (arr[i] <= arr[j]) {
			merge_compare[num] += 1;
			tmp[k++] = arr[i++];
			merge_move[num] += 1;
		}

		else {
			tmp[k++] = arr[j++];
			merge_move[num] += 1;
		}
	}
	merge_compare[num] += 1;
	while (i <= d) {
		merge_compare[num] += 1;
		tmp[k++] = arr[i++];
		merge_move[num] += 1;
	}
	merge_compare[num] += 1;

	while (j <= n) {
		tmp[k++] = arr[j++];
		merge_move[num] += 1;
		merge_compare[num] += 1;
	}
	merge_compare[num] += 1;

	for (int t = m; t <= n; t++) {
		arr[t] = tmp[t];
		merge_move[num] += 1;
		merge_compare[num] += 1;
	}
	merge_compare[num] += 1;
}

void mergeSort(int arr[], int m, int n, int num) {
	int d;
	merge_compare[num] += 1;
	if (m < n) {
		d = (m + n) / 2;
		mergeSort(arr, m, d, num);
		mergeSort(arr, d + 1, n, num);
		merge(arr, m, d, n, num);
	}
}

//퀵정렬
int Partition(int arr[], int left, int right, int n)
{
	int pivot = arr[left]; // 피벗의 위치
	int L = left + 1;
	int R = right;
	int tmp;
	while (L <= R) // 교차되기 전까지 반복
	{
		merge_compare[n] += 1;
		while (pivot >= arr[L] && L <= right) // pivot보다 큰 값을 찾기 
		{
			L++;
			merge_compare[n] += 1;
		}
		merge_compare[n] += 1;

		while (pivot <= arr[R] && R >= (left + 1)) // pivot보다 작은 값을 찾기
		{
			R--;
			merge_compare[n] += 1;
		}
		merge_compare[n] += 1;

		if (L <= R)// 교차되지 않은 상태이면 바꾸기
		{
			tmp = arr[L];
			arr[L] = arr[R];
			arr[R] = tmp;
			merge_move[n] += 2;
		}
		merge_compare[n] += 1;
	}
	merge_compare[n] += 1;
	tmp = arr[left];
	arr[left] = arr[R];
	arr[R] = tmp;
	merge_move[n] += 2;
	return R;
}

void QuickSort(int arr[], int begin, int end, int n)
{
	if (begin <= end)
	{
		int pivot = Partition(arr, begin, end, n); // 둘로 나누어서
		QuickSort(arr, begin, pivot - 1, n); // 왼쪽 영역을 정렬한다.
		QuickSort(arr, pivot + 1, end, n); // 오른쪽 영역을 정렬한다.
	}
	merge_compare[n] += 1;
}


//중복 난수발생 막는 함수
void make_tenArray(int arr[],int num) {
	int temp = 0;
	for (int i = 0; i < (num*1000); i++) {
	again:;
		temp = rand() % 10000 + 1;
		for (int j = 0; j <= i - 1; j++) {
			if (arr[j] == temp) {
				goto again;
			}
		}
		arr[i] = temp;
	}
}

//여러번 호출해야하는 함수들이나 배열들을 한번에 초기화해주고 랜덤함수 부르는 함수
void tenArray_call(int one[], int two[], int three[], int four[], int five[], int six[], int seven[], int eight[], int nine[], int ten[]) {
	//memset을 이용하여 10개의 배열 초기화
	memset(one, 0, sizeof(1000));
	memset(two, 0, sizeof(2000));
	memset(three, 0, sizeof(3000));
	memset(four, 0, sizeof(4000));
	memset(five, 0, sizeof(5000));
	memset(six, 0, sizeof(6000));
	memset(seven, 0, sizeof(7000));
	memset(eight, 0, sizeof(8000));
	memset(nine, 0, sizeof(9000));
	memset(ten, 0, sizeof(10000));

	make_tenArray(one, 1);
	make_tenArray(two, 2);
	make_tenArray(three, 3);
	make_tenArray(four, 4);
	make_tenArray(five, 5);
	make_tenArray(six, 6);
	make_tenArray(seven, 7);
	make_tenArray(eight, 8);
	make_tenArray(nine, 9);
	make_tenArray(ten, 10);
}

int main() {
	printf("정렬 알고리즘 비교 201503564 한민지\n\n");
	//비교할 10개 크기 배열
	srand((unsigned int)time(NULL));
	int one[1000];
	int two[2000];
	int three[3000];
	int four[4000];
	int five[5000];
	int six[6000];
	int seven[7000];
	int eight[8000];
	int nine[9000];
	int ten[10000];

	//1. 선택정렬 출력
	printf("\nSelection Sort\n");
	int n = 0;
	tenArray_call(one, two, three, four, five, six, seven, eight, nine, ten);
	selectionSort(one, 1);
	selectionSort(two, 2);
	selectionSort(three, 3);
	selectionSort(four, 4);
	selectionSort(five, 5);
	selectionSort(six, 6);
	selectionSort(seven, 7);
	selectionSort(eight, 8);
	selectionSort(nine, 9);
	selectionSort(ten, 10);
	n = 0;
	for (n = 1; n <= 10; n++) {
		printf("size=%d  compare=%d  move=%d\n", n * 1000, selection_compare[n], selection_move[n]);
	}

	//2. 버블정렬
	printf("\nBubble Sort\n");
	tenArray_call(one, two, three, four, five, six, seven, eight, nine, ten);
	BubbleSort(one, 1);
	BubbleSort(two, 2);
	BubbleSort(three, 3);
	BubbleSort(four, 4);
	BubbleSort(five, 5);
	BubbleSort(six, 6);
	BubbleSort(seven, 7);
	BubbleSort(eight, 8);
	BubbleSort(nine, 9);
	BubbleSort(ten, 10);
	n = 0;
	for (n = 1; n <= 10; n++) {
		printf("size=%d  compare=%d  move=%d\n", n * 1000, bubble_compare[n], bubble_move[n]);
	}
	
	//3. 삽입정렬
	printf("\nInsert Sort\n");
	tenArray_call(one, two, three, four, five, six, seven, eight, nine, ten);
	InsertSort(one, 1);
	InsertSort(two, 2);
	InsertSort(three, 3);
	InsertSort(four, 4);
	InsertSort(five, 5);
	InsertSort(six, 6);
	InsertSort(seven, 7);
	InsertSort(eight, 8);
	InsertSort(nine, 9);
	InsertSort(ten, 10);
	
	n = 0;
	for (n = 1; n <= 10; n++) {
		printf("size=%d  compare=%d  move=%d\n", n * 1000, insert_compare[n], insert_move[n]);
	}


	//4. 쉘정렬
	printf("\nShell Sort\n");
	tenArray_call(one, two, three, four, five, six, seven, eight, nine, ten);
	ShellSort(one, 1);
	ShellSort(two, 2);
	ShellSort(three, 3);
	ShellSort(four, 4);
	ShellSort(five, 5);
	ShellSort(six, 6);
	ShellSort(seven, 7);
	ShellSort(eight, 8);
	ShellSort(nine, 9);
	ShellSort(ten, 10);
	n = 0;
	for (n = 1; n <= 10; n++) {
		printf("size=%d  compare=%d  move=%d\n", n * 1000, shell_compare[n], shell_move[n]);
	}
	
	//5. 병합정렬
	printf("\nMerge Sort\n");
	tenArray_call(one, two, three, four, five, six, seven, eight, nine, ten);
	mergeSort(one, 0, 999, 1);
	mergeSort(two, 0, 1999, 2);
	mergeSort(three, 0, 2999, 3);
	mergeSort(four, 0, 3999, 4);
	mergeSort(five, 0, 4999, 5);
	mergeSort(six, 0, 5999, 6);
	mergeSort(seven, 0, 6999, 7);
	mergeSort(eight, 0, 7999, 8);
	mergeSort(nine, 0, 8999, 9);
	mergeSort(ten, 0, 9999, 10);
	n = 0;
	for (n = 1; n <= 10; n++) {
		printf("size=%d  compare=%d  move=%d\n", n * 1000, merge_compare[n], merge_move[n]);
	}

	//6. 퀵정렬
	printf("\nQuick Sort\n");
	tenArray_call(one, two, three, four, five, six, seven, eight, nine, ten);
	mergeSort(one, 0, 1 - 1, 1); //해당 비교, 교환 배열에 넣기위해 파라미터 하나 추가(merge_compare[n], merge_move[n]에 추가하기 위함)
	mergeSort(two, 0, 2 - 1, 2);
	mergeSort(three, 0, 3 - 1, 3);
	mergeSort(four, 0, 4 - 1, 4);
	mergeSort(five, 0, 5 - 1, 5);
	mergeSort(six, 0, 6 - 1, 6);
	mergeSort(seven, 0, 7 - 1, 7);
	mergeSort(eight, 0, 8 - 1, 8);
	mergeSort(nine, 0, 9 - 1, 9);
	mergeSort(ten, 0, 10 - 1, 10);
	n = 0;
	for (n = 1; n <= 10; n++) {
		printf("size=%d  compare=%d  move=%d\n", n * 1000, merge_compare[n], merge_move[n]);
	}
	//malloc을 사용하지 않고 10개의 배열을 만들어서 사용했기 때문에 free를 사용하지 않았습니다.
	while (1);
	return 0;
}