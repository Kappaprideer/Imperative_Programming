#include <stdio.h>
#include <math.h> // for NAN

#define STACK_SIZE 10

#define OK        0 
#define EMPTY    -1
#define FULL     -2
#define OVERFLOW1 -3

double stack[STACK_SIZE];
int top = 0;

int stack_push(double x)
{	
	if(top==STACK_SIZE)
	{
		printf("OVERFLOW ");
		return OVERFLOW1;
	}
	stack[top]=x;
	top++;
	return OK;

}

double stack_pop(void)
{
	if(top==0) return NAN;
	top--;
	return stack[top];
}

int stack_state(void)
{
	if(top==STACK_SIZE) return FULL;
	return top;	

}


// FIFO queue with shifts

#define QUEUE_SIZE 10

int queue[QUEUE_SIZE];
int in = 0, curr_nr = 0;

// ONE OVERFLOW for many resigning

void queue_push(int in_nr)
{	
	for(int i=in; i<in+in_nr; i++)
	{	
		curr_nr++;
		if(i<QUEUE_SIZE)
			queue[i]=curr_nr;
	}
	in+=in_nr;
	if(in>QUEUE_SIZE)
	{
		in=QUEUE_SIZE;
		printf("OVERFLOW ");
	}
}


void queue_pop(int out_nr)
{
	if(out_nr>in)
	{
		in=0;
		printf("UNDERFLOW ");
	}
	else if(out_nr==in)
		in=0;
	else
	{
		for(int i=0; i<in-out_nr; i++)
			queue[i]=queue[i+out_nr];
		
		in-=out_nr;
	}
}

void queue_state(void)
{
	for(int i=0; i<in; i++)
	{
		printf("%d ", queue[i]);
	}
	if(in==0) printf("EMPTY ");

}

// Queue with cyclic buffer

#define CBUFF_SIZE 10

int cbuff[CBUFF_SIZE];
int out=0, len=0;


void cbuff_push(int cli_nr)
{
	if(len==CBUFF_SIZE)
		printf("OVERFLOW ");
	else
	{	
		cbuff[(out+len)%10]=cli_nr;
		len++;
	}
		

}

void cbuff_pop(void)
{
	if(len==0)
		printf("UNDERFLOW ");
	else
	{
		len--;
		out=(out+1)%10;
	}
}

void cbuff_state(void)
{
	if(len==0)
	{
		printf("EMPTY ");
	}
	
	for(int i=0; i<len; i++)
		{
			printf("%d ", cbuff[(out+i)%10]);
		}
}

int main(void) {
	int to_do, n, client_no, op_code;
	double x;
	scanf("%d",&to_do);
	switch(to_do) {
		case 1: // stack
			do {
				scanf("%lf",&x);
				if(x > 0) stack_push(x);
				else {
					if(x < 0) printf("%.2f ", stack_pop());
					else printf("\n%d\n", stack_state());
				} 
			} while(x != 0);
			break;
		case 2: // FIFO queue with shifts
			do {
				scanf("%d",&n);
				if(n > 0) queue_push(n);
				else {
					if(n < 0) queue_pop(-n);
					else queue_state();
				} 
			} while(n != 0);
			break;
		case 3: // queue with cyclic buffer
			client_no = 0;
			do {
				scanf("%d",&op_code);
				if(op_code > 0) cbuff_push(++client_no);
				else {
					if(op_code < 0) cbuff_pop();
					else cbuff_state();
				} 
			} while(op_code != 0);
			break;
		default: 
			printf("NOTHING TO DO!\n");
	}
	return 0;
}
