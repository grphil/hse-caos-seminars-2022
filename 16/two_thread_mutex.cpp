#include <bits/stdc++.h>

using namespace std;

struct mut {
	void lock(int id) {
		want[id].store(true);
		wait_thread.store(id);
		while (want[1-id].load() && wait_thread.load() == id) {
		}
	}

	void unlock(int id) {
		want[id].store(false);
	}

private:
	atomic<int> wait_thread;
	atomic<bool> want[2];
};

int a;
int t;

mut m;

void doo(int id) {
	m.lock(id);
	a = 1 + id;
	t += a;
	a = 0;
	m.unlock(id);
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