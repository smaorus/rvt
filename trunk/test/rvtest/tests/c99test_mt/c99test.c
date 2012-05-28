int checkInput(int n) {
    return (n >= 0)? 1 : 0;
}
 
int f(int n) {
    if (checkInput(n))
        return 0;

    int i, sum = 0;
    for (i = 1; i < n; ++i)
        sum += i;
    return sum;
}

int main() {
    int n;
    int sum = f(n);
    return 0;
}
