#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX 20

void print_list(struct Point list[]);
double squared_point(struct Point point);
void far_point(struct Point list[], int num);
void near_point(struct Point list[], int num);
void sort_point_asc(struct Point list[], struct Point l_copy[], int num);
void sort_point_des(struct Point list[], struct Point l_copy[], int num);

struct Point {
	int x;
	int y;
	int z;
	bool is_empty;
};

int main()
{
	struct Point points[MAX] = { {0, 0, 0} };
	int point_num = 0, point_num_last = 0;
	int x, y, z;
	char command;

	for (int i = 0; i < MAX; i++) {
		points[i].is_empty = true;
	}

	int count_s = 0;
	int list_len = 0;
	struct Point p_copy[MAX] = { {0, 0, 0} };

	for (int i = 0; i < MAX; i++) {
		p_copy[i].is_empty = true;
	}

	while (1) {
		printf("command: ");
		scanf(" %c", &command);

		switch (command)
		{
		case'+':
			printf("point: ");
			scanf("%d %d %d", &x, &y, &z);

			if (point_num >= MAX) {
				printf("FULL\n");
				return;
			}

			points[point_num].x = x;
			points[point_num].y = y;
			points[point_num].z = z;
			points[point_num].is_empty = false;

			point_num++;

			print_list(points);
			break;

		case'-':
			if (point_num == 0) {
				printf("EMPTY\n");
				return;
			}

			points[point_num - 1].is_empty = true;
			point_num--;

			print_list(points);
			break;

		case 'e':
			printf("point: ");
			scanf("%d %d %d", &x, &y, &z);

			if (point_num >= MAX) {
				printf("FULL\n");
				return;
			}

			for (int i = point_num; i > 0; i--) {
				points[i] = points[i - 1];
			}

			points[0].x = x;
			points[0].y = y;
			points[0].z = z;
			points[0].is_empty = false;

			if (point_num < MAX) {
				point_num++;
			}

			print_list(points);
			break;

		case 'd':
			if (point_num == 0) {
				printf("EMPTY\n");
				return;
			}

			points[point_num_last].is_empty = true;

			point_num_last++;

			print_list(points);
			break;

		case 'l':
			for (int i = 0; i < MAX; i++) {
				if (!points[i].is_empty) {
					list_len++;
				}
			}

			printf("List length: %d\n", list_len);
			list_len = 0;
			break;

		case 'c':
			for (int i = 0; i < MAX; i++) {
				points[i].is_empty = true;
			}

			point_num = 0;

			print_list(points);
			break;

		case 'm':
			far_point(points, point_num);
			break;

		case 'n':
			near_point(points, point_num);
			break;

		case 'a':
			if (count_s == 1) {
				print_list(points);
				count_s = 0;
			}
			else {
				sort_point_asc(points, p_copy, point_num);
			}
			
			break;

		case 's':
			if (count_s == 1) {
				print_list(points);
				count_s = 0;
			}
			else {
				sort_point_des(points, p_copy, point_num);
				count_s++;
			}
			
			break;

		case 'q':
			printf("program exit\n");
			exit(0);
			break;

		default:
			printf("wrong command\n");
			break;
		}
	}


}

void print_list(struct Point list[]) {
	printf("index |  x  y  z\n");
	printf("-----------------\n");

	for (int i = 9; i >= 0; i--) {
		if (list[i].is_empty) {
			printf("%5d |\n", i);
		}
		else {
			printf("%5d | %2d %2d %2d\n", i, list[i].x, list[i].y, list[i].z);
		}
	}

	printf("\n");
}

double squared_point(struct Point point) {
	return point.x * point.x + point.y * point.y + point.z * point.z;
}

void far_point(struct Point list[], int num) {
	if (num == 0) {
		printf("EMPTY\n");
		return;
	}

	double max_distance = -1.0;
	int far_index = 0;

	for (int i = 0; i < num; i++) {
		if (!list[i].is_empty) {
			double distance = squared_point(list[i]);

			if (distance > max_distance) {
				max_distance = distance;
				far_index = i;
			}
		}
	}

	printf("Farthest Point: (%d, %d, %d)\n", list[far_index].x, list[far_index].y, list[far_index].z);
}

void near_point(struct Point list[], int num) {
	if (num == 0) {
		printf("EMPTY\n");
		return;
	}

	double min_distance = -1.0;
	int near_index = 0;

	for (int i = 0; i < num; i++) {
		if (!list[i].is_empty) {
			double distance = squared_point(list[i]);

			if (distance > min_distance) {
				min_distance = distance;
				near_index = i;
			}
		}
	}

	printf("Farthest Point: (%d, %d, %d)\n", list[near_index].x, list[near_index].y, list[near_index].z);
}

void sort_point_asc(struct Point list[], struct Point l_copy[], int num) {
	struct Point temp;
	int valid_p = 0;

	for (int i = 0; i < num; i++) {
		if (!list[i].is_empty) {
			l_copy[valid_p] = list[i];
			valid_p++;
		}
	}

	for (int i = 0; i < valid_p - 1; i++) {
		for (int j = i + 1; j < valid_p; j++) {
			if (squared_point(l_copy[i]) > squared_point(l_copy[j])) {
				temp = l_copy[i];
				l_copy[i] = l_copy[j];
				l_copy[j] = temp;
			}
		}
	}

	print_list(l_copy);
}

void sort_point_des(struct Point list[], struct Point l_copy[], int num) {
	struct Point temp;
	int valid_p = 0;

	for (int i = 0; i < num; i++) {
		if (!list[i].is_empty) {
			l_copy[valid_p] = list[i];
			valid_p++;
		}
	}

	for (int i = 0; i < valid_p - 1; i++) {
		for (int j = i + 1; j < valid_p; j++) {
			if (squared_point(l_copy[i]) < squared_point(l_copy[j])) {
				temp = l_copy[i];
				l_copy[i] = l_copy[j];
				l_copy[j] = temp;
			}
		}
	}

	print_list(l_copy);
}