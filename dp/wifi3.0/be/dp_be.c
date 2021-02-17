/*
 * Copyright (c) 2021 The Linux Foundation. All rights reserved.
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

#include <dp_internal.h>
#include <dp_htt.h>
#include "dp_be.h"
#include "dp_be_tx.h"
#include "dp_be_rx.h"

qdf_size_t dp_get_context_size_be(enum dp_context_type context_type)
{
	switch (context_type) {
	case DP_CONTEXT_TYPE_SOC:
		return sizeof(struct dp_soc_be);
	case DP_CONTEXT_TYPE_PDEV:
		return sizeof(struct dp_pdev_be);
	case DP_CONTEXT_TYPE_VDEV:
		return sizeof(struct dp_vdev_be);
	case DP_CONTEXT_TYPE_PEER:
		return sizeof(struct dp_peer_be);
	default:
		return 0;
	}
}

static QDF_STATUS dp_soc_attach_be(struct dp_soc *soc)
{
	struct dp_soc_be *be_soc = dp_get_be_soc_from_dp_soc(soc);
	QDF_STATUS qdf_status = QDF_STATUS_SUCCESS;

	soc->wbm_sw0_bm_id = hal_tx_get_wbm_sw0_bm_id();
	qdf_status = dp_tx_init_bank_profiles(be_soc);

	return qdf_status;
}

static QDF_STATUS dp_soc_detach_be(struct dp_soc *soc)
{
	struct dp_soc_be *be_soc = dp_get_be_soc_from_dp_soc(soc);

	dp_tx_deinit_bank_profiles(be_soc);

	return QDF_STATUS_SUCCESS;
}

static QDF_STATUS dp_pdev_attach_be(struct dp_pdev *pdev)
{
	return QDF_STATUS_SUCCESS;
}

static QDF_STATUS dp_pdev_detach_be(struct dp_pdev *pdev)
{
	return QDF_STATUS_SUCCESS;
}

static QDF_STATUS dp_vdev_attach_be(struct dp_soc *soc, struct dp_vdev *vdev)
{
	struct dp_soc_be *be_soc = dp_get_be_soc_from_dp_soc(soc);
	struct dp_vdev_be *be_vdev = dp_get_be_vdev_from_dp_vdev(vdev);

	be_vdev->bank_id = dp_tx_get_bank_profile(be_soc, be_vdev);

	/* Needs to be enabled after bring-up*/
	be_vdev->vdev_id_check_en = false;

	if (be_vdev->bank_id == DP_BE_INVALID_BANK_ID) {
		QDF_BUG(0);
		return QDF_STATUS_E_FAULT;
	}
	return QDF_STATUS_SUCCESS;
}

static QDF_STATUS dp_vdev_detach_be(struct dp_soc *soc, struct dp_vdev *vdev)
{
	struct dp_soc_be *be_soc = dp_get_be_soc_from_dp_soc(soc);
	struct dp_vdev_be *be_vdev = dp_get_be_vdev_from_dp_vdev(vdev);

	dp_tx_put_bank_profile(be_soc, be_vdev);
	return QDF_STATUS_SUCCESS;
}

qdf_size_t dp_get_soc_context_size_be(void)
{
	return sizeof(struct dp_soc_be);
}

/**
 * dp_rxdma_ring_sel_cfg_be() - Setup RXDMA ring config
 * @soc: Common DP soc handle
 *
 * Return: QDF_STATUS
 */
