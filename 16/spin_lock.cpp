#include <bits/stdc++.h>

using namespace std;

struct mut {
	void lock() {
		while (locked.exchange(true)) {
		}
	}

	void unlock() {
		locked.store(false);
	}

private:
	atomic<bool> locked = false;
};

int a;
int t;

mut m;

void doo(int id) {
	m.lock();
	a = 1 + id;
	t += a;
	a = 0;
	m.unlock();
}

int main() {
	for (int i = 0; i < 1e9; i++) {
		if (i % 10'000 == 0) {
			cout << i << '\n';
		}
		a = 0;
		t = 0;
		thread t1(doo, 0);
		thread t2(doo, 1);
		t1.join();
		t2.join();
		if (t != 3) {
			cout << "CPU is broken " << i << "\n";
			return 0;
		}
	}
}