#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#define DO(n,x) {int i=0,_i=(n);for(;i<_i;++i){x;}}
#define BAR(s1,s2) {printf("%s",(s1));DO(7,printf("%s",(s2)));}

#define LINE(x, y, z) (z)?printf("\t    \x1B[%dmL%d\t\x1B[0m\u2503\t\x1B[%dm%d\t\x1B[0m\u2503\t\x1B[0m%d\n",(y.col),(x+1),(y.col),(y.num),(z)):printf("\t    \x1B[%dmL%d\t\x1B[0m\u2503\t\x1B[%dm%d\t\x1B[0m\u2503\t\x1B[0m---\n",(y.col),(x+1),(y.col),(y.num));

typedef struct Rod {
	int col;
	int num;
} rod;

int len;

int find_max(rod* arr)
{
	int _i = 0, i;
	for (i = 0; i < len; i++) {
		if (arr[i].num > arr[_i].num)
			_i = i;
	}
	return _i;
}

char yes_or_no(char* string) 
{	
	char c;
	printf("%s [y/n]  ", string);
	scanf("%c", &c);
	getchar();
	if (c == 'y')
		return 1;
	return 0;
}

//	количество ребер в одной плоскости
int one_line_edge(int n)
{
	return pow(2, n - 1);
}

void horizontal_table(rod* array)
{
	int k = one_line_edge(len);

	printf("\n\n\t\t");
	DO(len, printf("\u2503\tL%d\t", i + 1))

	BAR("\n\t\u2501", "\u2501");

	DO(len, BAR("\u254b", "\u2501")BAR("\u2501", "\u2501"));

	// DO(len, BAR("\u254b", "\u2501"));

	printf("\n\tfound\t");
	DO(len, printf("\u2503 \x1B[%dm     %d\x1B[0m\t", array[i].col, array[i].num));

	printf("\n\tlost\t");
	DO(len, k - array[i].num ? 	printf("\u2503      %d\t", k - array[i].num) 	: 		printf("\u2503      -\t");)

	BAR("\n\t\u2501", "\u2501");
	DO(len, BAR("\u253b", "\u2501")BAR("\u2501", "\u2501"));

	free(array);
}

void vertical_table(rod* array)
{
	int k = one_line_edge(len);

	printf("\n\n\t\t\u2503     found\t\u2503     lost\n");
	BAR("\t\u2501", "\u2501");

	DO(2, BAR("\u254b", "\u2501")BAR("\u2501", "\u2501"));

	printf("\n");
	DO(len, LINE(i, array[i], k - array[i].num));
	printf("\n");
	free(array);
}

rod* get_info()
{
	int i;
	rod *array;
	char c = ' ';
	array = malloc(sizeof(rod) * len);

	for (i = 0; i < len; i++) {
		scanf("%d", &(array[i].num));
		
		array[i].col = (i < 7 || i > 9) ? i : i + 3;		//<	colour magic ^***^
		array[i].col += 31;

		if (array[i].num < 1) {
			array = realloc(array, sizeof(rod) * (--len));
			i--;
		}
	}

	while (c != '\n' && c)
		scanf("%c", &c);

	return array;
}

//	проверка на превышение лимита количества ребер одной плоскости
int check(rod *array, int max)
{
	for (int i = 0; i < len; i++)
		if (array[i].num > max)
			return 0;

	return 1;
}

//	вычисление минимальной размерности пространства
int calc_dim(rod *array)
{
	int n, k, max_edge, m_e_ = 0, i;

	if (!len) {
		printf("\t\e[31mERROR:\e[0m incorrect input\n");
		return 0;
	}

	max_edge = one_line_edge(len);

	if (check(array, max_edge)) {
		if (yes_or_no("\tvertical output [else: horizontal]?"))
			vertical_table(array);
		else 
			horizontal_table(array);

		return len;
	}
	else {
		n = find_max(array);
		array = realloc(array, sizeof(rod) * ++len);

		for (i = 0; m_e_ <= array[n].num/2; i++) 
			m_e_ = one_line_edge(len + i);
	
		m_e_ /= 2;
		array[len - 1].num = m_e_;
		array[len - 1].col = array[n].col;

		array[n].num -= m_e_;


		return calc_dim(array);
	}
	return 0;
}

int main()
{
	loop: 
	printf("\n\tenter number of lengths and number of edges of each length\n\n\t");
	scanf("%d", &len);

	if (len < 1) {
		printf("\e[31mERROR:\e[0m incorrect input\n");
		return 1;
	}

	printf("\n\tN - %d\n\t\n", calc_dim(get_info()));
	if (yes_or_no("\tfind another dimension?"))
		goto loop;
	return 0;
}







