#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "calc.h"

int len;

//	пользовательский ввод да/нет
char y_or_n(char* string) 
{	
	char c;
	O("%s [y/n]  ", string);
	scanf("%c", &c);
	getchar();
	if (c == 'y')
		R 1;
	R 0;
}

//	количество ребер в одном измерении n-параллелепипеда
int edges_in_one_dim(int n)
{
	R pow(2, n - 1);
}

//	вывод результатов горизонтальной таблицей
void hor_tbl(rod* arr)
{
	int k = edges_in_one_dim(len);

	O("\n\n\t\t");
	DO(len, O(""VER"\tL%d\t", i + 1))

	BAR("\n\t"HOR"", ""HOR"");

	DO(len, BAR(""CRS"", ""HOR"")BAR(""HOR"", ""HOR""));

	O("\n\tfound\t");
	DO(len, O(""VER" \x1B[%dm     %d\x1B[0m\t", arr[i].col, arr[i].num));

	O("\n\tlost\t");
	DO(len, {O(""VER"      "); k - arr[i].num ? O("%d\t", k = arr[i].num) : O("---\t");})			
	BAR("\n\t"HOR"", ""HOR"");
	DO(len, BAR(""CLP"", ""HOR"")BAR(""HOR"", ""HOR""));
	free(arr);
}

//	вывод результатов вертикальной таблицой
void ver_tbl(rod* arr)
{
	int k = edges_in_one_dim(len);

	O("\n\n\t\t"VER"     found\t"VER"     lost\n");
	BAR("\t"HOR"", ""HOR"");

	DO(2, BAR(""CRS"", ""HOR"")BAR(""HOR"", ""HOR""));

	O("\n");


	DO(len, {	O("\t    \x1B[%dmL%d\t\x1B[0m"VER"\t\x1B[%dm%d\t\x1B[0m"VER"\t\x1B[0m", 
				(arr[i].col),(i+1),(arr[i].col),(arr[i].num));
				(k-arr[i].num)	?	O("%d\n",(k-arr[i].num))	:	O("---\n");})

	O("\n");
	free(arr);
}

// 	возвращает массив длиной k найденных длин
//	составляет массив с учетом большинства возможных деффектов ввода
rod* input()
{
	int i;
	rod *arr;
	char c = ' ';
	arr = malloc(SZ(rod) * len);

	for (i = 0; i < len; i++) {
		scanf("%d", &(arr[i].num));
		
		arr[i].col = (i < 7 || i > 9) ? i : i + 3;		//<	colour magic ^***^
		arr[i].col += 31;

		if (arr[i].num < 1) {
			arr = realloc(arr, SZ(rod) * (--len));
			i--;
		}
	}

	while (c != '\n' && c)
		scanf("%c", &c);

	R arr;
}

//	проверка на превышение лимита количества ребер одной плоскости
//	возвращает номер самого большого элемента массива, если было превышение
//	если превышения не было, то -1
int check(rod *arr, int max)
{
	int j = -1, a = 0;
	for (int i = 0; i < len; i++)
		if (arr[i].num > max && arr[i].num > a) {  
			a = arr[i].num; 
			j = i;
		}
		
	R j;
}

//	вычисление минимальной размерности пространства
int compute(rod *arr)
{
	int k, max_edge, m_e_ = 0, i;

	if (!len) {
		O("\t\e[31mERROR:\e[0m incorrect input\n");
		free(arr);
		R 0;
	}

	max_edge = edges_in_one_dim(len);
	k = check(arr, max_edge);

	if (k == -1) {
		if (y_or_n("\tvertical output [else: horizontal]?"))
			ver_tbl(arr);
		else 
			hor_tbl(arr);
		R len;
	} else {
		arr = realloc(arr, SZ(rod) * ++len);

		for (i = 0; m_e_ <= arr[k].num/2; i++) 
			m_e_ = edges_in_one_dim(len + i);

		// 	выбирает самое близкое значение к arr[k].num/2 из 
		//	двух ближайших лимитов ребер пространств N и N-1
		m_e_ /= ((m_e_*3/2)>= arr[k].num) ? 2 : 1;

		//	от самого большого элемента вычитается найденный 
		// 	ближайший лимит ребер. сам лимит записывается в 
		//	в новый элемент массива. туда же и записывается 
		//	родительский цвет
		arr[len - 1].num = m_e_;
		arr[k].num -= m_e_;
		arr[len - 1].col = arr[k].col;

		R compute(arr);
	}
}

int main()
{
	loop: 
	O("\n\tenter number of lengths and number of edges of each length\n\n\t");
	scanf("%d", &len);

	if (len < 1) {
		O("\e[31mERROR:\e[0m incorrect input\n");
		R 1;
	}

	O("\n\tN - %d\n\t\n", compute(input()));
	if (y_or_n("\tfind another dimension?"))
		goto loop;
	R 0;
}







