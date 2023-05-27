#include <bits/stdc++.h>
#include <futex>

using namespace std;

class CondVar {
public:
	template <typename Mutex>
	void wait(Mutex& m) {
		uint32_t old = notify_count.load();
		m.unlock();
		
		futex::SystemWait((uint32_t*)(&notify_count), old);

		m.lock();
	}

	void notify_one() {
		notify_count.fetch_add(1);
		futex::SystemWake((uint32_t*)(&notify_count), 1);
	}

private:
	atomic<uint32_t> notify_count = 0;
};

using func = function<void()>;

class ThreadPool {
public:
	ThreadPool(size_t n) {
		for (size_t i = 0; i < n; i++) {
			threads.emplace_back([this](){ run_thread(); });
		}
	}

	void add(func f) {
		lock_guard lock(m);
		if (finished) {
			throw std::runtime_error("add to finished pool");
		}
		queue.emplace_back(std::move(f));
		v.notify_one();
	}

	void wait() {
		m.lock();
		finished = true;
		m.unlock();
		for (auto& thread : threads) {
			thread.join();
		}
	}

private:
	vector<thread> threads;
	deque<func> queue;
	bool finished = false;
	CondVar v;
	mutex m;

	void run_thread() {
		while (true) {
			m.lock();

			while (queue.empty() && !finished) {
				v.wait(m);
			}

			if (finished) {
				m.unlock();
				break;
			}

			auto f = std::move(queue.front());
			queue.pop_front();
			m.unlock();
			f();
		}
	}
};

int main() {
	ThreadPool pool(2);

	for (int i = 0; i < 3; i++) {
		pool.add([]() {
			for (int i = 0; i < 100; i++) {
				cout << i << '\n';
			}
		});
	}

	pool.wait();
}