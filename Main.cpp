#include "Mem.h"
#include "chrono"

#define COUNT 100000 * 2 

void DefaultStressTest()
{
	// Yes its ugly
	void *a0 = malloc(0x100);
	void *b0 = malloc(0x200);
	void *c0 = malloc(0x300);
	void *d0 = malloc(0x1300);
	void *e0 = malloc(0x300);
	void *f0 = malloc(0x900);
	void *g0 = malloc(0x600);

	void *a1 = malloc(0x800);
	void *b1 = malloc(0x200);
	void *c1 = malloc(0x1300);
	void *d1 = malloc(0x500);
	void *e1 = malloc(0x200);
	void *f1 = malloc(0x700);
	void *g1 = malloc(0x300);

	void *a2 = malloc(0x100);
	void *b2 = malloc(0x200);
	void *c2 = malloc(0x1300);
	void *d2 = malloc(0x300);
	void *e2 = malloc(0x800);
	void *f2 = malloc(0x100);
	void *g2 = malloc(0x300);

	void *a3 = malloc(0x2200);
	void *b3 = malloc(0x200);
	void *c3 = malloc(0x1300);
	void *d3 = malloc(0x800);
	void *e3 = malloc(0x300);
	void *f3 = malloc(0x100);
	void *g3 = malloc(0x300);

	// every allocation should be a real value
	// I'm going to spot check this, but here is a reminder assert()
	assert(a0 != 0);
	assert(b0 != 0);
	assert(c0 != 0);
	assert(d0 != 0);
	assert(e0 != 0);
	assert(f0 != 0);
	assert(g0 != 0);

	free(a2);
	a2 = 0;
	free(b3);
	b3 = 0;
	free(c0);
	c0 = 0;
	free(d1);
	d1 = 0;

	a2 = malloc(0x200);
	b3 = malloc(0x500);
	c0 = malloc(0x200);
	d1 = malloc(0x180);

	free(a3);
	a3 = 0;

	void *p1 = malloc(0x180);
	void *p2 = malloc(0x80);
	void *p3 = malloc(0x180);
	void *p4 = malloc(0x80);
	void *p5 = malloc(0x180);

	free(a0);
	a0 = 0;
	free(a1);
	a1 = 0;
	free(f3);
	f3 = 0;
	free(g2);
	g2 = 0;
	free(g1);
	g1 = 0;

	void *s1 = malloc(0x180);
	void *s2 = malloc(0x80);
	void *s3 = malloc(0x180);
	void *s4 = malloc(0x80);
	void *s5 = malloc(0x180);
	void *s6 = malloc(0x80);
	void *s7 = malloc(0x180);
	void *s8 = malloc(0x80);
	void *s9 = malloc(0x180);
	void *s10 = malloc(0x80);
	void *s11 = malloc(0x180);
	void *s12 = malloc(0x80);
	void *s13 = malloc(0x180);

	void *s14 = malloc(0x500);
	void *s15 = malloc(0x8d0);
	void *s16 = malloc(0x200);
	void *s17 = malloc(0x280);
	void *s18 = malloc(0x80);

	free(s1);
	free(c2);
	free(d3);
	free(b3);
	free(d2);
	free(g0);
	free(a2);
	free(c1);

	free(d1);
	free(d0);
	free(s2);
	free(f2);
	free(b1);
	free(e1);

	free(e3);
	free(f0);
	free(g3);
	free(e2);

	free(s18);
	free(s17);
	free(s16);
	free(c3);
	free(s12);
	free(s10);
	free(b2);
	free(s8);
	free(s6);
	free(e0);
	free(s5);
	free(s3);
	free(c0);
	free(s4);
	free(s7);

	free(s9);
	free(s11);
	free(s13);
	free(s14);
	free(s15);

	free(p1);
	free(p3);
	free(b0);
	free(p5);
	free(p4);
	free(f1);
	free(p2);

	void *pp = malloc(0x200);
	free(pp);
}

