// https://atcoder.jp/contests/jsc2021/tasks/jsc2021_g
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "structure/UnionFind.hpp"
/*</head>*/
#else
/*<body>*/
/* #region auto includes */
/* #region stl */
/*<stl>*/
#    include <bits/stdc++.h>
#    include <sys/types.h>
#    include <unistd.h>
using namespace std;
/*</stl>*/
/* #endregion */
/* #region template/Grid.hpp*/

/**
 * @brief グリッドをラップするための関数
 * @tparam T std::string や std;:vector を想定
 * @tparam U 周りに配置する要素の型
 * @param grid 入力、R > 0 でないとバグる
 * @param material 周りに配置する要素
 * @return std::vector<T> material で 周りを埋めた grid
 */
template <typename T, typename U>
inline std::vector<T> wrapGrid(std::vector<T> grid, U material) {
    std::vector<T> wrappedGrid(grid.size() + 2,
                               T(grid[0].size() + 2, material));
    for (std::size_t i = 0; i < grid.size(); i++) {
        for (std::size_t j = 0; j < grid[i].size(); j++) {
            wrappedGrid[i + 1][j + 1] = grid[i][j];
        }
    }
    return wrappedGrid;
}

/**
 * @brief
 *
 */
constexpr int dr4[] = {0, 1, 0, -1};
constexpr int dc4[] = {-1, 0, 1, 0};
/* #endregion */
/* #region template/IO.hpp*/
/**
 * @file IO.hpp
 * @author btk
 * @brief cin高速化とか，出力の小数桁固定とか
 * @version 0.2
 * @date 2021-03-01
 *
 * @copyright Copyright (c) 2021
 */


/**
 * @brief 入出力の設定を行うための構造体
 */

namespace io {
    inline void enableFastIO() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(0);
    }
    inline void setDigits(int digits) {
        std::cout << std::fixed;
        std::cout << std::setprecision(digits);
    }
} // namespace io

/**
 * @brief
 * vectorに直接cin流すためのやつ
 * @tparam T
 * @param is
 * @param v
 * @return istream&
 */
template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &it : v) is >> it;
    return is;
}
/* #endregion */
/* #region template/IncludeSTL.hpp*/
/**
 * @file IncludeSTL.hpp
 * @author btk
 * @brief 標準ライブラリをincludeするだけ
 * @version 0.1
 * @date 2019-07-21
 * @todo 何故か2回includeされる（展開scriptに
 * @copyright Copyright (c) 2019
 *
 */


/* #endregion */
/* #region template/Loop.hpp*/
/**
 * @file Loop.hpp
 * @author btk
 * @brief rangeとかループ系のクラス
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 *
 */


/**
 * @brief
 * rangeを逆向きに操作したいとき用
 * @details
 * ループの範囲は[bg,ed)なので注意
 * @see range
 */
class reverse_range {
  private:
    struct I {
        int x;
        int operator*() { return x - 1; }
        bool operator!=(I &lhs) { return x > lhs.x; }
        void operator++() { --x; }
    };
    I i, n;

  public:
    /**
     * @brief Construct a new reverse range object
     *
     * @param n
     */
    reverse_range(int n) : i({0}), n({n}) {}
    /**
     * @brief Construct a new reverse range object
     *
     * @param i
     * @param n
     */
    reverse_range(int i, int n) : i({i}), n({n}) {}
    /**
     * @brief
     * begin iterator
     * @return I&
     */
    I &begin() { return n; }
    /**
     * @brief
     * end iterator
     * @return I&
     */
    I &end() { return i; }
};
/**
 * @brief
 * python みたいな range-based for を実現
 * @details
 * ループの範囲は[bg,ed)なので注意
 * !つけると逆向きにループが回る (reverse_range)
 * 空間計算量はO(1)
 * 使わない変数ができて警告が出がちなので，unused_varとかを使って警告消しするとよい
 */
class range {
  private:
    struct I {
        int x;
        int operator*() { return x; }
        bool operator!=(I &lhs) { return x < lhs.x; }
        void operator++() { ++x; }
    };
    I i, n;

  public:
    /**
     * @brief Construct a new range object
     *
     * @param n
     */
    range(int n) : i({0}), n({n}) {}
    /**
     * @brief Construct a new range object
     *
     * @param i
     * @param n
     */
    range(int i, int n) : i({i}), n({n}) {}
    /**
     * @brief
     * begin iterator
     * @return I&
     */
    I &begin() { return i; }
    /**
     * @brief
     * end iterator
     * @return I&
     */
    I &end() { return n; }
    /**
     * @brief
     * 逆向きに参照するrange(reverse_rangeを取得できるs)
     * @return reverse_range
     */
    reverse_range operator!() { return reverse_range(*i, *n); }
};
/* #endregion */
/* #region template/Macro.hpp*/
/**
 * @file Macro.hpp
 * @author btk
 * @brief マクロとか，LLとか
 * @version 0.1
 * @date 2019-07-13
 *
 * @copyright Copyright (c) 2019
 *
 */


/**
 * @def DEBUG
 * @brief デバッグ用のif文 提出時はif(0)で実行されない
 */

/*</head>*/
#    ifdef BTK
#        define DEBUG if (1)
#    else
#        define DEBUG if (0)
#    endif
/**
 * @def ALL(v)
 * @brief
 * ALLマクロ
 */
#    define ALL(v) (v).begin(), (v).end()

/**
 * @def REC(ret, ...)
 * @brief
 * 再帰ラムダをするためのマクロ
 */
#    define REC(ret, ...) std::function<ret(__VA_ARGS__)>

/**
 * @def VAR_NAME(var)
 * @brief 変数名を取得する
 */
#    define VAR_NAME(var) #    var

