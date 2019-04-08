//201503564 �ѹ���
#include<stdio.h>
#include<stdlib.h> //random�Լ�
#include<time.h>
#include<string.h> //memset�Լ� (�޸� �ʱ�ȭ�Լ�)

//�� ������ ��, �̵� array (1000 ~ 10000�� - 10�� �迭�� �ش�Ǵ� ��, ��ȯ���� �����ϱ� ����)
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

//��������
int selectionSort(int *arr, int n) {
	int i, j;
	int least;
	for (i = 0; i < (n*1000) - 1; i++) { //n�� 1~10������ �Ѿ��, �� ������ 1000�� ���ϸ� sort�� ũ�Ⱑ �ȴ�.
		least = arr[i];
		for (j = i + 1; j < (n*1000); j++) {
			//�ι�° for�� �� Ƚ�� ����
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

//��������
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

//��������
int InsertSort(int *arr, int n) {
	int i, j;
	int min;
	for (i = 1; i < n*1000; i++) {
		min = arr[i]; //�ּҰ��� ������ �� 
		for (j = i - 1; j >= 0; j--) { //�ش� �ε��� ������ 0�� �ε������� ��
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

//������
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
		for (i = 0; i < h; i++) //���� �ȿ� �ִ� �迭�� ����
		{
			InsertionSort2(arr + i, (n*1000) - i, h, n);
		}
	}
}

//�պ�����
void merge(int arr[], int m, int d, int n, int num) {
	int i = m;
	int j = d + 1;
	int k = m;
	int *tmp = (int*)malloc(sizeof(int) * (num * 1000));
	while (i <= d && j <= n) {
		merge_compare[num] += 2; //while �񱳿� if�� �񱳱���
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

//������
int Partition(int arr[], int left, int right, int n)
{
	int pivot = arr[left]; // �ǹ��� ��ġ
	int L = left + 1;
	int R = right;
	int tmp;
	while (L <= R) // �����Ǳ� ������ �ݺ�
	{
		merge_compare[n] += 1;
		while (pivot >= arr[L] && L <= right) // pivot���� ū ���� ã�� 
		{
			L++;
			merge_compare[n] += 1;
		}
		merge_compare[n] += 1;

		while (pivot <= arr[R] && R >= (left + 1)) // pivot���� ���� ���� ã��
		{
			R--;
			merge_compare[n] += 1;
		}
		merge_compare[n] += 1;

		if (L <= R)// �������� ���� �����̸� �ٲٱ�
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
		int pivot = Partition(arr, begin, end, n); // �ѷ� �����
		QuickSort(arr, begin, pivot - 1, n); // ���� ������ �����Ѵ�.
		QuickSort(arr, pivot + 1, end, n); // ������ ������ �����Ѵ�.
	}
	merge_compare[n] += 1;
}


//�ߺ� �����߻� ���� �Լ�
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

//������ ȣ���ؾ��ϴ� �Լ����̳� �迭���� �ѹ��� �ʱ�ȭ���ְ� �����Լ� �θ��� �Լ�
void tenArray_call(int one[], int two[], int three[], int four[], int five[], int six[], int seven[], int eight[], int nine[], int ten[]) {
	//memset�� �̿��Ͽ� 10���� �迭 �ʱ�ȭ
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
	printf("���� �˰��� �� 201503564 �ѹ���\n\n");
	//���� 10�� ũ�� �迭
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

	//1. �������� ���
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

	//2. ��������
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
	
	//3. ��������
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


	//4. ������
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
	
	//5. ��������
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

	//6. ������
	printf("\nQuick Sort\n");
	tenArray_call(one, two, three, four, five, six, seven, eight, nine, ten);
	mergeSort(one, 0, 1 - 1, 1); //�ش� ��, ��ȯ �迭�� �ֱ����� �Ķ���� �ϳ� �߰�(merge_compare[n], merge_move[n]�� �߰��ϱ� ����)
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
	//malloc�� ������� �ʰ� 10���� �迭�� ���� ����߱� ������ free�� ������� �ʾҽ��ϴ�.
	while (1);
	return 0;
}