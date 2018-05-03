/*
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
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

/**
 * DOC: wlan_cfg80211_ic_cp_stats.c
 *
 * This file provide definitions to cp stats supported cfg80211 cmd handlers
 */
#include <wlan_cfg80211_ic_cp_stats.h>
#include <wlan_cp_stats_ic_ucfg_api.h>
#include <wlan_cfg80211.h>
#include <qdf_util.h>

int wlan_cfg80211_get_peer_cp_stats(struct wlan_objmgr_peer *peer_obj,
				    struct peer_ic_cp_stats *peer_cp_stats)
{
	QDF_STATUS status;

	if (!peer_obj) {
		cfg80211_err("Invalid input, peer obj NULL");
		return -EINVAL;
	}

	if (!peer_cp_stats) {
		cfg80211_err("Invalid input, peer cp obj is NULL");
		return -EINVAL;
	}

	status = wlan_ucfg_get_peer_cp_stats(peer_obj, peer_cp_stats);
	if (QDF_IS_STATUS_ERROR(status)) {
		cfg80211_err("wlan_cfg80211_get_peer_cp_stats status: %d",
			     status);
	}

	return qdf_status_to_os_return(status);
}