/**
 * @brief
 * rangeで生まれる使わない変数を消す用（警告消し）
 */
template <typename T>
inline T &unused_var(T &v) {
    return v;
}

template <typename T>
std::vector<T> nestingVector(std::size_t size) {
    return std::vector<T>(size);
}

template <typename T, typename... Ts>
inline auto nestingVector(std::size_t size, Ts... ts) {
    return std::vector<decltype(nestingVector<T>(ts...))>(
        size, nestingVector<T>(ts...));
}
/* #endregion */
/* #region template/ChainOperation.hpp*/
/**
 * @file ChainOperation.hpp
 * @author btk
 * @brief パラメータパックを利用した演算子結合を実現
 */


/**
 * @brief テンプレート再帰の末尾
 * @tparam F 二項演算
 * @tparam T
 * @param v
 * @return T
 */
template <typename F, typename T>
inline T chain(T &&v) {
    return v;
}

/**
 * @brief 複数項における演算の結果を返す
 * @tparam F
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename F, typename T, typename... Ts>
inline auto chain(const T head, Ts &&...tail) {
    return F::exec(head, chain<F>(tail...));
}

/**
 * @brief
 * 先頭の値をFで参照する関数に基づいて変更できたらする
 * @tparam F
 * @tparam T
 * @tparam Ts
 * @param target
 * @param candidates
 * @return true
 * @return false
 */
template <typename F, typename T, typename... Ts>
inline bool changeTarget(T &target, Ts &&...candidates) {
    const T old = target;
    target      = chain<F>(target, candidates...);
    return old != target;
}
/* #endregion */
/* #region template/Math.hpp*/
/**
 * @file Math.hpp
 * @author btk
 * @brief 最大値とか最小値を求める
 */

/**
 * @brief gcd, ceil等自作算数用関数を集める。stdと被るので名前空間を区切る
 */
namespace math {

    /**
     * @brief 拡張ユークリッド互除法
     * @details ax + by = gとなるx,yを求める
     * @param a 入力
     * @param b 入力
     * @param x 値引き継ぎ用の変数
     * @param y 値引き継ぎ用の変数
     * @return int64_t g:aとbの最大公約数
     */
    int64_t extgcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
        int64_t g = a;
        x         = 1;
        y         = 0;
        if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
        return g;
    }


    /**
     * @brief 一次不定方程式の解
     * @details 値の説明は betouzEquation 関数を参照のこと
     */
    struct BetouzSolution {
        int64_t x, y, dx, dy;
    };


    /**
     * @brief 一次不定方程式
     * @details a(x + k*dx) + b(y -k*dy) = cとなる x, y, dx, dy を求める。
     * @param a 入力
     * @param b 入力
     * @param c 入力
     * @return int64_t 解がないときは nullopt が返る
     */
    std::optional<BetouzSolution> betouzEquation(int64_t a, int64_t b,
                                                 int64_t c) {
        BetouzSolution sol;
        const int64_t g = extgcd(a, b, sol.x, sol.y);
        if (c % g == 0) {
            return std::nullopt;
        }
        sol.dx = b / g;
        sol.dy = a / g;
        sol.x *= c / g;
        sol.y *= c / g;
        return sol;
    }

    namespace inner {
        /**
         * @brief 2項のgcdを求める
         * @tparam T
         */
        template <typename T>
        struct GCDFunc {
            /**
             * @brief 本体
             * @param l
             * @param r
             * @return T
             */
            static inline T exec(T l, T r) {
                while (r != 0) {
                    T u = l % r;
                    l   = r;
                    r   = u;
                }
                return l;
            }
        };

        /**
         * @brief 2項のgcdを求める
         * @tparam T
         */
        template <typename T>
        struct LCMFunc {
            /**
             * @brief 本体
             * @param l
             * @param r
             * @return T
             */
            static inline T exec(T l, T r) {
                return (l / GCDFunc<T>::exec(l, r)) * r;
            }
        };

    } // namespace inner

    /**
     * @brief valuesの最大公約数
     * @tparam Ts パラメータパック
     * @param values gcdを求めたい値の集合（2個以上）
     * @return int64 最大公約数
     */
    template <typename... Ts>
    inline int64_t gcd(Ts &&...values) {
        return chain<inner::GCDFunc<int64_t>>(values...);
    }

    /**
     * @brief valuesの最小公倍数
     * @tparam Ts パラメータパック
     * @param values lcmを求めたい値の集合（2個以上）
     * @return int64 最小公倍数
     */
    template <typename... Ts>
    inline int64_t lcm(Ts &&...values) {
        return chain<inner::LCMFunc<int64_t>>(values...);
    }

    /**
     * @brief iterator で指定された集合のlcmを求める
     * @tparam ITR iterator
     * @param l 開始位置
     * @param r 終了位置
     * @return int64_t lcm
     */
    template <typename ITR>
    inline int64_t lcmAll(ITR l, ITR r) {
        int64_t ret = 1;
        for (auto it = l; it != r; ++it) {
            ret = lcm(ret, *it);
        }
        return ret;
    }

    /**
     * @brief container (配列など) で指定された要素のlcmを求める
     * @tparam Container vectorやlist
     * @param container コンテナ
     * @return int64_t lcm
     */
    template <typename Container>
    inline int64_t lcmAll(Container container) {
        int64_t ret = 1;
        for (auto e : container) {
            ret = lcm(ret, e);
        }
        return ret;
    }

    /**
     * @brief iterator で指定された集合のgcdを求める
     * @tparam ITR iterator
     * @param l 開始位置
     * @param r 終了位置
     * @return int64_t lcm
     */
    template <typename ITR>
    inline int64_t gcdAll(ITR l, ITR r) {
        int64_t ret = 0;
        for (auto it = l; it != r; ++it) {
            ret = gcd(ret, *it);
        }
        return ret;
    }

    /**
     * @brief container (配列など) で指定された要素のgcdを求める
     * @tparam Container vectorやlist
     * @param container コンテナ
     * @return int64_t gcd
     */
    template <typename Container>
    inline int64_t gcdAll(Container container) {
        int64_t ret = 0;
        for (auto e : container) {
            ret = gcd(ret, e);
        }
        return ret;
    }

    /**
     * @brief u/dを切り上げした整数を求める
     * @todo 負の数への対応
     * @tparam T 整数型
     * @param u 入力
     * @param d 入力
     * @return T 切り上げ後の値
     */
    template <typename T>
    inline T ceil(T u, T d) {
        return (u + d - (T)1) / d;
    }

} // namespace math

