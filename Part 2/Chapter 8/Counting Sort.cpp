#include <iostream>
#include <random>
#include <vector>

using namespace std;

vector<int> Count_Sort(vector<int>& A, int k)
{
    vector<int> B(A.size(), 0);
    vector<int> C(k + 1, 0);

    for (int i = 0; i < A.size(); i++)
        C[A[i]]++;

    for (int j = 1; j < C.size(); j++)
        C[j] += C[j - 1]; 

    for (int i = A.size() - 1; i >= 0; i--)
    {
        C[A[i]]--;
        B[C[A[i]]] = A[i];
    }

    return B;
}

int main()
{
    vector<int> A;
    int n = 100;
    for (int i = 0; i < 50; i++)
        A.push_back(rand() % n);
    for (auto i : A)
    {
        cout << i << " ";
    }
    cout << endl;
    auto B = Count_Sort(A, n);
    for (auto i : B)
    {
        cout << i << " ";
    }
    return 0;
}