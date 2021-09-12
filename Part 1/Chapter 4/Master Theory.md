主方法是对：
$$
T(n)=aT(n/b)+f(n)
$$
形式的函数的求解。

1. $\exist\epsilon>0, f(n)=O(n^{\log_ba-\epsilon})\Rightarrow T(n)=\Theta(n^{\log_ba})$
2. $f(n)=\Theta(n^{\log_ba})\Rightarrow T(n)=\Theta(n^{\log_ba}\ln n)$
3. $\exist\epsilon>0, f(n)=\Omega(n^{\log_ba+\epsilon})\and\exist c<1,n_0>0,\forall n\ge n_0,af(n/b)\le cf(n)\Rightarrow$$ T(n)=\Theta(n^{\log_ba})$

