#include "base.h"
#include "arena.h"
#include "prng.h"

#include "arena.c"
#include "prng.c"
#include <string.h>

typedef struct {
  u32 rows, cols;
  f32* data;
} matrix;

matrix* mat_create(mem_arena* arena, u32 rows, u32 cols);
b32 mat_copy(matrix* dst, matrix* src);
void mat_clear(matrix* mat);
void mat_fill(matrix* mat, f32 x);
void mat_scale(matrix* mat, f32 scale);

f32 mat_sum(matrix* mat);
b32 mat_add(matrix* out, const matrix* a, const matrix* b);
b32 mat_sub(matrix* out, const matrix* a, const matrix* b);
b32 mat_mul(
  matrix* out, const matrix* a, const matrix* b,
  b8 zero_out, b8 transpose_a, b8 transpose_b
);
b32 mat_relu(matrix* out, const matrix* in);
b32 mat_softmax(matrix* out, const matrix* in);
b32 mat_cross_entropy(matrix* out, const matrix* p, const matrix* q);
b32 mat_relu_add_grad(matrix* out, const matrix* in);
b32 mat_softmax_add_grad(matrix* out, const matrix* softmax_out);
b32 mat_cross_entropy_add_grad(matrix* out, const matrix* p, const matrix* q);

int main(void) {
  mem_arena* perm_arena = arena_create(GiB(1), MiB(1));
  arena_destroy(perm_arena);

  return 0;
}

matrix* mat_create(mem_arena* arena, u32 rows, u32 cols) {
  matrix* mat = PUSH_STRUCT(arena, matrix);

  mat->rows = rows;
  mat->cols = cols;
  mat->data = PUSH_ARRAY(arena, f32, (u64)rows * cols);

  return mat;
}

b32 mat_copy(matrix* dst, matrix* src) {
  if (dst->rows != src->rows || dst->cols != src->cols) {
    return false;
  }

  memcpy(dst->data, src->data, sizeof(f32) * (u64)dst->rows * dst->cols);

  return true;
}


void mat_clear(matrix* mat) {
  memset(mat->data, 0, sizeof(f32) * (u64)mat->rows * mat->cols);
}

void mat_fill(matrix* mat, f32 x) {
  u64 size = (u64)mat->rows * mat->cols;

  for (u64 i = 0; i < size; i++) {
    mat->data[i] = x;
  }
}

void mat_scale(matrix* mat, f32 scale) {
  u64 size = (u64)mat->rows * mat->cols;

  for (u64 i = 0; i < size; i++) {
    mat->data[i] *= scale;
  }
}

f32 mat_sum(matrix* mat) {
  u64 size = (u64)mat->rows * mat->cols;

  f32 sum = 0.0f;
  for (u64 i = 0; i < size; i++) {
    sum += mat->data[i];
  }

  return sum;
}

b32 mat_add(matrix* out, const matrix* a, const matrix* b) {
  if (a->rows != b->rows || a->cols != b->cols) {
    return false;
  }
  if (a->rows != out->rows || a->cols != out->cols) {
    return false;
  }

  u64 size = (u64)out->rows * out->cols;
  for (u64 i = 0; i < size; i++) {
    out->data[i] = a->data[i] + b->data[i];
  }

  return true;
}

b32 mat_sub(matrix* out, const matrix* a, const matrix* b) {
  if (a->rows != b->rows || a->cols != b->cols) {
    return false;
  }
  if (a->rows != out->rows || a->cols != out->cols) {
    return false;
  }

  u64 size = (u64)out->rows * out->cols;
  for (u64 i = 0; i < size; i++) {
    out->data[i] = a->data[i] - b->data[i];
  }

  return true;
}

