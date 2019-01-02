#ifndef TOKEN_BUCKET_H
#define TOKEN_BUCKET_H

#include <stdint.h>

struct token_bucket;
typedef struct token_bucket token_bucket_t;

token_bucket_t * tb_create(uint64_t capa);
void tb_consume(token_bucket_t *tb, uint64_t num_bucket);
void tb_refill(token_bucket_t *tb, uint64_t num_tokens);
void tb_destroy(token_bucket_t *tb);

#endif
