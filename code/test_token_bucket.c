#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

#include "token_bucket.h"

token_bucket_t *tb;

static void refiller(int signo)
{
	tb_refill(tb, 1);
}

static void start_tb_refiller(void)
{
	struct itimerval itv;

	if (signal(SIGALRM, refiller) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	itv.it_interval = (struct timeval){1, 0};
	itv.it_value = (struct timeval){1, 0};

	if (setitimer(ITIMER_REAL, &itv, NULL) < 0) {
		perror("setitimer");
		exit(1);
	}
}

int main(void)
{
	tb = tb_create(1);
	if (!tb) {
		printf("no tb\n");
		exit(1);
	}

	start_tb_refiller();

	while (1) {
		tb_consume(tb, 1);
		printf("hi\n");
	}

	return 0;
}
