/*
 * Copyright (c) 2017 The Linux Foundation. All rights reserved.
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
 * DOC: Contains mandatory API from legacy
 */

#ifndef _WLAN_UTILITY_H_
#define _WLAN_UTILITY_H_

#include <qdf_types.h>
#include <wlan_objmgr_psoc_obj.h>
#include <wlan_objmgr_pdev_obj.h>
#include <wlan_objmgr_vdev_obj.h>

/**
 * struct wlan_find_vdev_filter - find vdev filter object. this can be extended
 * @ifname:           interface name of vdev
 * @found_vdev:       found vdev object matching one or more of above params
 */
struct wlan_find_vdev_filter {
	char *ifname;
	struct wlan_objmgr_vdev *found_vdev;
};

/**
 * wlan_chan_to_freq() - converts channel to frequency
 * @chan: channel number
 *
 * @return frequency of the channel
 */
uint32_t wlan_chan_to_freq(uint8_t chan);

/*
 * wlan_is_dsrc_channel() - is the channel DSRC
 * @center_freq: center freq of the channel
 *
 * Return: true if DSRC channel or false otherwise
 */
bool wlan_is_dsrc_channel(uint16_t center_freq);

/**
 * wlan_freq_to_chan() - converts frequency to channel
 * @freq: frequency
 *
 * Return: channel of frequency
 */
uint8_t wlan_freq_to_chan(uint32_t freq);

/**
 * wlan_get_ie_ptr_from_eid() - Find out ie from eid
 * @eid: element id
 * @ie: source ie address
 * @ie_len: source ie length
 *
 * Return: vendor ie address - success
 *         NULL - failure
 */
const uint8_t *wlan_get_ie_ptr_from_eid(uint8_t eid,
					const uint8_t *ie,
					int ie_len);

/**
 * wlan_get_vendor_ie_ptr_from_oui() - Find out vendor ie
 * @oui: oui buffer
 * @oui_size: oui size
 * @ie: source ie address
 * @ie_len: source ie length
 *
 * This function find out vendor ie by pass source ie and vendor oui.
 *
 * Return: vendor ie address - success
 *         NULL - failure
 */
const uint8_t *wlan_get_vendor_ie_ptr_from_oui(const uint8_t *oui,
					       uint8_t oui_size,
					       const uint8_t *ie,
					       uint16_t ie_len);

/**
 * wlan_get_ext_ie_ptr_from_ext_id() - Find out ext ie
 * @oui: oui buffer
 * @oui_size: oui size
 * @ie: source ie address
 * @ie_len: source ie length
 *
 * This function find out ext ie from ext id (passed oui)
 *
 * Return: vendor ie address - success
 *         NULL - failure
 */
const uint8_t *wlan_get_ext_ie_ptr_from_ext_id(const uint8_t *oui,
					       uint8_t oui_size,
					       const uint8_t *ie,
					       uint16_t ie_len);

/**
 * wlan_is_emulation_platform() - check if platform is emulation based
 * @phy_version - psoc nif phy_version
 *
 * Return: boolean value based on platform type
 */
bool wlan_is_emulation_platform(uint32_t phy_version);

/**
 * wlan_get_pdev_id_from_vdev_id() - Helper func to derive pdev id from vdev_id
 * @psoc    : psoc object
 * @vdev_id : vdev identifier
 * @dbg_id  : object manager debug id
 *
 * This function is used to derive the pdev id from vdev id for a psoc
 *
 * Return : pdev_id - +ve integer for success and WLAN_INVALID_PDEV_ID
 *          for failure
 */
uint32_t wlan_get_pdev_id_from_vdev_id(struct wlan_objmgr_psoc *psoc,
				 uint8_t vdev_id,
				 wlan_objmgr_ref_dbgid dbg_id);

/**
 * wlan_util_get_vdev_by_ifname() - function to return vdev object from psoc
 * matching given interface name
 * @psoc    : psoc object
 * @ifname  : interface name
 * @ref_id  : object manager ref id
 *
 * This function returns vdev object from psoc by interface name. If found this
 * will also take reference with given ref_id
 *
 * Return : vdev object if found, NULL otherwise
 */
struct wlan_objmgr_vdev *wlan_util_get_vdev_by_ifname(
				struct wlan_objmgr_psoc *psoc, char *ifname,
				wlan_objmgr_ref_dbgid ref_id);

#endif /* _WLAN_UTILITY_H_ */
