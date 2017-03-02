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
 /**
  * DOC: This file provides the common defintions for object manager
  */

#ifndef _WLAN_OBJMGR_CMN_H_
#define _WLAN_OBJMGR_CMN_H_

#include "qdf_lock.h"
#include "qdf_list.h"
#include "qdf_status.h"
#include "wlan_cmn.h"
#include "qdf_atomic.h"

/* No. of PSOCs can be supported */
#define WLAN_OBJMGR_MAX_DEVICES 3

/* size of Hash */
#define WLAN_PEER_HASHSIZE 64

/* simple hash is enough for variation of macaddr */
#define WLAN_PEER_HASH(addr)   \
(((const uint8_t *)(addr))[WLAN_MACADDR_LEN - 1] % WLAN_PEER_HASHSIZE)

/**
 * enum WLAN_OBJ_STATE - State of Object
 * @WLAN_OBJ_STATE_CREATED:             All component objects are created
 * @WLAN_OBJ_STATE_DELETED:             All component objects are destroyed
 * @WLAN_OBJ_STATE_PARTIALLY_CREATED:   Few/All component objects creation is
 *                                      in progress
 * @WLAN_OBJ_STATE_PARTIALLY_DELETED:   Component objects deletion is triggered,
 *                                      they are yet to be destroyed
 * @WLAN_OBJ_STATE_COMP_DEL_PROGRESS:   If a component is disabled run time,
 *                                      and this state is used to represent the
 *                                      deletion in progress after that
 *                                      component object is destroyed, object
 *                                      state would be moved to CREATED state
 * @WLAN_OBJ_STATE_LOGICALLY_DELETED:   Object deletion has been initiated,
 *                                      object destroy invoked once references
 *                                      are released
 * @WLAN_OBJ_STATE_CREATION_FAILED:     any component object is failed to be
 *                                      created
 * @WLAN_OBJ_STATE_DELETION_FAILED:     any component object is failed to be
 *                                      destroyed
 */
typedef enum {
	WLAN_OBJ_STATE_CREATED            = 0,
	WLAN_OBJ_STATE_DELETED            = 1,
	WLAN_OBJ_STATE_PARTIALLY_CREATED  = 2,
	WLAN_OBJ_STATE_PARTIALLY_DELETED  = 3,
	WLAN_OBJ_STATE_COMP_DEL_PROGRESS  = 4,
	WLAN_OBJ_STATE_LOGICALLY_DELETED  = 5,
	WLAN_OBJ_STATE_CREATION_FAILED    = 6,
	WLAN_OBJ_STATE_DELETION_FAILED    = 7,
} WLAN_OBJ_STATE;

/* Object type is assigned with value */
enum wlan_objmgr_obj_type {
	WLAN_PSOC_OP  = 0,
	WLAN_PDEV_OP  = 1,
	WLAN_VDEV_OP  = 2,
	WLAN_PEER_OP  = 3,
};

/**
 * struct wlan_peer_list {
 * @peer_hash[]:    peer sub lists
 * @peer_list_lock: List lock, this has to be acquired on
 *		    accessing/updating the list
 *
 *  Peer list, it maintains sublists based on the MAC address as hash
 *  Note: For DA WDS similar peer list has to be maintained
 *  This peer list will not have WDS nodes
 */
struct wlan_peer_list {
	qdf_list_t peer_hash[WLAN_PEER_HASHSIZE];
	qdf_spinlock_t peer_list_lock;
};

struct wlan_objmgr_psoc;
struct wlan_objmgr_pdev;
struct wlan_objmgr_vdev;
struct wlan_objmgr_peer;

/* Create handler would return the following status
	QDF_STATUS_SUCCESS--
		For synchronous handler:- this is returned on successful
	component object creation

	QDF_STATUS_COMP_DISABLED--
		For synchronous handler:- this is returned on if component
	doesn't want to allocate

	QDF_STATUS_COMP_ASYNC--
		For asynchronous handler:- this is returned on if component
	needs a context break

	QDF_STATUS_E_NOMEM--
		For synchronous handler:- this is returned on if component
	can't allocate
	QDF_STATUS_E_FAILURE--
		For synchronous handler:- If it is failed,
		For asynchronous handler:- If it is failed to post message
	(means, not required)/feature is not supported
*/
typedef QDF_STATUS (*wlan_objmgr_psoc_create_handler)(
				struct wlan_objmgr_psoc *psoc, void *arg);
