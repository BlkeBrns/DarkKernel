/* SPDX-License-Identifier: GPL-2.0 OR Apache-2.0 */

#ifndef RAMDUMP_REGIONS_H_
#define RAMDUMP_REGIONS_H_

#ifdef __KERNEL__
#include <linux/kernel.h>
#else
#include <stdint.h>
#endif

enum core_ramdump_status : u32 {
	CORE_RAMDUMP_NOT_STARTED = 0,
	CORE_RAMDUMP_IN_PROGRESS,
	CORE_RAMDUMP_COMPLETED,
};

enum ramdump_section_type : u32 {
	SECTION_TYPE_MEMORY = 0,
	SECTION_TYPE_CPU_REGISTER,
	SECTION_TYPE_CPU_DCACHE,
	SECTION_TYPE_CPU_ICACHE,
	SECTION_TYPE_CPU_TLB,
	SECTION_TYPE_SFR,
	SECTION_TYPE_SECURITY_SFR,
	SECTION_TYPE_TRACE,
	SECTION_TYPE_CRASH_INFO,
};

enum ramdump_section_flag : u32 {
	RAMDUMP_FLAG_VALID = 0x1,
};

/*
 * Number of sections:
 * 1 for SRAM
 * 1 for SFR
 * 4 for each CPU register
 * 8 for each CPU instruction and data cache
 * 1 for A32 TLB
 */
enum ramdump_section_index {
	RAMDUMP_SECTION_SRAM_INDEX = 0,
	RAMDUMP_SECTION_SFR_INDEX,
	RAMDUMP_SECTION_A32_REGISTER_INDEX,
	RAMDUMP_SECTION_A32_DCACHE_INDEX,
	RAMDUMP_SECTION_A32_ICACHE_INDEX,
	RAMDUMP_SECTION_A32_TLB_INDEX,
	RAMDUMP_SECTION_F1_REGISTER_INDEX,
	RAMDUMP_SECTION_F1_DCACHE_INDEX,
	RAMDUMP_SECTION_F1_ICACHE_INDEX,
	RAMDUMP_SECTION_HF0_REGISTER_INDEX,
	RAMDUMP_SECTION_HF0_DCACHE_INDEX,
	RAMDUMP_SECTION_HF0_ICACHE_INDEX,
	RAMDUMP_SECTION_HF1_REGISTER_INDEX,
	RAMDUMP_SECTION_HF1_DCACHE_INDEX,
	RAMDUMP_SECTION_HF1_ICACHE_INDEX,
	RAMDUMP_SECTION_A32_TRACE_INDEX,
	RAMDUMP_SECTION_CRASH_INFO_INDEX,

	RAMDUMP_NUM_SECTIONS,
};

enum RamdumpPlatform : uint32_t {
	RAMDUMP_PLATFORM_WHI = 1,
	RAMDUMP_PLATFORM_WHI_PRO,
};

struct aoc_section_header {
	char name[16]; /* User-friendly name */
	enum ramdump_section_type type;
	u32 core; /* Core that generated the dump */
	u32 flags; /* RamdumpSectionFlag */
	u32 offset; /* Offset from aoc_ramdump_header where data is stored */
	u32 size; /* Size of data */
	u32 vma; /* Section start virtual address */
	u32 lma; /* Section start physical address */
};

struct aoc_ramdump_header {
	char magic[8]; /* "AOCDUMP" */
	u32 valid;
	u32 num_sections;
	u32 time_taken[5]; /* Time taken for ramdump to complete per core, in AoC timer ticks */
	struct aoc_section_header sections[RAMDUMP_NUM_SECTIONS];
	enum RamdumpPlatform platform;
	uint32_t version;
	uint32_t breadcrumbs[16];
	uint8_t debug_authorized;
};

#define RAMDUMP_MAGIC "AOCDUMP"

#define RAMDUMP_HEADER_OFFSET 0x2000000 /* 32 MiB offset from start of DRAM carveout */
#define RAMDUMP_HEADER_ADDR (0x98000000 + RAMDUMP_HEADER_OFFSET) /* Start of DRAM carveout + offset */

#define RAMDUMP_SECTION_SRAM_OFFSET 0x1000
#define RAMDUMP_SECTION_SRAM_SIZE 0x600000
#define RAMDUMP_SECTION_SRAM_NAME "SRAM"

#define RAMDUMP_SECTION_SFR_OFFSET (RAMDUMP_SECTION_SRAM_OFFSET + RAMDUMP_SECTION_SRAM_SIZE)
#define RAMDUMP_SECTION_SFR_SIZE (0x100000)
#define RAMDUMP_SECTION_SFR_NAME "SFRs"

#define RAMDUMP_SECTION_A32_REGISTER_OFFSET (RAMDUMP_SECTION_SFR_OFFSET + RAMDUMP_SECTION_SFR_SIZE)
#define RAMDUMP_SECTION_A32_REGISTER_SIZE 0x1000
#define RAMDUMP_SECTION_A32_REGISTER_NAME "A32 registers"

#define RAMDUMP_SECTION_A32_DCACHE_OFFSET (RAMDUMP_SECTION_A32_REGISTER_OFFSET + RAMDUMP_SECTION_A32_REGISTER_SIZE)
#define RAMDUMP_SECTION_A32_DCACHE_SIZE (16 * 1024 * 2)
#define RAMDUMP_SECTION_A32_DCACHE_NAME "A32 D-cache"

