### A. Mental Rotation

**题意**　给定一张网格图，要求进行左右旋转。

**题解**　向左转和向右转是相互抵消的，因此最多转三次。



### B. SpongeBob SquarePants

**题意**　给定两个数，问是否相等。

**题解**　如题。



### C. I Don't Want To Pay For The Late Jar!

**题意**　给一堆的 $t_i$ 和 $f_i$，求 $f_i - (t_i - S)$ 的最大值。

**题解**　如题。



### F. Military Class

**题意**　给定 $n$ 和 $w$，以及 $K$ 对禁用，问有多少个排列 $p_i$ 满足 $|p_i - i| \leqslant w$。$K$ 个禁用表示某个位置上的数不能为另一个数。$w \leqslant 4$

**题解**　状压 DP。枚举当前考虑到第 $i$ 位，以 $i$ 为中心的周围 $9$ 个数字是否被用过。直接转移即可。



### H. Are You Safe?

**题意**　给一堆点，求它们的凸包。之后又问一堆点是否在凸包内。

**题解**　如题。



### I. To Crash Or Not To Crash

**题意**　给三行字符串，问 `=` 右边第一个非 `.` 的字符是啥。

**题解**　如题。



### J. Kitchen Plates

**题意**　给 $5$ 个不等式，求一个合法的排序，使得其满足 $5$ 个不等式。

**题解**　做拓扑排序即可。



### K. Help The Support Lady

**题意**　给定 $n$ 个事情，每个事情需要 $t_i$ 的时间完成，且 DDL 在 $2t_i$ 之前。要求安排完成事情的顺序，使得在 DDL 前完成的事情数量最多。

**题解**　显然是按照 $t_i$ 从小到大贪心完成。如果当前这个事情不能在 DDL 前完成了，就直接排到末尾。

