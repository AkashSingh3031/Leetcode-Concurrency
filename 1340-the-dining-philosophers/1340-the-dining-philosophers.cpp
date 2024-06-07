class DiningPhilosophers {
    int n;
    vector<std::mutex> fork_locks;

public:
    DiningPhilosophers() {
        n = 5;
        fork_locks = vector<std::mutex>(n);
    }

    void wantsToEat(int philosopher, function<void()> pickLeftFork,
                    function<void()> pickRightFork, function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        int left_id = philosopher % n;
        int right_id = (philosopher + 1) % n;

        if (philosopher % n == 1) {
            fork_locks[right_id].lock();
            fork_locks[left_id].lock();
            pickRightFork();
            pickLeftFork();
            eat();
            putLeftFork();
            putRightFork();
            fork_locks[left_id].unlock();
            fork_locks[right_id].unlock();
        } else {
            fork_locks[left_id].lock();
            fork_locks[right_id].lock();
            pickRightFork();
            pickLeftFork();
            eat();
            putLeftFork();
            putRightFork();
            fork_locks[right_id].unlock();
            fork_locks[left_id].unlock();
        }
    }
};