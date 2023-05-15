#include <bits/stdc++.h>

using namespace std;

atomic<int> a1, a2, res1, res2;

void doo1() {
	int x = 1;
	a2.store(x);
	res1.store(a1.load());
}

void doo2() {
	int x = 1;
	a1.store(1);
	res2.store(a2.load());
}

int main() {
	for (int i = 0; i < 1e9; i++) {
		if (i % 10'000 == 0) {
			cout << i << '\n';
		}
		a1 = 0;
		a2 = 0;
		res1 = 0;
		res2 = 0;
		thread t1(doo1);
		thread t2(doo2);
		t1.join();
		t2.join();
		if (res1 == 0 && res2 == 0) {
			cout << "CPU is broken " << i << "\n";
			return 0;
		}
	}
}