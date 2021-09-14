# Chapter 11 Hash Table

## 11.1 直接寻址表 Direct Address Table

假设全集 $U$ 比较小，且元素是取自全集的。我们用一个数组——直接寻址表——来表示。数组长度为 $|U|$，每个位置为槽 slot，对应 $U$ 的一个元素。直接寻址表的寻找，插入，删除操作时间复杂度都为 $O(1)$。

## 11.2 散列表 Hash Table

如果全集 $U$ 很大，则直接寻址表无法存储且大部分空间是浪费的。我们需要一个更小的表且保持寻找，插入，删除操作时间复杂度都为 $O(1)$。在直接寻址表中，元素 $k$ 被放在槽 $k$ 中；在散列表中，利用散列函数 $h$，元素被放在槽 $h(k)$ 中。这里
$$
h:U\to\{0, 1, \dots,m-1\}\qquad(m<<|U|)
$$
$h(k)$ 是 $k$ 的散列值。

但是非单射函数比如存在冲突 collision。故我们选取一个尽可能随机的散列函数以减少冲突次数。

### 通过链接法解决冲突

链接法中，把散列到同一个槽的元素都用链表链接起来。

### 链接法散列分析

给定一个存放了 $n$ 个元素，$m$ 个槽的散列表，定义装载因子 load factor $\alpha=n/m$。

#### 最坏情况

所有元素都被散列到一个槽中，产生一个长度为 $n$ 的链表。此时寻找，插入，删除时间复杂度为 $O(n)$。

#### 平均情况

假定所有元素被均匀地散列到 $m$ 个槽，且互相独立。

对于 $j=0,...,m-1$，散列表 $T[j]$ 的长度用 $n_j$ 表示，于是
$$
n = n_0+\dots+n_{m-1}
$$
且 $E(n_j)=\alpha=n/m$。

### 定理 11.1

在上述条件下，一次不成功查找的平均时间为 $\Theta(1+\alpha)$。

#### Proof

当查找一个元素 $k$ 的情况下，我们需要找到链表 $T[h(k)]$ 的末尾，故寻找的期望时间是 $\alpha$，加上散列函数计算的时间 $O(1)$，故一次不成功查找的平均时间为 $\Theta(1+\alpha)$。

### 定理 11.2

在上述条件下，一次成功查找的平均时间也为 $\Theta(1+\alpha)$。

#### Proof

假设要查找的元素是 $n$ 个元素之中的一个，称为 $x$。在一次成功的查找中，所检查的元素的个数就是 $x$ 所在槽且在 $x$ 之前的元素个数加一。

在前述条件下，两个元素被散列到同一个槽的概率是 $1/m$。

定义指示变量 $I_{ij}$ 为元素 $i$ 和元素 $j$ 被散列到同一个槽中，故 $E(I_{ij})=1/m$。
$$
\begin{align*}
E(\frac{1}{n}\sum_{i=1}^{n}(1+\sum_{j=i+1}^nI_{ij}))&=\frac{1}{n}\sum_{i=1}^{n}(1+\sum_{j=i+1}^nE(I_{ij}))\\
&=\frac{1}{n}\sum_{i=1}^{n}(1+\sum_{j=i+1}^n\frac{1}{m})\\
&=1+\frac{1}{nm}\sum_{i=1}^n(n-i)\\
&=1+\frac{n^2-\frac{1}{2}n(n+1)}{nm}\\
&=1+\frac{n-1}{2m}\\
&=1+\frac{1}{2}\alpha-\frac{1}{2n}\alpha\in\Theta(1+\alpha)
\end{align*}
$$

## 11.3 散列函数 Hash Function

### 11.3.1 除法散列法

$$
h(k)=k\mod m
$$

$m$ 最好是一个不太接近 2 的整数幂的素数。

### 11.3.2 乘法散列法

$$
h(k)=\lfloor m(kA-\lfloor kA\rfloor)\rfloor
$$

### 11.3.3 全域散列法 universal hash

从一系列函数中随机选取一个作为散列函数。

设 $\mathfrak{H}:U\to\{0,\dots,m-1\}$ 为一组有限的散列函数集，如果对于每一对不同的关键字 $k,l\in U$，使得满足 $h(k)=h(l)$ 的散列函数 $h\in\mathfrak H$ 的数量至多为 $|\mathfrak{H}|/m$ 个，则这个集合是全域的。

### 定理 11.3

如果 $h$ 选自一组全域散列函数中，将 $n$ 个元素散列到一个大小为 $m$ 的表中，用链表法解决冲突。如果 $k$ 不在表中，则 $k$ 被散列到表中链表的期望长度 $E[n_{h(k)}]$ 至多为 $\alpha=n/m$，如果 $k$ 在表中，则包含 $k$ 的链表的期望长度 $E[n_{h(k)}]$ 至多为 $\alpha+1$。

#### proof:

定义指示变量 $I_{ij}$ 为元素 $i$ 和元素 $j$ 被散列到同一个槽中，由于全域散列定义，$Pr(h(i)=h(j))\le1/m$，则 $E[X_{ij}]\le1/m$。

在定义随机变量 $Y_k$ 表示与 $k$ 散列到同样一个槽中但不是 $k$ 的其他元素的数目，于是 $Y_k=\sum_{l\in T\\l\ne k}X_{kl}$ ，故
$$
E[Y_k]=E[\sum_{l\in T\\l\ne k}X_{kl}]=\sum_{l\in T\\l\ne k}E[X_{kl}]\le\sum_{l\in T\\l\ne k}\frac{1}{m}
$$
如果 $k\notin T$，则 $n_{h(k)}=Y_k$，且 $|\{l:l\in T\and l\ne k\}|=n$，于是 $E[n_{h(k)}]=E[Y_k]\le n/m=\alpha$。

