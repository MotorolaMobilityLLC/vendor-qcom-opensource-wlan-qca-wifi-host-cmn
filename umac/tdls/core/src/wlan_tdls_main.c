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
 * DOC: wlan_tdls_main.c
 *
 * TDLS core function definitions
 */

#include "wlan_tdls_main.h"
#include "wlan_tdls_cmds_process.h"
#include "wlan_tdls_peer.h"
#include "wlan_tdls_ct.h"
#include "wlan_tdls_mgmt.h"
#include "wlan_tdls_tgt_api.h"
#include "wlan_policy_mgr_public_struct.h"
#include "wlan_policy_mgr_api.h"


QDF_STATUS tdls_psoc_obj_create_notification(struct wlan_objmgr_psoc *psoc,
					     void *arg_list)
{
	QDF_STATUS status;
	struct tdls_soc_priv_obj *tdls_soc_obj;

	tdls_soc_obj = qdf_mem_malloc(sizeof(*tdls_soc_obj));
	if (!tdls_soc_obj) {
		tdls_err("Failed to allocate memory for tdls object");
		return QDF_STATUS_E_NOMEM;
	}

	tdls_soc_obj->soc = psoc;

	status = wlan_objmgr_psoc_component_obj_attach(psoc,
						       WLAN_UMAC_COMP_TDLS,
						       (void *)tdls_soc_obj,
						       QDF_STATUS_SUCCESS);

	if (QDF_IS_STATUS_ERROR(status)) {
		tdls_err("Failed to attach psoc tdls component");
		qdf_mem_free(tdls_soc_obj);
	}

	tdls_notice("TDLS obj attach to psoc successfully");

	return status;
}

QDF_STATUS tdls_psoc_obj_destroy_notification(struct wlan_objmgr_psoc *psoc,
					      void *arg_list)
{
	QDF_STATUS status;
	struct tdls_soc_priv_obj *tdls_soc_obj;

	tdls_soc_obj = wlan_objmgr_psoc_get_comp_private_obj(psoc,
						WLAN_UMAC_COMP_TDLS);
	if (!tdls_soc_obj) {
		tdls_err("Failed to get tdls obj in psoc");
		return QDF_STATUS_E_FAILURE;
	}

	status = wlan_objmgr_psoc_component_obj_detach(psoc,
						       WLAN_UMAC_COMP_TDLS,
						       tdls_soc_obj);

	if (QDF_IS_STATUS_ERROR(status))
		tdls_err("Failed to detach psoc tdls component");

	qdf_mem_free(tdls_soc_obj);

	return status;
}

static QDF_STATUS tdls_vdev_init(struct tdls_vdev_priv_obj *vdev_obj)
{
	uint8_t i;
	struct tdls_config_params *config;
	struct tdls_user_config *user_config;
	struct tdls_soc_priv_obj *soc_obj;

	soc_obj = wlan_vdev_get_tdls_soc_obj(vdev_obj->vdev);
	if (!soc_obj) {
		tdls_err("tdls soc obj NULL");
		return QDF_STATUS_E_FAILURE;
	}

	config = &vdev_obj->threshold_config;
	user_config = &soc_obj->tdls_configs;
	config->tx_period_t = user_config->tdls_tx_states_period;
	config->tx_packet_n = user_config->tdls_tx_pkt_threshold;
	config->discovery_tries_n = user_config->tdls_max_discovery_attempt;
	config->idle_timeout_t = user_config->tdls_idle_timeout;
	config->idle_packet_n = user_config->tdls_idle_pkt_threshold;
	config->rssi_trigger_threshold =
		user_config->tdls_rssi_trigger_threshold;
	config->rssi_teardown_threshold =
		user_config->tdls_rssi_teardown_threshold;
	config->rssi_delta = user_config->tdls_rssi_delta;

	for (i = 0; i < WLAN_TDLS_PEER_LIST_SIZE; i++) {
		qdf_list_create(&vdev_obj->peer_list[i],
				WLAN_TDLS_PEER_SUB_LIST_SIZE);
	}
	qdf_mc_timer_init(&vdev_obj->peer_update_timer, QDF_TIMER_TYPE_SW,
			  tdls_ct_handler, vdev_obj->vdev);
	qdf_mc_timer_init(&vdev_obj->peer_discovery_timer, QDF_TIMER_TYPE_SW,
			  tdls_discovery_timeout_peer_cb, vdev_obj);

	return QDF_STATUS_SUCCESS;
}

static void tdls_vdev_deinit(struct tdls_vdev_priv_obj *vdev_obj)
{
	qdf_mc_timer_stop(&vdev_obj->peer_update_timer);
	qdf_mc_timer_stop(&vdev_obj->peer_discovery_timer);

	qdf_mc_timer_destroy(&vdev_obj->peer_update_timer);
	qdf_mc_timer_destroy(&vdev_obj->peer_discovery_timer);

	tdls_peer_idle_timers_destroy(vdev_obj);
	tdls_free_peer_list(vdev_obj);
}

