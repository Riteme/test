由于DFS序和BFS序都要相同，相当于要满足两类条件。
分开考虑这两种顺序，首先考虑对BFS序的划分方式决定了树的高度，所以记$s_i$表示BFS序上第$i$位和第$i + 1$位中间是否“换行”，如果是则为$1$，否则为$0$。
显然$s[1] = 1$，因为$1$必须是根。
为了方便，我们先将BFS重新从$1$至$n$标号，DFS序同时也改变一下。
对于BFS序而言，两个位置$i < j$如果满足$i$在DFS序中在$j$的后面，那么说明$i$和$j$不在同一层。因为如果在同一层，由于$i < j$，则$i$应当先被访问。换言之$s[i] = 1$。
对于DFS序而言，任意满足$i < j$，满足DFS序上第$i$个点到第$j$个点的深度之差不会大于$j - i$。这是因为从$i$到$j$至多走这么多步。由于BFS序已经重标号，所以也就是DFS序上的第$i$号点到第$j$号点之间最多一处“换行”。这等价于对$s$的一个区间和做出了限制。
最后考虑期望。对于$1$到$n - 1$的每个$s$，如果被限制为$1$，那么对期望的贡献就是$1$。如果有上界$1$，并且存在一个和它相连的位置被钦定为$1$，那么他就只能为$0$。对于其他没有限制的地方，既可以$+1$也可以不$+1$，所以期望贡献是$0.5$。
最后实现的时候只用挑出所有包含了一个$1$的区间，然后做差分将区间内置为$0$，就可以累加求期望高度了。
