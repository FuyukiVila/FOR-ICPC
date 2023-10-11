#include "testlib.h"

#include "bits/stdc++.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = rnd.next(1, 200000);
    int k = rnd.next(1, n), m = rnd.next(0, n), x = rnd.next(1, n);
    printf("%d %d %d %d\n", n, k, m, x);
    string s;
    for (int i = 1; i <= n; i++) {
        s.push_back(rnd.next('0', '7'));
        if (i != n)s.push_back(' ');
    }
    println(s);
}