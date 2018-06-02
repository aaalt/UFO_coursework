# Неопознанный летающий объект 

Однажды утром Вася пошёл на пробежку в сторону озера и нашёл К титановых стержней. Как потом выянилось, этой ночью в озеро упал НЛО. НЛО представляет собой каркас N-мерного прямоугольного параллелепипеда из титановых ребер. Все ребра имеют целые длины. Когда НЛО падал, все соединения были разрушены, а сами рёбра упали на озеро: часть из них утонула, а часть осталась на берегу. 
Считая, что те стержни, которые нашел Вася, являются ребрами каркаса НЛО, определите нименьшую возможную размерность пространства, из которого прибыл НЛО.

## Расшифровка

Дан набор ребёр длин `l1`, `Ll`, `Ll`..., `Ll`. `A` ребёр длины `L1`, `B` ребёр длины `L2`, `C` ребёр длины `L3`..., `K` ребёр длины `lk`. Исходя из свойств N-мерных прямоугольных параллелепипедов (хотя прямоугольность особого значения в конкретном случае не имеет) вычислить минимальную размерность параллелепипеда, часть из рёбер которого составляет этот набор.

## Рассуждения и алгоритм

Далее n-мерный параллелепипед будет называться искомый параллелепипед или просто параллелепипед 

Предположим, дан набор из `К` длин. Из определяющего параллепипед свойства, что на каждое измерение имеет только одну длину и противолежащие грани равны (все ребра встречаются в каждой вершине и размерность пространства характеризует количество ребер, выходящих из одной вершины параллелепипеда), очевиден вывод, что минимальная гипотетическая (!), потому что вычисления еще не проводились, размерность параллелепипеда равна `К`

ТАБЛИЦА

Но длина, характеризующая одно изммерение, также может охарактеризовывать и другое. Наглядный пример -- это куб и все его n-мерные разновидности. Также есть правильные трехмерные параллелепипеды, у которых два измерения равны. 

Именно на этом свойстве и построен мой алгоритм решения задачи. 

Также есть замечательная формула [1] для вычисления M-мерных граней в N-мерном параллелепипеде: `L = 2^(N - M)C(M N)`. Так как размерность ребра 1 (отрезок), то формулу можно сократить до `2^(N - 1) * N! / (N - 1)! == 2^(N - 1) * N`.
Если в параллелепипеде содержится `L` ребер, то на каждое измерение приходится `L/N` ребер.
Таким образом формула сокращается просто до `2^(N - 1)`, так как общее количество ребер в параллелепипеде в задаче искать не надо, а нужно только число ребер в одном измерении. 

Основное действие рекурсиивной части алгорима заключается в увеличении массива, а значит и минимальной гипотетической размерности пространства, на один элемент, и разбиении одного набора длины на два, который численно является самым большим. И так пока ни один элемент массива не станет превышать лимит, зависящий от длины массива (минимальной размерности). 

Если проще, то есть набор "куч" и если размер каких-то "куч" превышает дозволеный (вычисляется по формуле, то берется самая большая "куча" и разделяется на две "кучи", одна из которых равна некоему самому близкому значению лимита `L(Ny)`, который находится максимально близко к половине значения "кучи", вторая равна остаточному значению "родительской кучи". 
Обобщенный пример: 
``` 
[x] ... y ... 	(L = 2^(x - 1))
    ~
	y is max && y > L 	//< |2^a - y/2| < |2^(a + 1) - y/2|
	y = 2^a + b 		//< |2^a - y/2| < |2^(a - 1) - y/2|
    ~
    ->
[x + 1] ... 2^a ... b (L = 2^x)
```

Если же просто использовать деление пополам, то могут возникнуть недоразумения из-за гипотетической возможности равности чисел после распределению следующему или позаследующему лимиту вроде:

```
[2] 8 24 (L = 2) -> [3] 8 12 12 (L = 4) -> [4] 8 12 6 6 (L = 8) -> 
    -> [5] 8 6 6 6 6 (L = 16) 
    End: 	N = 5
```
когда в результате `N` должен быть 4:
```
[2] 8 24 (L = 2) -> [3] 8 16 8 (L = 4) -> [4] 8 8 8 8 (L = 8) 
    End: 	N = 4
```

Ещё пример:
```
[2] 32 160 (L = 2) -> [3] 32 80 80 (L = 4) -> [4] 32 80 40 40 (L = 8) ->
    -> [5] 32 40 40 40 40 (L = 16) -> [6] 32 40 40 40 20 20 (L = 32) ->
    -> [7] 32 40 40 20 20 20 20 (L = 64) 
    End: 	N = 7
```
и 
```
[2] 32 160 (L = 2) -> [3] 32 128 32 (L = 4) -> [4] 32 64 64 32 (L = 8) ->
    -> [5] 32 64 32 32 32 (L = 16) -> [6] 32 32 32 32 32 32 (L = 32)
    End: 	N = 6
```

Каждая "куча" представляет из себя набор ребер для одного измерения. Таким образом при каждом распределении добавляется еще одно измерение. 

Если же превышений лимита нет, то выводится количество элементов в массиве, которое является минимальной размерностью пространства. 

Для наглядности оригинальные "кучи" окрашены в индивидуальные цвета. Производные "кучи" окрашиваются в цвет "родительской кучи".

ПРИМЕРЫ 

![ex_1](https://github.com/altnova/UFO/blob/master/ex_1.png)	
![ex_2](https://github.com/altnova/UFO/blob/master/ex_2.png)  

[1]: [Hans Walser: Der n-dimensionale Hyperwürfel](https://www.walser-h-m.ch/hans/Vortraege/Vortrag39_2/Hyperwuerfel.pdf)

