class ZeroEvenOdd {
private:
    const int n;
    int next{1};
    mutex z, o, e;
public:
    ZeroEvenOdd(int n) : n(n) {
        o.lock();
        e.lock();
    }
    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while (true) {
            z.lock();
            if (next <= n) {
                printNumber(0);
                ((next % 2) ? o : e).unlock();
            } else {
                o.unlock();
                e.unlock();
                break;
            }
        }
    }
    void even(function<void(int)> printNumber) {
        int last = n % 2 ? n - 1 : n;
        while (true) {
            e.lock();
            if (next <= last) {
                printNumber(next++);
                z.unlock();
            } else {
                z.unlock();
                break;
            }
        }
    }
    void odd(function<void(int)> printNumber) {
        int last = n % 2 ? n : n - 1;
        while (true) {
            o.lock();
            if (next <= last) {
                printNumber(next++);
                z.unlock();
            } else {
                z.unlock();
                break;
            }
        }
    }
};