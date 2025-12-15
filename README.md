此れはlibcなしの「こんにちは、世界」のデモです。

This is a libc-less "hello, world" demo.

## 対応 | Support
| OS      | CPU     | 対応 | テスト済み |
|---------|---------|------|------------|
| Linux   | x86-64  | 〇   | 〇         |
| Linux   | AArch64 | 〇   | 〇         |
| Linux   | RISC-V  | 〇   | 〇         |
| FreeBSD | x86-64  | 〇   | 〇         |
| OpenBSD | x86-64  | ✕    | ✕          |
| NetBSD  | x86-64  | 〇   | ✕          |
| macOS   | x86-64  | 〇   | ✕          |
| macOS   | AArch64 | 〇   | ✕          |
| Windows | x86-64  | ✕    | ✕          |
| Windows | AArch64 | ✕    | ✕          |

## 使い方 | How to use

### x86-64
```sh
$ cc -nostdlib -static -masm=intel -o main main.c
$ ls -thal main
-rwxr-xr-x  1 suwako suwako  1.5K 12月 15 15:57 main
$ file main
main: ELF 64-bit LSB executable, x86-64, version 1 (FreeBSD), statically linked, not stripped
$ objdump -M intel -d main

main:   file format elf64-x86-64

Disassembly of section .text:

00000000002011f0 <_start>:
  2011f0: 55                            push    rbp
  2011f1: 48 89 e5                      mov     rbp, rsp
  2011f4: b8 04 00 00 00                mov     eax, 0x4
  2011f9: bf 01 00 00 00                mov     edi, 0x1
  2011fe: 48 c7 c6 20 22 20 00          mov     rsi, 0x202220
  201205: ba 1c 00 00 00                mov     edx, 0x1c
  20120a: 0f 05                         syscall
  20120c: b8 01 00 00 00                mov     eax, 0x1
  201211: 31 ff                         xor     edi, edi
  201213: 0f 05                         syscall
  201215: 5d                            pop     rbp
  201216: c3                            ret
$ ./main
こんにちは、世界！
```

### AArch64、RISC-V
```sh
$ cc -nostdlib -static -o main main.c
$ ls -thal main
-rwxrwxr-x 1 suwako suwako 5.5K 12月 15 16:54 main
$ file main
main: ELF 64-bit LSB executable, UCB RISC-V, RVC, double-float ABI, version 1 (SYSV), statically linked, BuildID[sha1]=〇〇, not stripped
$ objdump -d main

main:     file format elf64-littleriscv


Disassembly of section .text:

000000000001017c <_start>:
   1017c:       00001797                auipc   a5,0x1
   10180:       e8478793                addi    a5,a5,-380 # 11000 <msg>
   10184:       04000893                li      a7,64
   10188:       4505                    li      a0,1
   1018a:       85be                    mv      a1,a5
   1018c:       4671                    li      a2,28
   1018e:       00000073                ecall
   10192:       05d00893                li      a7,93
   10196:       4501                    li      a0,0
   10198:       00000073                ecall
   1019c:       0001                    nop
$ ./main
こんにちは、世界！
```
