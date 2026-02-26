#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum lds_type {
	LDS_ARRAY,
	LDS_LL,
	LDS_MAX
};

enum lds_ops_type {
	LDS_OPS_CREATE,
	LDS_OPS_READ,
	LDS_OPS_UPDATE,
	LDS_OPS_DELETE,
	LDS_OPS_SEARCH,
	LDS_OPS_MAX
};

/* Forward declaration for the function pointer prototype */
struct lds;
typedef void * (*lds_ops_fptr)(struct lds *lds, void *arg);

struct lds {
	void *mem;
	enum lds_type type;
	lds_ops_fptr ops[LDS_OPS_MAX];
	unsigned int selem;
	unsigned int nelem;
};

typedef struct lds *(*lds_init_cb) (const unsigned int nelem, const unsigned int selem);
lds_init_cb lds_cb[LDS_MAX];

static struct lds *_lds_alloc(enum lds_type type)
{
	printf("%s: type: %d\n", __func__, type);
	struct lds *lds = malloc(1);
	assert(lds != NULL);
	lds->type = type;
	return lds;
}

void *array_create(struct lds *array, void *arg)
{
	return NULL;
}

void *array_read(struct lds *array, void *arg)
{
	return NULL;
}

void *array_update(struct lds *array, void *arg)
{
	return NULL;
}

void *array_delete(struct lds *array, void *arg)
{
	return NULL;
}

void *array_search(struct lds *array, void *arg)
{
	return NULL;
}

struct lds *array_init(const unsigned int selem, const unsigned int nelem)
{
	struct lds *array = _lds_alloc(LDS_ARRAY);

	array->mem = calloc(nelem, selem);
	assert(array->mem != NULL);

	array->selem = selem;
	array->nelem = nelem;

	array->ops[LDS_OPS_CREATE] 	= array_create;
	array->ops[LDS_OPS_READ] 	= array_read;
	array->ops[LDS_OPS_UPDATE] 	= array_update;
	array->ops[LDS_OPS_DELETE] 	= array_delete;
	array->ops[LDS_OPS_SEARCH] 	= array_search;

	return array;
}

struct lds *ll_init(const unsigned int selem, const unsigned int nelem)
{
	struct lds *ll = NULL;
	return ll;
}

static struct lds *lds_init(enum lds_type type, const unsigned int selem,
		const unsigned int nelem)
{
	/* populate all callbacks */
	lds_cb[LDS_ARRAY] = array_init;
	lds_cb[LDS_LL] = ll_init;

	lds_init_cb cb = lds_cb[type];
	return cb ? cb(selem, nelem): NULL; 
}

static void print_lds(struct lds *lds)
{
	printf("%s: lds @ %p\n", __func__, lds);
	if (!lds) return;
	printf("mem: %p\n", lds->mem);
	printf("type: %d\n", lds->type);
	printf("selem: %u\n", lds->selem);
	printf("nelem: %u\n", lds->nelem);
	printf("\n");
}

int main(void)
{
	struct lds *lds = lds_init(LDS_ARRAY, sizeof(int), 100);
	print_lds(lds);
	return 0;
}
