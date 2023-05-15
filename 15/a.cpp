#include <bits/stdc++.h>

using namespace std;

int a1, a2, res1, res2;

void doo1() {
	a2 = 1;
	res1 = a1;
}

void doo2() {
	a1 = 1;
	res2 = a2;
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