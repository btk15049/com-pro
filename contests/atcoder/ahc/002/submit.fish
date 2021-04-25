while test -f submission.cpp
    echo "sleep"
    sleep 300
    echo "submit"
    oj submit "https://atcoder.jp/contests/ahc002/tasks/ahc002_a" submission.cpp -y
    echo "done"
end