QDF_STATUS tdls_vdev_obj_create_notification(struct wlan_objmgr_vdev *vdev,
					     void *arg)
{
	QDF_STATUS status;
	struct tdls_vdev_priv_obj *tdls_vdev_obj;

	tdls_notice("tdls vdev mode %d", wlan_vdev_mlme_get_opmode(vdev));
	if (wlan_vdev_mlme_get_opmode(vdev) != QDF_STA_MODE &&
	    wlan_vdev_mlme_get_opmode(vdev) != QDF_P2P_CLIENT_MODE)
		return QDF_STATUS_SUCCESS;

	/* TODO: Add concurrency check */

	tdls_vdev_obj = qdf_mem_malloc(sizeof(*tdls_vdev_obj));
	if (!tdls_vdev_obj) {
		tdls_err("Failed to allocate memory for tdls vdev object");
		return QDF_STATUS_E_NOMEM;
	}

	status = wlan_objmgr_vdev_component_obj_attach(vdev,
						       WLAN_UMAC_COMP_TDLS,
						       (void *)tdls_vdev_obj,
						       QDF_STATUS_SUCCESS);
	if (QDF_IS_STATUS_ERROR(status)) {
		tdls_err("Failed to attach vdev tdls component");
		qdf_mem_free(tdls_vdev_obj);
		goto out;
	}
	tdls_vdev_obj->vdev = vdev;
	status = tdls_vdev_init(tdls_vdev_obj);
	if (QDF_IS_STATUS_ERROR(status))
		goto out;

	tdls_notice("tdls object attach to vdev successfully");
out:
	return status;
}

QDF_STATUS tdls_vdev_obj_destroy_notification(struct wlan_objmgr_vdev *vdev,
					      void *arg)
{
	QDF_STATUS status;
	void *tdls_vdev_obj;

	tdls_notice("tdls vdev mode %d", wlan_vdev_mlme_get_opmode(vdev));
	if (wlan_vdev_mlme_get_opmode(vdev) != QDF_STA_MODE &&
	    wlan_vdev_mlme_get_opmode(vdev) != QDF_P2P_CLIENT_MODE)
		return QDF_STATUS_SUCCESS;

	tdls_vdev_obj = wlan_objmgr_vdev_get_comp_private_obj(vdev,
							WLAN_UMAC_COMP_TDLS);
	if (!tdls_vdev_obj) {
		tdls_err("Failed to get tdls vdev object");
		return QDF_STATUS_E_FAILURE;
	}

	status = wlan_objmgr_vdev_component_obj_detach(vdev,
						       WLAN_UMAC_COMP_TDLS,
						       tdls_vdev_obj);
	if (QDF_IS_STATUS_ERROR(status))
		tdls_err("Failed to detach vdev tdls component");

	tdls_vdev_deinit(tdls_vdev_obj);
	qdf_mem_free(tdls_vdev_obj);

	return status;
}

QDF_STATUS tdls_process_cmd(struct scheduler_msg *msg)
{
	QDF_STATUS status = QDF_STATUS_SUCCESS;

	if (!msg || !msg->bodyptr) {
		tdls_err("msg: 0x%p", msg);
		QDF_ASSERT(0);
		return QDF_STATUS_E_NULL_VALUE;
	}
	tdls_debug("TDLS process command: %d", msg->type);

	switch (msg->type) {
	case TDLS_CMD_TX_ACTION:
		tdls_process_mgmt_req(msg->bodyptr);
		break;
	case TDLS_CMD_ADD_STA:
		tdls_process_add_peer(msg->bodyptr);
		break;
	case TDLS_CMD_CHANGE_STA:
		tdls_process_update_peer(msg->bodyptr);
		break;
	case TDLS_CMD_ENABLE_LINK:
		tdls_process_enable_link(msg->bodyptr);
		break;
	case TDLS_CMD_DISABLE_LINK:
		tdls_process_del_peer(msg->bodyptr);
		break;
	case TDLS_CMD_CONFIG_FORCE_PEER:
		tdls_process_setup_peer(msg->bodyptr);
		break;
	case TDLS_CMD_REMOVE_FORCE_PEER:
		tdls_process_remove_force_peer(msg->bodyptr);
		break;
	case TDLS_CMD_STATS_UPDATE:
		break;
	case TDLS_CMD_CONFIG_UPDATE:
		break;
	case TDLS_CMD_SET_RESPONDER:
		tdls_set_responder(msg->bodyptr);
		break;
	case TDLS_NOTIFY_STA_CONNECTION:
		tdls_notify_sta_connect(msg->bodyptr);
		break;
	case TDLS_NOTIFY_STA_DISCONNECTION:
		tdls_notify_sta_disconnect(msg->bodyptr);
		break;
	case TDLS_CMD_SET_TDLS_MODE:
		tdls_set_operation_mode(msg->bodyptr);
		break;
	case TDLS_CMD_SESSION_INCREMENT:
	case TDLS_CMD_SESSION_DECREMENT:
		tdls_process_policy_mgr_notification(msg->bodyptr);
		break;

	default:
		break;
	}

	return status;
}

