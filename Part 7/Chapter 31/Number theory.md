# Chapter 31 Number Theory

利用输入所需的位数来衡量输入的大小，给定 $k$ 个整数输入 $a_1,a_2,\dots,a_k$，如果算法可以在关于 $\log a_1,\log a_2, \dots, \log a_k$ 的*多项式时间*内完成，即算法在关于二进制编码后的输入长度的多项式时间内完成，则算法是多项式时间算法。

数论算法中基本的四则运算时间用位运算的数目来衡量，即两个 $n$ 位数的加减法需要 $\Theta(n)$ 的时间，乘除法需要 $\Theta(n^2)$ 的时间。

## 31.1 基本数论概念

### 定理 31.1

$$
\forall a\in\mathbb Z,\forall n\in\mathbb N,\exist_1\ q,r\in\mathbb Z\and 0\le r<n:a=qn+r
$$

### 定理 31.2

$$
\forall a, b\in\mathbb Z-\{0\}:\gcd(a,b)=\min_{x,y\in\mathbb Z}\{ax+by\}
$$

### 推论 31.3

$$
\forall a, b\in\mathbb Z,\ d|a\and d|b\to d|\gcd(a,b)
$$

### 推论 31.4

$$
\forall a, b\in\mathbb Z,\forall n\in\mathbb N+\{0\},\gcd(an,bn)=n\gcd(a,b)
$$

### 推论 31.5

$$
\forall a,b,n\in\mathbb N,\ n|ab\and\gcd(a,n)=1\to n|b
$$

### 定理 31.6

$$
\forall a,b,p\in\mathbb Z,\ \gcd(a,p)=1\and \gcd(b,p)=1\to\gcd(ab,p)=1
$$

### 定理 31.7

$$
\forall a,b\in\mathbb Z,\forall p\in\mathbb P,\ p|ab\to (p|a\or p|b)
$$

### 定理 31.8

$$
a=p_1^{e_1}p_2^{e_2}\dots p_n^{e_n}\\
\forall i\in[1,n], p_i\in\mathbb P,p_1<p_2<\dots<p_n,e_i\in\mathbb N
$$

## 31.2 最大公约数 greatest common divisor

### 定理 31.9 欧几里得算法 Euclidean Algorithm

$$
\forall a\in\mathbb N+\{0\},b\in\mathbb N,\gcd(a,b)=\gcd(b,a\text{ mod }b)
$$

### 欧几里得算法的时间复杂度

我们把改算法看成关于 $a$ 和 $b$ 的函数。不妨设 $a>b\ge1$，引入斐波那契数列。

#### 引理 31.10

如果 $a>b\ge1$ 并且函数进行了 $k\ge1$ 次递归，则 $a\ge F_{k+2},b\ge F_{k+1}$。

##### proof：

$k=1$，则 $b_1\ge1=F_2$，$b_1<a_1\ge2=F_3$。

每次递归时候，$b_i>(a_i\mod b_i)$，故每轮递归中 $a_i>b_i$ 不变。

假设 $k-1$ 轮都成立，第 $k$ 轮，$b_k=a_{k-1}\ge F_{k+1}$，$a_{k-1}\mod b_{k-1}\ge F_k$，故 $a_k\ge b_k+(a_{k-1}\mod b_{k-1})=F_{k+2}$。

#### 定理 31.11 $Lam\acute{e}$ 定理

对于任意整数 $k\ge1$，如果 $a>b\ge1$，且 $b<F_{k+1}$，则递归次数少于 $k$ 次。

##### proof:

对于斐波那契数列
$$
\gcd(F_{k+1},F_{k})=\gcd(F_{k},F_{k+1}\mod F_k)=\gcd(F_{k},F_{k-1})
$$
故经过 $k-1$ 次，达到 $F_3,F_2$ 的终止条件。

由此可知，该算法的时间复杂度是 $\log b$。

### 31.2-5

