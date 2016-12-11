// Function declaration
void m1();

void m2();

void m3();

// function definition
void m1() {
    m2();
}

void m2() {
    m3();
}

void m3() {
    m4();
}

void m4(int n) {
    // do nothing
    if (n < 10) {
        m4(n + 1);
    }
}

void main() {
    m1();
    m2();
    m3();
    m4();
}
