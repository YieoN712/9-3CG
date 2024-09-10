#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <stdlib.h> 

void highlight_upper(FILE* file);
void print_original(FILE* file);
void set_color(unsigned short color);
void reset_file_pointer(FILE* file);
void reverse_sentence(FILE* file);
void reverse_word(FILE* file);
void insert_sign(FILE* file);
void words_count_line(FILE* file);
int count_words(const char* line);
int word_match(const char* word, const char* search_word);
void highlight_search_word(FILE* file, const char* search_word);
void asc_order(FILE* file); void desc_order(FILE* file);
void replace_char(FILE* file, char old_char, char new_char);

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

	char search_word[50];
	char old_char, new_char;

	while (1) {
		printf("\ncommand: ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'c':
			if (con.c == 0) {
				reset_file_pointer(file);
				highlight_upper(file);
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

		case 'f':
			if (con.f == 0) {
				reset_file_pointer(file);
				reverse_word(file);
				con.f++;
			}
			else {
				reset_file_pointer(file);
				print_original(file);
				con.f = 0;
			}
			break;

		case 'e':
			if (con.e == 0) {
				reset_file_pointer(file);
				insert_sign(file);
				con.e++;
			}
			else {
				reset_file_pointer(file);
				print_original(file);
				con.e = 0;
			}
			break;

		case 'g':
			if (con.g == 0) {
				printf("바꿀 문자를 입력하세요: ");
				scanf(" %c", &old_char);

				printf("새로 입력할 문자를 입력하세요: ");
				scanf(" %c", &new_char);
				reset_file_pointer(file);
				replace_char(file, old_char, new_char);
				con.g++;
			}
			else {
				reset_file_pointer(file);
				print_original(file);
				con.g = 0;
			}
			break;

		case 'h':
			reset_file_pointer(file);
			words_count_line(file);
			break;

		case 'r':
			if (con.r == 2) {
				reset_file_pointer(file);
				words_count_line(file);
				con.r = 0;
			}
			else if(con.r == 1){
				reset_file_pointer(file);
				asc_order(file);
				con.r++;
			}
			else {
				reset_file_pointer(file);
				desc_order(file);
				con.r++;
			}
			break;

		case's':
			printf("searching : ");
			scanf(" %s", search_word);
			reset_file_pointer(file);
			highlight_search_word(file, search_word);
			break;

		case 'q':
			printf("program exit\n");
			exit(0);
			break;

		default:
			printf("worng command\n");
			break;
		}
	}

	fclose(file);
	return 0;
}

