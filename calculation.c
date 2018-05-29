#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#define DO(n,x) {int i=0,_i=(n);for(;i<_i;++i){x;}}
#define BAR(s1, s2) printf("%s%s%s%s%s%s%s%s", (s1), (s2), (s2), (s2), (s2), (s2), (s2), (s2));
#define LINE(x, y, z) (z)?printf("\t   L%d\t\u2503\t%d\t\u2503\t%d\n",(x),(y),(z)):printf("\t   L%d\t\u2503\t%d\t\u2503\t---\n",(x),(y));

int len;

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
int one_line_edge()
{
	return pow(2, len - 1);
}

void horizontal_table(int* array)
{
	int k = one_line_edge();

	printf("\n\t\t");
	DO(len, printf("\u2503  L%d\t", i))

	printf("\n\t");
	BAR("\u2501", "\u2501");
	DO(len, BAR("\u254b", "\u2501"));

	printf("\n\tfound\t");
	DO(len, printf("\u2503  %d\t", array[i]);)

	printf("\n\tlost\t");
	DO(len, k - array[i] ? printf("\u2503  %d\t", k - array[i]) : printf("\u2503  -\t");)

	printf("\n\t");
	BAR("\u2501", "\u2501");
	DO(len, BAR("\u253b", "\u2501"));

	free(array);
}

void vertical_table(int* array)
{
	int k = one_line_edge();

	printf("\n\t\t\u2503\tfound\t\u2503\tlost\n");
	BAR("\t\u2501", "\u2501");

	DO(2, BAR("\u254b", "\u2501")BAR("\u2501", "\u2501"));

	printf("\n");
	DO(len, LINE(i, array[i], k - array[i]));
	printf("\n");
	free(array);
}

int* get_info()
{
	int *array, i, j;
	array = malloc(sizeof(int) * len);

	for (i = 0; i < len; i++) {
		scanf("%d", &array[i]);
		if (array[i] < 1) {
			array = realloc(array, sizeof(int) * (--len));
			i--;
		}
	}
	getchar();
	return array;
}

//	проверка на превышение лимита количества ребер одной плоскости
int check(int *array, int max)
{
	for (int i = 0; i < len; i++)
		if (array[i] > max)
			return ++i;

	return 0;
}

//	вычисление минимальной размерности пространства
int calc_dim(int *array)
{
	int num, k, max_edge;

	if (!len) {
		printf("\t\e[31mERROR:\e[0m incorrect input\n");
		return 0;
	}

	max_edge = one_line_edge();

	num = check(array, max_edge);

	if (!num) {
		if (yes_or_no("\tvertical output [else: horizontal]?"))
			vertical_table(array);
		else 
			horizontal_table(array);

		return len;
	}
	else {
		num--;
		array = realloc(array, sizeof(int) * ++len);
		array[len - 1] = array[num] / 2 + array[num] % 2;
		array[num] /= 2;
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







