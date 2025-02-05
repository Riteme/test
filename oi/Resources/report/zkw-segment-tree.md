# 阅读报告：ZKW线段树
#### 1. 关于分治
看了线段树，感觉二分思想确实很重要，能够把很多算法降为```O(logN)```级别。  
包括今年的NOIP的跳石头，当初没想到要用二分，过后发现这种思想确实十分巧妙。  
以后做题时要拓宽思路，不应被题目的标签给限制住了。

#### 2. 关于二进制
ZKW线段树巧妙的将堆与线段树结合起来了，并且用二进制降低了常数。  
我在做借教室时，最后六个点总是TLE，后来放弃指针，改用堆存储，速度快了15%，顺利过了。  
ZKW线段树则更是巧妙，直接利用二进制的位操作，不仅进一步提升性能，而且使代码更加简洁。  
这使我发现二进制的许多有趣的性质。之前影响最深的是在Leetcode上的一道题，能在```O(n)```的时间复杂度和```O(1)```的空间找出单个存在的数字，就是利用了异或的性质。

#### 3. 关于数据结构
数据结构这一块也是一个很大很繁杂的东西，各种各样数据结构都有自己的特性，学习起来十分费劲。  
许多算法都建立在数据结构的基础上，没有一个好的数据结构，算法也只能是百搭。
因此两者密不可分。
在ZKW线段树中，正是因为二进制的利用，才有了非常快速的非递归算法。  
因此今后要注重创新，多思考，才能使自己的程序更加强大。

#### 总结
1. 多学习思想，数学思想也非常重要。
2. 多了解数据结构和算法，拓宽思路。
3. 多学会些小技巧，多利用二进制的特性。