QDF_STATUS tdls_process_evt(struct scheduler_msg *msg)
{
	struct wlan_objmgr_vdev *vdev;
	struct tdls_event_notify *notify;
	struct tdls_event_info *event;

	if (!msg || !msg->bodyptr) {
		tdls_err("msg is not valid: %p", msg);
		return QDF_STATUS_E_NULL_VALUE;
	}
	notify = msg->bodyptr;
	vdev = notify->vdev;
	if (!vdev) {
		tdls_err("NULL vdev object");
		qdf_mem_free(notify);
		return QDF_STATUS_E_NULL_VALUE;
	}
	event = &notify->event;

	tdls_debug("evt type: %d", event->message_type);
	switch (event->message_type) {
	case TDLS_SHOULD_DISCOVER:
		tdls_process_should_discover(vdev, event);
		break;
	case TDLS_SHOULD_TEARDOWN:
	case TDLS_PEER_DISCONNECTED:
		tdls_process_should_teardown(vdev, event);
		break;
	case TDLS_CONNECTION_TRACKER_NOTIFY:
		tdls_process_connection_tracker_notify(vdev, event);
		break;
	default:
		break;
	}

	wlan_objmgr_vdev_release_ref(vdev, WLAN_TDLS_SB_ID);
	qdf_mem_free(notify);

	return QDF_STATUS_SUCCESS;
}

void tdls_timer_restart(struct wlan_objmgr_vdev *vdev,
				 qdf_mc_timer_t *timer,
				 uint32_t expiration_time)
{
	qdf_mc_timer_stop(timer);
	qdf_mc_timer_start(timer, expiration_time);
}

/**
 * wlan_hdd_tdls_monitor_timers_stop() - stop all monitoring timers
 * @hdd_tdls_ctx: TDLS context
 *
 * Return: none
 */
static void tdls_monitor_timers_stop(struct tdls_vdev_priv_obj *tdls_vdev)
{
	qdf_mc_timer_stop(&tdls_vdev->peer_discovery_timer);
}

/**
 * tdls_peer_idle_timers_stop() - stop peer idle timers
 * @tdls_vdev: TDLS vdev object
 *
 * Loop through the idle peer list and stop their timers
 *
 * Return: None
 */
static void tdls_peer_idle_timers_stop(struct tdls_vdev_priv_obj *tdls_vdev)
{
	int i;
	qdf_list_t *head;
	qdf_list_node_t *p_node;
	struct tdls_peer *curr_peer;
	QDF_STATUS status;

	tdls_vdev->discovery_peer_cnt = 0;

	for (i = 0; i < WLAN_TDLS_PEER_LIST_SIZE; i++) {
		head = &tdls_vdev->peer_list[i];
		status = qdf_list_peek_front(head, &p_node);
		while (QDF_IS_STATUS_SUCCESS(status)) {
			curr_peer = qdf_container_of(p_node, struct tdls_peer,
						     node);
			if (curr_peer->is_peer_idle_timer_initialised)
				qdf_mc_timer_stop(&curr_peer->peer_idle_timer);
			status = qdf_list_peek_next(head, p_node, &p_node);
		}
	}

}

/**
 * wlan_hdd_tdls_ct_timers_stop() - stop tdls connection tracker timers
 * @tdls_vdev: TDLS vdev
 *
 * Return: None
 */
static void tdls_ct_timers_stop(struct tdls_vdev_priv_obj *tdls_vdev)
{
	qdf_mc_timer_stop(&tdls_vdev->peer_update_timer);
	tdls_peer_idle_timers_stop(tdls_vdev);
}

/**
 * wlan_hdd_tdls_timers_stop() - stop all the tdls timers running
 * @tdls_vdev: TDLS vdev
 *
 * Return: none
 */
void tdls_timers_stop(struct tdls_vdev_priv_obj *tdls_vdev)
{
	tdls_monitor_timers_stop(tdls_vdev);
	tdls_ct_timers_stop(tdls_vdev);
}

QDF_STATUS tdls_get_vdev_objects(struct wlan_objmgr_vdev *vdev,
				   struct tdls_vdev_priv_obj **tdls_vdev_obj,
				   struct tdls_soc_priv_obj **tdls_soc_obj)
{
	enum tQDF_ADAPTER_MODE device_mode;

	if (NULL == vdev)
		return QDF_STATUS_E_FAILURE;

	*tdls_vdev_obj = wlan_vdev_get_tdls_vdev_obj(vdev);
	if (NULL == (*tdls_vdev_obj))
		return QDF_STATUS_E_FAILURE;

	*tdls_soc_obj = wlan_vdev_get_tdls_soc_obj(vdev);
	if (NULL == (*tdls_soc_obj))
		return QDF_STATUS_E_FAILURE;

	wlan_vdev_obj_lock(vdev);
	device_mode = wlan_vdev_mlme_get_opmode(vdev);
	wlan_vdev_obj_unlock(vdev);

	if (device_mode != QDF_STA_MODE &&
	    device_mode != QDF_P2P_CLIENT_MODE)
		return QDF_STATUS_E_FAILURE;

	return QDF_STATUS_SUCCESS;
}

/**
 * tdls_state_param_setting_dump() - print tdls state & parameters to send to fw
 * @info: tdls setting to be sent to fw
 *
 * Return: void
 */
