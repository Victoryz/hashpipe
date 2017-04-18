/*
 * demo_output_thread.c
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include "hashpipe.h"
#include "demo_databuf.h"

static void *run(hashpipe_thread_args_t * args)
{
    // Local aliases to shorten access to args fields
    // Our input buffer happens to be a demo_ouput_databuf
    demo_output_databuf_t *db = (demo_output_databuf_t *)args->ibuf;
    hashpipe_status_t st = args->st;
    const char * status_key = args->thread_desc->skey;
    int c,rv;
    int block_idx = 0;
    FILE * demo_file;
    demo_file=fopen("./demo_file.txt","w");
    
    /* Main loop */
    while (run_threads()) {

        hashpipe_status_lock_safe(&st);
        hputi4(st.buf, "OUTBLKIN", block_idx);
        hputs(st.buf, status_key, "waiting");
        hashpipe_status_unlock_safe(&st);

       // get new data
       while ((rv=demo_output_databuf_wait_filled(db, block_idx))
                != HASHPIPE_OK) {
            if (rv==HASHPIPE_TIMEOUT) {
                hashpipe_status_lock_safe(&st);
                hputs(st.buf, status_key, "blocked");
                hashpipe_status_unlock_safe(&st);
                continue;
            } else {
                hashpipe_error(__FUNCTION__, "error waiting for filled databuf");
                pthread_exit(NULL);
                break;
            }
        }

        hashpipe_status_lock_safe(&st);
        hputs(st.buf, status_key, "processing");
        hashpipe_status_unlock_safe(&st);

        // TODO check mcnt
	c=db->block[block_idx].sum;
        fwrite(&c,1,1,demo_file);

        hashpipe_status_lock_safe(&st);
        hputi8(st.buf, "SUM", c);
        hashpipe_status_unlock_safe(&st);
    }
    fclose(demo_file);
    return NULL;
}

static hashpipe_thread_desc_t output_thread = {
    name: "demo_output_thread",
    skey: "OUTSTAT",
    init: NULL, 
    run:  run,
    ibuf_desc: {demo_output_databuf_create},
    obuf_desc: {NULL}
};

static __attribute__((constructor)) void ctor()
{
  register_hashpipe_thread(&output_thread);
}

