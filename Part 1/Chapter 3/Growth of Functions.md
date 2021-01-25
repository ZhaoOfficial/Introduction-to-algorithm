# Chapter 3 Growth of Functions

## 3.1 渐近记号 Asymptotic notation

$$
\Theta(g(n))=\{f(n)|\exist c_1,c_2>0,\exist n_0>0,s.t.\forall n\ge n_0:0\le c_1g(n)\le f(n)\le c_2g(n)\}
$$

即在 $n$ 足够大的时候，$f(n)$ 能夹在 $c_1g(n)$ 和 $c_2g(n)$ 之间。


$$
O(g(n))=\{f(n)|\exist c>0,\exist n_0>0,s.t.\forall n\ge n_0:0\le f(n)\le cg(n)\}
$$
即在 $n$ 足够大的时候，$f(n)$ 一直小于 $cg(n)$ 。


$$
\Omega(g(n))=\{f(n)|\exist c>0,\exist n_0>0,s.t.\forall n\ge n_0:0\le cg(n)\le f(n)\}
$$
即在 $n$ 足够大的时候，$f(n)$ 一直大于 $cg(n)$ 。

### 定理 1

$$
f(n)=\Theta(g(n))\Leftrightarrow f(n)=O(g(n)) \and f(n)=\Omega(g(n))
$$


$$
o(g(n))=\{f(n)|\forall c>0,\exist n_0>0,s.t.\forall n\ge n_0:0\le f(n)<cg(n)\}
$$
$f(n)$ 是 $g(n)$ 的高阶无穷小。


$$
\omega(g(n))=\{f(n)|\forall c>0,\exist n_0>0,s.t.\forall n\ge n_0:0\le cg(n)<f(n)\}
$$
$f(n)$ 是 $g(n)$ 的高阶无穷大。

### 定理 2

$$
f(n)=\Theta(g(n))\ \and\ g(n)=\Theta(h(n))\ \Rightarrow\ f(n)=\Theta(h(n))\\
f(n)=O(g(n))\ \and\ g(n)=O(h(n))\ \Rightarrow\ f(n)=O(h(n))\\
f(n)=\Omega(g(n))\ \and\ g(n)=\Omega(h(n))\ \Rightarrow\ f(n)=\Omega(h(n))\\
f(n)=o(g(n))\ \and\ g(n)=o(h(n))\ \Rightarrow\ f(n)=o(h(n))\\
f(n)=\omega(g(n))\ \and\ g(n)=\omega(h(n))\ \Rightarrow\ f(n)=\omega(h(n))\\
$$

$$
f(n)=\Theta(f(n))\\
f(n)=O(f(n))\\
f(n)=\Omega(f(n))\\
$$

$$
f(n)=\Theta(g(n)) \ \Leftrightarrow \ g(n)=\Theta(f(n))
$$

$$
f(n)=O(g(n)) \ \Leftrightarrow \ g(n)=\Omega(f(n))\\
f(n)=o(g(n)) \ \Leftrightarrow \ g(n)=\omega(f(n))
$$

$$
1<n^{\frac{1}{\ln n}}<\ln(\ln^*n)<\ln^*(\ln n)<\ln^*n<2^{\ln^*n}<\\
\ln \ln n<\sqrt{\ln n}<\ln n<2^{\sqrt{2\ln n}}<(\sqrt2)^{\ln n}<\ln^2n<\\
2^{\ln n}\le n<n\ln n\le \ln(n!)<n^2<n^3<\\
n^{\ln \ln n}\le(\ln n)^{\ln n}<4^{\ln n}<(\frac{3}{2})^n<2^n<n2^n<\\
e^n<(\ln n)!<n!<(n+1)!<2^{2^n}<2^{2^{n+1}}
$$

