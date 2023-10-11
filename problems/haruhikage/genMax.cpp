#include "testlib.h"

#include "bits/stdc++.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = 200000;
    int k = 1, m = n, x = n;
    printf("%d %d %d %d\n", n, k, m, x);
    string s;
    for (int i = 1; i <= n; i++) {
        s.push_back('7');
        if (i != n)s.push_back(' ');
    }
    println(s);
}