/**
 * @brief 2項の最小値求める
 * @tparam T
 */
template <typename T>
struct minFunc {
    /**
     * @brief 本体
     * @param l
     * @param r
     * @return T
     */
    static T exec(const T l, const T r) { return l < r ? l : r; }
};

/**
 * @brief 2項の最大値求める
 *
 * @tparam T
 */
template <typename T>
struct maxFunc {
    /**
     * @brief 本体
     *
     * @param l
     * @param r
     * @return T
     */
    static T exec(const T l, const T r) { return l > r ? l : r; }
};

/**
 * @brief 複数項の最小値
 * @see chain
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename T, typename... Ts>
inline T minOf(T head, Ts... tail) {
    return chain<minFunc<T>>(head, tail...);
}

/**
 * @brief 複数項の最大値
 * @see chain
 * @tparam T
 * @tparam Ts
 * @param head
 * @param tail
 * @return T
 */
template <typename T, typename... Ts>
inline T maxOf(T head, Ts... tail) {
    return chain<maxFunc<T>>(head, tail...);
}

/**
 * @brief change min
 * @tparam T 型
 * @param target 変更する値
 * @param candidates
 * @return 更新があればtrue
 */
template <typename T, typename... Ts>
inline bool chmin(T &target, Ts &&...candidates) {
    return changeTarget<minFunc<T>>(target, candidates...);
}

/**
 * @brief chminのmax版
 * @see chmin
 * @tparam T 型
 * @param target 変更する値
 * @param candidates
 * @return 更新があればtrue
 */
template <typename T, typename... Ts>
inline bool chmax(T &target, Ts &&...candidates) {
    return changeTarget<maxFunc<T>>(target, candidates...);
}
/* #endregion */
/* #region template/Random.hpp*/
/**
 * @file Random.hpp
 * @author btk
 * @brief 乱数生成系
 * @version 0.1
 * @date 2019-07-13
 * @copyright Copyright (c) 2019
 */


//! 乱数のシード値をプロセスIDとして取得
const pid_t pid = getpid();

/**
 * @brief XorShift32の実装
 */
class XorShift32 {
  private:
    //! XorShiftの現在の値
    unsigned value;

    /**
     * @brief XorShift32のアルゴリズムに基づいて value を更新
     */
    inline void update() {
        value = value ^ (value << 13);
        value = value ^ (value >> 17);
        value = value ^ (value << 5);
    }

    /**
     * @brief 値を更新し，更新前の値を返却
     * @return unsigned 呼び出し時の value を用いる
     */
    inline unsigned get() {
        unsigned v = value;
        update();
        return v;
    }

  public:
    /**
     * @brief [0, 2^bit) の範囲の乱数値を取り出す
     * @tparam デフォルトは31
     * @return int
     */
    template <int bit = 31>
    inline int next_int() {
        return (int)(get() >> (32 - bit));
    }

    /**
     * @brief [-2^bit,2^bit)の範囲の乱数値を取り出す
     * @tparam デフォルトは31
     * @return int
     */
    template <int bit = 31>
    inline int next_signed() {
        unsigned v = get();
        return (int)((v >> (31 - bit)) - (1 << (bit)));
    }

    /**
     * @brief next_int呼び出し時の最大値を取得
     * @tparam 31
     * @return int
     */
    template <int bit = 31>
    inline int range_max() {
        return (int)((1u << bit) - 1);
    };

    /**
     * @brief Construct a new XorShift32 object
     * @param seed
     * @details 初期シードをvalueとするXorShift32のインスタンスを生成
     */
    XorShift32(const unsigned seed) {
        value = seed;
        update();
    }

    /**
     * @brief Construct a new XorShift 32 object
     * @details 初期シードをプロセスIDとするXorShift32のインスタンスを生成
     */
    XorShift32() : XorShift32(pid) {}
};
/* #endregion */
/* #region template/STLExtension.hpp*/
/**
 * @file STLExtension.hpp
 * @brief STL独自拡張
 */

namespace ext {
    /**
     * @brief std::sortのWrapper関数
     * @tparam Container std::vectorやstd::listを想定
     * @param container ソートしたいコンテナオブジェクト
     * @return Container&
     * ソート後のコンテナオブジェクト==引数に渡したオブジェクト
     */
    template <typename Container>
    inline Container &sort(Container &container) {
        sort(std::begin(container), std::end(container));
        return container;
    }

    /**
     * @brief std::sortのWrapper関数
     * @tparam Container std::vectorやstd::listを想定
     * @tparam Comparator 比較関数の型
     * @param container ソートしたいコンテナオブジェクト
     * @param comparator 比較関数
     * @return Container&
     * ソート後のコンテナオブジェクト==引数に渡したオブジェクト
     */
    template <typename Container, typename Comparator>
    inline Container &sort(Container &container, Comparator comparator) {
        sort(std::begin(container), std::end(container), comparator);
        return container;
    }

