#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 4

void main() {
	int matrix1[SIZE][SIZE], matrix2[SIZE][SIZE];
	int matrix_result[SIZE][SIZE];
	int rand_num = 0, counting_2 = 0;
	char command;
	srand(time(NULL));

	// matrix 1
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			rand_num = rand() % 3;
			if (rand_num == 2 && counting_2 < 2) {
				matrix1[i][j] = rand_num;
				counting_2++;
			}
			else if(rand_num!=2){
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

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%d  ", matrix1[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%d  ", matrix2[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	scanf("%c", &command);

	int sum = 0;
	switch (command)
	{
	case 'm':
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				sum = matrix1[0][j] * matrix2[j][i] + sum;
			}
			matrix_result[0][i] = sum;
			sum = 0;
		}
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				sum = matrix1[1][j] * matrix2[j][i] + sum;
			}
			matrix_result[1][i] = sum;
			sum = 0;
		}
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				sum = matrix1[2][j] * matrix2[j][i] + sum;
			}
			matrix_result[2][i] = sum;
			sum = 0;
		}
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				sum = matrix1[3][j] * matrix2[j][i] + sum;
			}
			matrix_result[3][i] = sum;
			sum = 0;
		}
		printf("\n");
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				printf("%d  ", matrix_result[i][j]);
			}
			printf("\n");
		}
		break;
	case 'a':
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
	case'd':
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
	case 'r':
		break;
	case 't':
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				printf("%d  ", matrix1[j][i]);
			}
			printf("\n");
		}
		printf("\n");
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				printf("%d  ", matrix2[j][i]);
			}
			printf("\n");
		}
		break;
	case 'e':
		break;
	}
}