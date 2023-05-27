#include <cstdint>
#include <unistd.h>


#if __linux__

#include <sys/syscall.h>
#include <linux/futex.h>
#include <stdint.h>

int futex(unsigned int* uaddr, int op, int val, const struct timespec* timeout,
          int* uaddr2, int val3) {
  return syscall(SYS_futex, uaddr, op, val, timeout, uaddr2, val3);
}


namespace futex {

int SystemWait(uint32_t* addr, uint32_t old) {
  return futex(addr, FUTEX_WAIT_PRIVATE, old, nullptr, nullptr, 0);
}

int SystemWake(uint32_t* addr, size_t count) {
  return futex(addr, FUTEX_WAKE_PRIVATE, (int)count, nullptr, nullptr, 0);
}

}

#elif __APPLE__

extern "C" int __ulock_wait(uint32_t operation, void *addr, uint64_t value,
                            uint32_t timeout); /* timeout is specified in microseconds */
extern "C" int __ulock_wake(uint32_t operation, void *addr, uint64_t wake_value);

#define UL_COMPARE_AND_WAIT				1
#define ULF_WAKE_ALL					0x00000100


namespace futex {


int SystemWait(uint32_t* addr, uint32_t old) {
  return __ulock_wait(UL_COMPARE_AND_WAIT, addr, old, 0);
}

int SystemWake(uint32_t* addr, size_t count) {
  return __ulock_wake(UL_COMPARE_AND_WAIT | ((count == 1) ? 0 : ULF_WAKE_ALL), addr, 0);
}

}


#else

#pragma message("SystemWait is not implemented")

#endif
