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
 * DOC: public API related to the pmo called by north bound HDD/OSIF
 */

#include "wlan_pmo_ucfg_api.h"
#include "wlan_pmo_arp.h"
#include "wlan_pmo_ns.h"
#include "wlan_pmo_gtk.h"
#include "wlan_pmo_wow.h"
#include "wlan_pmo_mc_addr_filtering.h"
#include "wlan_pmo_main.h"
#include "wlan_pmo_lphb.h"
#include "wlan_pmo_suspend_resume.h"

QDF_STATUS pmo_ucfg_get_psoc_config(struct wlan_objmgr_psoc *psoc,
		struct pmo_psoc_cfg *psoc_cfg)
{
	return pmo_core_get_psoc_config(psoc, psoc_cfg);
}

QDF_STATUS pmo_ucfg_update_psoc_config(struct wlan_objmgr_psoc *psoc,
		struct pmo_psoc_cfg *psoc_cfg)
{
	return pmo_core_update_psoc_config(psoc, psoc_cfg);
}

bool pmo_ucfg_is_ap_mode_supports_arp_ns(struct wlan_objmgr_psoc *psoc,
	enum tQDF_ADAPTER_MODE vdev_opmode)
{
	return pmo_core_is_ap_mode_supports_arp_ns(psoc, vdev_opmode);
}

bool pmo_ucfg_is_vdev_connected(struct wlan_objmgr_vdev *vdev)
{
	return pmo_core_is_vdev_connected(vdev);
}

bool pmo_ucfg_is_vdev_supports_offload(struct wlan_objmgr_vdev *vdev)
{
	return pmo_core_is_vdev_supports_offload(vdev);
}

void pmo_ucfg_enable_wakeup_event(struct wlan_objmgr_psoc *psoc,
	uint32_t vdev_id, uint32_t bitmap)
{
	pmo_core_enable_wakeup_event(psoc, vdev_id, bitmap);
}

void pmo_ucfg_disable_wakeup_event(struct wlan_objmgr_psoc *psoc,
	uint32_t vdev_id, uint32_t bitmap)
{
	pmo_core_disable_wakeup_event(psoc, vdev_id, bitmap);
}

QDF_STATUS pmo_ucfg_cache_arp_offload_req(struct pmo_arp_req *arp_req)
{
	return pmo_core_cache_arp_offload_req(arp_req);
}

QDF_STATUS pmo_ucfg_flush_arp_offload_req(struct wlan_objmgr_vdev *vdev)
{
	return pmo_core_flush_arp_offload_req(vdev);
}

QDF_STATUS pmo_ucfg_enable_arp_offload_in_fwr(struct wlan_objmgr_vdev *vdev,
		enum pmo_offload_trigger trigger)
{
	return pmo_core_enable_arp_offload_in_fwr(vdev, trigger);
}

QDF_STATUS pmo_ucfg_disable_arp_offload_in_fwr(struct wlan_objmgr_vdev *vdev,
		enum pmo_offload_trigger trigger)
{
	return pmo_core_disable_arp_offload_in_fwr(vdev, trigger);
}

QDF_STATUS pmo_ucfg_cache_ns_offload_req(struct pmo_ns_req *ns_req)
{
	return pmo_core_cache_ns_offload_req(ns_req);
}

QDF_STATUS pmo_ucfg_flush_ns_offload_req(struct wlan_objmgr_vdev *vdev)
{
	return pmo_core_flush_ns_offload_req(vdev);
}

QDF_STATUS pmo_ucfg_enable_ns_offload_in_fwr(struct wlan_objmgr_vdev *vdev,
		enum pmo_offload_trigger trigger)
{
	return pmo_core_enable_ns_offload_in_fwr(vdev, trigger);
}

QDF_STATUS pmo_ucfg_disable_ns_offload_in_fwr(struct wlan_objmgr_vdev *vdev,
		enum pmo_offload_trigger trigger)
{
	return pmo_core_disable_ns_offload_in_fwr(vdev, trigger);
}

QDF_STATUS pmo_ucfg_cache_mc_addr_list(
		struct pmo_mc_addr_list_params *mc_list_config)
{
	return pmo_core_cache_mc_addr_list(mc_list_config);
}

QDF_STATUS pmo_ucfg_flush_mc_addr_list(struct wlan_objmgr_psoc *psoc,
	uint8_t vdev_id)
{
	return pmo_core_flush_mc_addr_list(psoc, vdev_id);
}

QDF_STATUS pmo_ucfg_enable_mc_addr_filtering_in_fwr(
		struct wlan_objmgr_psoc *psoc,
		uint8_t vdev_id,
		enum pmo_offload_trigger trigger)
{
	return pmo_core_enable_mc_addr_filtering_in_fwr(psoc,
			vdev_id, trigger);
}

QDF_STATUS pmo_ucfg_disable_mc_addr_filtering_in_fwr(
		struct wlan_objmgr_psoc *psoc,
		uint8_t vdev_id,
		enum pmo_offload_trigger trigger)
{
	return pmo_core_disable_mc_addr_filtering_in_fwr(psoc,
			vdev_id, trigger);
}

uint8_t pmo_ucfg_max_mc_addr_supported(struct wlan_objmgr_psoc *psoc)
{
	return pmo_core_max_mc_addr_supported(psoc);
}

QDF_STATUS pmo_ucfg_cache_gtk_offload_req(struct wlan_objmgr_vdev *vdev,
		struct pmo_gtk_req *gtk_req)
{
	return pmo_core_cache_gtk_offload_req(vdev, gtk_req);
}

