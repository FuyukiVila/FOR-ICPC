#include "testlib.h"

#include "bits/stdc++.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = rnd.next(1, 200000);
    int k = rnd.next(1, n), m = rnd.next(0, n), x = rnd.next(1, n);
    printf("%d %d %d %d\n", n, k, m, x);
    int tmp = 0;
    string s;
    for (int i = 1; i <= n; i++) {
        int j = rnd.next(0, 2);
        if (tmp + j >= m) {
            j = 0;
        }
        tmp += j;
        s.push_back(j + '0');
        if (i != n)s.push_back(' ');
    }
    println(s);
}