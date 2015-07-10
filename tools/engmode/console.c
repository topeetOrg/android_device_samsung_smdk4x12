#include <stdio.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <termios.h>
#include <stdlib.h>
#include <pthread.h>
#include "console.h"

#define DEBUG 0

FILE* output;
FILE* input;

static int uart_fd = -1;
static struct termios termios;

/**
 * for cyit dvt, uses ttySAC3
 * shaoguodong.
 */
#define CONSOLE_TTY "/dev/ttySAC3"
//#define CONSOLE_TTY "/dev/tty"

static struct pollfd ufds;

static int uart_init()
{
	uart_fd = open(CONSOLE_TTY, O_RDWR);
	if (uart_fd < 0)
		return -1;

	tcflush(uart_fd, TCIOFLUSH);
	tcgetattr(uart_fd, &termios);

	tcflush(uart_fd, TCIOFLUSH);
	cfsetospeed(&termios, B115200);
	cfsetispeed(&termios, B115200);
	tcsetattr(uart_fd, TCSANOW, &termios);

	return 0;
}


static void* uart_event_proc(void* args)
{
	char buffer[101];
	char* p;
	int n = -1;
	int len = 0;

	while (1)
	{
		if (n < 0) {
			p = buffer;
			buffer[99] = 0;
		} else
			p = buffer+n;
		n = read(uart_fd, p, 100 - len);
		len += n;
		if (p[n - 1] == '\n' || len == 100) {	
			p[n] = 0;
			if (DEBUG) 
				print("%s", buffer);
			
			process_event(buffer, 100); /* process the uart data, enqueue a event or dismiss it */
			n = -1; /* reset the buffer */
			len = 0;
		}
	}

	/* should nerver reach here */
	return NULL;
}

void console_init(void)
{
	pthread_t p;

	uart_init();
	output = fopen(CONSOLE_TTY, "w");
	input = fopen(CONSOLE_TTY, "r");

	ufds.fd = open(CONSOLE_TTY, O_RDWR);
	ufds.events = POLLIN;

	p = pthread_create(&p, NULL, uart_event_proc, NULL);
}

int get_input(char* buffer, int len)
{
	while (1) {
		poll(&ufds, 1, -1);
		if (ufds.revents & POLLIN) {
			return fread(buffer, 1, len, input);
		}
	}
}

void console_exit(void)
{
	fflush(output);
	fflush(input);
	fclose(output);
	fclose(input);
}