每一次递归中
$$
\begin{align*}
a,b&&\gcd(a,b)(a',b')\\
b,a-b\lfloor a/b\rfloor&&\gcd(a,b)(b',a'-b'\lfloor a'/b'\rfloor) 
\end{align*}
$$
因为
$$
b=\gcd(a,b)b'\\
a-b\lfloor a/b\rfloor=\gcd(a,b)a'-\gcd(a,b)(b'\lfloor a'/b'\rfloor)
$$
故可以改进为
$$
1+\log_{\phi}(\frac{b}{\gcd(a,b)})
$$

### 31.2-6

返回 $(1,F_{k-1},-F_{k})\quad(k\ mod\ 2=0)$ 或 $(1,F_{k-2},-F_{k-1})\quad(k\ mod\ 1=0)$ 。

#### 1. 

$$
\gcd(F_{k+1},F_{k})=\gcd(F_{k},F_{k-1})=\gcd(F_{3},F_{2})=\gcd(2,1)=1
$$

#### 2.

$$
\begin{align*}
F_{k+1}F_{k-1}-F_{k}F_{k}&=(F_{k}+F_{k-1})F_{k-1}-F_{k}^2\\
&=F_{k}F_{k-1}+F_{k-1}^2-F_{k}^2\\
&=(F_{k-1}+F_{k-2})F_{k-1}+F_{k-1}^2-(F_{k-1}+F_{k-2})^2\\
&=-F_{k-1}F_{k-2}-F_{k-2}^2+F_{k-1}^2\\
&=F_{k-2}F_{k-3}+F_{k-3}^2-F_{k-2}^2\\
&=\dots\\
&=F_{2}F_{1}+F_{1}^2-F_{2}^2\\
&=1
\end{align*}
$$

$$
\begin{align*}
F_{k+1}F_{k-2}-F_{k}F_{k-1}&=(F_{k}+F_{k-1})F_{k-2}-F_{k}F_{k-1}\\
&=F_{k}F_{k-2}+F_{k-1}F_{k-2}-F_{k}F_{k-1}\\
&=(-F_{k-1}+F_{k-2})(F_{k-1}+F_{k-2})+F_{k-1}F_{k-2}\\
&=-F_{k-1}^2+F_{k-2}^2+F_{k-1}F_{k-2}\\
&=\dots\\
&=-F_{2}^2+F_{1}^2+F_{2}F_{1}\\
&=1
\end{align*}
$$

### 31.2-7

#### 1.

$$
\gcd(a_0,a_1,\dots,a_n)=\gcd(a_i,\gcd(a_0,\dots,a_{i-1},a_{i+1},\dots ,a_n))
$$

设 $d=\gcd(a_0,\dots,a_n)$，则 $d|\gcd(a_0,\dots,a_{i-1},a_{i+1},\dots, a_n)$。由于 $d|a_i$，则 $d|\gcd(a_i,\gcd(a_0,\dots,a_{i-1},a_{i+1},\dots, a_n))$，故 $\gcd(a_i,\gcd(a_0,\dots,a_{i-1},a_{i+1},\dots a_n))\ge d$。

设 $d'=\gcd(a_i,\gcd(a_0,\dots,a_{i-1},a_{i+1},\dots, a_n))$，则 $d'|a_i$ 且 $d'|\gcd(a_0,\dots,a_{i-1},a_{i+1},\dots, a_n)$。由于 $d'|a_i\ \forall i$，则 $d'|\gcd(a_0,\dots ,a_n))$，故 $d'\le d$。

故 $d'=d$。

### 31.2-9

$\Longrightarrow$
$$
n_3\nmid n_1n_2\\
n_4\nmid n_1n_2\\
\Rightarrow n_3n_4\nmid n_1n_2\\
\Rightarrow\gcd(n_1n_2,n_3n_4)=1
$$
$\Longleftarrow$
$$
\gcd(n_1n_2,n_3n_4)=1\Rightarrow an_1n_2+bn_3n_4=1\\
$$
故 $n_1,n_3$ $n_1,n_4$ 互质，由另一个式子得 $n_1,n_2$ 互质。

## 31.3 模运算 Modular arithmetic

### 定理 31.12

$(\mathbb Z_{n},+)$ 是一个有限交换群。

### 定理 31.13

$(\mathbb Z_{n}^{*},\cdot)$ 是一个有限交换群。

