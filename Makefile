all:
	cc -nostdlib -static -masm=intel -o main main.c
