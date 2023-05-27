#include <bits/stdc++.h>
#include <futex>

using namespace std;

class CondVar {
public:
	template <typename Mutex>
	void wait(Mutex& m) {
		mut.lock();

		atomic<uint32_t> wait = 0;
		queue.emplace_back(&wait);

		mut.unlock();

		m.unlock();
		
		futex::SystemWait((uint32_t*)(&wait), 1);

		m.lock();
	}

	void notify_one() {
		lock_guard lock(mut);
		if (!queue.empty()) {
			auto waiter = queue.front();
			queue.pop_front();

			waiter->store(1);
			futex::SystemWake((uint32_t*)(waiter), 1);
		}
	}

private:
	mutex mut;
	deque<atomic<uint32_t>*> queue;
};
