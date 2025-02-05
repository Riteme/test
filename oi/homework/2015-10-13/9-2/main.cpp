#include <cmath>
#include <cassert>
#include <iostream>

using namespace std;

bool IsRepeatOf(int n, int i);
int Length(int n);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    int upload = 0;
    int mult = 0;
    int cnt = 0;

    while (true) {
        for (int i = 0; i <= 9; i++) {
            mult = n * i + upload;

            if (mult % 10 == 1) { break; }
        }  // for

        upload = mult / 10;

        if (IsRepeatOf(upload, 1)) { break; } else {
            cnt++;
        }
    }  // while

    cout << cnt + Length(mult) << endl;

    return 0;
}  // function main

bool IsRepeatOf(int n, int i) {
    if (n == 0) { return false; }

    while (n > 0) {
        if (n % 10 != i) { return false; }

        n /= 10;
    }  // while

    return true;
}

int Length(int n) {
    int cnt = 0;

    while (n > 0) {
        cnt++;
        n /= 10;
    }  // while

    return cnt;
}
