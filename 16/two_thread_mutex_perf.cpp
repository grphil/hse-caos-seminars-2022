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
	for (int i = 0; i < 1000'000; i++) {
		m.lock(id);
		a = 1 + id;
		t += a;
		a = 0;
		m.unlock(id);
	}
}

int main() {
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < 100; i++) {
		a = 0;
		t = 0;
		thread t1(doo, 0);
		thread t2(doo, 1);
		t1.join();
		t2.join();
		
		auto end = std::chrono::steady_clock::now();
		cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
		start = end;
	}
}