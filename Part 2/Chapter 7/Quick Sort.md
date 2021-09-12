# Chapter 7 Quick Sort

## 7.1 描述

快速排序是利用了分治思想。具体是选定一个轴，把比轴小的都放一边，比轴大的放另一边，此时可以不用处理顺序。最后轴放在两堆数的中间，此时轴处于最后排序好数组中所在的位置。

对于长度为 $n$ 的数组来说，上述步骤的时间复杂度为 $\Theta(n)$。

## 7.2 性能

如果每次只能划分出去 1 个元素，则递归式会变成：
$$
T(n)=T(n-1)+\Theta(n)
$$
解得 $T(n)=\Theta(n^2)$。

但如果每次都把数组分为 $a:b$ 的两部分，那么递归式是：
$$
T(n)=T(\frac{a}{a+b}n)+T(\frac{b}{a+b}n)+\Theta(n)
$$
解得 $T(n)=\Theta(n\log n)$。

## 7.4 时间复杂度分析

### 7.4.1 最坏情况分析

假设 $T(n)$ 是最坏情况下的用时，则：
$$
T(n)=\max_{0\le q\le n-1}(T(q)+T(n-q-1))+\Theta(n)
$$
假设 $T(n)\le cn^2$，那么：
$$
\begin{align*}
T(n)&\le\max_{0\le q\le n-1}(cq^2+c(n-q-1)^2)+\Theta(n)\\
&\le c(n-1)^2+\Theta(n)\\
&=O(n^2)
\end{align*}
$$
这里：
$$
f(q)=q^2+(n-q-1)^2\\
f'(q)=2q-2(n-q-1)=0\\
q^*=(n-1)/2
$$
假设 $T(n)\ge cn^2-dn$，那么：
$$
\begin{align*}
T(n)&\ge\max_{0\le q\le n-1}(cq^2+c(n-q-1)^2)+\Theta(n)\\
&\ge c(n-1)^2+\Theta(n)\\
&=cn^2-2c(n-1)+\Theta(n)\\
&=\Omega(n^2)&\exist c>0
\end{align*}
$$
所以 $T(n)=\Theta(n^2)$。

### 7.4.2 平均运行时间

快速排序的时间主要花费在，选取完轴之后的元素比较上。

假设数组元素各不相同，故设数组元素从小到大分别为 $a_1,\dots,a_n$。

定义：
$$
X_{ij}=I\{a_i\text{ compared with }a_j\}
$$
那么所有值比较的次数就是：
$$
X=\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}X_{ij}
$$
取期望就是：
$$
E(X)=E(\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}X_{ij})=\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}E(X_{ij})=\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}Pr\{a_i\text{ compared with }a_j\}
$$
对于被选取的轴来说，它要和数组中的所有元素进行比较。但是对于非轴元素来说，一旦被分开，就不可能跨越轴进行比较。

还可以定义 $A_{ij}=\{a_i,\dots,a_j\}$，表示 $a_i$ 到 $a_j$ 之间的值。

故：
$$
\begin{align*}
&\qquad Pr\{a_i\text{ compared with }a_j\}\\
&=Pr\{a_i\text{ is the pivot of }A_{ij}\}+Pr\{a_j\text{ is the pivot of }A_{ij}\}\\
&=\frac{2}{j-i+1}\\
\end{align*}
$$

$$
E(X)=\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}\frac{2}{j-i+1}=\sum_{i=1}^{n-1}\sum_{k=1}^{n-i}\frac{2}{k+1}<\sum_{i=1}^{n-1}\sum_{k=1}^{n}\frac{2}{k}=O(n\log n)
$$

