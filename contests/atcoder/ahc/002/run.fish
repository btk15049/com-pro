if test -f ./a.out
    rm a.out
end
g++ main.cpp -O3 \
-D_GLIBCXX_DEBUG \
-std=c++17 \
-Wall \
-Wextra

if test -f ./a.out
    for x in 0 1 2 3 4 5 6 7 8 9
        ./a.out < in/000$x.txt > out/000$x.txt &
    end
    sleep 5
end
