# Chapter 22 基本的图算法 Basic

## 22.1 图的表示 Representation

### 22.1.1 邻接链表 Adjacency List

- 性质：

1. $|E|=\Theta(|V|)$ 。
2. 链表中存储的是与头结点对应的顶点相连的顶点。
3. 不能快速判断两个顶点之间是否有边相连。
4. 空间复杂度 $\Theta(|V|+|E|)$ 。

### 22.1.2 邻接矩阵 Adjacency Matrix

- 性质：

1. $|E|=\Theta(|V|^2)$ 。
2. $A[u][v]=\begin{cases}1&(u,v)\in E\\0&(u,v)\notin E\end{cases}$  。
3. 可以快速判断两个顶点之间是否有边相连。
4. 空间复杂度 $\Theta(|V|^2)$ 。

## 22.2 广度优先搜索 Breadth First Search

```python
def BFS(G, s):
    for v in G.V():							# 3|V|
        v.isVisited = False
        v.distanceFromSource = math.inf
        v.prior = None
    s.isVisited = True
    s.distanceFromSource = 0
    s.prior = None
    
    Q = queue()
    Q.push(s)
    while not Q.empty():					# |V|
        v = Q.pop()
        for u in G.adj(v):					# 2|E|
            if u.isVisited == False:
                u.isVisited = True
                u.distanceFromSource = v.distanceFromSource + 1
                u.prior = v
                Q.push(u)
```

时间复杂度 $\Theta(|V|+|E|)$ 。

空间复杂度 $\Theta(|V|)$ 。

## 22.3 深度优先搜索 Depth First Search

```python
def DFS(G):
    for v in G.V():							# 3|V|
        v.isVisited = False
        v.pushTime = 0
        v.popTime = 0
        v.prior = None
    globalTime = 0							# globalTime can be ignored
    for v in G.V():							# |V|
        if v.isVisited == False:
            DFS_VISIT(G, s)
            
def DFSVisit(G, s):
    nonlocal globalTime
    globalTime += 1
    s.pushTime = globalTime
    v.isVisited = True
    for u in G.adj(v):						# 2|E|
        if u.isVisited == False:
            u.prior = v
            DFS_VISIT(G, u)
    globalTime += 1
    v.popTime = globalTime
```

时间复杂度 $\Theta(|V|+|E|)$ 。

空间复杂度 $\Theta(|V|)$ 。

## 22.4 拓扑排序 Topology Sort

```python
# method 1
def TopologySort(G):
    DFS(G)							# |V| + |E|
    # sort with popTime
    sort(G.V(), reverse = True)		# |V|log|V|
    
    return G.V()
```

```python
# method 2
def TopologySort(G):
    Q = queue()
    result = queue()
    for v in G.V():					# |V|
        if v.inDegree == 0:
            Q.push(v)
    
    while not Q.empty():
        v = Q.pop()					# |V|
        for u in G.adj(v):			# |E|
            u.inDegree -= 1
            if u.inDegree == 0:
                Q.push(u)
        result.push(v)				# |V|
        
    return result
```

时间复杂度 $\Theta(|V|+|E|)$ 。

空间复杂度 $\Theta(|V|)$ 。

## 22.5 强连通分量 Strong Connected Component

bfs

# Chapter 23 最小生成树 Minimal Spanning Tree

## 23.1 最小生成树的形成 Build

有连通无向图 $G(V,E)$ 和权重函数 $w:E\to\mathbb R$ ，希望找出最小生成树。用贪心算法。

```python
def GeneratingMST(G):
    # subMST is a subset of minimal spanning tree of G
    subMST = []
    while subMST != G.spanningTree():
        # safe edge will not form a circle
        e = safeEdge(G)
        subMST.append(e)
    return subMST
```

## 23.2 Kruskal 和 Prim

### 23.2.1 Kruskal

在 Kruskal 里面，subMST 是一个森林，safe edge 是最小权重且不成环的边。

```python
def FindRoot(u):
    if u != root[u]:
        u = FindRoot(root[u])
    return u

def Merge(u, v):
    a = FindRoot(u)
    b = FindRoot(v)
    if a != b:
        root[a] = b

def KruskalSort(G):
    subMST = []
    root = G.V().copy()							# |v|
    
    sort(G.E())									# |E|log|E|
    # G.E() is in ascending order
    for e in G.E():								# |E|
        if FindRoot(e.u) != FindRoot(e.v):
            subMST.append(e)
            Merge(e.u, e.v)
    return subMST

def KruskalHeap(G):
    subMST = []
    root = G.V().copy()							# |v|
    
    Q = MakeHeap(G.E())							# |E|log|E|
    # e is the smallest in G.E()
    while len(subMST) <= n:						# |E|log|E|
        e = Q.pop()
        if FindRoot(e.u) != FindRoot(e.v):
            subMST.append(e)
            Merge(e.u, e.v)
    return subMST
```

1. Sort 

   时间复杂度 $\Theta(|E|log|E|)=\Theta(|E|log|V|)$。

   空间复杂度 $\Theta(|E|)$ 。

2. heap

   时间复杂度 $\Theta(|E|log|E|)=\Theta(|E|log|V|)$。

   空间复杂度 $\Theta(|E|)$ 。