static void tdls_state_param_setting_dump(struct tdls_info *info)
{
	if (!info)
		return;

	tdls_debug("Setting tdls state and param in fw: vdev_id: %d, tdls_state: %d, notification_interval_ms: %d, tx_discovery_threshold: %d, tx_teardown_threshold: %d, rssi_teardown_threshold: %d, rssi_delta: %d, tdls_options: 0x%x, peer_traffic_ind_window: %d, peer_traffic_response_timeout: %d, puapsd_mask: 0x%x, puapsd_inactivity_time: %d, puapsd_rx_frame_threshold: %d, teardown_notification_ms: %d, tdls_peer_kickout_threshold: %d",
		   info->vdev_id,
		   info->tdls_state,
		   info->notification_interval_ms,
		   info->tx_discovery_threshold,
		   info->tx_teardown_threshold,
		   info->rssi_teardown_threshold,
		   info->rssi_delta,
		   info->tdls_options,
		   info->peer_traffic_ind_window,
		   info->peer_traffic_response_timeout,
		   info->puapsd_mask,
		   info->puapsd_inactivity_time,
		   info->puapsd_rx_frame_threshold,
		   info->teardown_notification_ms,
		   info->tdls_peer_kickout_threshold);

}

/**
 * tdls_update_fw_tdls_state() - update tdls status info
 * @tdls_soc_obj: TDLS soc object
 * @tdls_info_to_fw: TDLS state info to update in f/w.
 *
 * send message to WMA to set TDLS state in f/w
 *
 * Return: QDF_STATUS.
 */
static
QDF_STATUS tdls_update_fw_tdls_state(struct tdls_soc_priv_obj *tdls_soc_obj,
				     struct tdls_info *tdls_info_to_fw)
{
	QDF_STATUS status;

	/*  wmi_unified_update_fw_tdls_state_cmd() will be called directly */
	status = tgt_tdls_set_fw_state(tdls_soc_obj->soc, tdls_info_to_fw);

	if (!QDF_IS_STATUS_SUCCESS(status))
		status = QDF_STATUS_E_FAILURE;

	return status;
}

bool tdls_check_is_tdls_allowed(struct wlan_objmgr_vdev *vdev)
{
	struct tdls_vdev_priv_obj *tdls_vdev_obj;
	struct tdls_soc_priv_obj *tdls_soc_obj;
	bool state = false;

	if (QDF_STATUS_SUCCESS != wlan_objmgr_vdev_try_get_ref(vdev,
							       WLAN_TDLS_NB_ID))
		return state;

	if (QDF_STATUS_SUCCESS != tdls_get_vdev_objects(vdev, &tdls_vdev_obj,
						   &tdls_soc_obj)) {
		wlan_objmgr_vdev_release_ref(vdev,
					     WLAN_TDLS_NB_ID);
		return state;
	}

	if (policy_mgr_get_connection_count(tdls_soc_obj->soc) == 1)
		state = true;
	else
		tdls_warn("Concurrent sessions are running or TDLS disabled");
	/* If any concurrency is detected */
	/* print session information */
	wlan_objmgr_vdev_release_ref(vdev,
				     WLAN_TDLS_NB_ID);
	return state;
}

/**
 * cds_set_tdls_ct_mode() - Set the tdls connection tracker mode
 * @hdd_ctx: hdd context
 *
 * This routine is called to set the tdls connection tracker operation status
 *
 * Return: NONE
 */
void tdls_set_ct_mode(struct wlan_objmgr_psoc *psoc)
{
	bool state = false;
	struct tdls_soc_priv_obj *tdls_soc_obj;

	tdls_soc_obj = wlan_psoc_get_tdls_soc_obj(psoc);
	if (NULL == tdls_soc_obj)
		return;

	/* If any concurrency is detected, skip tdls pkt tracker */
	if (policy_mgr_get_connection_count(psoc) > 1) {
		state = false;
		goto set_state;
	}

	if (TDLS_SUPPORT_DISABLED == tdls_soc_obj->tdls_current_mode ||
	    TDLS_SUPPORT_SUSPENDED == tdls_soc_obj->tdls_current_mode ||
	    !TDLS_IS_IMPLICIT_TRIG_ENABLED(
			tdls_soc_obj->tdls_configs.tdls_feature_flags)) {
		state = false;
		goto set_state;
	} else if (policy_mgr_mode_specific_connection_count(psoc,
							     PM_STA_MODE,
							     NULL) == 1) {
		state = true;
	} else if (policy_mgr_mode_specific_connection_count(psoc,
							     PM_P2P_CLIENT_MODE,
							     NULL) == 1){
		state = true;
	} else {
		state = false;
		goto set_state;
	}

	/* In case of TDLS external control, peer should be added
	 * by the user space to start connection tracker.
	 */
	if (TDLS_IS_EXTERNAL_CONTROL_ENABLED(
			tdls_soc_obj->tdls_configs.tdls_feature_flags)) {
		if (tdls_soc_obj->tdls_external_peer_count)
			state = true;
		else
			state = false;
	}

set_state:
	tdls_soc_obj->enable_tdls_connection_tracker = state;

	tdls_notice("enable_tdls_connection_tracker %d",
		 tdls_soc_obj->enable_tdls_connection_tracker);
}

QDF_STATUS
tdls_process_policy_mgr_notification(struct wlan_objmgr_psoc *psoc)
{
	if (!psoc) {
		tdls_err("psoc: %p", psoc);
		return QDF_STATUS_E_NULL_VALUE;
	}
	tdls_debug("enter ");
	tdls_set_ct_mode(psoc);
	tdls_debug("exit ");
	return QDF_STATUS_SUCCESS;
}

