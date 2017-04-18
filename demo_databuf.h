#include <stdint.h>
#include <stdio.h>
#include "hashpipe.h"
#include "hashpipe_databuf.h"

#define CACHE_ALIGNMENT         256
#define N_INPUT_BLOCKS          3 
#define N_OUTPUT_BLOCKS         3

/* INPUT BUFFER STRUCTURES
  */
typedef struct demo_input_block_header {
   uint64_t mcnt;                    // mcount of first packet
} demo_input_block_header_t;

typedef uint8_t demo_input_header_cache_alignment[
   CACHE_ALIGNMENT - (sizeof(demo_input_block_header_t)%CACHE_ALIGNMENT)
];

typedef struct demo_input_block {
   demo_input_block_header_t header;
   demo_input_header_cache_alignment padding; // Maintain cache alignment
   uint64_t number1;
   uint64_t number2;
} demo_input_block_t;

typedef struct demo_input_databuf {
   hashpipe_databuf_t header;
   demo_input_header_cache_alignment padding;
   //hashpipe_databuf_cache_alignment padding; // Maintain cache alignment
   demo_input_block_t block[N_INPUT_BLOCKS];
} demo_input_databuf_t;


/*
  * OUTPUT BUFFER STRUCTURES
  */
typedef struct demo_output_block_header {
   uint64_t mcnt;
} demo_output_block_header_t;

typedef uint8_t demo_output_header_cache_alignment[
   CACHE_ALIGNMENT - (sizeof(demo_output_block_header_t)%CACHE_ALIGNMENT)
];

typedef struct demo_output_block {
   demo_output_block_header_t header;
   demo_output_header_cache_alignment padding; // Maintain cache alignment
   uint64_t sum;
} demo_output_block_t;

typedef struct demo_output_databuf {
   hashpipe_databuf_t header;
   demo_output_header_cache_alignment padding;
   //hashpipe_databuf_cache_alignment padding; // Maintain cache alignment
   demo_output_block_t block[N_OUTPUT_BLOCKS];
} demo_output_databuf_t;

/*
 * INPUT BUFFER FUNCTIONS
 */
hashpipe_databuf_t *demo_input_databuf_create(int instance_id, int databuf_id);

static inline demo_input_databuf_t *demo_input_databuf_attach(int instance_id, int databuf_id)
{
    return (demo_input_databuf_t *)hashpipe_databuf_attach(instance_id, databuf_id);
}

static inline int demo_input_databuf_detach(demo_input_databuf_t *d)
{
    return hashpipe_databuf_detach((hashpipe_databuf_t *)d);
}

static inline void demo_input_databuf_clear(demo_input_databuf_t *d)
{
    hashpipe_databuf_clear((hashpipe_databuf_t *)d);
}

static inline int demo_input_databuf_block_status(demo_input_databuf_t *d, int block_id)
{
    return hashpipe_databuf_block_status((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_input_databuf_total_status(demo_input_databuf_t *d)
{
    return hashpipe_databuf_total_status((hashpipe_databuf_t *)d);
}

static inline int demo_input_databuf_wait_free(demo_input_databuf_t *d, int block_id)
{
    return hashpipe_databuf_wait_free((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_input_databuf_busywait_free(demo_input_databuf_t *d, int block_id)
{
    return hashpipe_databuf_busywait_free((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_input_databuf_wait_filled(demo_input_databuf_t *d, int block_id)
{
    return hashpipe_databuf_wait_filled((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_input_databuf_busywait_filled(demo_input_databuf_t *d, int block_id)
{
    return hashpipe_databuf_busywait_filled((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_input_databuf_set_free(demo_input_databuf_t *d, int block_id)
{
    return hashpipe_databuf_set_free((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_input_databuf_set_filled(demo_input_databuf_t *d, int block_id)
{
    return hashpipe_databuf_set_filled((hashpipe_databuf_t *)d, block_id);
}

/*
 * OUTPUT BUFFER FUNCTIONS
 */

hashpipe_databuf_t *demo_output_databuf_create(int instance_id, int databuf_id);

static inline void demo_output_databuf_clear(demo_output_databuf_t *d)
{
    hashpipe_databuf_clear((hashpipe_databuf_t *)d);
}

static inline demo_output_databuf_t *demo_output_databuf_attach(int instance_id, int databuf_id)
{
    return (demo_output_databuf_t *)hashpipe_databuf_attach(instance_id, databuf_id);
}

static inline int demo_output_databuf_detach(demo_output_databuf_t *d)
{
    return hashpipe_databuf_detach((hashpipe_databuf_t *)d);
}

static inline int demo_output_databuf_block_status(demo_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_block_status((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_output_databuf_total_status(demo_output_databuf_t *d)
{
    return hashpipe_databuf_total_status((hashpipe_databuf_t *)d);
}

static inline int demo_output_databuf_wait_free(demo_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_wait_free((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_output_databuf_busywait_free(demo_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_busywait_free((hashpipe_databuf_t *)d, block_id);
}
static inline int demo_output_databuf_wait_filled(demo_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_wait_filled((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_output_databuf_busywait_filled(demo_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_busywait_filled((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_output_databuf_set_free(demo_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_set_free((hashpipe_databuf_t *)d, block_id);
}

static inline int demo_output_databuf_set_filled(demo_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_set_filled((hashpipe_databuf_t *)d, block_id);
}