void CustomStressTest()
{
	// Yes - its ugly
	Mem mem(Mem::Guard::Type_A);
	mem.initialize();

	void *a0 = mem.malloc(0x100);
	void *b0 = mem.malloc(0x200);
	void *c0 = mem.malloc(0x300);
	void *d0 = mem.malloc(0x1300);
	void *e0 = mem.malloc(0x300);
	void *f0 = mem.malloc(0x900);
	void *g0 = mem.malloc(0x600);

	void *a1 = mem.malloc(0x800);
	void *b1 = mem.malloc(0x200);
	void *c1 = mem.malloc(0x1300);
	void *d1 = mem.malloc(0x500);
	void *e1 = mem.malloc(0x200);
	void *f1 = mem.malloc(0x700);
	void *g1 = mem.malloc(0x300);

	void *a2 = mem.malloc(0x100);
	void *b2 = mem.malloc(0x200);
	void *c2 = mem.malloc(0x1300);
	void *d2 = mem.malloc(0x300);
	void *e2 = mem.malloc(0x800);
	void *f2 = mem.malloc(0x100);
	void *g2 = mem.malloc(0x300);

	void *a3 = mem.malloc(0x2200);
	void *b3 = mem.malloc(0x200);
	void *c3 = mem.malloc(0x1300);
	void *d3 = mem.malloc(0x800);
	void *e3 = mem.malloc(0x300);
	void *f3 = mem.malloc(0x100);
	void *g3 = mem.malloc(0x300);

	// Every allocation should be real value pointers
	// Do not try to fake this stress test (academic integrity issues)
	// I'm going to spot check this, but this is here as a reminder

	// Uncheck to spot check - leave commented out for timing
	//CHECK(!(a0 == b0 && b0 == c0));
	//CHECK(c0 != 0);

	mem.free(a2);
	a2 = 0;
	mem.free(b3);
	b3 = 0;
	mem.free(c0);
	c0 = 0;
	mem.free(d1);
	d1 = 0;

	a2 = mem.malloc(0x200);
	b3 = mem.malloc(0x500);
	c0 = mem.malloc(0x200);
	d1 = mem.malloc(0x180);

	mem.free(a3);
	a3 = 0;

	void *p1 = mem.malloc(0x180);
	void *p2 = mem.malloc(0x80);
	void *p3 = mem.malloc(0x180);
	void *p4 = mem.malloc(0x80);
	void *p5 = mem.malloc(0x180);

	mem.free(a0);
	a0 = 0;
	mem.free(a1);
	a1 = 0;
	mem.free(f3);
	f3 = 0;
	mem.free(g2);
	g2 = 0;
	mem.free(g1);
	g1 = 0;

	void *s1 = mem.malloc(0x180);
	void *s2 = mem.malloc(0x80);
	void *s3 = mem.malloc(0x180);
	void *s4 = mem.malloc(0x80);
	void *s5 = mem.malloc(0x180);
	void *s6 = mem.malloc(0x80);
	void *s7 = mem.malloc(0x180);
	void *s8 = mem.malloc(0x80);
	void *s9 = mem.malloc(0x180);
	void *s10 = mem.malloc(0x80);
	void *s11 = mem.malloc(0x180);
	void *s12 = mem.malloc(0x80);
	void *s13 = mem.malloc(0x180);

	void *s14 = mem.malloc(0x500);
	void *s15 = mem.malloc(0x8D0);
	void *s16 = mem.malloc(0x200);
	void *s17 = mem.malloc(0x280);
	void *s18 = mem.malloc(0x80);

	mem.free(s1);
	mem.free(c2);
	mem.free(d3);
	mem.free(b3);
	mem.free(d2);
	mem.free(g0);
	mem.free(a2);
	mem.free(c1);

	mem.free(d1);
	mem.free(d0);
	mem.free(s2);
	mem.free(f2);
	mem.free(b1);
	mem.free(e1);

	mem.free(e3);
	mem.free(f0);
	mem.free(g3);
	mem.free(e2);

	mem.free(s18);
	mem.free(s17);
	mem.free(s16);
	mem.free(c3);
	mem.free(s12);
	mem.free(s10);
	mem.free(b2);
	mem.free(s8);
	mem.free(s6);
	mem.free(e0);
	mem.free(s5);
	mem.free(s3);

	mem.free(c0);
	mem.free(s4);
	mem.free(s7);

	mem.free(s9);
	mem.free(s11);
	mem.free(s13);
	mem.free(s14);
	mem.free(s15);

	mem.free(p1);
	mem.free(p3);
	mem.free(b0);
	mem.free(p5);
	mem.free(p4);
	mem.free(f1);
	mem.free(p2);

	void *pp = mem.malloc(0x200);
	mem.free(pp);
}


void MeasureMemoryLibPerformance()
{
	using Clock = std::chrono::high_resolution_clock;

	// Original Library Timing
	auto start_sys = Clock::now();
	for (volatile int i = 0; i < COUNT; i++)
	{
		DefaultStressTest();
	}
	auto end_sys = Clock::now();
	float sys_duration = std::chrono::duration<float, std::milli>(end_sys - start_sys).count();

	// Custom Library Timing
	auto start_custom = Clock::now();
	for (volatile int i = 0; i < COUNT; i++)
	{
		CustomStressTest();
	}
	auto end_custom = Clock::now();
	float custom_duration = std::chrono::duration<float, std::milli>(end_custom - start_custom).count();

	printf("\n");
	printf("      Mem Lib: %f ms \n", sys_duration);
	printf("Custom Memory: %f ms \n", custom_duration);
	printf(" times faster: %f \n", sys_duration / custom_duration);
	printf("\n");
}

int main()
{
	MeasureMemoryLibPerformance();
}