/**
 * tdls_get_vdev() - Get tdls specific vdev object manager
 * @psoc: wlan psoc object manager
 * @dbg_id: debug id
 *
 * If TDLS possible, return the corresponding vdev
 * to enable TDLS in the system.
 *
 * Return: vdev manager pointer or NULL.
 */
struct wlan_objmgr_vdev *tdls_get_vdev(struct wlan_objmgr_psoc *psoc,
					  wlan_objmgr_ref_dbgid dbg_id)
{
	if (policy_mgr_get_connection_count(psoc) > 1)
		return NULL;
	if (policy_mgr_mode_specific_connection_count(psoc,
						      PM_STA_MODE,
						      NULL) == 1)
		return wlan_objmgr_get_vdev_by_opmode_from_psoc(psoc,
							QDF_STA_MODE,
							dbg_id);
	if (policy_mgr_mode_specific_connection_count(psoc,
						      PM_P2P_CLIENT_MODE,
						      NULL) == 1)
		return wlan_objmgr_get_vdev_by_opmode_from_psoc(psoc,
							QDF_P2P_CLIENT_MODE,
							dbg_id);
	return NULL;
}

/**
 * tdls_process_session_update() - update session count information
 * @psoc: soc object
 * @notification: TDLS os if notification
 *
 * update the session information in connection tracker
 *
 * Return: None
 */
static void tdls_process_session_update(struct wlan_objmgr_psoc *psoc,
				 enum tdls_command_type cmd_type)
{
	struct scheduler_msg msg = {0};
	QDF_STATUS status;

	msg.bodyptr = psoc;
	msg.callback = tdls_process_cmd;
	msg.type = (uint16_t)cmd_type;

	status = scheduler_post_msg(QDF_MODULE_ID_OS_IF, &msg);
	if (QDF_IS_STATUS_ERROR(status))
		tdls_alert("message post failed ");
}

void tdls_notify_increment_session(struct wlan_objmgr_psoc *psoc)
{
	tdls_process_session_update(psoc, TDLS_CMD_SESSION_INCREMENT);
}

void tdls_notify_decrement_session(struct wlan_objmgr_psoc *psoc)
{
	tdls_process_session_update(psoc, TDLS_CMD_SESSION_DECREMENT);
}

/**
 * tdls_send_update_to_fw - update tdls status info
 * @tdls_vdev_obj: tdls vdev private object.
 * @tdls_prohibited: indicates whether tdls is prohibited.
 * @tdls_chan_swit_prohibited: indicates whether tdls channel switch
 *                             is prohibited.
 * @sta_connect_event: indicate sta connect or disconnect event
 * @session_id: session id
 *
 * Normally an AP does not influence TDLS connection between STAs
 * associated to it. But AP may set bits for TDLS Prohibited or
 * TDLS Channel Switch Prohibited in Extended Capability IE in
 * Assoc/Re-assoc response to STA. So after STA is connected to
 * an AP, call this function to update TDLS status as per those
 * bits set in Ext Cap IE in received Assoc/Re-assoc response
 * from AP.
 *
 * Return: None.
 */
