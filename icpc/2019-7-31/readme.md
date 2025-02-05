<br /><center class="subtitle">Fudan ICPC Summer Training Camp 2019</center>

# 杭电第四场训练报告

<br />
<center>[Fudan U2] 刘明君、孙亮亮、薛振梁</center>
<center>2019 年 7 月 31 日</center>
<br />

### 概况

比赛中通过 3 题，赛后补 3 题，总共通过 6 题。

### 比赛过程

<pre class="replay">
|0        |30       |60       |90       |120      |150      |180      |210      |240      |270      (min)
..............??.....!....!?h......................................................................g lmj
..............................?..x.J................................xg.......................x.....c sll
..................-A..........................!..?...............H.................................g xzl
-: Presentation Error
x: Wrong Answer
?: Time Limit Exceeded / Memory Limit Exceeded
!: Runtime Error
大写字母：Accepted
小写字母：未通过
</pre>

### 总结

**刘明君：**成功为队伍做出负的贡献。开场写出了主席树，然后超时调不过去，感觉自己卡不了常数，丢给 xzl 重写。看到 $15$ 数码发现是自己见过的游戏，但是之前就不会玩，只记得有个和奇偶性相关的结论，疯狂怂恿队友这题规律不好找，提供了负面效果。看了 E 和 F 也没有什么想法。不应该害怕大量人过了的题。

**孙亮亮：**对构造题还是不够熟练，要多做多练。

**薛振梁：**这次比赛前期还算正常，除了 H 题被莫名卡常非常无奈，后来又重写浪费了很多时间。后期的时候遇到了两道我们队伍不擅长的构造题，导致后半场基本上都卡在那两道题上。解决构造题的能力还是很弱，需要以后特别关注练习一下。

***

### 解题报告

#### A. AND Minimum Spanning Tree

**情况**　通过（-1）

**题意**　已知一个完全图有 $n$ 个点，点的编号为 $1$ 到 $n$，两点之间的边权为这两个点编号按位与的结果。要求构造一棵父亲数组字典序最小的最小生成树。$n \leqslant 2×10^5$。

**题解**　考虑将所有大于 $1$ 的 $2^k$ 与 $1$ 相连，这一部分的贡献均为 $0$。然后对于其它数字，将其与其最小的空缺的二进制位相连，如果这个二进制位不超过 $n$，则这个数字的贡献为 $0$。否则将其与 $1$ 相连，贡献为 $1$。

<hr />
#### C. Divide the Stones

**情况**　补题通过

**题意**　有 $n$ 个石子，第 $i$ 堆重为 $i$，要求把 $n$ 个石子分成 $k$ 组，每组 $n/k$ 个，要求每组重量相同。$k$ 保证是 $n$ 的因子。

**题解**　构造解，考虑如果 $2k \mid n$，则只要每组有 $n/2k$ 对 $1+n$（首尾各取一个）即可，否则如果 $n$ 为偶数，则无解。$n$ 为奇数可以考虑先将 $1$~$3k$ 分成 $k$ 组，再将其他石子用 $2k \mid n$ 时的方法分组。给 $1$~$3k$ 分组需要分类讨论。如果 $i$ 为偶数，则将 $i,\ 2k-i/2+1,\ 3(3k+1)/2-i-(2k-i/2+1)$ 分一组，若 $i$ 为奇数，则将 $i,\ 2k-k/2-i/2,\ 3(3k+1)/2-i-(2k-k/2-i/2)$ 分一组。

<hr />
#### F. Horse

**情况**　补题通过

**题意**　一匹马要通过 $n$ 棵树，每个树有高度，每次通过会降低能量值 $h_i$，并且在降低之后获得当前能量值的分数。有两种额外操作，一种是在通过之前，吃掉这棵树，把树的高度变为 $0$，另一种是通过一棵树之后，进行休息，能量值变为之前吃掉的树的高度总和。求最大的分数。

**题解**　考虑两种操作没有关系，没有操作时，每棵树对于之后的所有点贡献是 $-h_i$，吃树可以理解为把这个点对后面点的贡献取消。休息相当于把能量恢复到 $0$，然后将 $h_i$ 划分为 $k+1$ 段，每段的代价是 $(h_l)+(h_l+h_{l+1})+(h_l+h_{l+1}+h_{l+2})+\cdots+(h_l+\cdots+h_r)$。要求 $\mathrm{ans}_1-\mathrm{ans}_2$ 最大。$\mathrm{ans}_1$ 只需要优先队列找出最大的 $m$ 个，$\mathrm{ans}_2$ 考虑 $\mathrm{dp}[i,\ j]$ 表示前 $i$ 个树分成 $j$ 段的最小的代价，每次向前找一个区间从 $\mathrm{dp}[k,\ j-1]$ 转移，可以斜率优化。

<hr />
#### G. Just an Old Puzzle

**情况**　补题通过

**题意**　输入一个 $15$ 数码，问能不能恢复到初始状态。

**题解**　把网格排成一行，算出除去 $0$ 的逆序对个数，因为网格大小是 $4$，每次上下交换会导致逆序对个数的奇偶性改变，再算出每个数到初始的行上面的交换次数，如果总和是偶数则可行，奇数则不行。

<hr />
#### H. K-th Closest Distance

**情况**　通过（-7）

**题意**　给定一个长度为 $n$ 的序列 $a_i$，以及 $q$ 次询问。每次询问给出一个 $p$ 和 $K$ 和区间 $[l,\ r]$，问 $\{|p - a_i|:\ i\in [l,\ r]\}$ 中的第 $K$ 大是多少。$n,\ q \leqslant 10^5$。

**题解**　二分答案 $x$，用主席树查询区间内在范围 $[p-x,\ p+x]$ 的数有多少个。时间复杂度为 $\mathrm O(n \log^2 n)$。

<hr />
#### J. Minimal Power of Prime

**情况**　通过（-2）

**题意**　有 $T$ 次询问，每次询问给出一个正整数 $n$，设 $n = p_1^{k_1}p_2^{k_2}\cdots p_m^{k_m}$ 为 $n$ 的质因数分解，要求输出 $\min\{k_i\}$。$T \leqslant 50000$，$n \leqslant 10^{18}$。

**题解**　考虑先枚举所有小于 $10000$ 的质数，计算它们的答案。设删去这些质数后的 $n$ 变为 $m$，那么 $m$ 包含的质因数均大于 $10000$，因此 $m$ 的次数之和不超过 $4$。当答案为 $4$ 时，$m = p^4$；当答案为 $3$ 时，$m = p^3$；当答案为 $2$ 时，$m = p^2$ 或 $m = p^2q^2$；否则答案为 $1$。以上几种情况均可以用二分判断。