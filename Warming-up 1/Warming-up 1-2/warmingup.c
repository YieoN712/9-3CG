#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <stdlib.h> 

void highlight_words(FILE* file);
void print_original(FILE* file);
void set_color(unsigned short color);
void reset_file_pointer(FILE* file);
void reverse_sentence(FILE* file);

struct Confirm {
	int c; int d; int e; int f; int g; int r;
};

int main() {
	char filename[100];
	FILE* file;
	char command;
	struct Confirm con = { 0 };

	printf("file name : ");
	scanf("%s", filename);

	file = fopen(filename, "r");
	if (file == NULL) {
		printf("파일을 열 수 없습니다.\n");
		return 1;
	}

	print_original(file);

	

	while (1) {
		printf("command: ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'c':
			if (con.c == 0) {
				reset_file_pointer(file);
				highlight_words(file);
				con.c++;
			}
			else {
				reset_file_pointer(file);
				print_original(file);
				con.c = 0;
			}
			break;

		case 'd':
			if (con.d == 0) {
				reset_file_pointer(file);
				reverse_sentence(file);
				con.d++;
			}
			else {
				reset_file_pointer(file);
				print_original(file);
				con.d = 0;
			}
			break;

		case 'q':
			printf("프로그램 종료\n");
			exit(0);
			break;
		}
	}

	fclose(file);
	return 0;
}

// 대문자로 시작하는 단어 강조하기
void highlight_words(FILE* file)
{
	int countUper = 0;
	int in_word = 0, word_index = 0;
	char word[100];
	char ch;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while ((ch = fgetc(file)) != EOF) {
		if (isalpha(ch)) {
			if (!in_word) {
				in_word = 1;
				word_index = 0;

				if (isupper(ch)) {
					set_color(12);
					countUper++;
				}
				else {
					set_color(7);
				}
			}
			word[word_index++] = ch;
		}
		else {
			if (in_word) {
				in_word = 0;
				word[word_index] = '\0';
				printf("%s", word);
				set_color(7);
			}

			if (ch == '\n') {
				printf("%4d", countUper);
				countUper = 0;
			}

			putchar(ch);
		}
	}

	set_color(7);
	printf("%4d\n", countUper);
}
// 원본 출력
void print_original(FILE* file)
{
	char ch;

	while ((ch = fgetc(file)) != EOF) {
		putchar(ch);
	}

	printf("\n");
}
// 색 설정
void set_color(unsigned short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void reset_file_pointer(FILE* file)
{
	fseek(file, 0, SEEK_SET);
}
// 거꾸로 출력(문장)
void reverse_sentence(FILE* file)
{
	char line[500];
	
	while (fgets(line, sizeof(line), file) != NULL) {
		int len = strlen(line);

		if (line[len - 1] == '\n') {
			len--;
		}

		for (int i = len - 1; i >= 0; i--) {
			putchar(line[i]);
		}
		putchar('\n');
	}
}