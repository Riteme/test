A Image Recognition

题意：给定一个01矩阵，问其中有多少个正方形的框，满足框的四边全部是1。

题解：对每个点算出上下左右四个方向上的最长的连续是1的数量。之后对于每条对角线，相当于每个点有一个向前覆盖的距离和向后覆盖的距离，问相互覆盖的点对有多少个。这个可以使用树状数组来解决。



C Revolving Digits

题意：给定一个串，问它的所有循环位移中（去重后），有多少字典序比原串小，有多少比原串大。

题解：考虑将原串重复一边后计算后缀数组，则答案就是在 n+1开始的后缀前后的串的数量。其中需要使用 lcp 数组进行去重。



D Trouble 

题意：给5个数组，问能不能从每个数组选一个数，使得它们的和为0。

题解：meet in the middle + hash表。



H Simple Path

题意：给定一张图，多次询问，每次询问给出两个点，问没有被这两个点间的简单路径的点的数量。

题解：圆方树裸题。



G King Arthur's Knights

题意：给一张满足 Dirac 定理中的条件的图，要求构造 Hamilton 回路。

题解：按照 Dirac 定理的证明来即可。