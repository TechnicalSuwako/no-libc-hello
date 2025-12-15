此れはlibcなしの「こんにちは、世界」のデモです。\
Linux、FreeBSD、OpenBSD、NetBSD、及びmacOSで実行出来ますが、IntelやAMD CPUが必須に成ります。

This is a libc-less "hello, world" demo.\
It runs on Linux, FreeBSD, OpenBSD, NetBSD, and macOS, but requires an Intel or AMD CPU.

```sh
$ cc -nostdlib -static -masm=intel -o main main.c
$ ls -thal main
-rwxr-xr-x  1 suwako suwako  1.6K 12月 15 15:57 main
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
```
