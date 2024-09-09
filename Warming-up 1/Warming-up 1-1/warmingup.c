#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 4
int determinant(int matrix[SIZE][SIZE], int size);
void minor_matrix(int matrix[SIZE][SIZE], int temp[SIZE][SIZE], int row, int size);
void Num_multiplyMatirix(int matrix[SIZE][SIZE], char multiplier);

void main() {
	int matrix1[SIZE][SIZE], matrix2[SIZE][SIZE];
	int matrix_result[SIZE][SIZE];
	int rand_num = 0, counting_2 = 0;
	char command;
	srand(time(NULL));

	int sum = 0, number = 0;
	int det1 = 0, det2 = 0;
	int count = 0, matrix_rand = 0;

	while (1) {
		if (matrix_rand == 0) {
			// matrix 1
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					rand_num = rand() % 3;
					if (rand_num == 2 && counting_2 < 2) {
						matrix1[i][j] = rand_num;
						counting_2++;
					}
					else if (rand_num != 2) {
						matrix1[i][j] = rand_num;
					}
					else {
						j--;
					}
				}
			}
			// matrix 2
			counting_2 = 0;
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					rand_num = rand() % 3;
					if (rand_num == 2 && counting_2 < 2) {
						matrix2[i][j] = rand_num;
						counting_2++;
					}
					else if (rand_num != 2) {
						matrix2[i][j] = rand_num;
					}
					else {
						j--;
					}
				}
			}

			// 행렬 확인용
			printf("1번 행렬\n");
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					printf("%d  ", matrix1[i][j]);
				}
				printf("\n");
			}
			printf("\n2번 행렬\n");
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					printf("%d  ", matrix2[i][j]);
				}
				printf("\n");
			}
			printf("\n");

			matrix_rand++;
		}

		printf("command : ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'm':		// 행렬의 곱
			for (int k = 0; k < SIZE; k++) {
				for (int i = 0; i < SIZE; i++) {
					for (int j = 0; j < SIZE; j++) {
						sum = matrix1[k][j] * matrix2[j][i] + sum;
					}
					matrix_result[k][i] = sum;
					sum = 0;
				}
			}

			printf("\n");
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					printf("%d  ", matrix_result[i][j]);
				}
				printf("\n");
			}
			break;

		case 'a':		// 행렬의 덧셈
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					matrix_result[i][j] = matrix1[i][j] + matrix2[i][j];
				}
			}
			printf("\n");
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					printf("%d  ", matrix_result[i][j]);
				}
				printf("\n");
			}
			break;

		case'd':		// 행렬의 뺄셈
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					matrix_result[i][j] = matrix1[i][j] - matrix2[i][j];
				}
			}
			printf("\n");
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					printf("%d  ", matrix_result[i][j]);
				}
				printf("\n");
			}
			break;

		case 'r':		// 행렬식
			det1 = determinant(matrix1, SIZE);
			printf("1번 행렬의 행렬식 = %d\n", det1);
			det2 = determinant(matrix2, SIZE);
			printf("2번 행렬의 행렬식 = %d\n", det2);

			break;

		case 't':
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					printf("%d  ", matrix1[j][i]);
				}
				printf("\n");
			}
			printf("\n행렬식 = %d\n", det1);
			printf("\n");
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					printf("%d  ", matrix2[j][i]);
				}
				printf("\n");
			}
			printf("\n행렬식 = %d\n", det2);
			break;

		case 'e':
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (count == 0 && matrix1[i][j] % 2 == 0) {
						printf("%3d", matrix1[i][j]);
					}
					else if (count == 1 && matrix1[i][j] % 2 != 0) {
						printf("%3d", matrix1[i][j]);
					}
					else if (count == 2) {
						printf("%3d", matrix1[i][j]);
					}
					else {
						printf("   ");
					}

				}
				printf("\n");
			}
			printf("\n");
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (count == 0 && matrix2[i][j] % 2 == 0) {
						printf("%3d", matrix2[i][j]);
					}
					else if (count == 1 && matrix2[i][j] % 2 != 0) {
						printf("%3d", matrix2[i][j]);
					}
					else if (count == 2) {
						printf("%3d", matrix2[i][j]);
					}
					else {
						printf("   ");
					}

				}
				printf("\n");
			}

			if (count == 2) {
				count = 0;
			}
			else {
				count++;
			}
			break;

		case 's':
			matrix_rand = 0;
			break;

		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			Num_multiplyMatirix(matrix1, command);
			Num_multiplyMatirix(matrix2, command);
			break;

		case 'q':
			printf("\n프로그램 종료");
			exit(0);
			break;
		}
	}

	return 0;
}

void minor_matrix(int matrix[SIZE][SIZE], int temp[SIZE][SIZE], int row, int size)
{
	int a = 0, b = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i != 0 && j != row) {
				temp[a][b++] = matrix[i][j];

				if (b == size - 1) {
					b = 0;
					a++;
				}
			}
		}
	}
}

int determinant(int matrix[SIZE][SIZE], int size)
{
	int det = 0;
	int temp[SIZE][SIZE];
	int sign = 1;

	for (int i = 0; i < size; i++) {
		minor_matrix(matrix, temp, i, size);

		det += sign * matrix[0][i] * determinant(temp, size - 1);

		sign = sign * -1;
	}

	return det;
}

void Num_multiplyMatirix(int matrix[SIZE][SIZE], char multiplier)
{
	int num = multiplier - '0';
	int temp[SIZE][SIZE];

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			temp[i][j] = matrix[i][j] * num;
		}
	}

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%3d", temp[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}