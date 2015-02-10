extern  int input,result;   
void test(void)
{   
	input = 1;   
	__asm__ __volatile__ ("movl %1,%0" : "=r" (result) : "r" (input)); 
	return ;
}
