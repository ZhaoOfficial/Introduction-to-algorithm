# Chapter 12 Binary Search Tree

## 12.1 什么是二叉搜索树

性质：左子树节点的值不大于右子树节点的值。

### 定理 12.1

如果 $x$ 是一个有 $n$ 个结点子树的根，中序遍历需要 $\Theta(n)$ 的时间。

#### proof:

用 $T(n)$ 表示中序遍历时间，$n$ 个结点需要 $\Omega(n)$ 的时间。
$$
T(n)=T(k)+T(n-k-1)+d\\
=((c+d)k+c)+((c+d)(n-k-1)+c)+d\\
=(c+d)n+c\in O(n)
$$
故 $T(n)=\Theta(n)$。

## 12.2 查询二叉搜索树

### 定理 12.2

在一棵高度为 $h$ 的二叉搜索树上，查找，最值，前后继的时间复杂度是 $O(h)$。

## 12.3 插入和删除

### 定理 12.3

插入删除操作都是 $O(h)$。

## 12.4 随机构建二叉搜索树

### 定理 12.4

一棵有 $n$ 个不同关键字的二叉搜索树期望高度 $O(\ln n)$。