static void tdls_send_update_to_fw(struct tdls_vdev_priv_obj *tdls_vdev_obj,
				   struct tdls_soc_priv_obj *tdls_soc_obj,
				   bool tdls_prohibited,
				   bool tdls_chan_swit_prohibited,
				   bool sta_connect_event,
				   uint8_t session_id)
{
	struct tdls_info *tdls_info_to_fw;
	struct tdls_config_params *threshold_params;
	uint32_t tdls_feature_flags;
	QDF_STATUS status;


	/* If TDLS support is disabled then no need to update target */
	if (tdls_soc_obj->tdls_current_mode <= TDLS_SUPPORT_SUSPENDED) {
		tdls_err("TDLS not enabled or suspended");
		return;
	}

	if (tdls_soc_obj->set_state_info.set_state_cnt == 0 &&
	    !sta_connect_event) {
		return;
	}

	tdls_feature_flags = tdls_soc_obj->tdls_configs.tdls_feature_flags;

	/* If AP or caller indicated TDLS Prohibited then disable tdls mode */
	if (tdls_prohibited) {
		tdls_soc_obj->tdls_current_mode = TDLS_SUPPORT_DISABLED;
	} else {
		tdls_debug("TDLS feature flags from ini %d ",
				tdls_feature_flags);
		if (!TDLS_IS_IMPLICIT_TRIG_ENABLED(tdls_feature_flags))
			tdls_soc_obj->tdls_current_mode =
				TDLS_SUPPORT_EXP_TRIG_ONLY;
		else if (TDLS_IS_EXTERNAL_CONTROL_ENABLED(tdls_feature_flags))
			tdls_soc_obj->tdls_current_mode =
				TDLS_SUPPORT_EXT_CONTROL;
		else
			tdls_soc_obj->tdls_current_mode =
				TDLS_SUPPORT_IMP_MODE;
	}

	tdls_info_to_fw = qdf_mem_malloc(sizeof(struct tdls_info));

	if (!tdls_info_to_fw) {
		tdls_err("memory allocation failed for tdlsParams");
		QDF_ASSERT(0);
		return;
	}

	threshold_params = &tdls_vdev_obj->threshold_config;

	tdls_info_to_fw->notification_interval_ms =
		threshold_params->tx_period_t;
	tdls_info_to_fw->tx_discovery_threshold =
		threshold_params->tx_packet_n;
	tdls_info_to_fw->tx_teardown_threshold =
		threshold_params->idle_packet_n;
	tdls_info_to_fw->rssi_teardown_threshold =
		threshold_params->rssi_teardown_threshold;
	tdls_info_to_fw->rssi_delta = threshold_params->rssi_delta;

	if (tdls_soc_obj->set_state_info.set_state_cnt == 1 &&
	    sta_connect_event) {
		tdls_warn("Concurrency not allowed in TDLS! set state cnt %d",
			tdls_soc_obj->set_state_info.set_state_cnt);
		/* disable off channel and teardown links */
		/* Go through the peer list and delete them */
		tdls_soc_obj->tdls_current_mode = TDLS_SUPPORT_DISABLED;
		tdls_info_to_fw->vdev_id = tdls_soc_obj->set_state_info.vdev_id;
	} else {
		tdls_info_to_fw->vdev_id = session_id;
	}

	tdls_info_to_fw->tdls_state = tdls_soc_obj->tdls_current_mode;
	tdls_info_to_fw->tdls_options = 0;

	/* Do not enable TDLS offchannel, if AP prohibited TDLS
	 * channel switch
	 */
	if (TDLS_IS_OFF_CHANNEL_ENABLED(tdls_feature_flags) &&
		(!tdls_chan_swit_prohibited))
		tdls_info_to_fw->tdls_options = ENA_TDLS_OFFCHAN;

	if (TDLS_IS_BUFFER_STA_ENABLED(tdls_feature_flags))
		tdls_info_to_fw->tdls_options |= ENA_TDLS_BUFFER_STA;
	if (TDLS_IS_SLEEP_STA_ENABLED(tdls_feature_flags))
		tdls_info_to_fw->tdls_options |=  ENA_TDLS_SLEEP_STA;


	tdls_info_to_fw->peer_traffic_ind_window =
		tdls_soc_obj->tdls_configs.tdls_uapsd_pti_window;
	tdls_info_to_fw->peer_traffic_response_timeout =
		tdls_soc_obj->tdls_configs.tdls_uapsd_ptr_timeout;
	tdls_info_to_fw->puapsd_mask =
		tdls_soc_obj->tdls_configs.tdls_uapsd_mask;
	tdls_info_to_fw->puapsd_inactivity_time =
		tdls_soc_obj->tdls_configs.tdls_uapsd_inactivity_time;
	tdls_info_to_fw->puapsd_rx_frame_threshold =
		tdls_soc_obj->tdls_configs.tdls_rx_pkt_threshold;
	tdls_info_to_fw->teardown_notification_ms =
		tdls_soc_obj->tdls_configs.tdls_idle_timeout;
	tdls_info_to_fw->tdls_peer_kickout_threshold =
		tdls_soc_obj->tdls_configs.tdls_peer_kickout_threshold;

	tdls_state_param_setting_dump(tdls_info_to_fw);

	status = tdls_update_fw_tdls_state(tdls_soc_obj, tdls_info_to_fw);
	if (QDF_STATUS_SUCCESS != status) {
		qdf_mem_free(tdls_info_to_fw);
		goto done;
	}

	if (sta_connect_event) {
		tdls_soc_obj->set_state_info.set_state_cnt++;
		tdls_soc_obj->set_state_info.vdev_id = session_id;
	} else {
		tdls_soc_obj->set_state_info.set_state_cnt--;
	}

	tdls_debug("TDLS Set state cnt %d",
		tdls_soc_obj->set_state_info.set_state_cnt);

	if (tdls_soc_obj->set_state_info.set_state_cnt == 1)
		/* register callbacks with tx/rx mgmt */
		tdls_mgmt_rx_ops(tdls_soc_obj->soc, true);
	else
		/* deregister callbacks with tx/rx mgmt */
		tdls_mgmt_rx_ops(tdls_soc_obj->soc, false);

done:
	tdls_process_session_update(tdls_soc_obj->soc,
					TDLS_CMD_SESSION_INCREMENT);
	return;
}

static QDF_STATUS
tdls_process_sta_connect(struct tdls_sta_notify_params *notify)
{
	struct tdls_vdev_priv_obj *tdls_vdev_obj;
	struct tdls_soc_priv_obj *tdls_soc_obj;

	if (QDF_STATUS_SUCCESS != tdls_get_vdev_objects(notify->vdev,
							&tdls_vdev_obj,
							&tdls_soc_obj))
		return QDF_STATUS_E_INVAL;


	tdls_debug("Check and update TDLS state");

	/* Association event */
	if (!tdls_soc_obj->tdls_disable_in_progress) {
		tdls_send_update_to_fw(tdls_vdev_obj,
				   tdls_soc_obj,
				   notify->tdls_prohibited,
				   notify->tdls_chan_swit_prohibited,
				   true,
				   notify->session_id);
	}

	/* check and set the connection tracker */
	tdls_set_ct_mode(tdls_soc_obj->soc);
	if (tdls_soc_obj->enable_tdls_connection_tracker)
		tdls_implicit_enable(tdls_vdev_obj);

	return QDF_STATUS_SUCCESS;
}

