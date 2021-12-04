#pragma once

#include <gba.h>


/// https://github.com/karshan/tonclib/blob/ec5f2ef40ab272bb4057c8140284ceb30c4f833a/include/tonc_core.h#L486-L500
/// https://github.com/devkitPro/libgba/blob/a7b03d614aa5d31b1dd36f4f21fb8d4286017f94/include/gba_dma.h#L80-L88	

#define DMA_AT_NOW				 0	//!< Start transfer now
#define DMA_NOW		(DMA_ENABLE  | DMA_AT_NOW)
#define DMA_16					 0	//!< Transfer by halfword
#define DMA_32			0x04000000	//!< Transfer by word

#define DMA_FILL16	(DMA_NOW | DMA_SRC_FIXED | DMA_16)
#define DMA_FILL32	(DMA_NOW | DMA_SRC_FIXED | DMA_32)

static u32 dma_fill_val = 0x00000000;

#define DMA_Fill(channel, dest, val, count, mode) {\
	dma_fill_val = val; \
	REG_DMA##channel##CNT = 0; \
	REG_DMA##channel##SAD = (u32)(&(dma_fill_val));\
	REG_DMA##channel##DAD = (u32)(dest);\
	REG_DMA##channel##CNT = (count) | (mode) | DMA_SRC_FIXED; \
}

static inline void dmaFillDouble(void* dest, u32 value, u32 size)
{
	DMA_Fill(3, dest, value, size>>2, DMA_FILL32);
}