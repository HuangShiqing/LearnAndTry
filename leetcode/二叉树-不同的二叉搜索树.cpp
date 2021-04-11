#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 二叉搜索树定义:
// 1.若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
// 2.若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
// 3.它的左右子树也为二叉搜索树
// 4.二叉搜索树「中序遍历」得到的值构成的序列一定是升序的

// 给定一个有序序列 1⋯n，为了构建出一棵二叉搜索树，我们可以遍历每个数字 i，将该数字作为树根，将 1⋯(i−1)
// 序列作为左子树，将 (i+1)⋯n 序列作为右子树。接着我们可以按照同样的方式递归构建左子树和右子树

// G(n): 长度为 n 的序列能构成的不同二叉搜索树的个数。
// F(i, n): 以 i 为根、序列长度为 n 的不同二叉搜索树个数 (1≤i≤n)。
// G(n)=F(1, n)+F(2, n)+...F(n, n)
// F(i, n)=G(i-1)*G(n-i)
// G(n)=G(1-1)*G(n-1) + G(2-1)*G(n-2) ...+ G(n-1)*G(n-n) = G(0)*G(n-1) + G(1)*G(n-2) ...+ G(n-1)*G(0)
class Solution {
public:
    int numTrees(int n) {
        vector<int> G(n + 1, 0);
        G[0] = 1;
        G[1] = 1;

        for (int n_i = 2; n_i <= n; n_i++) {
            for (int j = 1; j <= n_i; j++) {
                G[n_i] += G[j - 1] * G[n_i - j];
            }
        }
        return G[n];
    }
};