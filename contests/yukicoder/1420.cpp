// https://yukicoder.me/problems/no/1420
#define STATIC_MOD 1e9 + 7

#ifdef BTK
/*<head>*/
#    include "Template.hpp"
#    include "graph/Graph.hpp"
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
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& it : v) is >> it;
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
        bool operator!=(I& lhs) { return x > lhs.x; }
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
    I& begin() { return n; }
    /**
     * @brief
     * end iterator
     * @return I&
     */
    I& end() { return i; }
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
        bool operator!=(I& lhs) { return x < lhs.x; }
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
    I& begin() { return i; }
    /**
     * @brief
     * end iterator
     * @return I&
     */
    I& end() { return n; }
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
inline T& unused_var(T& v) {
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
inline T chain(T&& v) {
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
inline auto chain(const T head, Ts&&... tail) {
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
inline bool changeTarget(T& target, Ts&&... candidates) {
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
    int64_t extgcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
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
    inline int64_t gcd(Ts&&... values) {
        return chain<inner::GCDFunc<int64_t>>(values...);
    }

    /**
     * @brief valuesの最小公倍数
     * @tparam Ts パラメータパック
     * @param values lcmを求めたい値の集合（2個以上）
     * @return int64 最小公倍数
     */
    template <typename... Ts>
    inline int64_t lcm(Ts&&... values) {
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
inline bool chmin(T& target, Ts&&... candidates) {
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
inline bool chmax(T& target, Ts&&... candidates) {
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
    inline Container& sort(Container& container) {
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
    inline Container& sort(Container& container, Comparator comparator) {
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
    inline Container& reverse(Container& container) {
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
    inline U accumulate(const std::vector<T>& container, U zero) {
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
    inline T accumulate(const std::vector<T>& container) {
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
    inline int count(Container& container, T value) {
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
std::string join(const T& v, const DelimiterType& delimiter) {
    std::stringstream ss;
    bool isFirst = true;
    for (auto& it : v) {
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
std::string join(const ITR bg, const ITR ed, const DelimiterType& delimiter) {
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
        static std::stringstream& join(std::stringstream& ss,
                                       const std::tuple<Ts...>& values,
                                       const DelimiterType& delimiter) {
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
        static std::stringstream& join(std::stringstream& ss,
                                       const std::tuple<Ts...>& values,
                                       const DelimiterType& delimiter) {
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
std::string join(const std::tuple<Ts...>& values,
                 const DelimiterType& delimiter) {
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
/* #region graph/Graph.hpp*/
/**
 * @file Graph.hpp
 * @brief グラフクラス
 * @author btk15049
 * @date 2019/03/11
 * @details
 *  verify: WUPC C
 */


/**
 * @brief 辺を扱う構造体の例
 * @details
 *   辺に重みなどを加えたい場合は変数とかを増やして作る．
 *   Graphに使うために必要な要件:
 *   - id,a,bは必須，他のパラメータ増やすときはコンストラクタを忘れずに
 *   - versusは必須，基本的にコピペでOK
 */
struct Edge {
    //! 辺id
    int id;
    //! 端点
    int a;
    //! 端点
    int b;
    /**
     * @brief Construct a new Edge object
     * @param id 辺番号
     * @param a 辺に接続する頂点番号
     * @param b 辺に接続する頂点番号
     */
    Edge(int id = 0, int a = 0, int b = 0) : id(id), a(a), b(b) {}
    /**
     * @brief 辺における，vの対になってる頂点番号を取得する
     * @param v 頂点番号
     * @return int vじゃない方の頂点番号
     */
    inline int versus(const int v) const { return a ^ b ^ v; }
};

/**
* @brief 重み付き辺を扱う構造体の例
* @details
辺に重みなどを加えたい場合は変数とかを増やして作る．
Graphに使うために必要な要件:
- id,a,bは必須，他のパラメータ増やすときはコンストラクタを忘れずに
- versusは必須，基本的にコピペでOK
*/
template <typename COST_TYPE>
struct WeightedEdge {
    //! 辺id
    int id;
    //! 端点
    int a;
    //! 端点
    int b;
    //! 辺重み
    COST_TYPE cost;

    /**
     * @brief Construct a new Weighted Edge object
     *
     * @param id
     * @param a
     * @param b
     * @param cost
     */
    WeightedEdge(int id = 0, int a = 0, int b = 0, int cost = 0)
        : id(id), a(a), b(b), cost(cost) {}
    /**
     * @brief 辺における，vの対になってる頂点番号を取得する
     * @param v 頂点番号
     * @return int vじゃない方の頂点番号
     */
    inline int versus(const int v) const { return a ^ b ^ v; }
};
/**
 * @brief グラフクラス
 * @tparam E=Edge 新たなグラフクラス作るときは書き換える
 * @details 0-indexedで使うことしか考えてないので注意．
 */
template <typename E = Edge>
class Graph {
  private:
    //! 辺集合
    std::vector<E> edges;
    //! 隣接リスト
    std::vector<std::vector<int>> g;

  public:
    /**
     * @brief Construct a new Graph object
     * @param reserved_vertex_size 頂点数の最大値，vectorのサイズ確保用
     * @param reserved_edge_size 辺数の最大値，vectorのサイズ確保用
     */
    Graph(int reserved_vertex_size = 1, int reserved_edge_size = -1) {
        g.reserve(reserved_vertex_size);
        edges.reserve(std::max(reserved_vertex_size, reserved_edge_size));
    }

    /**
     * @brief グラフの頂点数を返す
     * @return int 頂点数
     */
    inline int size() { return g.size(); }

    /**
     * @brief vの次数を返す
     * @param v 頂点番号
     * @return int 次数
     */
    inline int degree(const int v) { return g[v].size(); }

    /**
     * @brief グラフ全体の辺の数を返す
     * @return int グラフ全体の辺の数
     */
    inline int degree() { return edges.size(); }

    /**
     * @brief グラフの頂点数を変更する
     * @todo 分かりづらいので，set_vertex_sizeとかに変える
     * @return int
     */
    inline void resize(const int n) { g.resize(n); }

    /**
     * @brief "無向"辺(a,b)を追加する．
     * @param a 頂点番号
     * @param b 頂点番号
     * @param params 重みとか，容量とか
     * @details paramsはemplace_backと同じノリで続けて足してけばOK
     */
    template <typename... Ts>
    inline void add_edge(int a, int b, Ts&&... params) {
        const int id = edges.size();
        if ((int)g.size() <= std::max(a, b)) {
            g.resize(std::max(a, b) + 1);
        }
        g[a].emplace_back(id);
        g[b].emplace_back(id);
        edges.emplace_back(id, a, b, std::forward<Ts>(params)...);
    }

    /**
     * @brief "無向"辺Eを追加する．
     * @details paramsはemplace_backと同じノリで続けて足してけばOK
     */


    /**
     * @brief 辺を追加 idは自動付与
     * @param e
     */
    inline void add_edge(E e) {
        e.id = edges.size();
        if ((int)g.size() <= max(e.a, e.b)) {
            g.resize(max(e.a, e.b) + 1);
        }
        g[e.a].emplace_back(e.id);
        g[e.b].emplace_back(e.id);
        edges.emplace_back(e);
    }

    /**
     * @brief "有向"辺(a,b)を追加する．
     * @param a 頂点番号
     * @param b 頂点番号
     * @param params 重みとか，容量とか
     * @details paramsはemplace_backと同じノリで続けて足してけばOK
     */
    template <typename... Ts>
    inline void add_arc(int a, int b, Ts&&... params) {
        const int id = edges.size();
        if ((int)g.size() <= std::max(a, b)) {
            g.resize(std::max(a, b) + 1);
        }
        g[a].emplace_back(id);
        edges.emplace_back(id, a, b, std::forward<Ts>(params)...);
    }

    /**
     * @brief 辺を追加 idは自動付与
     * @param e
     */
    inline void add_arc(E e) {
        e.id = edges.size();
        if ((int)g.size() <= std::max(e.a, e.b)) {
            g.resize(std::max(e.a, e.b) + 1);
        }
        g[e.a].emplace_back(e.id);
        edges.emplace_back(e);
    }

    /**
     * @brief vの隣接頂点を返す
     * @param v int
     * @return vector<int>
     */
    inline std::vector<int> Ns(const int v) {
        std::vector<int> ns(g[v].size());
        for (int i = 0; i < degree(v); i++) {
            ns[i] = edges[g[v][i]].versus(v);
        }
        return ns;
    }

    /**
     * @brief vに隣接する辺番号の集合を返す
     * @param v int 頂点番号
     * @return vector<int> 辺番号の集合
     */
    inline const std::vector<int>& operator[](const int v) { return g[v]; }

    /**
     * @brief 辺番号から辺の参照を取得する
     * @param edge_id
     * @return E&
     */
    inline E& i2e(const int edge_id) { return edges[edge_id]; }
};
/* #endregion */
/* #endregion */
/*</body>*/
#endif

struct cww {
    cww() {
        io::enableFastIO();
        io::setDigits(10);
    }
} star;

Graph<WeightedEdge<int32_t>> g(112345, 112345);

int32_t val[112345];
bool vis1[112345];
bool vis2[112345];

void dfs(int v) {
    if (vis1[v]) return;
    vis1[v] = true;
    for (int ei : g[v]) {
        auto e      = g.i2e(ei);
        const int u = e.versus(v);
        val[u]      = val[v] ^ e.cost;
        dfs(u);
    }
}
void check(int v) {
    if (vis2[v]) return;
    vis2[v] = true;
    for (int ei : g[v]) {
        auto e      = g.i2e(ei);
        const int u = e.versus(v);
        if ((val[u] ^ val[v]) != e.cost) {
            cout << -1 << endl;
            exit(0);
        }
        check(u);
    }
}
int main() {
    /* write here */
    int N, M;
    cin >> N >> M;
    for (int i : range(M)) {
        int a, b, y;
        cin >> a >> b >> y;
        a--;
        b--;
        g.add_edge(a, b, y);
    }
    for (int i : range(N)) {
        dfs(i);
        check(i);
    }


    for (int i : range(N)) {
        cout << val[i] << endl;
    }

    return 0;
}