QDF_STATUS tdls_notify_sta_connect(struct tdls_sta_notify_params *notify)
{
	QDF_STATUS status;

	if (!notify || !notify->vdev)
		return QDF_STATUS_E_INVAL;

	if (QDF_STATUS_SUCCESS != wlan_objmgr_vdev_try_get_ref(notify->vdev,
							WLAN_TDLS_NB_ID))
		return QDF_STATUS_E_INVAL;

	status = tdls_process_sta_connect(notify);

	wlan_objmgr_vdev_release_ref(notify->vdev,
				     WLAN_TDLS_NB_ID);
	qdf_mem_free(notify);
	return status;
}

static QDF_STATUS
tdls_process_sta_disconnect(struct tdls_sta_notify_params *notify)
{
	struct tdls_vdev_priv_obj *tdls_vdev_obj;
	struct tdls_vdev_priv_obj *curr_tdls_vdev;
	struct tdls_soc_priv_obj *tdls_soc_obj;
	struct tdls_soc_priv_obj *curr_tdls_soc;
	struct wlan_objmgr_vdev *temp_vdev = NULL;


	QDF_STATUS status = QDF_STATUS_SUCCESS;

	if (QDF_STATUS_SUCCESS != tdls_get_vdev_objects(notify->vdev,
							&tdls_vdev_obj,
							&tdls_soc_obj))
		return QDF_STATUS_E_INVAL;

	tdls_debug("Check and update TDLS state");

	curr_tdls_vdev = tdls_vdev_obj;
	curr_tdls_soc = tdls_soc_obj;

	/* Disassociation event */
	if (!tdls_soc_obj->tdls_disable_in_progress)
		tdls_send_update_to_fw(tdls_vdev_obj, tdls_soc_obj, false,
				       false, false, notify->session_id);

	/* If concurrency is not marked, then we have to
	 * check, whether TDLS could be enabled in the
	 * system after this disassoc event.
	 */
	if (!notify->lfr_roam && !tdls_soc_obj->tdls_disable_in_progress) {
		temp_vdev = tdls_get_vdev(tdls_soc_obj->soc, WLAN_TDLS_NB_ID);
		if (NULL != temp_vdev) {
			status = tdls_get_vdev_objects(temp_vdev,
						       &tdls_vdev_obj,
						       &tdls_soc_obj);
			if (QDF_STATUS_SUCCESS == status) {
				tdls_send_update_to_fw(tdls_vdev_obj,
						       tdls_soc_obj,
						       false,
						       false,
						       true,
						       notify->session_id);
				curr_tdls_vdev = tdls_vdev_obj;
				curr_tdls_soc = tdls_soc_obj;
			}
		}
	}

	/* Check and set the connection tracker and implicit timers */
	tdls_set_ct_mode(curr_tdls_soc->soc);
	if (curr_tdls_soc->enable_tdls_connection_tracker)
		tdls_implicit_enable(curr_tdls_vdev);
	else
		tdls_implicit_disable(curr_tdls_vdev);

	/* release the vdev ref , if temp vdev was acquired */
	if (temp_vdev)
		wlan_objmgr_vdev_release_ref(temp_vdev,
					     WLAN_TDLS_NB_ID);

	return status;
}

QDF_STATUS tdls_notify_sta_disconnect(struct tdls_sta_notify_params *notify)
{
	QDF_STATUS status;

	if (!notify || !notify->vdev)
		return QDF_STATUS_E_INVAL;

	if (QDF_STATUS_SUCCESS != wlan_objmgr_vdev_try_get_ref(notify->vdev,
							       WLAN_TDLS_NB_ID))
		return QDF_STATUS_E_INVAL;

	status = tdls_process_sta_disconnect(notify);

	wlan_objmgr_vdev_release_ref(notify->vdev,
			     WLAN_TDLS_NB_ID);

	qdf_mem_free(notify);
	return status;
}

/**
 * tdls_set_mode_in_vdev() - set TDLS mode
 * @tdls_vdev: tdls vdev object
 * @tdls_soc: tdls soc object
 * @tdls_mode: TDLS mode
 * @source: TDLS disable source enum values
 *
 * Return: Void
 */
static void tdls_set_mode_in_vdev(struct tdls_vdev_priv_obj *tdls_vdev,
				  struct tdls_soc_priv_obj *tdls_soc,
				  enum tdls_feature_mode tdls_mode,
				  enum tdls_disable_sources source)
{
	if (!tdls_vdev)
		return;
	tdls_debug("enter tdls mode is %d", tdls_mode);

