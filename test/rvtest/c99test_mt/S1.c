# 1 ".//c99test1.c"
# 1 "<command-line>"
# 1 ".//c99test1.c"
int checkInput(int n) {
    return (n >= 0)? 1 : 0;
}

int f(int n) {
    if (checkInput(n))
        return 0;

    int sum = 0;
    for (int i = 1; i < n; ++i)
        sum += i;
    return sum;
}

int main() {
    int n;
    int sum = f(n);
    return 0;
}