    /**
     * @brief std::reverseのWrapper関数
     * @tparam Container std::vectorやstd::listを想定
     * @param container 反転したいコンテナオブジェクト
     * @return Container&
     * 反転後のコンテナオブジェクト==引数に渡したオブジェクト
     */
    template <typename Container>
    inline Container &reverse(Container &container) {
        reverse(std::begin(container), std::end(container));
        return container;
    }

    /**
     * @brief std::accumulateのvector限定Wrapper関数
     * @tparam T 配列の要素の型
     * @tparam U 戻り値の型
     * @param container 配列
     * @param zero 初期値
     * @return U 総和
     */
    template <typename T, typename U>
    inline U accumulate(const std::vector<T> &container, U zero) {
        return std::accumulate(std::begin(container), std::end(container),
                               zero);
    }

    /**
     * @brief std::accumulateのvector限定Wrapper関数の、引数省略版
     * @tparam T 配列の要素の型 && 戻り値の型
     * @param container 配列
     * @return T 総和 overflowに注意
     */
    template <typename T>
    inline T accumulate(const std::vector<T> &container) {
        return accumulate(container, T(0));
    }

    /**
     * @brief std::countのWrapper関数
     * @tparam Container std::vectorやstd::listを想定
     * @tparam T 数える値の型
     * @param container コンテナオブジェクト
     * @param value 数える値
     * @return int
     */
    template <typename Container, typename T>
    inline int count(Container &container, T value) {
        return std::count(std::begin(container), std::end(container), value);
    }

    /**
     * @brief 等差数列のvectorを作る関数
     * @param n 要素数
     * @param startFrom 初項
     * @param step 公差
     * @return std::vector<int> 等差数列
     */
    inline std::vector<int> iota(int n, int startFrom = 0, int step = 1) {
        std::vector<int> container(n);
        int v = startFrom;
        for (int i = 0; i < n; i++, v += step) {
            container[i] = v;
        }
        return container;
    }

    /**
     * @brief
     * (*max_element) のwrapper、位置は返さない
     * @tparam ITR iterator
     * @param l iteratorの最初
     * @param r iteratorの終了位置
     * @param defaultValue 要素がないときのデフォルト値
     * @return auto 最大値、型はコンテナ内の型
     */
    template <typename ITR>
    inline auto maxIn(ITR l, ITR r,
                      std::remove_reference_t<decltype(*l)> defaultValue = 0) {
        if (r == l) {
            return defaultValue;
        }
        return *std::max_element(l, r);
    }


    /**
     * @brief maxIn の vector 限定版
     * @tparam T 戻り値の型
     * @param containter 最大値求める対象のコンテナ
     * @param defaultValue コンテナの要素がない場合の初期値
     * @return T 最大値、コンテナ似要素がない場合はdefaultValue
     */
    template <typename T>
    inline T maxIn(std::vector<T> container, T defaultValue = 0) {
        return maxIn(container.begin(), container.end(), defaultValue);
    }

    /**
     * @brief
     * (*min_element) のwrapper、位置は返さない
     * @tparam ITR iterator
     * @param l iteratorの最初
     * @param r iteratorの終了位置
     * @param defaultValue 要素がないときのデフォルト値
     * @return auto 最小値、型はコンテナ内の型
     */
    template <typename ITR>
    inline auto minIn(ITR l, ITR r,
                      std::remove_reference_t<decltype(*l)> defaultValue = 0) {
        if (r == l) {
            return defaultValue;
        }
        return *std::min_element(l, r);
    }

    /**
     * @brief minIn の vector 限定版
     * @tparam T 戻り値の型
     * @param containter 最大値求める対象のコンテナ
     * @param defaultValue コンテナの要素がない場合の初期値
     * @return T 最小値、コンテナ似要素がない場合はdefaultValue
     */
    template <typename T>
    inline T minIn(std::vector<T> container, T defaultValue = 0) {
        return minIn(container.begin(), container.end(), defaultValue);
    }

} // namespace ext
/* #endregion */
/* #region template/Strings.hpp*/
/**
 * @file Strings.hpp
 * @author btk
 * @brief 文字列を扱いやすくするライブラリ
 */


/**
 * @brief コレクションを文字列に変換する関数
 * @tparam T コレクションの型、range-based for に対応している必要あり
 * @tparam DelimiterType 区切り文字の型
 * @param v コレクション
 * @param delimiter 区切り文字
 * @return std::string delimiterで結合された文字列
 */
template <typename T, typename DelimiterType>
std::string join(const T &v, const DelimiterType &delimiter) {
    std::stringstream ss;
    bool isFirst = true;
    for (auto &it : v) {
        if (!isFirst) {
            ss << delimiter;
        }
        isFirst = false;
        ss << it;
    }
    return ss.str();
}

/**
 * @brief コレクションを文字列に変換する関数（イテレータ版）
 * @tparam ITR イテレータ型
 * @tparam DelimiterType 区切り文字の型
 * @param bg 開始
 * @param ed 終了
 * @param delimiter 区切り文字
 * @return std::string delimiterで結合された文字列
 */
template <typename ITR, typename DelimiterType>
std::string join(const ITR bg, const ITR ed, const DelimiterType &delimiter) {
    std::stringstream ss;
    bool isFirst = true;
    for (auto it = bg; it != ed; ++it) {
        if (!isFirst) {
            ss << delimiter;
        }
        isFirst = false;
        ss << *it;
    }
    return ss.str();
}

/**
 * @brief Strings.hppの内部関数
 */
namespace strings {

    /**
     * @brief std::size_tをWrapする構造体
     * @tparam i 本体
     */
    template <std::size_t i>
    struct IndexWrapper {};