	if (TDLS_SUPPORT_IMP_MODE == tdls_mode ||
	    TDLS_SUPPORT_EXT_CONTROL == tdls_mode) {
		clear_bit((unsigned long)source,
			  &tdls_soc->tdls_source_bitmap);
		/*
		 * Check if any TDLS source bit is set and if
		 * bitmap is not zero then we should not
		 * enable TDLS
		 */
		if (tdls_soc->tdls_source_bitmap) {
			tdls_notice("Don't enable TDLS, source bitmap: %lu",
				tdls_soc->tdls_source_bitmap);
			return;
		}
		tdls_implicit_enable(tdls_vdev);
		/* tdls implicit mode is enabled, so
		 * enable the connection tracker
		 */
		tdls_soc->enable_tdls_connection_tracker =
			true;
	} else if (TDLS_SUPPORT_DISABLED == tdls_mode) {
		set_bit((unsigned long)source,
			&tdls_soc->tdls_source_bitmap);
		tdls_implicit_disable(tdls_vdev);
		/* If tdls implicit mode is disabled, then
		 * stop the connection tracker.
		 */
		tdls_soc->enable_tdls_connection_tracker =
			false;
	} else if (TDLS_SUPPORT_EXP_TRIG_ONLY ==
		   tdls_mode) {
		clear_bit((unsigned long)source,
			  &tdls_soc->tdls_source_bitmap);
		tdls_implicit_disable(tdls_vdev);
		/* If tdls implicit mode is disabled, then
		 * stop the connection tracker.
		 */
		tdls_soc->enable_tdls_connection_tracker =
			false;

		/*
		 * Check if any TDLS source bit is set and if
		 * bitmap is not zero then we should not
		 * enable TDLS
		 */
		if (tdls_soc->tdls_source_bitmap)
			return;
	}
	tdls_debug("exit ");

}

/**
 * tdls_set_current_mode() - set TDLS mode
 * @tdls_soc: tdls soc object
 * @tdls_mode: TDLS mode
 * @update_last: indicate to record the last tdls mode
 * @source: TDLS disable source enum values
 *
 * Return: Void
 */
static void tdls_set_current_mode(struct tdls_soc_priv_obj *tdls_soc,
				   enum tdls_feature_mode tdls_mode,
				   bool update_last,
				   enum tdls_disable_sources source)
{
	struct wlan_objmgr_vdev *vdev;
	struct tdls_vdev_priv_obj *tdls_vdev;

	if (!tdls_soc)
		return;

	tdls_debug("mode %d", (int)tdls_mode);

	if (update_last)
		tdls_soc->tdls_last_mode = tdls_mode;

	if (tdls_soc->tdls_current_mode == tdls_mode) {
		tdls_debug("already in mode %d", tdls_mode);

		switch (tdls_mode) {
		/* TDLS is already enabled hence clear source mask, return */
		case TDLS_SUPPORT_IMP_MODE:
		case TDLS_SUPPORT_EXP_TRIG_ONLY:
		case TDLS_SUPPORT_EXT_CONTROL:
			clear_bit((unsigned long)source,
				  &tdls_soc->tdls_source_bitmap);
			tdls_debug("clear source mask:%d", source);
			return;
		/* TDLS is already disabled hence set source mask, return */
		case TDLS_SUPPORT_DISABLED:
			set_bit((unsigned long)source,
				&tdls_soc->tdls_source_bitmap);
			tdls_debug("set source mask:%d", source);
			return;
		default:
			return;
		}
	}

	/* get sta vdev */
	vdev = wlan_objmgr_get_vdev_by_opmode_from_psoc(tdls_soc->soc,
							QDF_STA_MODE,
							WLAN_TDLS_NB_ID);
	if (NULL != vdev) {
		tdls_debug("set mode in tdls vdev ");
		tdls_vdev = wlan_vdev_get_tdls_vdev_obj(vdev);
		if (!tdls_vdev)
			tdls_set_mode_in_vdev(tdls_vdev, tdls_soc,
					      tdls_mode, source);
		wlan_objmgr_vdev_release_ref(vdev, WLAN_TDLS_NB_ID);
	}

	/* get p2p client vdev */
	vdev = wlan_objmgr_get_vdev_by_opmode_from_psoc(tdls_soc->soc,
							QDF_P2P_CLIENT_MODE,
							WLAN_TDLS_NB_ID);
	if (NULL != vdev) {
		tdls_debug("set mode in tdls vdev ");
		tdls_vdev = wlan_vdev_get_tdls_vdev_obj(vdev);
		if (!tdls_vdev)
			tdls_set_mode_in_vdev(tdls_vdev, tdls_soc,
					      tdls_mode, source);
		wlan_objmgr_vdev_release_ref(vdev, WLAN_TDLS_NB_ID);
	}

	if (!update_last)
		tdls_soc->tdls_last_mode = tdls_soc->tdls_current_mode;

	tdls_soc->tdls_current_mode = tdls_mode;

}

QDF_STATUS tdls_set_operation_mode(struct tdls_set_mode_params *tdls_set_mode)
{
	struct tdls_soc_priv_obj *tdls_soc;
	struct tdls_vdev_priv_obj *tdls_vdev;
	QDF_STATUS status;

	if (!tdls_set_mode || !tdls_set_mode->vdev)
		return QDF_STATUS_E_INVAL;

	if (QDF_STATUS_SUCCESS !=
		wlan_objmgr_vdev_try_get_ref(tdls_set_mode->vdev,
						WLAN_TDLS_NB_ID))
		return QDF_STATUS_E_INVAL;

	status = tdls_get_vdev_objects(tdls_set_mode->vdev,
				       &tdls_vdev, &tdls_soc);

	if (status != QDF_STATUS_SUCCESS)
		goto release_mode_ref;

	tdls_set_current_mode(tdls_soc,
			      tdls_set_mode->tdls_mode,
			      tdls_set_mode->update_last,
			      tdls_set_mode->source);

release_mode_ref:
	wlan_objmgr_vdev_release_ref(tdls_set_mode->vdev, WLAN_TDLS_NB_ID);
	qdf_mem_free(tdls_set_mode);
	return status;
}

