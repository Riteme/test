# 空袭 (airstrike.c/cpp)
时间限制：N/A / 内存限制：1024 MB / 打开`-O2`优化 / 支持C11\C++11

## 题目描述
**这是一道交互题**。
注意本交互库**不提供Pascal支持**。只支持C\C++。

统计学家Lunk所居住的城市遭到的软斯兰国的空袭，弄得Lunk心神不定。
然而伟大的统计学家怎么会就因为空袭而四处避难呢？Lunk决定弄出个大新闻。
由于各种原因，Lunk所居住的城市的市区的形状十分奇怪。Lunk将其大致的轮廓画在地图上，形成了一个**多边形的形状**。软斯兰国的飞机每丢下一枚炸弹，Lunk就会马上观测到炸弹的位置，并将其画在地图上。但是，他所想要统计的只是智障的软斯兰国**有多少枚炸弹攻击到了市区**。
于是Lunk放弃了在地图上画下每一个炸弹的位置，而是转而在地下室里直接统计。

现在它所需要的就是一个能帮他统计的程序。他希望能在你们写的程序中选出一个**精确度高**并且**跑得比香港记者还快**的程序来帮助它完成这个任务。

## 我该如何编写这个程序
选手目录下将会下发`interface.h`这个文件。
你需要实现`interface.h`中的接口。
你需要在同一目录下新建一个文件`airstrike.cpp`，其中包含以下内容：

```c++
#include "interface.h"

// 实现部分
```

你需要实现的接口在头文件中有简要说明。这里做详细说明。

```c++
void initialize(const double *x, const double *y, const size_t n, const int id);
```

是载入程序的入口。在进行查询之前，会调用这个函数。
载入所用的时间不会计入你的程序用时。但是载入时间不能超过$3\text{s}$。
`x`和`y`是两个数组，给出的是市区的轮廓，即Lunk绘制的多边形的顶点，按照**逆时针顺序**给出。
`n`是多边形的顶点数量。
`id`是当前数据点的标号，在下文会有解释。


```c++
bool query(const double dx, const double dy);
```

是Lunk的操作，每次调用即查询炸弹是否炸在市区内。如果炸在市区内则返回`true`，否则返回`false`。
`dx`和`dy`是炸弹炸到的坐标。
该函数的用时会被计入程序用时。

```c++
void finalize();
```

是结束程序。这个函数将在所有查询任务完成后调用。
用于释放你的程序所用的资源。
该函数的用时不会计入程序用时，但是其运行时间不能超过$3\text{s}$。
注意，请不要使用`delete[]`删除掉之前`initialize`参数中给你的顶点数组，否则后果自负。

## 我该如何测试这个程序
选手目录下将会下发`main.cpp`这个文件。
首先你需要有输入的数据，其格式将在下文给出。
假设你的程序文件是`airstrike.cpp`，那么使用以下命令来编译：

```shell
g++ main.cpp airstrike.cpp -std=c++11 -o main
```

或者你需要调试：

```shell
g++ main.cpp airstrike.cpp -std=c++11 -o main -g
```

打开`-O2`优化：
```shell
g++ main.cpp airstrike.cpp -std=c++11 -o main -O2
```

对于C语言，将`main.cpp`改名为`main.c`，使用`gcc`，并且将`-std=c++11`改为`-std=c11`即可。
然后使用：

```shell
./main
```

来运行程序。
如果需要使用文件输入输出，你可以使用管道，也可以修改`main.cpp`，将其中的两行带有注释的`freopen`取消注释，然后重新编译即可。
注意，该程序**不会测试你的用时并给你评分**。并且与最终评测时的运行程序不同。

## 输入格式
此处的输入格式是根据上面的测试程序所说的。

第一行输入两个整数$n$和$d$，表示顶点数量和数据编号。
下面$n$行描述市区，每一行给出一个**整点**$(x,\;y)$，表示一个顶点。
之后给出若干行，**一直到文件尾**，每行给出一个**整点**$(x_q,\;y_q)$，表示炸弹的位置。

## 输出格式
对于每一个Lunk的询问，输出对应的信息 (`YES`或`NO`)。

## 样例输入1
```
3 1
0 0
6 1
8 7

6 5
2 7
8 1
3 1
```

## 样例输出1
```
YES
NO
NO
YES
```

## 样例解释1
样例输入1如下图所示：

