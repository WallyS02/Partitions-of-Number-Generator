#include <iostream>

using namespace std;

#define MAX_AMOUNT_PRIME 54
#define MAX_NUMBER 256

int findMinIndex(int* result, int size) {
    int minIndex = 0;
    for (int i = 0; i <= size; i++)
        if (result[i] != 0) {
            minIndex = i;
            break;
        }
    return minIndex;
}

void print(int* result, int size, int tab[]) {
    int minIndex = findMinIndex(result, size);
    for (int i = size; i > minIndex; i--) {
        for (int j = 0; j < result[i]; j++) {
            cout << tab[i] << "+";
        }
    }
    for (int i = 0; i < result[minIndex] - 1; i++)
        cout << tab[minIndex] << "+";
    cout << tab[minIndex];
    cout << "\n";
}

void searchForPartition(int n, int l, int tab[], int* result, int size) {
    if (n == 0) {
        print(result, size, tab);
        return;
    }
    for (int i = 0; i <= l; i++) {
        if (n >= tab[i]) {
            result[i]++;
            searchForPartition(n - tab[i], i, tab, result, size);
            result[i]--;
        }
    }
}

void erastotenes(int n, int tab[]) {
    bool pom[MAX_NUMBER+1];
    for (int i = 2; i <= n; i++) {
        pom[i] = 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (!pom[i]) {
            for (int j = i * i; j <= n; j += i) {
                pom[j] = 1;
            }
        }
    }
    int p = 0;
    for (int i = 2; i <= n; i++)
        if (!pom[i]) {
            tab[p] = i;
            p++;
        }
} /*procedure from - https://pl.wikipedia.org/wiki/Sito_Eratostenesa */

int binarySearch(int left, int right, int searched, int tab[]) {
    while (left <= right) {
        int middle = (left + right) / 2;
        if (tab[middle] == searched)
            return middle;
        if (tab[middle] < searched)
            left = middle + 1;
        else
            right = middle - 1;
    }
    return -1;
} /*procedure from - https://pl.wikipedia.org/wiki/Wyszukiwanie_binarne */

int main() {
    int tab[MAX_AMOUNT_PRIME];
    erastotenes(MAX_NUMBER, tab);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int n, k, l;
        cin >> n;
        cin >> k;
        l = binarySearch(0, MAX_AMOUNT_PRIME, k, tab);
        n -= k;
        int* result = new int[l+1];
        result[l] = 1;
        for (int j = 0; j < l; j++) {
            result[j] = 0;
        }
        if(l != -1)
            searchForPartition(n, l, tab, result, l);
        delete[] result;
    }
    return 0;
}