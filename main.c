#if defined(__linux__)
#define SYS_WRITE 1
#define SYS_EXIT 60
#elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)
#define SYS_WRITE 4
#define SYS_EXIT 1
#elif defined(__APPLE__)
#define SYS_WRITE 0x2000004
#define SYS_EXIT 0x2000001
#endif

char msg[] = "こんにちは、世界！\n";

void _start() {
  asm volatile(
    ".intel_syntax noprefix\n"
    "mov eax, %[sys_write]\n"
    "mov edi, 1\n"
    "mov rsi, offset msg\n"
    "mov edx, %[len]\n"
    "syscall\n"

    "mov eax, %[sys_exit]\n"
    "xor edi, edi\n"
    "syscall\n"

    ".att_syntax prefix\n"
    :: [sys_write] "i" (SYS_WRITE),
       [sys_exit] "i" (SYS_EXIT),
       [len] "i" (sizeof(msg) - 1)
    : "rax", "rdi", "rsi", "rdx", "rcx", "r11"
  );
}
