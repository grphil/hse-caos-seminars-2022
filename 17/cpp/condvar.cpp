#include <bits/stdc++.h>

using namespace std;

class RWMutex {
public:
	void rlock() {
		while (true) {
			if (mode.load() != 0) {
				continue;
			}

			counter.fetch_add(1);

			if (mode.load() == 0) {
				break;
			}

			counter.fetch_add(-1);
		}
	}

	void runlock() {
		counter.fetch_add(-1);
	}

	void lock() {
		while (true) {
			int curr_mode = mode.load();
			if (curr_mode == 2) {
				continue;
			}
			if (curr_mode == 0) {
				mode.compare_exchange(curr_mode, 1);
				continue;
			}
			if (curr_mode == 1) {
				if (counter.load() > 0) {
					continue;
				}
				if (mode.compare_exchange(curr_mode, 2)) {
					return;
				}
			}
		}
	}

	void unlock() {
		mode.store(0);
	}

private:
	atomic<int> counter;
	// 0 - can be rlocked
	// 1 - no new rlocks
	// 2 - locked for write
	atomic<int> mode; 
}



int main() {

}