### 23.2.1 Prim

在 Prim里面，subMST 是一棵树，safe edge 是最小权重且不成环的边。

```python
def Prim(G, s):
    for v in G.V():									# 3|V|
        v.prior = None
        v.dist = math.inf
        v.inHeap = True
        
    s.dist = 0
    # sort with dist
    Q = MakeHeap(G.V())
    while not Q.empty():
        v = Q.Pop()									# |v|log|V|
        for u in G.adj(v):							# |E|log|V| or |E| FibHeap
            if u.inHeap and weightFunc(u, v) < v.dist:
                u.prior = v
                u.dist = weightFunc(u, v)
```

1. binary heap

   时间复杂度 $\Theta(|V|log|V|+|E|log|V|)=\Theta(|E|log|V|)$ 。

2. Fibonacci heap

   Pop is still $O(ln(|V|))$，but inserting and moving a key is $O(1)$。

   时间复杂度 $\Theta(|V|log|V|+|E|)$ 。

空间复杂度 $\Theta(|V|)$ 。

# Chapter 24 单源最短路径 Single Source Shortest Path

```python
def Initial(G, s):
    for v in G.V():
        v.dist = math.inf
        v.prior = None
    s.dist = 0

def Relax(u, v, weightFunc = default):
    if u.dist > v.dist + weightFunc(u, v):
        u.dist = v.dist + weightFunc(u, v)
        u.prior = v
```

## 24.1 Bellman-Ford

边的权重可以是负数。

```python
def BellmanFord(G, s):
    Initial(G, s)
    for i in range(1, G.V().size()):			# |V| - 1
        for e in G.E():							# |E|
            Relax(e.u, e.v)
            
    # check if there is an negative circle
    for e in G.E():
        if e.u.dist > e.v.dist + weightFunc(e.u, e.v):
            return False
    return True
```

时间复杂度 $\Theta(|V||E|)$ 。

空间复杂度 $\Theta(|V|)$ 。

## 24.2 

pass

## 24.3 Dijkstra

边的权重非负。

```python
def Dijkstra(G, s):
    Initial(G, s)				# |V|
    path = []
     # sort with dist
    Q = MakeHeap(G.V())			# |V|
    
    while not Q.empty():
        v = Q.pop()				# |V|log|V|
        path.append(v)
        for u in G.adj(v):		# |E|log|V| or |E| FibHeap
            Relax(u, v)
    return path
```

1. binary heap

   时间复杂度 $\Theta(|V|log|V|+|E|log|V|)=\Theta(|E|log|V|)$ 。

2. Fibonacci heap

   时间复杂度 $\Theta(|V|log|V|+|E|)$ 。

空间复杂度 $\Theta(|V|)$ 。

# Chapter 25 所有结点对的最短路径 Pairs Shortest Path

$|V|$ 次 Dijkstra 

时间复杂度binary heap $\Theta(|V||E|log|V|)$ Fibonacci heap $\Theta(|V|^2log|V|+|V||E|)$ 。

$|V|$ 次 Bellman-Ford

时间复杂度 $\Theta(|V|^2|E|)$ 。

## 25.2 Floyd-Warshall

可以有负边，不能有负环。

```python
def Floyd_Warshall(G):
    # adjacent matrix
    n = G.V().size()
    # infinty if G[i][j] not in G.E()
    dist = [[G[i][j] for i in range(n)] for j in range(n)]
    post = [[j if (i, j) in G.E() else None for i in range(n)] for j in range(n)]
    mid = [[None for i in range(n)] for j in range(n)]
    
    for k in range(n):
        for i in range(n):
            for j in range(n):
    			if dist[i][j] > dist[i][k] + dist[k][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    post[i][j] =  post[i][k]
                    mid[i][j] = k
                
```

时间复杂度 $\Theta(|V|^3)$ 。

# A*

```python
def Astar(G, s, t):
    for v in G.V():
        v.prior = None
        v.dist = math.inf
    path = []
    
    # sort with w(v) = v.dist + h(v, e)
    # w is weight function
    # h is heuristic function
    Q = MakeHeap(G.V())
    s.dist = 0
    Q.push(s)
    
    v = Q.pop()
    while v != e:
    	path.append(v)
        for u in G.adj(v):
            # Push u with w(u) = v.dist + d(v, u) + h(u, e)
            # = u.dist + h(u, e)
            u.prior = v
            u.dist = min(v.dist + w(v, u), u.dist)
        v = Q.pop()    
```

## 1 可接受的启发函数 Admissible Heuristics

1. 可接受的启发函数得到的距离 $\le$ 两个结点的最短路径距离。
2. 如果启发函数是可接受的，那么树搜索是最优的。

## 2 一致的启发函数 Consistent Heuristics

1. 满足三角不等式。（直达比有中介短）
2. 如果启发函数是一致的，那么图搜索是最优的。

## 3 时间复杂度

$O(b^d)$ ，$b$ 是平均分叉数目，$d$ 分叉深度。

# Backtracking

每次做出一次选择，我们距离最后的结果就进一步，但是同时产生分叉。分叉可能会汇集起来。这样就形成了一个有向无环图。

数独，八皇后问题，迷宫算法

