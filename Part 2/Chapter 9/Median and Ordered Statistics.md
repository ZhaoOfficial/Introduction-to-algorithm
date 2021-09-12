# Chapter 9 Median and Ordered Statistics

## 9.1 最小值和最大值 minimum and maximum

只找到一个最值的时间复杂度是 $O(n)$。但是同时找到最大值和最小值并不需要 $2n$ 次比较，通过两个一组的方法，可优化为 $3n/2$ 次比较。

## 9.2 平均时间为 $O(n)$ 选择算法

快速排序的变种，用于找到第 $i$ 个数。

partition 操作使得左子数组长度为 $k$ 的概率是 $1/n$。故定义指示变量
$$
X_k=\text{left subarray contains }k\text{ elements}
$$
假设最坏情况，每次第 $i$ 个数都落在更长的子数组中，那么递归式就是
$$
\begin{align*}
T(n)&\le \sum_{k=1}^n X_k\cdot(T(\max(k-1, n-k))+O(n))\\
&= \sum_{k=1}^n X_k\cdot T(\max(k-1, n-k))+O(n)\\
E(T(n))&\le E[\sum_{k=1}^n X_k\cdot T(\max(k-1, n-k))+O(n)]\\
&= \sum_{k=1}^n E[X_k]\cdot E[T(\max(k-1, n-k))]+O(n)\\
&= \sum_{k=1}^n \frac{1}{n}\cdot E[T(\max(k-1, n-k))]+O(n)\\
&= \le \frac{2}{n}\sum_{k=\lfloor n/2\rfloor}^{n-1} E[T(k)]+O(n)\\
&= O(n)
\end{align*}
$$

## 9.3 最坏情况为 $O(n)$ 选择算法

对于一个长度为 $n$ 的数组进行如下操作：

1. 将数组划分为 $\lceil n/5\rceil$ 组，每组 5 个元素，且最多只有 1 组元素不满 5 个。
2. 寻找这些组中每一组的中位数。
3. 对于第二布找出来的中位数们，再找出这些中位数的中位数 $x$。
4. 按 $x$ 进行划分。
5. 递归搜索。