    /**
     * @brief tuple用のjoin関数の内部で使われるテンプレート構造体（関数）
     * @tparam CurrentIndex 現在のindex
     * @tparam LastIndex 最後のindex
     * @tparam DelimiterType 区切り文字
     * @tparam Ts tupleに使用するパラメータパック
     */
    template <typename CurrentIndex, typename LastIndex, typename DelimiterType,
              typename... Ts>
    struct JoinFunc;


    /**
     * @brief tuple用join関数の再帰末尾用構造体 .joinが本体
     * @tparam i 現在のid = tupleの最後の要素のid
     * @tparam DelimiterType 区切り文字
     * @tparam Ts tupleに使用するパラメータパック
     */
    template <std::size_t i, typename DelimiterType, typename... Ts>
    struct JoinFunc<IndexWrapper<i>, IndexWrapper<i>, DelimiterType, Ts...> {
        /**
         * @brief tuple用join関数の末尾再帰
         * @param ss stringstream
         * @param values 文字列化したいtuple
         * @param delimiter 区切り文字
         * @return std::stringstream& 引数で渡したもの
         */
        static std::stringstream &join(std::stringstream &ss,
                                       const std::tuple<Ts...> &values,
                                       const DelimiterType &delimiter) {
            unused_var(delimiter);
            ss << std::get<i>(values);
            return ss;
        }
    };

    /**
     * @brief tuple用join関数の内部構造体
     * @tparam i 現在のid
     * @tparam j tupleの最後の要素のid
     * @tparam DelimiterType 区切り文字
     * @tparam Ts パラメータパック
     */
    template <std::size_t i, std::size_t j, typename DelimiterType,
              typename... Ts>
    struct JoinFunc<IndexWrapper<i>, IndexWrapper<j>, DelimiterType, Ts...> {
        /**
         * @brief tuple用join関数の本体
         * @param ss stringstream
         * @param values 文字列化したいtuple
         * @param delimiter 区切り文字
         * @return std::stringstream& 引数で渡したもの
         */
        static std::stringstream &join(std::stringstream &ss,
                                       const std::tuple<Ts...> &values,
                                       const DelimiterType &delimiter) {
            ss << std::get<i>(values);
            ss << delimiter;
            return JoinFunc<IndexWrapper<i + 1>, IndexWrapper<j>, DelimiterType,
                            Ts...>::join(ss, values, delimiter);
        }
    };
} // namespace strings


/**
 * @brief 複数の値をjoinする関数
 * @tparam DelimiterType 区切り文字の型
 * @tparam Ts パラメータパック
 * @param values 文字列として結合したいタプル
 * @param delimiter 区切り文字
 * @return std::string 結合後の文字列
 */
template <typename DelimiterType, typename... Ts>
std::string join(const std::tuple<Ts...> &values,
                 const DelimiterType &delimiter) {
    std::stringstream ss;
    constexpr std::size_t lastIndex =
        std::tuple_size<std::tuple<Ts...>>::value - 1u;
    return strings::JoinFunc<strings::IndexWrapper<0>,
                             strings::IndexWrapper<lastIndex>, DelimiterType,
                             Ts...>::join(ss, values, delimiter)
        .str();
}
/* #endregion */
/* #region Template.hpp*/
/**
 * @file Template.hpp
 * @brief 競技プログラミング用テンプレート
 * @author btk15049
 * @date 2019/05/02
 */


/* #endregion */
/* #region structure/UnionFind.hpp*/
/**
 * @file UnionFind.hpp
 * @author btk
 * @brief Union-Find 木
 * @version 0.1
 * @date 2019-06-26
 * @todo test
 */

/**
 * @brief unionとfindとsameができる普通のUnion-Find
 */
class UnionFind {
  private:
    std::vector<int> par, rank;

    /**
     * @brief ${x}の親を${new_par}に設定åå
     * @param x
     * @param new_par
     */
    inline void set_par(int x, int new_par) { par[x] = new_par; }

  public:
    /**
     * @brief xの親を探す
     * @param x
     * @return int
     */
    int find(int x) {
        if (par[x] != x) {
            int new_par = find(par[x]);
            set_par(x, new_par);
        }
        return par[x];
    }

    /**
     * @brief Construct a new Union Find object
     *
     * @param n
     */
    UnionFind(int n) : par(n), rank(n) {
        for (int i = 0; i < n; i++) {
            par[i] = i, rank[i] = 0;
        }
    }

    /**
     * @brief {xの属する集合}と{yの属する集合}をマージする
     *
     * @param x
     * @param y
     * @return true マージに成功したとき
     * @return false マージに失敗したとき（もともと同じ集合に属していた時）
     */
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) std::swap(x, y);
        set_par(y, x);
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }

    /**
     * @brief xとyが同じ集合に属しているかどうか判定する
     * @param x
     * @param y
     * @return true
     * @return false
     */
    bool same(int x, int y) { return find(x) == find(y); }
};
/* #endregion */
/* #endregion */
/*</body>*/
#endif

#include <atcoder/convolution>

namespace nyaan {
    template <class T>
    struct Matrix {
        vector<vector<T>> A;

        Matrix() = default;
        Matrix(int n, int m) : A(n, vector<T>(m, T())) {}
        Matrix(int n) : A(n, vector<T>(n, T())){};

        int H() const { return A.size(); }

        int W() const { return A[0].size(); }

        int size() const { return A.size(); }

        inline const vector<T> &operator[](int k) const { return A[k]; }

        inline vector<T> &operator[](int k) { return A[k]; }

        static Matrix I(int n) {
            Matrix mat(n);
            for (int i = 0; i < n; i++) mat[i][i] = 1;
            return (mat);
        }

        Matrix &operator+=(const Matrix &B) {
            int n = H(), m = W();
            assert(n == B.H() && m == B.W());
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) (*this)[i][j] += B[i][j];
            return (*this);
        }

