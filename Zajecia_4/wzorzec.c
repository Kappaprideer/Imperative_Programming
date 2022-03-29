
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// consider chars from [FIRST_CHAR, LAST_CHAR)
#define FIRST_CHAR 33
#define LAST_CHAR 127
#define MAX_CHARS (LAST_CHAR - FIRST_CHAR)
#define MAX_DIGRAMS (LAST_CHAR - FIRST_CHAR) * (LAST_CHAR - FIRST_CHAR)

#define NEWLINE '\n'
#define IN_WORD 1

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2

#define TEST 0   // 1 dla testowania, 0 dla automatycznej oceny

int count[MAX_DIGRAMS] = { 0 };

int cmp (const void *a, const void *b) {
	int va = *(int*)a;
	int vb = *(int*)b;
	if (count[va] == count[vb]) return va - vb; // sort alphabetically if counts equal
	return count[vb] - count[va];
}

int cmp_di (const void *a, const void *b) {
	int va = *(int*)a;
	int vb = *(int*)b;
	// sort according to second char if counts and the first char equal
	if (count[va] == count[vb] && va / MAX_CHARS == vb / MAX_CHARS) return va % MAX_CHARS - vb % MAX_CHARS;
	// sort according to first char if counts equal
	if (count[va] == count[vb]) return va / MAX_CHARS - vb / MAX_CHARS;
	return count[vb] - count[va];
}

void wc(int *nl, int *nw, int *nc, FILE *stream) {

    *nl = 0;
    *nw = 0;
    *nc = 0;
    int state = 0;
    int c;
	while ((c = getc(stream)) != EOF) {
		++(*nc);
		if (c == NEWLINE) ++(*nl);
		if (isspace(c)) {
			if(state & IN_WORD) state &= ~IN_WORD; // end of word
		} else if (!(state & IN_WORD)) {
			state = IN_WORD;
			++(*nw);
		}
	}
}

void char_count(int char_no, int *n_char, int *cnt, FILE *stream) {
	int indices[MAX_CHARS];
	for (int i = 0; i < MAX_CHARS; ++i) {
		indices[i] = i;
	}

	int c;
	while ((c = getc(stream)) != EOF) {
		if (c >= FIRST_CHAR && c < LAST_CHAR) ++count[c - FIRST_CHAR];
	}

	qsort(indices, MAX_CHARS, sizeof(int), cmp);

	*n_char = indices[char_no-1] + FIRST_CHAR;
	*cnt = count[indices[char_no-1]];

//	for (int i = 0; i < char_no; ++i) {
//		printf("'%c' %4d\n", indices[i] + FIRST_CHAR, count[indices[i]]);
//	}
}

void digram_count(int digram_no, int digram[], FILE *stream) {
	int indices[MAX_DIGRAMS];
	for (int i = 0; i < MAX_DIGRAMS; ++i) {
		indices[i] = i;
	}

	int c, c_prev = getc(stream);
	while ((c = getc(stream)) != EOF) {
		if (c < FIRST_CHAR || c >= LAST_CHAR || c_prev < FIRST_CHAR || c_prev >= LAST_CHAR) {
			c_prev = c;
			continue;
		}
		int index = (c_prev - FIRST_CHAR) * MAX_CHARS + c - FIRST_CHAR;
//	    printf("%c %8d\n", c, index);
		++count[index];
		c_prev = c;
	}

	qsort(indices, MAX_DIGRAMS, sizeof(int), cmp_di);
	digram[0] = indices[digram_no-1] / MAX_CHARS + FIRST_CHAR;
	digram[1] = indices[digram_no-1] % MAX_CHARS + FIRST_CHAR;
	digram[2] = count[indices[digram_no-1]];

//	for (int i = 0; i < MAX_DIGRAMS; ++i) {
//	for (int i = 0; i < digram_no; ++i) {
//		if (count[indices[i]]) {
//			int first = indices[i] / MAX_CHARS;
//			int second = indices[i] % MAX_CHARS;
//			printf("'%c%c' %4d\n", first + FIRST_CHAR,
//			       second + FIRST_CHAR, count[indices[i]]);
//		}
//	}
}


void find_comments(int *line_comment_counter, int *block_comment_counter, FILE *stream) {
	int c, c_next;
	*line_comment_counter = 0;
	*block_comment_counter = 0;
	int state = 0;

	while ((c = getc(stream)) != EOF) {
		switch (state) {

			case IN_LINE_COMMENT:
				if (c == '\n') {
					state = 0; // end of line comment
				}
				break;

			case IN_BLOCK_COMMENT:
				if (c != '*') break;
				c_next = getc(stream);
				if (c_next == '/') {
					state = 0; // end of block comment
				} else {
					ungetc(c_next, stream);
				}
				break;

			default:
				if (c != '/') break;
				c_next = getc(stream);
				if (c_next == '/') {
					state = IN_LINE_COMMENT; // line comment begins
					++*line_comment_counter;
					break;
				}
				if (c_next == '*') {
					state = IN_BLOCK_COMMENT; // block comment begins
					++*block_comment_counter;
					break;
				}
				ungetc(c_next, stream);
				break;
		}
	}
}

#define MAX_LINE 128

int read_line() {
	char line[MAX_LINE];
	int n;

	fgets (line, MAX_LINE, stdin); // to get the whole line
	sscanf (line, "%d", &n);
	return n;
}

int main(void) {
	int to_do;
	int nl, nw, nc, char_no, n_char, cnt;
	int line_comment_counter, block_comment_counter;
	int digram[3];

	char file_name[40];
	FILE *stream;

	if(TEST) printf("Wpisz nr zadania ");
	scanf ("%d", &to_do);
    if(TEST)  stream = stdin;
    else {
        scanf("%s",file_name);
        stream = fopen(file_name,"r");
        if(stream == NULL) {
            printf("fopen failed\n");
            return -1;
        }
    }

//	to_do = read_line();
	switch (to_do) {
		case 1: // wc()
			wc (&nl, &nw, &nc, stream);
			printf("%d %d %d\n", nl, nw, nc);
			break;
		case 2: // char_count()
//			char_no = read_line();
            if(TEST) printf("Wpisz numer znaku ");
            scanf("%d",&char_no);
			char_count(char_no, &n_char, &cnt, stream);
			printf("%c %d\n", n_char, cnt);
			break;
		case 3: // digram_count()
//			char_no = read_line();
            if(TEST) printf("Wpisz numer digramu ");
            scanf("%d",&char_no);
			digram_count(char_no, digram, stream);
			printf("%c%c %d\n", digram[0], digram[1], digram[2]);
			break;
		case 4:
			find_comments(&line_comment_counter, &block_comment_counter, stream);
			printf("%d %d\n", block_comment_counter, line_comment_counter);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