static QDF_STATUS
dp_rxdma_ring_sel_cfg_be(struct dp_soc *soc)
{
	int i;
	int mac_id;
	struct htt_rx_ring_tlv_filter htt_tlv_filter = {0};
	struct dp_srng *rx_mac_srng;
	QDF_STATUS status = QDF_STATUS_SUCCESS;

	/*
	 * In Beryllium chipset msdu_start, mpdu_end
	 * and rx_attn are part of msdu_end/mpdu_start
	 */
	htt_tlv_filter.msdu_start = 0;
	htt_tlv_filter.mpdu_end = 0;
	htt_tlv_filter.attention = 0;
	htt_tlv_filter.mpdu_start = 1;
	htt_tlv_filter.msdu_end = 1;
	htt_tlv_filter.packet = 1;
	htt_tlv_filter.packet_header = 1;

	htt_tlv_filter.ppdu_start = 0;
	htt_tlv_filter.ppdu_end = 0;
	htt_tlv_filter.ppdu_end_user_stats = 0;
	htt_tlv_filter.ppdu_end_user_stats_ext = 0;
	htt_tlv_filter.ppdu_end_status_done = 0;
	htt_tlv_filter.enable_fp = 1;
	htt_tlv_filter.enable_md = 0;
	htt_tlv_filter.enable_md = 0;
	htt_tlv_filter.enable_mo = 0;

	htt_tlv_filter.fp_mgmt_filter = 0;
	htt_tlv_filter.fp_ctrl_filter = FILTER_CTRL_BA_REQ;
	htt_tlv_filter.fp_data_filter = (FILTER_DATA_UCAST |
					 FILTER_DATA_MCAST |
					 FILTER_DATA_DATA);
	htt_tlv_filter.mo_mgmt_filter = 0;
	htt_tlv_filter.mo_ctrl_filter = 0;
	htt_tlv_filter.mo_data_filter = 0;
	htt_tlv_filter.md_data_filter = 0;

	htt_tlv_filter.offset_valid = true;

	/* Not subscribing to mpdu_end, msdu_start and rx_attn */
	htt_tlv_filter.rx_mpdu_end_offset = 0;
	htt_tlv_filter.rx_msdu_start_offset = 0;
	htt_tlv_filter.rx_attn_offset = 0;

	htt_tlv_filter.rx_packet_offset = soc->rx_pkt_tlv_size;
	htt_tlv_filter.rx_header_offset =
				hal_rx_pkt_tlv_offset_get(soc->hal_soc);
	htt_tlv_filter.rx_mpdu_start_offset =
				hal_rx_mpdu_start_offset_get(soc->hal_soc);
	htt_tlv_filter.rx_msdu_end_offset =
				hal_rx_msdu_end_offset_get(soc->hal_soc);

	dp_info("TLV subscription\n"
		"msdu_start %d, mpdu_end %d, attention %d"
		"mpdu_start %d, msdu_end %d, pkt_hdr %d, pkt %d\n"
		"TLV offsets\n"
		"msdu_start %d, mpdu_end %d, attention %d"
		"mpdu_start %d, msdu_end %d, pkt_hdr %d, pkt %d\n",
		htt_tlv_filter.msdu_start,
		htt_tlv_filter.mpdu_end,
		htt_tlv_filter.attention,
		htt_tlv_filter.mpdu_start,
		htt_tlv_filter.msdu_end,
		htt_tlv_filter.packet_header,
		htt_tlv_filter.packet,
		htt_tlv_filter.rx_msdu_start_offset,
		htt_tlv_filter.rx_mpdu_end_offset,
		htt_tlv_filter.rx_attn_offset,
		htt_tlv_filter.rx_mpdu_start_offset,
		htt_tlv_filter.rx_msdu_end_offset,
		htt_tlv_filter.rx_header_offset,
		htt_tlv_filter.rx_packet_offset);

	for (i = 0; i < MAX_PDEV_CNT; i++) {
		struct dp_pdev *pdev = soc->pdev_list[i];

		if (!pdev)
			continue;

		for (mac_id = 0; mac_id < NUM_RXDMA_RINGS_PER_PDEV; mac_id++) {
			int mac_for_pdev =
				dp_get_mac_id_for_pdev(mac_id, pdev->pdev_id);
			/*
			 * Obtain lmac id from pdev to access the LMAC ring
			 * in soc context
			 */
			int lmac_id =
				dp_get_lmac_id_for_pdev_id(soc, mac_id,
							   pdev->pdev_id);

			rx_mac_srng = dp_get_rxdma_ring(pdev, lmac_id);
			htt_h2t_rx_ring_cfg(soc->htt_handle, mac_for_pdev,
					    rx_mac_srng->hal_srng,
					    RXDMA_BUF, RX_DATA_BUFFER_SIZE,
					    &htt_tlv_filter);
		}
	}
	return status;

}

void dp_initialize_arch_ops_be(struct dp_arch_ops *arch_ops)
{
	arch_ops->tx_hw_enqueue = dp_tx_hw_enqueue_be;
	arch_ops->txrx_get_context_size = dp_get_context_size_be;
	arch_ops->dp_rx_process = dp_rx_process_be;

	arch_ops->txrx_soc_attach = dp_soc_attach_be;
	arch_ops->txrx_soc_detach = dp_soc_detach_be;
	arch_ops->txrx_pdev_attach = dp_pdev_attach_be;
	arch_ops->txrx_pdev_detach = dp_pdev_detach_be;
	arch_ops->txrx_vdev_attach = dp_vdev_attach_be;
	arch_ops->txrx_vdev_detach = dp_vdev_detach_be;
	arch_ops->tx_comp_get_params_from_hal_desc =
		dp_tx_comp_get_params_from_hal_desc_be;
	arch_ops->dp_rxdma_ring_sel_cfg = dp_rxdma_ring_sel_cfg_be;

}
