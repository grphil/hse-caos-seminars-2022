#include <bits/stdc++.h>

using namespace std;

struct mut {
	void lock() {
		while (locked.exchange(true)) {
			while (locked.load()) {

			}
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
	for (int i = 0; i < 100'000; i++) {
		m.lock();
		a = 1 + id;
		t += a;
		a = 0;
		m.unlock();
	}
}

int main() {
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < 100; i++) {
		a = 0;
		t = 0;
		thread t1(doo, 0);
		thread t2(doo, 1);
		thread t3(doo, 0);
		thread t4(doo, 1);
		thread t5(doo, 0);
		thread t6(doo, 1);
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();

		
		auto end = std::chrono::steady_clock::now();
		cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
		start = end;
	}
}