### 定理 31.14

如果 $(S,\oplus)$ 是一个有限群，$S'$ 是 $S$ 的任意一个非空子集且满足 $\forall a, b\in S'$，有 $a\oplus b\in S'$，则 $(S',\oplus)$ 是 $(S,\oplus)$ 的一个子群。

#### proof:

因为 $S’$ 是 $S$ 的一个非空子集，所以有 $S'\sub S$。

1. $a,b\in S'$，有$a\oplus b∈S'$。
2. 假设不存在单位元 $e$，则任取 $a\in S'$，反复进行二元运算，可得各个元素不相等，且二元运算可以无限进行，与有限集矛盾。故必存在单位元。
3. $a,b,c\in S$，故必满足结合律。
4. 反复进行二元运算，直至产生单位元 $e$，则产生了一对逆元。

由群的定义知：$(S',\oplus )$ 也是一个群。又因为：$(S,\oplus )$是一个群,则根据子群定义知：$(S',\oplus )$ 是 $(S,\oplus )$ 一个子群。

### 定理 31.15 拉格朗日定理

如果 $(S,\oplus)$ 是一个有限群，$(S,\oplus)$ 是 $(S',\oplus)$ 的一个子群，则 $|S'|$ 是 $|S|$ 的一个因数。

### 推论 31.16

如果 $S'$ 是有限群 $S$ 的真子群，则 $|S'|\le|S|/2$。

### 循环群 cyclic group

由一个元素生成的子群。$<a>$

### 阶 order

$$
\text{ord}(a)=\min\{t|a^{(t)}=e,t>0\}
$$

### 定理 31.17

对任意有限群 $(S,\oplus)$ 和任意 $a\in S$，一个元素的阶等于有它生成的循环群的规模，即 $\text{ord}(a)=|<a>|$。

#### proof:

设 $t=\text{ord}(a)$，则 $\forall k\ge 1$
$$
a^{(t+k)}=a^{(t)}\oplus a^{(k)}=a^{(k)}
$$
故
$$
<a>=\{a^{(1)},\dots,a^{(t)}\}
$$
且 $|<a>|\le t$。

假设 $<a>$ 中 $\exist\ 1\le i<j\le t$ 有 $a^{(i)}=a^{(j)}$。那么 $\forall k \ge 0$，$a^{(i+k)}=a^{(j+k)}$。

令 $k=t-j$，则 $a^{(i+t-j)}=a^{(t)}=e$。但 $i+t-j<t$，和 阶 的定义相矛盾。

故 $<a>$ 中所有元素是不同的。故 $|<a>|=t$。

### 推论 31.18

序列 $a^{(1)},\dots$ 是周期序列，周期为 $\text{ord}(a)$。

### 推论 31.19

如果 $(S,\oplus)$ 是具有单位元的有限群 $e$，则对所有 $a\in S$，
$$
a^{(|S|)}=e
$$

## 31.4 求解模线性方程 Solving modular linear equations

对于
$$
ax\equiv b\ (\text{mod }n)
$$
令 $<a>$ 表示由 $a$ 生成的 $\mathbf Z_n$ 的子群，当且仅当 $b\in<a>$ 时，方程有解。

### 定理 31.20

$\forall a,n\in \mathbb N,\gcd(a,n)=d\Rightarrow <a>=<d>\and |<a>|=n/d$。

#### 1.

$$
\gcd(a,n)=d\Rightarrow ax+ny=d\Rightarrow d\in<a>\Rightarrow <d>\sube<a>
$$

#### 2.

$$
\forall m\in<a>,m=ax+ny,d|a,d|n\Rightarrow d|m\Rightarrow m\in<d>\Rightarrow <a>\sube<d>
$$

所以 $<a>=<d>$。

### 推论 31.21

当且仅当 $d|b$ 时，$ax\equiv b\ (\text{mod }n)$ 有解。

### 推论 31.22

$ax\equiv b\ (\text{mod }n)$ 要么有 $\gcd(a,n)$ 个解，要么无解。

### 定理 31.23

$ax\equiv b\ (\text{mod }n)$ 的特解 $x_0=s(b/d)\ (\text{mod }n)$，$d=\gcd(a,n),d=as+nt$。

### 定理 31.24

假设方程有解，则 $\gcd(a,n)$ 个解分别是 $x_i=x_0+i(n/d),i\in[0,d-1]$。

### 推论 31.25

如果 $\gcd(a,n)=1$，则方程 $ax\equiv b\ (\text{mod }n)$ 解模 $n$ 唯一。

### 推论 31.26

如果 $\gcd(a,n)=1$，则方程 $ax\equiv 1\ (\text{mod }n)$ 解要么模 $n$ 唯一，要么无解。

### 31.4-3

已知
$$
as+nt=d\\
x_0=s\frac{b}{d}\ (\text{mod }\frac{n}{d})\Rightarrow x_0+\frac{n}{d}y=\frac{b}{d}s\Rightarrow x_0=\frac{b}{d}s-\frac{n}{d}y
$$
则
$$
\begin{align*}
ax_0&\equiv a(\frac{b}{d}s-\frac{n}{d}y)\ (\text{mod }n)\\
&\equiv \frac{as}{d}b\ (\text{mod }n)\\
&\equiv \frac{d-nt}{d}b\ (\text{mod }n)\\
&\equiv b-\frac{nt}{d}b\ (\text{mod }n)\\
&\equiv b\ (\text{mod }n)\\
\end{align*}
$$

## 31.5 中国剩余定理 Chinese remainder theorem

设 $n=n_1\dots n_k$，其中 $n_i,n_j$ 两两互质，用笛卡尔乘积 $\mathbf Z_{n_1}\times\dots\times\mathbf Z_{n_k}$ 描述了 $\mathbf Z_n$ 的结构。

### 定理 31.27

令 $n=n_1\dots n_k$，其中 $n_i,n_j$ 两两互质，考虑映射
$$
a\leftrightarrow(a_1,\dots,a_k)\qquad a\in\mathbf Z_n,a_i\in\mathbf Z_{n_i}\and a_i\equiv a\ \text{mod }n_i
$$
该映射是一个双射。

#### proof:

从左到右是平凡的。

从右到左：

定义 $N_i=n/n_i$。可知 $n_j|N_i,n_i\nmid N_i$。

再定义 $c_i=N_i(N_i^{-1}\ \text{mod }n_i)$，由于 $N_i,n_i$ 互质，故推论31.26可得逆存在。
$$
c_i=
N_i(N_i^{-1}\ \text{mod }n_i)\equiv\begin{cases}
1\ (\text{mod }n_j)&i=j\\
0\ (\text{mod }n_j)&i\ne j\\
\end{cases}
$$
令
$$
a\equiv \sum_{i=1}^ka_ic_i\ (\text{mod }n)
$$
因为
$$
a\equiv a_ic_i\equiv a_i\ (\text{mod }n_i)
$$
故该映射是一个双射。

### 推论 31.28

如果 $n_i,n_j$ 两两互质，且 $n=n_1\dots n_k$，则对任意整数 $a_1,\dots,a_k$，关于未知量 $x$ 的方程组
$$
x\equiv a_i\ (\text{mod }n_i)
$$
对模 $n$ 有唯一解。

### 推论 31.29

如果 $n_i,n_j$ 两两互质，且 $n=n_1\dots n_k$，则对所有整数 $x,a$，
$$
x\equiv a\ (\text{mod }n_i)
$$
当且仅当
$$
x\equiv a\ (\text{mod }n)
$$

## 31.6 元素的幂 Powers of an element

### 定理 31.30 欧拉定理

$$
a^{\phi(n)}\equiv1\ (\text{mod }n)\qquad a\in\mathbf Z_n^*
$$

### 定理 31.31 费马定理

$$
a^{p-1}\equiv1\ (\text{mod }p)\qquad a\in\mathbf Z_p^*
$$

### 定理 31.32

如果 $\text{ord}(g)=|\mathbf Z^*_n|$，则 $\mathbf Z_n^*$ 中的每个元素都是 $g$ 的一个幂，称 $g$ 是 $\mathbf Z_n^*$ 的一个原根或者生成元。如果 $\mathbf Z_n^*$ 有原根，则称 $\mathbf Z_n^*$ 是循环群。

使得 $\mathbf Z_n^*$ 是循环群的 $n>1$ 的值是 $2,4,p^e,2p^e(p\in\mathbb P,e\in\mathbb N)$。

### 定理 31.33 离散对数定理

如果 $g$ 是 $\mathbf Z_n^*$ 的一个原根且 $a\in\mathbf Z_n^*$，则存在一个 $z$，使得 $g^{z}\equiv a\ (\text{mod }n)$。这个 $z$ 称为对模 $n$ 到基 $g$ 上 $a$ 的离散对数。

如果 $g$ 是 $\mathbf Z_n^*$ 的一个原根，则当且仅当等式 $x\equiv y(\text{mod }\phi(n))$ 成立时，有

 $g^x\equiv g^y(\text{mod }\phi(n))$ 成立。

### 定理 31.34

如果 $p\ge3,p\in\mathbb P$，$e\ge1$，则 
$$
x^2\equiv 1(\text{mod }p^e)
$$
仅有两个解 $x=\pm1\ (\text{mod }p^e)$。

#### proof:

方程等价于
$$
p^e|(x-1)(x+1)
$$
故 $p^e$ 只能同时整除一个，故只能有两个解。

### 推论 31.35

如果一个数 $x$ 满足 $x^2\equiv 1(\text{mod }n)$，但 $x\ne\pm1\ (\text{mod }p^e)$，则 $x$ 是一个以 $n$ 为模的 1 的非平凡平方根。

如果对模 $n$ 存在 1 的非平凡平方根，则 $n$ 是合数。

#### proof:

逆否命题可知，$n$ 不是奇数或奇素数的幂，$n=2$ 时只有一个解，为保证有解，$n>1$，故 $n$ 为合数。

### 反复平方法时间复杂度

如果都是 $m$ 位数，则时间复杂度是 $O(m^3)$。

## 31.7 RSA 公钥加密系统 The RSA public-key crypto-system

RSA 基于寻找大素数是很方便的，但是大整数分解是很难的事实。

### 公钥加密系统

每个人都有公钥 $P$ 和密钥 $S$，假设 $\mathfrak D$ 表示允许的信息集合，对于 $M\in\mathfrak D$，
$$
M=S(P(M))\\
M=P(S(M))
$$
发送消息

1. B 取得 A 的密钥 $S_A$
2. B 计算出相应与 $M$ 的密文 $C=P_A(M)$
3. B 把 $C$ 发给 A
4. A 收到 $C$ 后用自己的密钥 $S_A$ 恢复信息: $S_A(C)=S_A(P_A(M))=M$

数字签名

1. A 用密钥 $S_A$ 和 $\sigma=S_A(M)$ 计算出 $M'$ 的数字签名
2. A 把消息签名对 $(M',\sigma)$ 发给 B
3. B 收到后用 $M'=P_A(\sigma)$ 来证实消息来自 A。

### RSA 加密系统

1. 随机选取两个大素数 $p,q$。
2. $n=pq$
3. 选取一个与 $\phi(n)=(p-1)(q-1)$ 互质的小奇数 $e$
4. 计算 $e$ 模 $\phi(n)$ 的逆元 $d$
5. RSA 公钥为 $P=(e,n)$
6. RSA 密钥为 $S=(d,n)$
7. 密文 $C=M^e\text{ mod }n$

### 定理 31.36 RSA 正确性

$$
ed=1+k\phi(n)\\
\begin{align*}
P(S(M))=S(P(M))&=M^{ed}\text{ mod }n\\
&= M^{1+k\phi(n)}\text{ mod }n\\
&= M\text{ mod }n\\
\end{align*}
$$

## 31.8 素性检验

### 素数的密度

### 定理 31.37 素数定理

$$
\lim_{n\to\infty}\frac{\pi(n)}{n/\ln(n)}=1
$$

费马定理
$$
a^{n-1}\equiv1\text{mod }n
$$
如果一个数是合数，大概率会不满足这个式子。故选取 $a=2$ 作为基数即可。

### Miller-Rabin 素性检验