QDF_STATUS pmo_ucfg_flush_gtk_offload_req(struct wlan_objmgr_vdev *vdev)
{
	return pmo_core_flush_gtk_offload_req(vdev);
}

QDF_STATUS pmo_ucfg_enable_gtk_offload_in_fwr(struct wlan_objmgr_vdev *vdev)
{
	return pmo_core_enable_gtk_offload_in_fwr(vdev);
}

QDF_STATUS pmo_ucfg_disable_gtk_offload_in_fwr(struct wlan_objmgr_vdev *vdev)
{
	return pmo_core_disable_gtk_offload_in_fwr(vdev);
}

QDF_STATUS pmo_ucfg_get_gtk_rsp(struct wlan_objmgr_vdev *vdev,
		struct pmo_gtk_rsp_req *gtk_rsp_req)
{
	return pmo_core_get_gtk_rsp(vdev, gtk_rsp_req);
}

void pmo_ucfg_update_nlo_scan_in_progress(struct wlan_objmgr_vdev *vdev,
	bool value)
{
	pmo_core_update_nlo_scan_in_progress(vdev, value);
}

void pmo_ucfg_update_nlo_match_found(struct wlan_objmgr_vdev *vdev,
	bool value)
{
	pmo_core_update_nlo_match_found(vdev, value);
}

void pmo_ucfg_update_extscan_in_progress(struct wlan_objmgr_vdev *vdev,
	bool value)
{
	pmo_core_update_extscan_in_progress(vdev, value);
}

void pmo_ucfg_update_p2plo_in_progress(struct wlan_objmgr_vdev *vdev,
	bool value)
{
	pmo_core_update_p2plo_in_progress(vdev, value);
}

QDF_STATUS pmo_ucfg_lphb_config_req(struct wlan_objmgr_psoc *psoc,
		struct pmo_lphb_req *lphb_req, void *lphb_cb_ctx,
		pmo_lphb_callback callback)
{
	return pmo_core_lphb_config_req(psoc, lphb_req, lphb_cb_ctx, callback);
}

void pmo_ucfg_update_alt_modulated_dtim_enable(struct wlan_objmgr_vdev *vdev,
	bool value)
{
	pmo_core_update_alt_modulated_dtim_enable(vdev, value);
}

void pmo_ucfg_psoc_update_power_save_mode(struct wlan_objmgr_psoc *psoc,
	uint8_t value)
{
	pmo_core_psoc_update_power_save_mode(psoc, value);
}

void pmo_ucfg_psoc_update_dp_handle(struct wlan_objmgr_psoc *psoc,
		void *dp_handle)
{
	pmo_core_psoc_update_dp_handle(psoc, dp_handle);
}

void pmo_ucfg_vdev_update_dp_handle(struct wlan_objmgr_vdev *vdev,
		void *dp_handle)
{
	pmo_core_vdev_update_dp_handle(vdev, dp_handle);
}

void pmo_ucfg_psoc_update_htc_handle(struct wlan_objmgr_psoc *psoc,
		void *htc_handle)
{
	pmo_core_psoc_update_htc_handle(psoc, htc_handle);
}

void pmo_ucfg_psoc_handle_initial_wake_up(void *cb_ctx)
{
	return pmo_core_psoc_handle_initial_wake_up(cb_ctx);
}

QDF_STATUS pmo_ucfg_psoc_user_space_suspend_req(struct wlan_objmgr_psoc *psoc,
		enum qdf_suspend_type type)
{
	return pmo_core_psoc_user_space_suspend_req(psoc, type);
}


QDF_STATUS pmo_ucfg_psoc_user_space_resume_req(struct wlan_objmgr_psoc *psoc,
		enum qdf_suspend_type type)
{
	return pmo_core_psoc_user_space_resume_req(psoc, type);
}

QDF_STATUS pmo_ucfg_psoc_bus_suspend_req(struct wlan_objmgr_psoc *psoc,
		enum qdf_suspend_type type,
		struct pmo_wow_enable_params *wow_params)
{
	return pmo_core_psoc_bus_suspend_req(psoc, type, wow_params);
}

QDF_STATUS pmo_ucfg_psoc_suspend_target(struct wlan_objmgr_psoc *psoc,
		int disable_target_intr)
{
	return pmo_core_psoc_suspend_target(psoc, disable_target_intr);
}

QDF_STATUS pmo_ucfg_psoc_bus_resume_req(struct wlan_objmgr_psoc *psoc,
		enum qdf_suspend_type type)
{
	return pmo_core_psoc_bus_resume_req(psoc, type);
}

bool pmo_ucfg_get_wow_bus_suspend(struct wlan_objmgr_psoc *psoc)
{
	return pmo_core_get_wow_bus_suspend(psoc);
}

int pmo_ucfg_psoc_is_target_wake_up_received(struct wlan_objmgr_psoc *psoc)
{
	return pmo_core_psoc_is_target_wake_up_received(psoc);
}

int pmo_ucfg_psoc_clear_target_wake_up(struct wlan_objmgr_psoc *psoc)
{
	return pmo_core_psoc_clear_target_wake_up(psoc);
}

void pmo_ucfg_psoc_target_suspend_acknowledge(void *context, bool wow_nack)
{
	pmo_core_psoc_target_suspend_acknowledge(context, wow_nack);
}

void pmo_ucfg_psoc_wakeup_host_event_received(struct wlan_objmgr_psoc *psoc)
{
	pmo_core_psoc_wakeup_host_event_received(psoc);
}