        Matrix &operator-=(const Matrix &B) {
            int n = H(), m = W();
            assert(n == B.H() && m == B.W());
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) (*this)[i][j] -= B[i][j];
            return (*this);
        }

        Matrix &operator*=(const Matrix &B) {
            int n = H(), m = B.W(), p = W();
            assert(p == B.H());
            vector<vector<T>> C(n, vector<T>(m, T{}));
            for (int i = 0; i < n; i++)
                for (int k = 0; k < p; k++)
                    for (int j = 0; j < m; j++)
                        C[i][j] += (*this)[i][k] * B[k][j];
            A.swap(C);
            return (*this);
        }

        Matrix &operator^=(long long k) {
            Matrix B = Matrix::I(H());
            while (k > 0) {
                if (k & 1) B *= *this;
                *this *= *this;
                k >>= 1LL;
            }
            A.swap(B.A);
            return (*this);
        }

        Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }

        Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }

        Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }

        Matrix operator^(const long long k) const {
            return (Matrix(*this) ^= k);
        }

        bool operator==(const Matrix &B) const {
            assert(H() == B.H() && W() == B.W());
            for (int i = 0; i < H(); i++)
                for (int j = 0; j < W(); j++)
                    if (A[i][j] != B[i][j]) return false;
            return true;
        }

        bool operator!=(const Matrix &B) const {
            assert(H() == B.H() && W() == B.W());
            for (int i = 0; i < H(); i++)
                for (int j = 0; j < W(); j++)
                    if (A[i][j] != B[i][j]) return true;
            return false;
        }

        friend ostream &operator<<(ostream &os, const Matrix &p) {
            int n = p.H(), m = p.W();
            for (int i = 0; i < n; i++) {
                os << (i ? "   " : "") << "[";
                for (int j = 0; j < m; j++) {
                    os << p[i][j] << (j + 1 == m ? "]\n" : ",");
                }
            }
            return (os);
        }

        T determinant() const {
            Matrix B(*this);
            assert(H() == W());
            T ret = 1;
            for (int i = 0; i < H(); i++) {
                int idx = -1;
                for (int j = i; j < W(); j++) {
                    if (B[j][i] != 0) {
                        idx = j;
                        break;
                    }
                }
                if (idx == -1) return 0;
                if (i != idx) {
                    ret *= T(-1);
                    swap(B[i], B[idx]);
                }
                ret *= B[i][i];
                T inv = T(1) / B[i][i];
                for (int j = 0; j < W(); j++) {
                    B[i][j] *= inv;
                }
                for (int j = i + 1; j < H(); j++) {
                    T a = B[j][i];
                    if (a == 0) continue;
                    for (int k = i; k < W(); k++) {
                        B[j][k] -= B[i][k] * a;
                    }
                }
            }
            return ret;
        }
    };

/**
 * @brief 行列ライブラリ
 */
#line 2 "matrix/polynomial-matrix-determinant.hpp"


