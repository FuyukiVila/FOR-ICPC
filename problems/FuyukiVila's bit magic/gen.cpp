#include "testlib.h"

#include "bits/stdc++.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int testCaseCount = rnd.next(1, 1000);
    println(testCaseCount);
    for (int i = 1; i <= testCaseCount; i++) {
        int len = rnd.next(1, 50);
        string s, t;
        for (int i = 1; i <= len; i++) {
            s.push_back(rnd.next('0', '1'));
        }
        for (int i = 1; i <= len; i++) {
            t.push_back(rnd.next('0', '1'));
        }
        println(s);
        println(t);
    }
}