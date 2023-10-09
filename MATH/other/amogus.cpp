#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

void selection_sort(vector <int> &arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) swap(arr[i], arr[j]);
        }
    }
}

int main() {

    int n;
    cin >> n;

    vector <int> vec(n);

    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    selection_sort(vec, n);

    for (int i = 0; i < n; i++) {
        cout << vec[i] << ' ';
    }

    return 0;
}