#define RAMDUMP_SECTION_A32_ICACHE_OFFSET (RAMDUMP_SECTION_A32_DCACHE_OFFSET + RAMDUMP_SECTION_A32_DCACHE_SIZE)
#define RAMDUMP_SECTION_A32_ICACHE_SIZE (16 * 1024 * 2)
#define RAMDUMP_SECTION_A32_ICACHE_NAME "A32 I-cache"

#define RAMDUMP_SECTION_A32_TLB_OFFSET (RAMDUMP_SECTION_A32_ICACHE_OFFSET + RAMDUMP_SECTION_A32_ICACHE_SIZE)
#define RAMDUMP_SECTION_A32_TLB_SIZE (320 * 2 * 4 * 4)
#define RAMDUMP_SECTION_A32_TLB_NAME "A32 TLB"

#define RAMDUMP_SECTION_F1_REGISTER_OFFSET (RAMDUMP_SECTION_A32_TLB_OFFSET + RAMDUMP_SECTION_A32_TLB_SIZE)
#define RAMDUMP_SECTION_F1_REGISTER_SIZE 0x1000
#define RAMDUMP_SECTION_F1_REGISTER_NAME "F1 registers"

#define RAMDUMP_SECTION_F1_DCACHE_OFFSET (RAMDUMP_SECTION_F1_REGISTER_OFFSET + RAMDUMP_SECTION_F1_REGISTER_SIZE)
#define RAMDUMP_SECTION_F1_DCACHE_SIZE (64 * 1024 * 2)
#define RAMDUMP_SECTION_F1_DCACHE_NAME "F1 D-cache"

#define RAMDUMP_SECTION_F1_ICACHE_OFFSET (RAMDUMP_SECTION_F1_DCACHE_OFFSET + RAMDUMP_SECTION_F1_DCACHE_SIZE)
#define RAMDUMP_SECTION_F1_ICACHE_SIZE (64 * 1024 * 2)
#define RAMDUMP_SECTION_F1_ICACHE_NAME "F1 I-cache"

#define RAMDUMP_SECTION_HF0_REGISTER_OFFSET (RAMDUMP_SECTION_F1_ICACHE_OFFSET + RAMDUMP_SECTION_F1_ICACHE_SIZE)
#define RAMDUMP_SECTION_HF0_REGISTER_SIZE 0x1000
#define RAMDUMP_SECTION_HF0_REGISTER_NAME "HF0 registers"

#define RAMDUMP_SECTION_HF0_DCACHE_OFFSET (RAMDUMP_SECTION_HF0_REGISTER_OFFSET + RAMDUMP_SECTION_HF0_REGISTER_SIZE)
#define RAMDUMP_SECTION_HF0_DCACHE_SIZE (128 * 1024 * 2)
#define RAMDUMP_SECTION_HF0_DCACHE_NAME "HF0 D-cache"

#define RAMDUMP_SECTION_HF0_ICACHE_OFFSET (RAMDUMP_SECTION_HF0_DCACHE_OFFSET + RAMDUMP_SECTION_HF0_DCACHE_SIZE)
#define RAMDUMP_SECTION_HF0_ICACHE_SIZE (32 * 1024 * 2)
#define RAMDUMP_SECTION_HF0_ICACHE_NAME "HF0 I-cache"

#define RAMDUMP_SECTION_HF1_REGISTER_OFFSET (RAMDUMP_SECTION_HF0_ICACHE_OFFSET + RAMDUMP_SECTION_HF0_ICACHE_SIZE)
#define RAMDUMP_SECTION_HF1_REGISTER_SIZE 0x1000
#define RAMDUMP_SECTION_HF1_REGISTER_NAME "HF1 registers"

#define RAMDUMP_SECTION_HF1_DCACHE_OFFSET (RAMDUMP_SECTION_HF1_REGISTER_OFFSET + RAMDUMP_SECTION_HF1_REGISTER_SIZE)
#define RAMDUMP_SECTION_HF1_DCACHE_SIZE (128 * 1024 * 2)
#define RAMDUMP_SECTION_HF1_DCACHE_NAME "HF1 D-cache"

#define RAMDUMP_SECTION_HF1_ICACHE_OFFSET (RAMDUMP_SECTION_HF1_DCACHE_OFFSET + RAMDUMP_SECTION_HF1_DCACHE_SIZE)
#define RAMDUMP_SECTION_HF1_ICACHE_SIZE (32 * 1024 * 2)
#define RAMDUMP_SECTION_HF1_ICACHE_NAME "HF1 I-cache"

#define RAMDUMP_SECTION_A32_TRACE_OFFSET (RAMDUMP_SECTION_HF1_ICACHE_OFFSET + RAMDUMP_SECTION_HF1_ICACHE_SIZE)
#define RAMDUMP_SECTION_A32_TRACE_SIZE (64 * 1024)
#define RAMDUMP_SECTION_A32_TRACE_NAME "A32 trace"

#define RAMDUMP_SECTION_CRASH_INFO_OFFSET (RAMDUMP_SECTION_A32_TRACE_OFFSET + RAMDUMP_SECTION_A32_TRACE_SIZE)
#define RAMDUMP_SECTION_CRASH_INFO_SIZE 256
#define RAMDUMP_SECTION_CRASH_INFO_NAME "Crash info"

#endif /* RAMDUMP_REGIONS_H_ */

