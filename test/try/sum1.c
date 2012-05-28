int n;

int sum(int n) {
        if (n <= 1) return n;
        return n + n-1 + sum(n-2);
}



int main() {
//n = getint();
return sum(n);
}
