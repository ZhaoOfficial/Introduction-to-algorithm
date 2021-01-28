#include <iostream>
#include <random>
#include <vector>

using namespace std;

template <typename T>
int partition(vector<T>& a, int low, int high)
{
    T pivot = a[high - 1];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high - 1]);
    return i + 1;
}

template <typename T>
void QSort(vector<T>& a, int low, int high)
{
    if (low < high)
    {
        int mid = partition(a, low, high);
        QSort(a, low, mid);
        QSort(a, mid + 1, high);
    }
}

int main()
{
    vector<int> data;
    int n = 121;
    for (int i = 0; i < n; i++)
    {
        data.push_back(i);
    }
    shuffle(data.begin(), data.end(), default_random_engine(0));
    for(auto& i : data)
    {
        cout << i << " ";
    }
    cout << endl;

    QSort(data, 0, n);

    for(auto& i : data)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}