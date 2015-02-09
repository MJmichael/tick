#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct kfifo{
	unsigned char *buffer;
	unsigned int size;
	unsigned int in;
	unsigned int out;	
};

#define min(a, b) ((a) < (b) ? (a) : (b))
//#define is_power_2

struct kfifo* kfifo_init(unsigned char* buf, unsigned int size)
{
	struct kfifo *fifo;	
	
	fifo = (struct kfifo*)malloc(sizeof(struct kfifo));
	if(!fifo) return NULL;

	fifo->buffer = buf;
	fifo->size = size;
	fifo->in = fifo->out = 0;

	return fifo;
}

struct kfifo* kfifo_alloc(unsigned int size)
{
	unsigned char *buf;
	struct kfifo *ret;
	
	buf = (unsigned char*)malloc(sizeof(unsigned char) * size);	
	if(!buf) return NULL;

	//return kfifo_init(buf, size);
	ret = kfifo_init(buf, size);
	if(!ret) {free(buf); return NULL;}

	return ret;
}

void kfifo_free(struct kfifo* fifo)
{
	free(fifo->buffer);
	free(fifo);
}

void kfifo_reset(struct kfifo* fifo)
{
	fifo->in = fifo->out = 0;
}

unsigned int kfifo_len(struct kfifo* fifo)
{
	return fifo->in - fifo->out;
}

unsigned int kfifo_in(struct kfifo* fifo, unsigned char* buf, unsigned int len)
{
	unsigned int l;

	//rest kfifo idle length
	len = min(len, fifo->size - fifo->in + fifo->out);

	//first we put data starting from fifo->in to buffer end
	l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));
	memcpy(fifo->buffer + (fifo->in &(fifo->size - 1)), buf, l);
	
	//then put rest at the beginning of the buffer;
	memcpy(fifo->buffer, buf + l, len -l);
	
	//update fifo->in length
	fifo->in += len;
	return len;	
}

unsigned int kfifo_out(struct kfifo* fifo, unsigned char* buf, unsigned int len)
{
	unsigned int l;

	//rest kfifo data length
	len = min(len, fifo->in - fifo->out);

	//first we get data starting from fifo->out until the end of the buffer
	l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));//just for rest < len
	memcpy(buf, fifo->buffer + (fifo->out & (fifo->size - 1)), l);
	
	//then get rest at the beginning of the buffer;
	memcpy(buf + l, fifo->buffer, len -l);
	
	//update fifo->in length
	fifo->out += len;

	return len;	
}

#define FIFO_SIZE 1024

void main(int argc, char** argv)
{
	struct kfifo* fifo;
	unsigned char buf[64];

	fifo = kfifo_alloc(FIFO_SIZE);	
	memset(buf, 0xAA, sizeof(buf));
	
	kfifo_in(fifo, buf, sizeof(buf));
	printf("kfifo:%d\n", kfifo_len(fifo));
	
	kfifo_out(fifo, buf, sizeof(buf));
	printf("kfifo:%d\n", kfifo_len(fifo));

	kfifo_free(fifo);
}
