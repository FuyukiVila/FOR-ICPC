#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
const int INF = 1 << 30;
const int N = 1005;

int dp[N][N];
int p[N][N];
int sum[N];
int n;

int getMinval() {
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
        p[i][i] = i;
    }
    for (int len = 1; len < n; len++) {
        for (int i = 1; i + len <= n; i++) {
            int end = i + len;
            int tmp = INF;
            int k = 0;
            for (int j = p[i][end - 1]; j <= p[i + 1][end]; j++) {
                if (dp[i][j] + dp[j + 1][end] + sum[end] - sum[i - 1] < tmp) {
                    tmp = dp[i][j] + dp[j + 1][end] + sum[end] - sum[i - 1];
                    k = j;
                }
            }
            dp[i][end] = tmp;
            p[i][end] = k;
        }
    }
    return dp[1][n];
}

int main() {
    while (scanf("%d", &n) != EOF) {
        sum[0] = 0;
        for (int i = 1; i <= n; i++) {
            int val;
            scanf("%d", &val);
            sum[i] = sum[i - 1] + val;
        }
        printf("%d\n", getMinval());
    }
    return 0;
}