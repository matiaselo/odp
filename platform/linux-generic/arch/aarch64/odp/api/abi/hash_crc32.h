/* Copyright (c) 2021 ARM Limited
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

#ifdef __ARM_FEATURE_CRC32

#include <arm_acle.h>

static inline uint32_t _crc32_u8(uint8_t data, uint32_t init_val)
{
	return __crc32b(init_val, data);
}

static inline uint32_t _crc32_u16(uint16_t data, uint32_t init_val)
{
	return __crc32h(init_val, data);
}

static inline uint32_t _crc32_u32(uint32_t data, uint32_t init_val)
{
	return __crc32w(init_val, data);
}

static inline uint64_t _crc32_u64(uint64_t data, uint32_t init_val)
{
	return __crc32d(init_val, data);
}

static inline uint32_t _crc32c_u8(uint8_t data, uint32_t init_val)
{
	return __crc32cb(init_val, data);
}

static inline uint32_t _crc32c_u16(uint16_t data, uint32_t init_val)
{
	return __crc32ch(init_val, data);
}

static inline uint32_t _crc32c_u32(uint32_t data, uint32_t init_val)
{
	return __crc32cw(init_val, data);
}

static inline uint64_t _crc32c_u64(uint64_t data, uint32_t init_val)
{
	return __crc32cd(init_val, data);
}

static inline uint32_t _odp_hash_crc32(const void *data_ptr, uint32_t data_len,
				       uint32_t init_val)
{
	uint32_t i;
	uintptr_t pd = (uintptr_t)data_ptr;

	for (i = 0; i < data_len / 8; i++) {
		init_val = _crc32_u64(*(const uint64_t *)pd, init_val);
		pd += 8;
	}

	if (data_len & 0x4) {
		init_val = _crc32_u32(*(const uint32_t *)pd, init_val);
		pd += 4;
	}

	if (data_len & 0x2) {
		init_val = _crc32_u16(*(const uint16_t *)pd, init_val);
		pd += 2;
	}

	if (data_len & 0x1)
		init_val = _crc32_u8(*(const uint8_t *)pd, init_val);

	return init_val;
}

static inline uint32_t _odp_hash_crc32c(const void *data, uint32_t data_len,
					uint32_t init_val)
{
	uint32_t i;
	uintptr_t pd = (uintptr_t)data;

	for (i = 0; i < data_len / 8; i++) {
		init_val = _crc32c_u64(*(const uint64_t *)pd, init_val);
		pd += 8;
	}

	if (data_len & 0x4) {
		init_val = _crc32c_u32(*(const uint32_t *)pd, init_val);
		pd += 4;
	}

	if (data_len & 0x2) {
		init_val = _crc32c_u16(*(const uint16_t *)pd, init_val);
		pd += 2;
	}

	if (data_len & 0x1)
		init_val = _crc32c_u8(*(const uint8_t *)pd, init_val);

	return init_val;
}

#else /* __ARM_FEATURE_CRC32 */

/*
 * Fall back to software implementation
 */

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

#endif

#ifdef __cplusplus
}
#endif

#endif