typedef QDF_STATUS (*wlan_objmgr_psoc_destroy_handler)(
				struct wlan_objmgr_psoc *psoc, void *arg);
typedef void (*wlan_objmgr_psoc_status_handler)(struct wlan_objmgr_psoc *psoc,
					 void *arg, QDF_STATUS status);

typedef QDF_STATUS (*wlan_objmgr_pdev_create_handler)(
				struct wlan_objmgr_pdev *pdev, void *arg);
typedef QDF_STATUS (*wlan_objmgr_pdev_destroy_handler)(
				struct wlan_objmgr_pdev *pdev, void *arg);
typedef void (*wlan_objmgr_pdev_status_handler)(
				struct wlan_objmgr_pdev *pdev, void *arg,
						QDF_STATUS status);

typedef QDF_STATUS (*wlan_objmgr_vdev_create_handler)(
				struct wlan_objmgr_vdev *vdev, void *arg);
typedef QDF_STATUS (*wlan_objmgr_vdev_destroy_handler)(
				struct wlan_objmgr_vdev *vdev, void *arg);
typedef void (*wlan_objmgr_vdev_status_handler)(
				struct wlan_objmgr_vdev *vdev, void *arg,
						QDF_STATUS status);

typedef QDF_STATUS (*wlan_objmgr_peer_create_handler)(
				struct wlan_objmgr_peer *peer, void *arg);
typedef QDF_STATUS (*wlan_objmgr_peer_destroy_handler)(
				struct wlan_objmgr_peer *peer, void *arg);
typedef void (*wlan_objmgr_peer_status_handler)(
				struct wlan_objmgr_peer *peer, void *arg,
						QDF_STATUS status);

/**
 * enum wlan_objmgr_ref_dbgid - ref count debug id
 * @WLAN_OBJMGR_ID:             Object manager internal operations
 * @WLAN_MLME_SB_ID:            MLME Southbound operations
 * @WLAN_MLME_NB_ID:            MLME Northbound operations
 * @WLAN_MGMT_SB_ID:            MGMT Northbound operations
 * @WLAN_MGMT_NB_ID:            MGMT Southbound operations
 * @WLAN_HDD_ID_OBJ_MGR:        HDD Object Manager operations
 * @WLAN_OSIF_ID:               New component's OS IF ID
 * @WLAN_LEGACY_MAC_ID:         Legacy MAC operations
 * @WLAN_LEGACY_WMA_ID:         Legacy WMA operations
 * @WLAN_SERIALIZATION_ID:      Serialization operations
 * @WLAN_PMO_ID:                power manager offload (PMO) ID
 * @WLAN_LEGACY_SME_ID:         Legacy SME operations
 * @WLAN_SCAN_ID:               scan operations
 * @WLAN_DFS_ID:                DFS operations
 * @WLAN_P2P_ID:                P2P operations
 * @WLAN_TDLS_SB_ID:            TDLS Southbound operations
 * @WLAN_TDLS_NB_ID:            TDLS Northbound operations
 * @WLAN_ATF_ID:                Airtime Fairness operations
 * @WLAN_REF_ID_MAX:            Max id used to generate ref count tracking array
 */
typedef enum {
	WLAN_OBJMGR_ID        = 0,
	WLAN_MLME_SB_ID       = 1,
	WLAN_MLME_NB_ID       = 2,
	WLAN_MGMT_SB_ID       = 3,
	WLAN_MGMT_NB_ID       = 4,
	WLAN_HDD_ID_OBJ_MGR   = 5,
	WLAN_OSIF_ID          = 6,
	WLAN_LEGACY_MAC_ID    = 7,
	WLAN_LEGACY_WMA_ID    = 8,
	WLAN_SERIALIZATION_ID = 9,
	WLAN_PMO_ID           = 10,
	WLAN_LEGACY_SME_ID    = 11,
	WLAN_SCAN_ID          = 12,
	WLAN_WIFI_POS_ID      = 13,
	WLAN_DFS_ID           = 14,
	WLAN_P2P_ID           = 15,
	WLAN_TDLS_SB_ID       = 16,
	WLAN_TDLS_NB_ID       = 17,
	WLAN_ATF_ID           = 19,
	WLAN_REF_ID_MAX,
} wlan_objmgr_ref_dbgid;

#ifdef WLAN_OBJMGR_DEBUG
#define WLAN_OBJMGR_BUG(val) QDF_BUG(val)
#else
#define WLAN_OBJMGR_BUG(val)
#endif
#endif /* _WLAN_OBJMGR_CMN_H_*/
