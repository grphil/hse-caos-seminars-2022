#include "lib/futex.h"
#include <bits/stdc++.h>

using namespace std;

class mut {
public:
	void lock() {
		while (!guard.exchange(1) == 0) {
			futex::SystemWait((uint32_t*)&guard, 1);
		}
	}

	void unlock() {
		guard.store(0);
		futex::SystemWake((uint32_t*)&guard, 1);
	}

private:
	std::atomic<uint32_t> guard = 0;
};

int main() {
	mut a;
	a.lock();
	a.unlock();
}