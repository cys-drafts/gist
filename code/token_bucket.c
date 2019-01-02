#include <stdlib.h>

#include "token_bucket.h"

struct token_bucket {
	uint64_t tokens;
	uint64_t capa;
};

void tb_refill(token_bucket_t *tb, uint64_t num_tokens)
{
	tb->tokens += num_tokens;
	if (tb->tokens > tb->capa)
		tb->tokens = tb->capa;
}

token_bucket_t * tb_create(uint64_t capa)
{
	token_bucket_t *tb;;

	tb = malloc(sizeof(*tb));
	if (!tb) {
		return NULL;
	}

	tb->tokens = 0;
	tb->capa = capa;
}

void tb_consume(token_bucket_t *tb, uint64_t num_tokens)
{
	volatile uint64_t *curr_tokens;

	curr_tokens = (volatile uint64_t *)&tb->tokens;

retry:
	if (*curr_tokens >= num_tokens) {
		tb->tokens -= num_tokens;
		return;
	}
	goto retry;
}

void tb_destroy(token_bucket_t *tb)
{
	free(tb);
}
