#include "CPU.cpp"
#include <stdio.h>

int main()
{
	register_state s;
	s.set(rEAX, 0x11111111);
	s.set(rAX, 0xABCD);
	s.set(rAL, 0x00);
	s.set(rBP, 0x1234);
	printf("%x : %x, %x\n", s.get(rEAX), s.get(rAH), s.get(rAL));
	printf("%x\n", s.get(rBP));
	printf("%x\n", s.get(fALL));
	s.set(fCF, 1);
	printf("%x\n", s.get(fALL));
}
