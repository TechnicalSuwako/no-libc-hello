#if defined(__linux__)
  #if defined(__x86_64__)
    #define SYS_WRITE 1
    #define SYS_EXIT 60
    #define SYSCALL_INST "syscall"
  #elif defined(__aarch64__)
    #define SYS_WRITE 64
    #define SYS_EXIT 93
    #define SYSCALL_INST "svc #0"
  #elif defined(__riscv) && __riscv_xlen == 64
    #define SYS_WRITE 64
    #define SYS_EXIT 93
    #define SYSCALL_INST "ecall"
  #endif
#elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)
  #define SYS_WRITE 4
  #define SYS_EXIT 1
  #define SYSCALL_INST "syscall"
#elif defined(__APPLE__)
  #define SYS_WRITE 0x2000004
  #define SYS_EXIT 0x2000001
  #if defined(__x86_64__)
    #define SYSCALL_INST "syscall"
  #elif defined(__aarch64__)
    #define SYSCALL_INST "svc #0"
  #endif
#endif

char msg[] = "こんにちは、世界！\n";

__attribute((naked))
void _start() {
  asm volatile(
  #if defined(__x86_64__)
    ".intel_syntax noprefix\n"
    "mov eax, %[sys_write]\n"
    "mov edi, 1\n"
    "mov rsi, offset msg\n"
    "mov edx, %[len]\n"
    SYSCALL_INST "\n"

    "mov eax, %[sys_exit]\n"
    "xor edi, edi\n"
    SYSCALL_INST "\n"
  #elif defined(__aarch64__)
    "mov x8, %[sys_write]\n"
    "mov x0, #1\n"
    "mov x1, %[msg]\n"
    "mov x2, %[len]\n"
    SYSCALL_INST "\n"

    "mov x8, %[sys_exit]\n"
    "mov x0, #0\n"
    SYSCALL_INST "\n"
  #elif defined(__riscv) && __riscv_xlen == 64
    "li a7, %[sys_write]\n"
    "li a0, 1\n"
    "mv a1, %[msg]\n"
    "li a2, %[len]\n"
    SYSCALL_INST "\n"

    "li a7, %[sys_exit]\n"
    "li a0, 0\n"
    SYSCALL_INST "\n"
  #endif
    :: [sys_write] "i" (SYS_WRITE),
       [sys_exit] "i" (SYS_EXIT),
       [len] "i" (sizeof(msg) - 1),
       [msg] "r" (msg)
    : "memory",
  #if defined(__x86_64__)
      "rax", "rdi", "rsi", "rdx"  // x86-64
  #elif defined(__aarch64__)
      "x0", "x1", "x2", "x8"      // AArch64
  #elif defined(__riscv) && __riscv_xlen == 64
      "a0", "a1", "a2", "a7"      // RISC-V
  #endif
  );
}