如果 $k\in T$，则 $n_{h(k)}=Y_k+1$，且 $|\{l:l\in T\and l\ne k\}|=n-1$，于是 $E[n_{h(k)}]=E[Y_k]+1\le (n-1)/m+1<1+\alpha$。

### 推论 11.4

对于一个具有 $m$ 个槽位且初始未空的表，利用全域散列法和链表法解决冲突，需要 $\Theta(n)$ 的期望时间来处理任何包含了 $n$ 个插入，查找和删除的操作序列，其中该序列包含了 $O(m)$ 个插入操作。

#### proof:

插入 $O(m)$ 次，因为 $n=O(m)$，故 $\alpha=O(1)$。故总计$\Theta(n)$ 时间。

### 设计一个全域散列函数

找到一个足够大的素数 $p$ 使得它包含所有的元素 $k$。对于任何 $a\in\mathbf Z_p^*,b\in\mathbf Z_p$:
$$
h(k)=((ak+b)\text{mod }p)\text{mod }m
$$
故散列函数集合为
$$
\mathfrak H_{pm}=\{h_{ab}:a\in\mathbf Z_p^*,b\in\mathbf Z_p\}
$$

### 定理 11.5

上述散列函数集合是全域的。

#### proof:

考虑 $\mathbf Z_p$ 中的两个不同关键字 $k,l$ 。
$$
r=(ak+b)\text{mod }p\\
s=(al+b)\text{mod }p\\
$$
故 $r\ne s$。

每一组 $(a,b)$ 和每一组 $(r,s)$ 一一对应。

故 $k,l$ 发生冲突的概率就是 $r\equiv s(\text{mod } m)$ 的概率，则这样的 $s$ 数目最多为
$$
\lceil p/m\rceil-1\le (p+m-1)/m-1=(p-1)/m
$$
模 $m$ 后冲突概率至多为 $((p-1)/m)/(p-1)=1/m$（会与 $r$ 冲突的数目 / $s$ 可能的取值总数）。

## 11.4 开放寻址法 open addressing

为了使得开放寻址法插入一个元素，需要探查 probe 散列表，找到一个空位放下。散列函数为
$$
h(k,i)
$$
其中 $k$ 为元素，$i$ 为第 $i$ 次寻找空位。

开放寻址法删除元素的操作比较困难，只能惰性删除。

### 线性探查 linear probing

$$
h(k,i)=(h'(k)+i)\text{ mod }m
$$

存在一次群集 primary clustering 的问题，当一个空槽前面有 $i$ 个满的槽时，这个空槽被占用的概率变成了 $(i+1)/m$，故探查时间会越来越长。

### 二次探查 quadratic probing

$$
h(k)=(h'(k)+c_1i+c_2i^2)\text{ mod }m
$$

存在二次群集 secondary clustering 的问题: $h_1(k,0)=h(k_2,0)$ 蕴含着 $h_1(k,i)=h(k_2,i)$。

### 双重散列 double hashing

$$
h(k,i)=(h_1(k)+ih_2(k))\text{ mod }m
$$

### 开放寻址法的分析

开放寻址法里面，$\alpha\le1$。

### 定理 11.6

给定一个开放寻址散列表，并假设是均匀散列，则对于一次不成功的查找，其期望的探查次数至多为 $\frac{1}{1-\alpha}$。

#### proof:

定义随机变量 $X$ 为一次不成功的查找的探查次数，定义事件 $A_i$ 为第 $i$ 次探查且探查到的是一个已经被占用的槽。那么 $X\ge i$ 为 $\cap_{k=1}^{i-1}A_k$。
$$
\begin{align*}
Pr(X\ge i)=Pr(\cap_{k=1}^{i-1}A_k)&=Pr(A_1)Pr(A_2|A_1)\cdots Pr(A_{i-1}|\cap_{k=1}^{i-2}A_k)\\
&=\frac{n}{m}\cdot\frac{n-1}{m-1}\cdots\frac{n-i+2}{m-i+2}\\
&\le(\frac{n}{m})^{i-1}\\
&=\alpha^{i-1}\\
E(X)&=\sum_{i=1}^{\infty}Pr(X\ge i)\\
&\le\sum_{i=1}^{\infty}\alpha^{i-1}=\sum_{i=0}^{\infty}\alpha^{i}\\
&=\frac{1}{1-\alpha}
\end{align*}
$$

### 推论 11.7

插入最多需要做 $1/(1-\alpha)$ 次探查。

### 定理 11.8

一次成功查找的探查期望次数至多为
$$
\frac{1}{\alpha}\ln\frac{1}{1-\alpha}
$$

#### proof:

一次插入需要 $1/(1-i/m)=\frac{m}{m-i}$ 次查找，$n$ 次平均是：
$$
\begin{align*}
\frac{1}{n}\sum_{i=0}^{n-1}\frac{m}{m-i}&=\frac{m}{n}\sum_{i=0}^{n-1}\frac{1}{m-i}\\
&=\frac{m}{n}\sum_{i=m-n+1}^{m}\frac{1}{i}\\
&=\frac{m}{n}\int_{m-n}^{m}\frac{1}{x}dx\\
&=\frac{1}{\alpha}\ln\frac{1}{1-\alpha}
\end{align*}
$$