#line 2 "fps/formal-power-series.hpp"

    template <typename mint>
    struct FormalPowerSeries : vector<mint> {
        using vector<mint>::vector;
        using FPS = FormalPowerSeries;

        FPS &operator+=(const FPS &r) {
            if (r.size() > this->size()) this->resize(r.size());
            for (int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
            return *this;
        }

        FPS &operator+=(const mint &r) {
            if (this->empty()) this->resize(1);
            (*this)[0] += r;
            return *this;
        }

        FPS &operator-=(const FPS &r) {
            if (r.size() > this->size()) this->resize(r.size());
            for (int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
            return *this;
        }

        FPS &operator-=(const mint &r) {
            if (this->empty()) this->resize(1);
            (*this)[0] -= r;
            return *this;
        }

        FPS &operator*=(const mint &v) {
            for (int k = 0; k < (int)this->size(); k++) (*this)[k] *= v;
            return *this;
        }

        FPS &operator/=(const FPS &r) {
            if (this->size() < r.size()) {
                this->clear();
                return *this;
            }
            int n = this->size() - r.size() + 1;
            if ((int)r.size() <= 64) {
                FPS f(*this), g(r);
                g.shrink();
                mint coeff = g.back().inverse();
                for (auto &x : g) x *= coeff;
                int deg = (int)f.size() - (int)g.size() + 1;
                int gs  = g.size();
                FPS quo(deg);
                for (int i = deg - 1; i >= 0; i--) {
                    quo[i] = f[i + gs - 1];
                    for (int j = 0; j < gs; j++) f[i + j] -= quo[i] * g[j];
                }
                *this = quo * coeff;
                this->resize(n, mint(0));
                return *this;
            }
            return *this = ((*this).rev().pre(n) * r.rev().inv(n)).pre(n).rev();
        }

        FPS &operator%=(const FPS &r) {
            *this -= *this / r * r;
            shrink();
            return *this;
        }

        FPS operator+(const FPS &r) const { return FPS(*this) += r; }
        FPS operator+(const mint &v) const { return FPS(*this) += v; }
        FPS operator-(const FPS &r) const { return FPS(*this) -= r; }
        FPS operator-(const mint &v) const { return FPS(*this) -= v; }
        FPS operator*(const FPS &r) const { return FPS(*this) *= r; }
        FPS operator*(const mint &v) const { return FPS(*this) *= v; }
        FPS operator/(const FPS &r) const { return FPS(*this) /= r; }
        FPS operator%(const FPS &r) const { return FPS(*this) %= r; }
        FPS operator-() const {
            FPS ret(this->size());
            for (int i = 0; i < (int)this->size(); i++) ret[i] = -(*this)[i];
            return ret;
        }

        void shrink() {
            while (this->size() && this->back() == mint(0)) this->pop_back();
        }

        FPS rev() const {
            FPS ret(*this);
            reverse(begin(ret), end(ret));
            return ret;
        }

        FPS dot(FPS r) const {
            FPS ret(min(this->size(), r.size()));
            for (int i = 0; i < (int)ret.size(); i++)
                ret[i] = (*this)[i] * r[i];
            return ret;
        }

        FPS pre(int sz) const {
            return FPS(begin(*this), begin(*this) + min((int)this->size(), sz));
        }

        FPS operator>>(int sz) const {
            if ((int)this->size() <= sz) return {};
            FPS ret(*this);
            ret.erase(ret.begin(), ret.begin() + sz);
            return ret;
        }

        FPS operator<<(int sz) const {
            FPS ret(*this);
            ret.insert(ret.begin(), sz, mint(0));
            return ret;
        }

        FPS diff() const {
            const int n = (int)this->size();
            FPS ret(max(0, n - 1));
            mint one(1), coeff(1);
            for (int i = 1; i < n; i++) {
                ret[i - 1] = (*this)[i] * coeff;
                coeff += one;
            }
            return ret;
        }

        FPS integral() const {
            const int n = (int)this->size();
            FPS ret(n + 1);
            ret[0] = mint(0);
            if (n > 0) ret[1] = mint(1);
            auto mod = mint::get_mod();
            for (int i = 2; i <= n; i++) ret[i] = (-ret[mod % i]) * (mod / i);
            for (int i = 0; i < n; i++) ret[i + 1] *= (*this)[i];
            return ret;
        }

        mint eval(mint x) const {
            mint r = 0, w = 1;
            for (auto &v : *this) r += w * v, w *= x;
            return r;
        }

        FPS log(int deg = -1) const {
            assert((*this)[0] == mint(1));
            if (deg == -1) deg = (int)this->size();
            return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
        }

        FPS pow(int64_t k, int deg = -1) const {
            const int n = (int)this->size();
            if (deg == -1) deg = n;
            for (int i = 0; i < n; i++) {
                if ((*this)[i] != mint(0)) {
                    if (i * k > deg) return FPS(deg, mint(0));
                    mint rev = mint(1) / (*this)[i];
                    FPS ret  = (((*this * rev) >> i).log(deg) * k).exp(deg)
                              * ((*this)[i].pow(k));
                    ret = (ret << (i * k)).pre(deg);
                    if ((int)ret.size() < deg) ret.resize(deg, mint(0));
                    return ret;
                }
            }
            return FPS(deg, mint(0));
        }

        static void *ntt_ptr;
        static void set_fft();
        FPS &operator*=(const FPS &r);
        void ntt();
        void intt();
        void ntt_doubling();
        static int ntt_pr();
        FPS inv(int deg = -1) const;
        FPS exp(int deg = -1) const;
    };
    template <typename mint>
    void *FormalPowerSeries<mint>::ntt_ptr = nullptr;

/**
 * @brief 多項式/形式的冪級数ライブラリ
 * @docs docs/fps/formal-power-series.md
 */
#line 2 "fps/polynomial-interpolation.hpp"

#line 2 "fps/multipoint-evaluation.hpp"

#line 4 "fps/multipoint-evaluation.hpp"

    template <typename mint>
    struct ProductTree {
        using fps = FormalPowerSeries<mint>;
        const vector<mint> &xs;
        vector<fps> buf;
        int N, xsz;
        vector<int> l, r;
        ProductTree(const vector<mint> &xs_) : xs(xs_), xsz(xs.size()) {
            N = 1;
            while (N < (int)xs.size()) N *= 2;
            buf.resize(2 * N);
            l.resize(2 * N, xs.size());
            r.resize(2 * N, xs.size());
            fps::set_fft();
            if (fps::ntt_ptr == nullptr)
                build();
            else
                build_ntt();
        }

        void build() {
            for (int i = 0; i < xsz; i++) {
                l[i + N]   = i;
                r[i + N]   = i + 1;
                buf[i + N] = {-xs[i], 1};
            }
            for (int i = N - 1; i > 0; i--) {
                l[i] = l[(i << 1) | 0];
                r[i] = r[(i << 1) | 1];
                if (buf[(i << 1) | 0].empty())
                    continue;
                else if (buf[(i << 1) | 1].empty())
                    buf[i] = buf[(i << 1) | 0];
                else
                    buf[i] = buf[(i << 1) | 0] * buf[(i << 1) | 1];
            }
        }

        void build_ntt() {
            fps f;
            f.reserve(N * 2);
            for (int i = 0; i < xsz; i++) {
                l[i + N]   = i;
                r[i + N]   = i + 1;
                buf[i + N] = {-xs[i] + 1, -xs[i] - 1};
            }
            for (int i = N - 1; i > 0; i--) {
                l[i] = l[(i << 1) | 0];
                r[i] = r[(i << 1) | 1];
                if (buf[(i << 1) | 0].empty())
                    continue;
                else if (buf[(i << 1) | 1].empty())
                    buf[i] = buf[(i << 1) | 0];
                else if (buf[(i << 1) | 0].size() == buf[(i << 1) | 1].size()) {
                    buf[i] = buf[(i << 1) | 0];
                    f.clear();
                    copy(begin(buf[(i << 1) | 1]), end(buf[(i << 1) | 1]),
                         back_inserter(f));
                    buf[i].ntt_doubling();
                    f.ntt_doubling();
                    for (int j = 0; j < (int)buf[i].size(); j++)
                        buf[i][j] *= f[j];
                }
                else {
                    buf[i] = buf[(i << 1) | 0];
                    f.clear();
                    copy(begin(buf[(i << 1) | 1]), end(buf[(i << 1) | 1]),
                         back_inserter(f));
                    buf[i].ntt_doubling();
                    f.intt();
                    f.resize(buf[i].size(), mint(0));
                    f.ntt();
                    for (int j = 0; j < (int)buf[i].size(); j++)
                        buf[i][j] *= f[j];
                }
            }
            for (int i = 0; i < 2 * N; i++) {
                buf[i].intt();
                buf[i].shrink();
            }
        }
    };

    template <typename mint>
    vector<mint> InnerMultipointEvaluation(const FormalPowerSeries<mint> &f,
                                           const vector<mint> &xs,
                                           const ProductTree<mint> &ptree) {
        using fps = FormalPowerSeries<mint>;
        vector<mint> ret;
        ret.reserve(xs.size());
        auto rec = [&](auto self, fps a, int idx) {
            if (ptree.l[idx] == ptree.r[idx]) return;
            a %= ptree.buf[idx];
            if ((int)a.size() <= 64) {
                for (int i = ptree.l[idx]; i < ptree.r[idx]; i++)
                    ret.push_back(a.eval(xs[i]));
                return;
            }
            self(self, a, (idx << 1) | 0);
            self(self, a, (idx << 1) | 1);
        };
        rec(rec, f, 1);
        return ret;
    }

    template <typename mint>
    vector<mint> MultipointEvaluation(const FormalPowerSeries<mint> &f,
                                      const vector<mint> &xs) {
        if (f.empty() || xs.empty()) return vector<mint>(xs.size(), mint(0));
        return InnerMultipointEvaluation(f, xs, ProductTree<mint>(xs));
    }

/**
 * @brief Multipoint Evaluation
 */
#line 5 "fps/polynomial-interpolation.hpp"

    template <class mint>
    FormalPowerSeries<mint> PolynomialInterpolation(const vector<mint> &xs,
                                                    const vector<mint> &ys) {
        using fps = FormalPowerSeries<mint>;
        assert(xs.size() == ys.size());
        ProductTree<mint> ptree(xs);
        fps w           = ptree.buf[1].diff();
        vector<mint> vs = InnerMultipointEvaluation<mint>(w, xs, ptree);
        auto rec        = [&](auto self, int idx) -> fps {
            if (idx >= ptree.N) {
                if (idx - ptree.N < (int)xs.size())
                    return {ys[idx - ptree.N] / vs[idx - ptree.N]};
                else
                    return {mint(1)};
            }
            if (ptree.buf[idx << 1 | 0].empty())
                return {};
            else if (ptree.buf[idx << 1 | 1].empty())
                return self(self, idx << 1 | 0);
            return self(self, idx << 1 | 0) * ptree.buf[idx << 1 | 1]
                   + self(self, idx << 1 | 1) * ptree.buf[idx << 1 | 0];
        };
        return rec(rec, 1);
    }
#line 8 "matrix/polynomial-matrix-determinant.hpp"

    template <typename mint>
    FormalPowerSeries<mint>
    PolynomialMatrixDeterminant(const Matrix<FormalPowerSeries<mint>> &m) {
        int N   = m.size();
        int deg = 0;
        for (int i = 0; i < N; ++i) deg += max<int>(1, m[i][i].size()) - 1;
        vector<mint> xs(deg + 1);
        vector<mint> ys(deg + 1);
        Matrix<mint> M(N);
        for (int x = 0; x <= deg; x++) {
            xs[x] = x;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j) M[i][j] = m[i][j].eval(x);
            ys[x] = M.determinant();
        }
        return PolynomialInterpolation<mint>(xs, ys);
    }

/**
 * @brief 多項式行列の行列式
 * @docs docs/matrix/polynomial-matrix-determinant.md
 */
#line 7 "matrix/matrix-tree.hpp"

    template <typename T>
    struct MatrixTree {
        int n;
        Matrix<T> m;
        MatrixTree(int _n) : n(_n), m(_n) { assert(n > 0); }

        void add(int i, int j, const T &x) {
            if (i < n) m[i][i] += x;
            if (j < n) m[j][j] += x;
            if (i < n and j < n) {
                m[i][j] -= x;
                m[j][i] -= x;
            }
        }

        Matrix<T> get() const { return m; }

        template <typename U, typename = void>
        struct has_value_type : false_type {};
        template <typename U>
        struct has_value_type<
            U, typename conditional<false, typename U::value_type, void>::type>
            : true_type {};

        template <typename U                                       = T,
                  enable_if_t<has_value_type<U>::value, nullptr_t> = nullptr>
        T calc() {
            return PolynomialMatrixDeterminant(m);
        }
        template <typename U                                        = T,
                  enable_if_t<!has_value_type<U>::value, nullptr_t> = nullptr>
        T calc() {
            return m.determinant();
        }
    };
} // namespace nyaan

struct cww {
    cww() {
        io::enableFastIO();
        io::setDigits(10);
    }
} star;

int A[312][312];
int main() {
    /* write here */
    int n;
    cin >> n;

    UnionFind uf(n);
    for (int i : range(n)) {
        for (int j : range(n)) {
            cin >> A[i][j];
        }
    }
    for (int i : range(n)) {
        for (int j : range(i)) {
            if (A[i][j] == 1) {
                if (!uf.unite(i, j)) {
                    cout << 0 << endl;
                    return 0;
                }
            }
        }
    }
    int c = 0;
    map<int, int> m;
    for (int i : range(n)) {
        if (uf.find(i) != i) continue;
        m[i] = c++;
    }
    if (c == 1) {
        cout << 1 << endl;
        return 0;
    }
    using mint = atcoder::modint1000000007;
    nyaan::MatrixTree<mint> t(c - 1);
    for (int i : range(n)) {
        for (int j : range(i)) {
            if (A[i][j] == -1) {
                int p = uf.find(i);
                int q = uf.find(j);
                if (p == q) continue;
                t.add(m[p], m[q], mint(1));
            }
        }
    }
    cout << t.calc().val() << endl;

    return 0;
}