![样例解释1](http://git.oschina.net/riteme/blogimg/raw/master/airstrike/airstrike1.svg)

## 样例输入2
```
7 1
1 1
7 1
4 2
3 4
7 5
5 6
1 6

0 4
2 4
4 4
5 3
5 5
3 1
```

## 样例输出2
```
NO
YES
NO
NO
YES
YES
```

## 样例解释2
样例输入2如下图所示：

![样例解释2](http://git.oschina.net/riteme/blogimg/raw/master/airstrike/airstrike2.svg)

## 数据限制
共$7$个数据测试点，限制如下：

| 数据编号 | $n$的规模 | 特殊限制 |
|:-:|:-:|:-:|
| $1$ | $\le 10$ | 无 |
| $2$ | $\le 10^3$ | 无 |
| $3$ | $\le 10^5$ | 无 |
| $4$ | $\le 2 \times 10^5$ | 无 |
| $5$ | $\le 10^6$ | 左右的边与$y$轴平行，<br/>下边与$x$轴平行，<br/>上边顶点$x$递增，<br/>均高于下边，<br/>输入数据从左下角开始。 |
| $6$ | $\le 10^6$ | 凸多边形 |
| $7$ | $\le 10^3$ | $0 \le x,\;y \le 10^3$ |

对于$100\%$的数据，满足$3 \le n \le 10^6,\;|x|,\;|y|,\;|x_q|,\;|y_q| \le 10^9$。
顶点按照**逆时针顺序**输入，没有两个顶点一样，并且为**简单多边形**。

## 评分标准
对于不同的数据点，分值和时间限制如下表所示：

| 数据编号 | 分值 | 时间限制 |
|:-:|:-:|:-:|
| $1$ | $5$ | $0.1\text{s}$ |
| $2$ | $10$ | $1\text{s}$ |
| $3$ | $15$ | $1\text{s}$ |
| $4$ | $30$ | $1\text{s}$ |
| $5$ | $10$ | $1\text{s}$|
| $6$ | $15$ | $1\text{s}$ |
| $7$ | $15$ | $1\text{s}$ |

在时间限制内，如果程序不出意外 (如运行时错误)，将会不断的给出询问。设你的程序完成的询问个数为$x$。对于每一个点的评分标准如下：

| 数据编号 | $20\%$ | $40\%$ | $60\%$ | $80\%$ | $100\%$ |
|:-:|:-:|:-:|:-:|:-:|:-:|
| $1$ | $\ge 10^5$ | $\ge 2\times 10^5$ | $\ge 3 \times 10^5$ | $\ge 4 \times 10^5$ | $\ge 5 \times 10^5$ |
| $2$ | $\ge 5 \times 10^4$ | $\ge 10^5$ | $\ge 2 \times 10^6$ | $\ge 3 \times 10^6$ | $\ge 4 \times 10^6$ |
| $3$ | $\ge 5 \times 10^2$ | $\ge 10^3$ | $\ge 2 \times 10^5$ | $\ge 4 \times 10^5$ | $\ge  5 \times 10^5$ |
| $4$ | $\ge 10^3$ | $\ge 1 \times 10^5$ | $\ge 2 \times 10^5$ | $\ge 3 \times 10^5$ | $\ge 4 \times 10^5$ |
| $5$ | $\ge 10^3$ | $\ge 8 \times 10^5$ | $\ge 10^6$ | $\ge 1.2 \times 10^6$ | $\ge 1.4 \times 10^6$ |
| $6$ | $\ge 5 \times 10^2$ | $\ge 8 \times 10^5$ | $\ge 10^6$ | $\ge 1.2 \times 10^6$ | $\ge 1.4 \times 10^6$ |
| $7$ | $\ge 10^6$ | $\ge 2 \times 10^6$ | $\ge 3 \times 10^6$ | $\ge 4 \times 10^6$ | $\ge 10^7$ |

你的$x$需要达到对应的要求才能得到对应的百分比。评测程序将选取你能达到的最高的百分比。
其中百分比是将该点总分乘上该百分比并**向下取整**，作为你该点的分数。

如果询问回答错误，将每回答错误一次扣除$1$分，扣分到$0$分为止，分数不会变为负数。
如果发生**运行时错误**，或者**运行严重超时**，将导致该点得$0$分。
如果你的`initialize`或`finalize`超时，该点得$0$分。

## 关于评测机
出于一些原因，GCC编译出来的评测器并不是很稳定，可能出现成绩波动的情况，所以评测时最好采用Clang进行编译，得到的结果会稳定一些。
如果你对你的算法十分自信，然而在评测时却没有得到满分，可以进行重测。

## 温馨提示
评测时限很长，请不要**恶意卡评测**，谢谢合作！

## 后记
Lunk的孙子L*nk完成了这个大新闻。
无奖竞猜：L*nk是谁？

> 第一次出交互题，祝你们早日AC这个**智障题**！QAQ
