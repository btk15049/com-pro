set -eux

g++ -std=c++17 -O3 -o $1.out $1.cpp -Wall -Wextra
./$1.out <$1/v.in | tee $1/v.out
