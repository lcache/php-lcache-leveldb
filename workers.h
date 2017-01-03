/*
  +----------------------------------------------------------------------+
  | UC                                                                   |
  +----------------------------------------------------------------------+
  | Copyright (c) 2015 The PHP Group                                     |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: David Strauss <david@davidstrauss.net>                      |
  +----------------------------------------------------------------------+
 */

#ifndef UC_WORKERS_H
#define UC_WORKERS_H

#include <pthread.h>
#include "marshalling.h"
#include "persistence.h"

#define MAX_KEY_LENGTH 512
#define MAX_VALUE_SIZE 2097152

typedef enum {
    kRunning = 0,
    kStopping = 1
} lifecycle_t;

typedef struct {
    size_t id;
    lifecycle_t l;
    uc_persistence_t* p;
    pthread_mutex_t use_l;
    pthread_mutex_t req_l;
    pthread_cond_t req;
    pthread_mutex_t resp_l;
    pthread_cond_t resp;
    pthread_cond_t* ow;
    pthread_t td;
    uc_metadata_t m;
    size_t kl;
    char k[MAX_KEY_LENGTH];
    size_t vl;
    char v[MAX_VALUE_SIZE];
} worker_t;

typedef struct {
    size_t workers_count;
    pthread_cond_t open_worker;
    pthread_mutex_t open_worker_lock;
    worker_t* workers;
} worker_pool_t;

int uc_workers_init(const uc_persistence_t* p, size_t workers_count, worker_pool_t** wp);
int uc_workers_destroy(worker_pool_t* wp);

#endif