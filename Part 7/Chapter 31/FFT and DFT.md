# 1 多项式 Polynomial

## 1.1 系数表达 Coefficient Representation

- 对于一个次数为**n**的多项式$\displaystyle{A(x)=\sum_{i=0}^{n-1}a_ix^i}$而言，其系数表达是一个由系数组成的向量$a = [a_0,a_1,\dots,a_{n-1}]^T$

1. 求值 Evaluation

   求值就是将某个值带入多项式，Horner法则可以使得在$\Theta(n)$时间内完成：
   $$
   A(x_0)=a_0+x_0(a_1+x_0(a_2+\dots x_0(a_{n-1})\dots))
   $$

2. 加法：$\Theta(n)$时间
3. 乘法/卷积：$\Theta(n^2)$时间

## 1.2 点值表达 Point-value Representation

- 对于一个次数为**n**的多项式$\displaystyle{A(x)=\sum_{i=0}^{n-1}a_ix^i}$而言，其点值表达是一个由**n**个点组成的集合$\{(x_0,y_0),(x_1,y_1)\dots(x_{n-1},y_{n-1})\}$，其中 $y_i = A(x_i)$

1. 求值

   对**n**个点用Horner法则求值，共$\Theta(n^2)$时间。这个时间是求得上述集合的时间。可以用特殊方法达到$\Theta(nlogn)$时间。

2. 加法：$\Theta(n)$时间

3. 乘法/卷积：$\Theta(n)$时间

## 1.3 插值 Interpolation

- 插值是指从点值表达确定其系数表达，是点值表达求值的逆运算。

- $$
  \begin{bmatrix}
  a_0\\
  a_1\\
  \vdots\\
  a_{n-1}
  \end{bmatrix}=\begin{bmatrix}
  1&x_0&x_0^2&\dots&x_0^{n-1}\\
  1&x_1&x_1^2&\dots&x_1^{n-1}\\
  \vdots&\vdots&\vdots&\ddots&\vdots\\
  1&x_{n-1}&x_{n-1}^2&\dots&x_{n-1}^{n-1}\\
  \end{bmatrix}^{-1}
  \begin{bmatrix}
  y_0\\
  y_1\\
  \vdots\\
  y_{n-1}
  \end{bmatrix}
  $$

- 如果$x_i\ne x_j\  (\forall\ i\ne j)$，则上述矩阵可逆。

## 1.4 $\Theta(nlogn)$时间的乘法

系数$-\text{DFT}-\Theta(nlogn)\to$点值$-$乘法$-\Theta(n)\to$结果$-$插值$-\Theta(nlogn)\to$系数结果。

总共时间为$\Theta(nlogn)$时间的乘法。



# 2 DFT和FFT

## 2.1 离散傅里叶变换 Discrete Fourier Transform

### 2.2.1 单位复数根 Unit Complex Root

- **n**次单位复数根是满足 $\omega^n=1$ 的复数。**n**次单位复数根刚好**n**个。令主**n**次单位复数根为$\omega_n=e^{2\pi i/n}$， 其余的均为主**n**次单位复数根的**k**次幂。

- **n**个**n**次单位复数根 $\omega_n^0,\omega_n^1,\dots,\omega_n^{n-1}$ 在乘法意义下形成一个群（和模**n**的整数加法群同构）。

- 消去定理
  $$
  \omega_{dn}^{dk}=\omega_n^k
  $$

- 折半定理
  $$
  \omega_n^{k+n/2}=-\omega_n^k\\
  \begin{align*}
  (\omega_n^0)^2&=\omega_{n}^0=\omega_{n/2}^0\\
  (\omega_n^1)^2&=\omega_{n}^2=\omega_{n/2}^1\\
  \vdots\\
  (\omega_n^{n-1})^2&=\omega_{n}^{2n-2}=\omega_{n/2}^{n/2-1}
  \end{align*}
  $$

### 2.2.2 DFT

