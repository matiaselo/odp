/* Copyright (c) 2021, Nokia
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

#ifndef ODP_API_ABI_HASH_CRC32_H_
#define ODP_API_ABI_HASH_CRC32_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint32_t _odp_hash_crc32_generic(const void *data, uint32_t data_len,
				 uint32_t init_val);
uint32_t _odp_hash_crc32c_generic(const void *data, uint32_t data_len,
				  uint32_t init_val);

static inline uint32_t _odp_hash_crc32(const void *data, uint32_t data_len,
				       uint32_t init_val)
{
	return _odp_hash_crc32_generic(data, data_len, init_val);
}

static inline uint32_t _odp_hash_crc32c(const void *data, uint32_t data_len,
					uint32_t init_val)
{
	return _odp_hash_crc32c_generic(data, data_len, init_val);
}

#ifdef __cplusplus
}
#endif

#endif
