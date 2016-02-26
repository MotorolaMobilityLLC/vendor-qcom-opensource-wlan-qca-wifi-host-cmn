/*
 * Copyright (c) 2014-2015 The Linux Foundation. All rights reserved.
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

#if !defined(__SMERRMAPI_H)
#define __SMERRMAPI_H

/**
 * \file  sme_rrm_api.h
 *
 * \brief prototype for SME RRM APIs
 */

/*--------------------------------------------------------------------------
  Include Files
  ------------------------------------------------------------------------*/
#include "cdf_lock.h"
#include "cdf_trace.h"
#include "cdf_memory.h"
#include "cdf_types.h"
#include "ani_global.h"
#include "sir_api.h"
#include "sme_internal.h"
#include "sme_rrm_internal.h"

CDF_STATUS sme_rrm_msg_processor(tpAniSirGlobal pMac, uint16_t msg_type,
		void *pMsgBuf);
CDF_STATUS rrm_close(tpAniSirGlobal pMac);
CDF_STATUS rrm_ready(tpAniSirGlobal pMac);
CDF_STATUS rrm_open(tpAniSirGlobal pMac);
CDF_STATUS rrm_change_default_config_param(tpAniSirGlobal pMac,
		struct rrm_config_param *rrm_config);
CDF_STATUS sme_rrm_neighbor_report_request(tpAniSirGlobal pMac,
		uint8_t sessionId, tpRrmNeighborReq pNeighborReq,
		tpRrmNeighborRspCallbackInfo callbackInfo);
tRrmNeighborReportDesc *sme_rrm_get_first_bss_entry_from_neighbor_cache(
		tpAniSirGlobal pMac);
tRrmNeighborReportDesc *sme_rrm_get_next_bss_entry_from_neighbor_cache(
		tpAniSirGlobal pMac,
		tpRrmNeighborReportDesc pBssEntry);
CDF_STATUS sme_rrm_process_beacon_report_req_ind(tpAniSirGlobal pMac,
		void *pMsgBuf);

#endif
