// https://yukicoder.me/problems/no/1419
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "num/ModInt.hpp"
/*</head>*/
#else
/*<body>*/
/*</body>*/
#endif

struct cww {
    cww() {
        io::enableFastIO();
        io::setDigits(10);
    }
} star;


int64_t modpow(int64_t a, int n, int m) {
    int64_t ret = 1;
    while (n) {
        if (n % 2 == 1) {
            ret = ret * a % m;
        }
        a = a * a % m;
        n /= 2;
    }
    return ret;
}

int main() {
    /* write here */
    // 1, 3, 5, ..., 2^k - 1 の位置に2^-k が加算される
    // 正の方向に2^(k-1)回
    // if N が奇数
    //   [(2^(k-1)) / N] 回ずつ 0,1,...,N-1 に加算
    //   (2^(k-1)) % N 回 1, 3, ..., に加算
    //   これを逆方向にもやる

    // if N が偶数
    //   [(2^(k-1)) / (N/2)] 回ずつ 1, 3, ...,N-1 に加算
    //   (2^(k-1)) % (N/2) 回 1, 3, ..., に加算

    int n, k;
    cin >> n >> k;

    vector<ModInt> ret(n, ModInt(0));

    if (n % 2 == 1) {
        int p    = modpow(2, k - 1, n);
        ModInt t = ModInt(2) ^ (k - 1);
        cerr << p << " " << *t << endl;
        for (int i : range(n)) {
            ret[i] += 2 * ((t - ModInt(p)) / n);
        }

        for (int i : range(n)) {
            cout << *(ret[i]) << " ";
        }
        cout << endl;

        int k;
        k = 1;
        for (int i : range(p)) {
            ret[k] += 1;
            ret[(n - k) % n] += 1;
            k = (k + 2) % n;
        }
    }
    else {
    }

    ModInt Q = ModInt(2) ^ k;


    for (int i : range(n)) {
        cout << *(ret[i] * inv(Q)) << "\n";
    }
    cout.flush();

    return 0;
}
