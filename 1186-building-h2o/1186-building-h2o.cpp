class H2O {
private:
    int h;
    int leftH;
    int o;
    int leftO;
    mutex m;
    condition_variable cvH;
    condition_variable cvO;
    bool pairing;
    void reset() {
        leftH = 2;
        leftO = 1;
        pairing = false;
    }
public:
    H2O() {
        h = 0;
        o = 0;
        reset();
    }
    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> ul(m);
        h++;
        cvH.wait(ul, [&]() {
            return (!pairing && o >= 1 && h >= 2) || (pairing && leftH > 0);
        });
        pairing = true;
        leftH--;
        h--;
        if (leftH > 0)
            cvH.notify_one();
        if (leftO > 0)
            cvO.notify_one();
        if (leftO == 0 && leftH == 0) {
            reset();
        }
        releaseHydrogen();
    }
    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> ul(m);
        o++;
        cvO.wait(ul, [&]() {
            return (!pairing && h >= 2 && o >= 1) || (pairing && leftO > 0);
        });
        pairing = true;
        leftO--;
        o--;
        if (leftH == 1)
            cvH.notify_one();
        else if (leftH == 2)
            cvH.notify_all();
        if (leftO == 0 && leftH == 0) {
            reset();
        }
        releaseOxygen();
    }
};