- 计算 $\displaystyle{A(x)=\sum_{i=0}^{n-1}a_ix^i}$ 在**n**个**n**次单位复数根 $\omega_n^0,\omega_n^1,\dots,\omega_n^{n-1}$ 处的值。

- 定义：
  $$
  y_k=A(w_n^k)=\sum_{j=0}^{n-1}a_jw_n^{kj}
  $$
  
- $y=[y_0,y_1,\dots,y_{n-1}]^T$ 就是系数 $a = [a_0,a_1,\dots,a_{n-1}]^T$ 的离散傅里叶变换。

### 2.2.3 快速傅里叶变换 Fast Fourier Transform

1.  将$\displaystyle{A(x)=\sum_{i=0}^{n-1}a_ix^i}$ 以奇偶分开。
   $$
   \begin{align*}
   A(x)&=(a_0+a_2x^2+\dots+a_{n-2}x^{n-2})+(a_1x+a_3x^3+\dots+a_{n-1}x^{n-1})\\
   &=(a_0+a_2x^2+\dots+a_{n-2}x^{n-2})+x(a_1+a_3x^2+\dots+a_{n-1}x^{n-2})\\
   \end{align*}
   $$
   令：
   $$
   A_{even}(x)=(a_0+a_2x+\dots+a_{n-2}x^{(n-2)/2})\\
   A_{odd}(x)=(a_1+a_3x+\dots+a_{n-1}x^{(n-2)/2})\\
   $$
   每部分为**n/2**次的多项式：
   $$
   A(x)=A_{even}(x^2)+xA_{odd}(x^2)
   $$
   故对于 $\omega_n^k$：
   $$
   \begin{align*}
   A(\omega_n^k)&=A_{even}((\omega_n^k)^2)+\omega_n^kA_{odd}((\omega_n^k)^2)\\
   &=A_{even}(\omega_{n/2}^k)+\omega_n^kA_{odd}(\omega_{n/2}^k)\\
   
   A(\omega_n^{k+n/2})&=A_{even}(\omega_{n/2}^{k+n/2})+\omega_n^{k+n/2}A_{odd}(\omega_{n/2}^{k+n/2})\\
   &=A_{even}(\omega_{n/2}^k)-\omega_n^kA_{odd}(\omega_{n/2}^k)\\
   \end{align*}
   $$

2. 时间复杂度
   $$
   T(n) = 2T(n/2)+\Theta(n)=\Theta(nlogn)
   $$

### 2.2.4 逆变换

- 将DFT写成矩阵形式 $\vec{y}=V\vec{a}$，

$$
\begin{bmatrix}
y_0\\
y_1\\
\vdots\\
y_{n-1}
\end{bmatrix}=\begin{bmatrix}
1&\omega_n^{11}&\omega_n^{12}&\dots&\omega_n^{1(n-1)}\\
1&\omega_n^{21}&\omega_n^{22}&\dots&\omega_n^{2(n-1)}\\
\vdots&\vdots&\vdots&\ddots&\vdots\\
1&\omega_n^{(n-1)1}&\omega_n^{(n-1)2}&\dots&\omega_n^{(n-1)(n-1)}\\
\end{bmatrix}
\begin{bmatrix}
a_0\\
a_1\\
\vdots\\
a_{n-1}
\end{bmatrix}
$$

这里，$V_{ij}=\omega_n^{ij} \ \ \forall i,j\in[0,n-1]$

- 可证明对于 $V^{-1}$ 来说，$V^{-1}_{ij}=\omega_n^{-ij}/n$ 

$$
\begin{align*}
VV^{-1}_{ij}&=\sum_{k=0}^{n-1}V_{ik}V^{-1}_{kj}\\
&=\sum_{k=0}^{n-1}\omega_n^{ik}\omega_n^{-kj}/n\\
&=\sum_{k=0}^{n-1}\omega_n^{k(i-j)}/n\\
&=\begin{cases}
1&i=j\\
0&i\ne j
\end{cases}
\end{align*}
$$

故和正向变换方法一致。