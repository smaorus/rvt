int n;

int sum(int n) {
        if (n <= 1) return n;
        return n + sum(n-1);
}

int main() {
return sum(n);
}
