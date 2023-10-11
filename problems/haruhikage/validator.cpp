#include "testlib.h"
#include "bits/stdc++.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readSpace();
    int m = inf.readInt(0, n, "m");
    inf.readSpace();
    int x = inf.readInt(1, n, "x");
    inf.readEoln();
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = inf.readInt(0, 7, "a[i]");
        if (i != n) inf.readSpace();
    }
    inf.readEoln();
    inf.readEof();
}