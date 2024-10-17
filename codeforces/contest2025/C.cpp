#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))
#define cpy(a, b) memcpy(a, b, sizeof(a))
//#define _DEBUG
//#define PRIME

#include <bits/stdc++.h>

#ifdef _DEBUG

#define dbg(x...) do { std::cout << #x << " -> "; err(x); } while (0)

void err() { std::cout << std::endl; }

template<class T, class... Ts>
void err(T arg, Ts &...args) {
	std::cout << arg << ' ';
	err(args...);
}

#else

#define dbg(x...) 114514;

#endif

using namespace std;
using ll = long long;
using ull = unsigned long long;
constexpr int INF = 0x3f3f3f3f;
ll mod = 0;

inline ll qpow(ll _a, ll _n, ll _mod = mod) {
	ll ans = 1;
	while (_n) {
		if (_n & 1)
			ans *= _a;
		_n >>= 1;
		_a *= _a;
		if (_mod > 0) {
			ans %= _mod;
			_a %= _mod;
		}
	}
	return ans;
}

#ifdef PRIME

namespace prime {
	const int N = 1e7 + 100;
	vector<int> minp(N);
	vector<int> primes;
	bitset<N> st;
	
	void get_primes(int n) {
		for (int i = 2; i <= n; i++) {
			if (!st[i])
				minp[i] = i, primes.emplace_back(i);
			for (int j = 0; primes[j] * i <= n; j++) {
				int t = primes[j] * i;
				st[t] = true;
				minp[t] = primes[j];
				if (i % primes[j] == 0)
					break;
			}
		}
	}
}

#endif


inline void init() {
	/*Init Here*/
	
}

void idol_produce(int testCase) {
	/*Code Here*/
	int n, k;
	cin >> n >> k;
	vector<pair<int,int> >a;
	map<int,int>cnt;
	for(int i = 1;i <= n; i++){
		int x;
		cin >> x;
		cnt[x] ++;
	}
	a.push_back({0, 0});
	for(auto [x, y] : cnt){
		a.push_back({x, y});
	}
	vector<int>pre(a.size() + 1);
	for(int i = 1;i < a.size(); i++){
		pre[i] = pre[i - 1] + a[i].second;
	}
	int ans = 0;
	for(int i = 1;i < a.size(); i++){
		int l = i, r = min((int)a.size() - 1, i + k - 1);
		int res = l;
		while(l <= r){
			int mid = (l + r) / 2;
			if(mid - i + 1 == a[mid].first - a[i].first + 1){
				res = mid;
				l = mid + 1;
			}
			else{
				r = mid - 1;
			}
		}
		ans = max(ans, pre[res] - pre[i - 1]);
	}
	cout << ans << '\n';
}


signed main() {
	GKD;
	init();
	int T = 1;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		idol_produce(i);
	}
	return 0;
}
