set -eux

g++ -std=c++17 -O3 -o $1.out $1.cpp -Wall -Wextra
./$1.out <$1/s.in | tee $1/s.out
