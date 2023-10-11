#include "testlib.h"
#include "bits/stdc++.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int testCaseCount = inf.readInt(1, 1000, "t");
    inf.readEoln();
    for (int testCase = 1; testCase <= testCaseCount; testCase++) {
        setTestCase(testCase);
        string s = inf.readString();
        string t = inf.readString();
    }
    inf.readEof();
}