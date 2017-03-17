/*
  +----------------------------------------------------------------------+
  | UC                                                                   |
  +----------------------------------------------------------------------+
  | Copyright (c) 2017 David Strauss                                     |
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

#ifndef UC_DATABASE_H
#define UC_DATABASE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* uc_storage_t;

typedef zend_bool success_t;

typedef struct {
    zval val;
    success_t success;
} zval_and_success;

uc_storage_t uc_storage_init(const size_t size);
success_t uc_storage_store(uc_storage_t st_opaque,
                           const zend_string* address,
                           const zval* data,
                           const time_t expiration,
                           const zend_bool exclusive);

zval_and_success uc_storage_increment(uc_storage_t st_opaque, const zend_string* address, const long step);
success_t uc_storage_cas(uc_storage_t st_opaque, const zend_string* address, const long next, const long expected);
void uc_storage_clear(uc_storage_t st_opaque);
zval_and_success uc_storage_get(uc_storage_t st_opaque, const zend_string* address, const time_t now);
size_t uc_storage_size(uc_storage_t st_opaque);
success_t uc_storage_exists(uc_storage_t st_opaque, const zend_string* address, const time_t now);
void uc_storage_dump(uc_storage_t st_opaque);
success_t uc_storage_delete(uc_storage_t st_opaque, const zend_string* address);

#ifdef __cplusplus
}
#endif

#endif
