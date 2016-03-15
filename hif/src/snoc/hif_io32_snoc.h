/*
 * Copyright (c) 2015-2016 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

/**
 * DOC: hif_io32_snoc.h
 *
 * snoc specific implementations and configurations
 */

#ifndef __HIF_IO32_SNOC_H__
#define __HIF_IO32_SNOC_H__

#include "hif.h"
#include "regtable.h"
#include "ce_reg.h"
#include "qdf_atomic.h"
#include <soc/qcom/icnss.h>
#include "hif_main.h"
#include "hif_debug.h"

/**
 * Following features are not supported for snoc bus
 * Force 0 and consider moving corresponding code into
 * pci specific files
 */
#define A_TARGET_ACCESS_BEGIN_RET_PTR(scn)
#define A_TARGET_ACCESS_END_RET_PTR(scn)
#define A_TARGET_ACCESS_BEGIN_RET(scn)
#define A_TARGET_ACCESS_END_RET(scn)
#define A_TARGET_ACCESS_BEGIN_RET_EXT(scn, val)
#define A_TARGET_ACCESS_END_RET_EXT(scn, val)

#define ADRASTEA_CE_INTR_ENABLES 0x002F00A8
#define ADRASTEA_CE_INTR_ENABLES_SET "COMING IN REGISTER SET36"
#define ADRASTEA_CE_INTR_ENABLES_CLEAR "COMING IN REGISTER SET36"

#define ADRASTEA_CE_INTR_STATUS 0x002F00AC

static inline void ce_enable_irq_in_individual_register(struct hif_softc *scn,
		int ce_id)
{
	uint32_t offset;
	offset = HOST_IE_ADDRESS + CE_BASE_ADDRESS(ce_id);
	hif_write32_mb(scn->mem + offset, 1);
	hif_read32_mb(scn->mem + offset);
}

static inline void ce_disable_irq_in_individual_register(struct hif_softc *scn,
		int ce_id)
{
	uint32_t offset;
	offset = HOST_IE_ADDRESS + CE_BASE_ADDRESS(ce_id);
	hif_write32_mb(scn->mem + offset, 0);
	hif_read32_mb(scn->mem + offset);
}

static inline void ce_read_irq_group_status(struct hif_softc *scn)
{
	uint32_t group_status = 0;
	group_status = hif_read32_mb(scn->mem +
			ADRASTEA_CE_INTR_STATUS);
}

static inline void ce_clear_irq_group_status(struct hif_softc *scn, int mask)
{
	uint32_t group_status = 0;
	group_status = hif_read32_mb(scn->mem +
			ADRASTEA_CE_INTR_STATUS);

	hif_write32_mb(scn->mem +
			ADRASTEA_CE_INTR_STATUS, mask);

	group_status = hif_read32_mb(scn->mem +
			ADRASTEA_CE_INTR_STATUS);
}

/* this will need to be changed when we move to reg set 36
 * because we will have set & clear registers provided
 */
static inline void ce_enable_irq_in_group_reg(struct hif_softc *scn,
		int mask)
{
	int new_mask = 0;
	new_mask = hif_read32_mb(scn->mem +
			ADRASTEA_CE_INTR_ENABLES);

	new_mask |= mask;

	hif_write32_mb(scn->mem +
			ADRASTEA_CE_INTR_ENABLES, new_mask);
	mask = hif_read32_mb(scn->mem +
			ADRASTEA_CE_INTR_ENABLES);
}

/* this will need to be changed when we move to reg set 36
 * because we will have set & clear registers provided
 */
static inline void ce_disable_irq_in_group_reg(struct hif_softc *scn,
		int mask)
{
	int new_mask = 0;
	new_mask = hif_read32_mb(scn->mem +
			ADRASTEA_CE_INTR_ENABLES);

	new_mask &= ~mask;

	hif_write32_mb(scn->mem +
			ADRASTEA_CE_INTR_ENABLES, new_mask);
	mask = hif_read32_mb(scn->mem +
			ADRASTEA_CE_INTR_ENABLES);
}

/**
 * ce_irq_enable() - enable copy engine IRQ
 * @scn: struct hif_softc
 * @ce_id: ce_id
 *
 * Return: N/A
 */
static inline void ce_irq_enable(struct hif_softc *scn,
		int ce_id)
{
	icnss_enable_irq(ce_id);
	ce_enable_irq_in_individual_register(scn, ce_id);
	ce_enable_irq_in_group_reg(scn, 1<<ce_id);
}

/**
 * ce_irq_disable() - disable copy engine IRQ
 * @scn: struct hif_softc
 * @ce_id: ce_id
 *
 * Return: N/A
 */
static inline void ce_irq_disable(struct hif_softc *scn, int ce_id)
{
	ce_disable_irq_in_group_reg(scn, 1<<ce_id);
	ce_clear_irq_group_status(scn, 1<<ce_id);
	ce_disable_irq_in_individual_register(scn, ce_id);
}
#endif