// 대문자로 시작하는 단어 강조하기
void highlight_upper(FILE* file)
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
// reset
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
// 거꾸로 출력(단어)
void reverse_word(FILE* file)
{
	char line[500];

	while (fgets(line, sizeof(line), file) != NULL) {
		int len = strlen(line);
		int start = 0;

		for (int i = 0; i <= len; i++) {
			if (line[i] == ' ' || line[i] == '\n' || line[i] == '\0') {
				for (int j = i - 1; j >= start; j--) {
					putchar(line[j]);
				}

				if (line[i] != '\0') {
					putchar(line[i]);
				}
				start = i + 1;
			}
		}
	}

	printf("\n");
}
// 문자사이에 @@삽입
void insert_sign(FILE* file)
{
	char line[500];
	char modified_line[1000];

	while (fgets(line, sizeof(line), file) != NULL) {
		int len = strlen(line);
		int index = 0;

		for (int i = 0; i < len; i++) {
			modified_line[index++] = line[i];

			if ((i + 1) % 3 == 0 && line[i] != ' ' && line[i] != '\n') {
				modified_line[index++] = '@';
				modified_line[index++] = '@';
			}
		}
		modified_line[index] = '\0';

		printf("%s", modified_line);
	}
}
// 특정 문자 변경
void replace_char(FILE* file, char old_char, char new_char) {
	char line[500];

	while (fgets(line, sizeof(line), file) != NULL) {
		for (int i = 0; line[i] != '\0'; i++) {
			if (line[i] == old_char) {
				line[i] = new_char;
			}
		}
		printf("%s", line);
	}
}
// 단어 개수 출력
void words_count_line(FILE* file) {
	char line[500];

	while (fgets(line, sizeof(line), file) != NULL) {
		int word_count = count_words(line);

		printf("%s(word : %d)\n", line, word_count);
	}
}
int count_words(const char* line) {
	int count = 0;
	int in_word = 0;

	for (int i = 0; line[i] != '\0'; i++) {
		if (isalnum(line[i])) {
			if (!in_word) {
				in_word = 1;
				count++;
			}
		}
		else {
			in_word = 0;
		}
	}
	return count;
}
// 입력 단어 강조
void highlight_search_word(FILE* file, const char* search_word) {
	char line[500];
	int word_len = strlen(search_word);
	int match_count = 0;

	while (fgets(line, sizeof(line), file) != NULL) {
		int i = 0;
		int len = strlen(line);
		char word[500];
		int word_idx = 0;

		// 각 단어 확인
		while (i < len) {
			if (isalnum(line[i])) {
				word[word_idx++] = line[i];
			}
			else {
				if (word_idx > 0) {
					word[word_idx] = '\0';
					if (word_match(word, search_word)) {
						set_color(12);
						printf("%s", word);
						set_color(7);
						match_count++;
					}
					else {
						printf("%s", word);
					}
					word_idx = 0;
				}
				printf("%c", line[i]);
			}
			i++;
		}

		if (word_idx > 0) {
			word[word_idx] = '\0';
			if (word_match(word, search_word)) {
				set_color(12);
				printf("%s", word);
				set_color(7);
				match_count++;
			}
			else {
				printf("%s", word);
			}
		}
	}

	printf("\n총 '%s' 단어의 개수: %d\n", search_word, match_count);
}
// 단어 비교 함수 (대소문자 구분 없음)
int word_match(const char* word, const char* search_word) {
	while (*word && *search_word) {
		if (tolower(*word) != tolower(*search_word)) {
			return 0;
		}
		word++;
		search_word++;
	}
	return *word == '\0' && *search_word == '\0';
}
// 단어가 많은 문장부터 출력
void asc_order(FILE* file)
{
	char lines[50][500];
	int word_counts[50];
	int num_lines = 0;

	while (fgets(lines[num_lines], sizeof(lines[num_lines]), file) != NULL && num_lines < 50) {
		word_counts[num_lines] = count_words(lines[num_lines]);
		num_lines++;
	}

	for (int i = 0; i < num_lines - 1; i++) {
		for (int j = 0; j < num_lines - 1 - i; j++) {
			if (word_counts[j] < word_counts[j + 1]) {
				// 문장 교환
				char temp_line[500];
				int temp_count = word_counts[j];
				word_counts[j] = word_counts[j + 1];
				word_counts[j + 1] = temp_count;

				strcpy(temp_line, lines[j]);
				strcpy(lines[j], lines[j + 1]);
				strcpy(lines[j + 1], temp_line);
			}
		}
	}

	for (int i = 0; i < num_lines; i++) {
		printf("%s(word : %d)\n", lines[i], word_counts[i]);
	}
}
void desc_order(FILE* file)
{
	char lines[50][500];
	int word_counts[50];
	int num_lines = 0;

	while (fgets(lines[num_lines], sizeof(lines[num_lines]), file) != NULL && num_lines < 50) {
		word_counts[num_lines] = count_words(lines[num_lines]);
		num_lines++;
	}

	for (int i = 0; i < num_lines - 1; i++) {
		for (int j = 0; j < num_lines - 1 - i; j++) {
			if (word_counts[j] < word_counts[j + 1]) {
				// 문장 교환
				char temp_line[500];
				int temp_count = word_counts[j];
				word_counts[j] = word_counts[j + 1];
				word_counts[j + 1] = temp_count;

				strcpy(temp_line, lines[j]);
				strcpy(lines[j], lines[j + 1]);
				strcpy(lines[j + 1], temp_line);
			}
		}
	}

	for (int i = num_lines - 1; i >= 0; i--) {
		printf("%s(word : %d)\n", lines[i], word_counts[i]);
	}
}