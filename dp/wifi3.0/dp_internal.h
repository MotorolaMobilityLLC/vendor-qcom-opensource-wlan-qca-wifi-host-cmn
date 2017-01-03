/*
 * Copyright (c) 2016-2017 The Linux Foundation. All rights reserved.
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

#ifndef _DP_INTERNAL_H_
#define _DP_INTERNAL_H_

#if DP_PRINT_ENABLE
#include <stdarg.h>       /* va_list */
#include <qdf_types.h> /* qdf_vprint */
#include <cdp_txrx_handle.h>

enum {
	/* FATAL_ERR - print only irrecoverable error messages */
	DP_PRINT_LEVEL_FATAL_ERR,

	/* ERR - include non-fatal err messages */
	DP_PRINT_LEVEL_ERR,

	/* WARN - include warnings */
	DP_PRINT_LEVEL_WARN,

	/* INFO1 - include fundamental, infrequent events */
	DP_PRINT_LEVEL_INFO1,

	/* INFO2 - include non-fundamental but infrequent events */
	DP_PRINT_LEVEL_INFO2,
};


#define dp_print(level, fmt, ...) do { \
	if (level <= g_txrx_print_level) \
		qdf_print(fmt, ## __VA_ARGS__); \
while (0)
#define DP_PRINT(level, fmt, ...) do { \
	dp_print(level, "DP: " fmt, ## __VA_ARGS__); \
while (0)
#else
#define DP_PRINT(level, fmt, ...)
#endif /* DP_PRINT_ENABLE */

#define DP_TRACE(LVL, fmt, args ...)                             \
	QDF_TRACE(QDF_MODULE_ID_DP, QDF_TRACE_LEVEL_##LVL,       \
		"%s:%d: "fmt, __func__, __LINE__, ## args)

#define DP_STATS_INIT(_handle) \
	qdf_mem_set(&((_handle)->stats), sizeof((_handle)->stats), 0x0)

#define DP_STATS_CLR(_handle) \
	qdf_mem_set(&((_handle)->stats), sizeof((_handle)->stats), 0x0)

#ifndef DISABLE_DP_STATS
#define DP_STATS_INC(_handle, _field, _delta) \
{ \
	_handle->stats._field += _delta; \
}

#define DP_STATS_INCC(_handle, _field, _delta, _cond) \
{ \
	if (_cond) { \
		_handle->stats._field += _delta; \
	} \
}

#define DP_STATS_DEC(_handle, _field, _delta) \
{ \
	_handle->stats._field -= _delta; \
}

#define DP_STATS_UPD(_handle, _field, _delta) \
{ \
	_handle->stats._field = _delta \
}

#define DP_STATS_INC_PKT(_handle, _field, _count, _bytes) \
{ \
	DP_STATS_INC(_handle, _field.num, _count); \
	DP_STATS_INC(_handle, _field.bytes, _bytes) \
}
#else
#define DP_STATS_INC(_handle, _field, _delta)
#define DP_STATS_INCC(_handle, _field, _delta, _cond)
#define DP_STATS_DEC(_handle, _field, _delta)
#define DP_STATS_UPD(_handle, _field, _delta)
#define DP_STATS_INC_PKT(_handle, _field, _count, _bytes)
#endif

extern int dp_peer_find_attach(struct dp_soc *soc);
extern void dp_peer_find_detach(struct dp_soc *soc);
extern void dp_peer_find_hash_add(struct dp_soc *soc, struct dp_peer *peer);
extern void dp_peer_find_hash_remove(struct dp_soc *soc, struct dp_peer *peer);
extern void dp_peer_find_hash_erase(struct dp_soc *soc);
extern void dp_peer_rx_init(struct dp_pdev *pdev, struct dp_peer *peer);
extern void dp_peer_cleanup(struct dp_vdev *vdev, struct dp_peer *peer);
extern void dp_peer_rx_cleanup(struct dp_vdev *vdev, struct dp_peer *peer);
extern void dp_peer_unref_delete(void *peer_handle);
extern void dp_rx_discard(struct dp_vdev *vdev, struct dp_peer *peer,
	unsigned tid, qdf_nbuf_t msdu_list);
extern void *dp_find_peer_by_addr(struct cdp_pdev *dev,
	uint8_t *peer_mac_addr, uint8_t *peer_id);
#ifndef CONFIG_WIN
QDF_STATUS dp_register_peer(struct cdp_pdev *pdev_handle,
		struct ol_txrx_desc_type *sta_desc);
QDF_STATUS dp_clear_peer(struct cdp_pdev *pdev_handle, uint8_t local_id);
void *dp_find_peer_by_addr_and_vdev(struct cdp_pdev *pdev_handle,
		struct cdp_vdev *vdev,
		uint8_t *peer_addr, uint8_t *local_id);
uint16_t dp_local_peer_id(void *peer);
void *dp_peer_find_by_local_id(struct cdp_pdev *pdev_handle, uint8_t local_id);
QDF_STATUS dp_peer_state_update(struct cdp_pdev *pdev_handle, uint8_t *peer_mac,
		enum ol_txrx_peer_state state);
QDF_STATUS dp_get_vdevid(void *peer_handle, uint8_t *vdev_id);
struct cdp_vdev *dp_get_vdev_for_peer(void *peer);
uint8_t *dp_peer_get_peer_mac_addr(void *peer);
int dp_get_peer_state(void *peer_handle);
void dp_local_peer_id_pool_init(struct dp_pdev *pdev);
void dp_local_peer_id_alloc(struct dp_pdev *pdev, struct dp_peer *peer);
void dp_local_peer_id_free(struct dp_pdev *pdev, struct dp_peer *peer);
qdf_time_t *dp_get_last_assoc_received(void *peer_handle);
qdf_time_t *dp_get_last_disassoc_received(void *peer_handle);
qdf_time_t *dp_get_last_deauth_received(void *peer_handle);
#endif
extern int dp_addba_requestprocess_wifi3(void *peer_handle,
	uint8_t dialogtoken, uint16_t tid, uint16_t batimeout,
	uint16_t buffersize, uint16_t startseqnum);
extern void dp_addba_responsesetup_wifi3(void *peer_handle, uint8_t tid,
	uint8_t *dialogtoken, uint16_t *statuscode,
	uint16_t *buffersize, uint16_t *batimeout);
extern int dp_delba_process_wifi3(void *peer_handle,
	int tid, uint16_t reasoncode);

extern int dp_rx_tid_setup_wifi3(struct dp_peer *peer, int tid,
	uint32_t ba_window_size, uint32_t start_seq);

extern QDF_STATUS dp_reo_send_cmd(struct dp_soc *soc,
	enum hal_reo_cmd_type type, struct hal_reo_cmd_params *params,
	void (*callback_fn), void *data);

extern void dp_reo_status_ring_handler(struct dp_soc *soc);
int dp_print_host_stats(struct cdp_vdev *vdev_handle,
		struct ol_txrx_stats_req *req, enum cdp_host_txrx_stats type);
void dp_print_pdev_tx_stats(struct dp_pdev *pdev);
void dp_print_pdev_rx_stats(struct dp_pdev *pdev);
void dp_print_soc_tx_stats(struct dp_soc *soc);
void dp_print_soc_rx_stats(struct dp_soc *soc);
void dp_txrx_host_stats_clr(struct dp_vdev *vdev);
void dp_print_rx_rates(struct dp_vdev *vdev);
void dp_print_tx_rates(struct dp_vdev *vdev);
#endif /* #ifndef _DP_INTERNAL_H_ */
