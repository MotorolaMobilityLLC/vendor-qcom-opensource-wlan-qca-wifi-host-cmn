/*
 * Copyright (c) 2014-2018 The Linux Foundation. All rights reserved.
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
 * DOC: qdf_types.h
 * QCA driver framework (QDF) basic type definitions
 */

#if !defined(__QDF_TYPES_H)
#define __QDF_TYPES_H

#ifndef CONFIG_MCL
#if !defined(__printf)
#define __printf(a, b)
#endif
#endif


/* Include Files */
#include <i_qdf_types.h>
#include <stdarg.h>
#ifdef TSOSEG_DEBUG
#include <qdf_atomic.h>
#endif

/* Preprocessor definitions and constants */
#define QDF_MAX_SGLIST 4

/**
 * struct qdf_sglist - scatter-gather list
 * @nsegs: total number of segments
 * struct __sg_segs - scatter-gather segment list
 * @vaddr: Virtual address of the segment
 * @len: Length of the segment
 */
typedef struct qdf_sglist {
	uint32_t nsegs;
	struct __sg_segs {
		uint8_t  *vaddr;
		uint32_t len;
	} sg_segs[QDF_MAX_SGLIST];
} qdf_sglist_t;

#define QDF_MAX_SCATTER __QDF_MAX_SCATTER
#define QDF_NSEC_PER_MSEC __QDF_NSEC_PER_MSEC

/**
 * QDF_SWAP_U16 - swap input u16 value
 * @_x: variable to swap
 */
#define QDF_SWAP_U16(_x) \
	((((_x) << 8) & 0xFF00) | (((_x) >> 8) & 0x00FF))

/**
 * QDF_SWAP_U32 - swap input u32 value
 * @_x: variable to swap
 */
#define QDF_SWAP_U32(_x) \
	(((((_x) << 24) & 0xFF000000) | (((_x) >> 24) & 0x000000FF)) | \
	 ((((_x) << 8) & 0x00FF0000) | (((_x) >> 8) & 0x0000FF00)))

/* ticks per second */
#define QDF_TICKS_PER_SECOND (1000)

/**
 * QDF_ARRAY_SIZE - get array size
 * @_arr: array variable name
 */
#define QDF_ARRAY_SIZE(_arr) (sizeof(_arr) / sizeof((_arr)[0]))

#define QDF_MAX_SCATTER __QDF_MAX_SCATTER

/**
 * qdf_packed - denotes structure is packed.
 */
#define qdf_packed __qdf_packed

/**
 * qdf_toupper - char lower to upper.
 */
#define qdf_toupper __qdf_toupper

typedef void *qdf_net_handle_t;

typedef void *qdf_netlink_handle_t;
typedef void *qdf_drv_handle_t;
typedef void *qdf_os_handle_t;
typedef void *qdf_pm_t;


/**
 * typedef qdf_handle_t - handles opaque to each other
 */
typedef void *qdf_handle_t;

/**
 * typedef qdf_device_t - Platform/bus generic handle.
 * Used for bus specific functions.
 */
typedef __qdf_device_t qdf_device_t;

/* Byte order identifiers */
typedef __qdf_le16_t qdf_le16_t;
typedef __qdf_le32_t qdf_le32_t;
typedef __qdf_le64_t qdf_le64_t;
typedef __qdf_be16_t qdf_be16_t;
typedef __qdf_be32_t qdf_be32_t;
typedef __qdf_be64_t qdf_be64_t;

/**
 * typedef qdf_size_t - size of an object
 */
typedef __qdf_size_t qdf_size_t;

/**
 * typedef __qdf_off_t - offset for API's that need them.
 */
typedef __qdf_off_t      qdf_off_t;

/**
 * typedef qdf_dma_map_t - DMA mapping object.
 */
typedef __qdf_dma_map_t qdf_dma_map_t;

/**
 * tyepdef qdf_dma_addr_t - DMA address.
 */
typedef __qdf_dma_addr_t qdf_dma_addr_t;

/**
 * typedef __qdf_dma_size_t - DMA size.
 */
typedef __qdf_dma_size_t     qdf_dma_size_t;

/**
 * tyepdef qdf_dma_context_t - DMA context.
 */
typedef __qdf_dma_context_t qdf_dma_context_t;

typedef __qdf_mem_info_t qdf_mem_info_t;
typedef __sgtable_t sgtable_t;

/**
 * pointer to net device
 */
typedef __qdf_netdev_t qdf_netdev_t;

/**
 * struct qdf_dma_map_info - Information inside a DMA map.
 * @nsegs: total number mapped segments
 * struct __dma_segs - Information of physical address.
 * @paddr: physical(dam'able) address of the segment
 * @len: length of the segment
 */
typedef struct qdf_dma_map_info {
	uint32_t nsegs;
	struct __dma_segs {
		qdf_dma_addr_t paddr;
		qdf_dma_size_t len;
	} dma_segs[QDF_MAX_SCATTER];
} qdf_dmamap_info_t;

/**
 * struct qdf_shared_mem - Shared memory resource
 * @mem_info: memory info struct
 * @vaddr: virtual address
 * @sgtable: scatter-gather table
 * @memctx: dma address
 */
typedef struct qdf_shared_mem {
	qdf_mem_info_t mem_info;
	void *vaddr;
	sgtable_t sgtable;
	qdf_dma_mem_context(memctx);
} qdf_shared_mem_t;

#define qdf_iomem_t __qdf_iomem_t;

/**
 * typedef enum QDF_TIMER_TYPE - QDF timer type
 * @QDF_TIMER_TYPE_SW: Deferrable SW timer it will not cause CPU to wake up
 * on expiry
 * @QDF_TIMER_TYPE_WAKE_APPS: Non deferrable timer which will cause CPU to
 * wake up on expiry
 */
typedef enum {
	QDF_TIMER_TYPE_SW,
	QDF_TIMER_TYPE_WAKE_APPS
} QDF_TIMER_TYPE;

/**
 * tyepdef qdf_resource_type_t - hw resources
 * @QDF_RESOURCE_TYPE_MEM: memory resource
 * @QDF_RESOURCE_TYPE_IO: io resource
 * Define the hw resources the OS has allocated for the device
 * Note that start defines a mapped area.
 */
typedef enum {
	QDF_RESOURCE_TYPE_MEM,
	QDF_RESOURCE_TYPE_IO,
} qdf_resource_type_t;

/**
 * tyepdef qdf_resource_t - representation of a h/w resource.
 * @start: start
 * @end: end
 * @type: resource type
 */
typedef struct {
	uint64_t start;
	uint64_t end;
	qdf_resource_type_t type;
} qdf_resource_t;

/**
 * typedef qdf_dma_dir_t - DMA directions
 * @QDF_DMA_BIDIRECTIONAL: bidirectional data
 * @QDF_DMA_TO_DEVICE: data going from device to memory
 * @QDF_DMA_FROM_DEVICE: data going from memory to device
 */
typedef enum {
	QDF_DMA_BIDIRECTIONAL = __QDF_DMA_BIDIRECTIONAL,
	QDF_DMA_TO_DEVICE = __QDF_DMA_TO_DEVICE,
	QDF_DMA_FROM_DEVICE = __QDF_DMA_FROM_DEVICE,
} qdf_dma_dir_t;

/**
 * enum qdf_driver_type - Indicate the driver type and based on this
 * do appropriate initialization.
 *
 * @QDF_DRIVER_TYPE_PRODUCTION: Driver used in the production
 * @QDF_DRIVER_TYPE_MFG: Driver used in the Factory
 * @QDF_DRIVER_TYPE_INVALID: Invalid and unrecognized type
 *
 */
enum qdf_driver_type {
	QDF_DRIVER_TYPE_PRODUCTION = 0,
	QDF_DRIVER_TYPE_MFG = 1,
	QDF_DRIVER_TYPE_INVALID = 0x7FFFFFFF
};

/* work queue(kernel thread)/DPC function callback */
typedef void (*qdf_defer_fn_t)(void *);

/*
 * Prototype of the critical region function that is to be
 * executed with spinlock held and interrupt disalbed
 */
typedef bool (*qdf_irqlocked_func_t)(void *);

/* Prototype of timer function */
typedef void (*qdf_timer_func_t)(void *);

#define qdf_offsetof(type, field) offsetof(type, field)

/**
 * typedef enum QDF_MODULE_ID  - Debug category level
 * @QDF_MODULE_ID_TDLS: TDLS
 * @QDF_MODULE_ID_ACS: auto channel selection
 * @QDF_MODULE_ID_SCAN_SM: scan state machine
 * @QDF_MODULE_ID_SCANENTRY: scan entry
 * @QDF_MODULE_ID_WDS: WDS handling
 * @QDF_MODULE_ID_ACTION: action management frames
 * @QDF_MODULE_ID_ROAM: sta mode roaming
 * @QDF_MODULE_ID_INACT: inactivity handling
 * @QDF_MODULE_ID_DOTH: 11.h
 * @QDF_MODULE_ID_IQUE: IQUE features
 * @QDF_MODULE_ID_WME: WME protocol
 * @QDF_MODULE_ID_ACL: ACL handling
 * @QDF_MODULE_ID_WPA: WPA/RSN protocol
 * @QDF_MODULE_ID_RADKEYS: dump 802.1x keys
 * @QDF_MODULE_ID_RADDUMP: dump 802.1x radius packets
 * @QDF_MODULE_ID_RADIUS: 802.1x radius client
 * @QDF_MODULE_ID_DOT1XSM: 802.1x state machine
 * @QDF_MODULE_ID_DOT1X: 802.1x authenticator
 * @QDF_MODULE_ID_POWER: power save handling
 * @QDF_MODULE_ID_STATS: state machine
 * @QDF_MODULE_ID_OUTPUT: output handling
 * @QDF_MODULE_ID_SCAN: scanning
 * @QDF_MODULE_ID_AUTH: authentication handling
 * @QDF_MODULE_ID_ASSOC: association handling
 * @QDF_MODULE_ID_NODE: node handling
 * @QDF_MODULE_ID_ELEMID: element id parsing
 * @QDF_MODULE_ID_XRATE: rate set handling
 * @QDF_MODULE_ID_INPUT: input handling
 * @QDF_MODULE_ID_CRYPTO: crypto work
 * @QDF_MODULE_ID_DUMPPKTS: IFF_LINK2 equivalant
 * @QDF_MODULE_ID_DEBUG: IFF_DEBUG equivalent
 * @QDF_MODULE_ID_MLME: MLME
 * @QDF_MODULE_ID_RRM: Radio resource measurement
 * @QDF_MODULE_ID_WNM: Wireless Network Management
 * @QDF_MODULE_ID_P2P_PROT: P2P Protocol driver
 * @QDF_MODULE_ID_PROXYARP: 11v Proxy ARP
 * @QDF_MODULE_ID_L2TIF: Hotspot 2.0 L2 TIF
 * @QDF_MODULE_ID_WIFIPOS: WifiPositioning Feature
 * @QDF_MODULE_ID_WRAP: WRAP or Wireless ProxySTA
 * @QDF_MODULE_ID_DFS: DFS debug mesg
 * @QDF_MODULE_ID_TLSHIM: TLSHIM module ID
 * @QDF_MODULE_ID_WMI: WMI module ID
 * @QDF_MODULE_ID_HTT: HTT module ID
 * @QDF_MODULE_ID_HDD: HDD module ID
 * @QDF_MODULE_ID_SME: SME module ID
 * @QDF_MODULE_ID_PE: PE module ID
 * @QDF_MODULE_ID_WMA: WMA module ID
 * @QDF_MODULE_ID_SYS: SYS module ID
 * @QDF_MODULE_ID_QDF: QDF module ID
 * @QDF_MODULE_ID_SAP: SAP module ID
 * @QDF_MODULE_ID_HDD_SOFTAP: HDD SAP module ID
 * @QDF_MODULE_ID_HDD_DATA: HDD DATA module ID
 * @QDF_MODULE_ID_HDD_SAP_DATA: HDD SAP DATA module ID
 * @QDF_MODULE_ID_HIF: HIF module ID
 * @QDF_MODULE_ID_HTC: HTC module ID
 * @QDF_MODULE_ID_TXRX: TXRX module ID
 * @QDF_MODULE_ID_QDF_DEVICE: QDF DEVICE module ID
 * @QDF_MODULE_ID_CFG: CFG module ID
 * @QDF_MODULE_ID_BMI: BMI module ID
 * @QDF_MODULE_ID_EPPING: EPPING module ID
 * @QDF_MODULE_ID_QVIT: QVIT module ID
 * @QDF_MODULE_ID_DP: Data-path module ID
 * @QDF_MODULE_ID_SOC: SOC module ID
 * @QDF_MODULE_ID_OS_IF: OS-interface module ID
 * @QDF_MODULE_ID_TARGET_IF: targer interface module ID
 * @QDF_MODULE_ID_SCHEDULER: schduler module ID
 * @QDF_MODULE_ID_MGMT_TXRX: management TX/RX module ID
 * @QDF_MODULE_ID_SERIALIZATION: serialization module ID
 * @QDF_MODULE_ID_PMO: PMO (power manager and offloads) Module ID
 * @QDF_MODULE_ID_P2P: P2P module ID
 * @QDF_MODULE_ID_POLICY_MGR: Policy Manager module ID
 * @QDF_MODULE_ID_CONFIG: CFG (configuration) component ID
 * @QDF_MODULE_ID_REGULATORY: REGULATORY module ID
 * @QDF_MODULE_ID_NAN: NAN module ID
 * @QDF_MODULE_ID_SPECTRAL: Spectral module ID
 * @QDF_MODULE_ID_ROAM_DEBUG: Roam Debug logging
 * @QDF_MODULE_ID_CDP: Converged Data Path module ID
 * @QDF_MODULE_ID_DIRECT_BUF_RX: Direct Buffer Receive module ID
 * @QDF_MODULE_ID_DISA: DISA (encryption test) module ID
 * @QDF_MODULE_ID_GREEN_AP: Green AP related logging
 * @QDF_MODULE_ID_FTM: FTM module ID
 * @QDF_MODULE_ID_EXTAP: Extender AP module ID
 * @QDF_MODULE_ID_FD: FILS discovery logging
 * @QDF_MODULE_ID_OCB: OCB module ID
 * @QDF_MODULE_ID_IPA: IPA module ID
 * @QDF_MODULE_ID_CP_STATS: Control Plane Statistics ID
 * @QDF_MODULE_ID_ANY: anything
 * @QDF_MODULE_ID_MAX: Max place holder module ID
 */
typedef enum {
	QDF_MODULE_ID_TDLS      = 0,
	QDF_MODULE_ID_ACS,
	QDF_MODULE_ID_SCAN_SM,
	QDF_MODULE_ID_SCANENTRY,
	QDF_MODULE_ID_WDS,
	QDF_MODULE_ID_ACTION,
	QDF_MODULE_ID_ROAM,
	QDF_MODULE_ID_INACT,
	QDF_MODULE_ID_DOTH      = 8,
	QDF_MODULE_ID_IQUE,
	QDF_MODULE_ID_WME,
	QDF_MODULE_ID_ACL,
	QDF_MODULE_ID_WPA,
	QDF_MODULE_ID_RADKEYS,
	QDF_MODULE_ID_RADDUMP,
	QDF_MODULE_ID_RADIUS,
	QDF_MODULE_ID_DOT1XSM   = 16,
	QDF_MODULE_ID_DOT1X,
	QDF_MODULE_ID_POWER,
	QDF_MODULE_ID_STATE,
	QDF_MODULE_ID_OUTPUT,
	QDF_MODULE_ID_SCAN,
	QDF_MODULE_ID_AUTH,
	QDF_MODULE_ID_ASSOC,
	QDF_MODULE_ID_NODE      = 24,
	QDF_MODULE_ID_ELEMID,
	QDF_MODULE_ID_XRATE,
	QDF_MODULE_ID_INPUT,
	QDF_MODULE_ID_CRYPTO,
	QDF_MODULE_ID_DUMPPKTS,
	QDF_MODULE_ID_DEBUG,
	QDF_MODULE_ID_MLME,
	QDF_MODULE_ID_RRM       = 32,
	QDF_MODULE_ID_WNM,
	QDF_MODULE_ID_P2P_PROT,
	QDF_MODULE_ID_PROXYARP,
	QDF_MODULE_ID_L2TIF,
	QDF_MODULE_ID_WIFIPOS,
	QDF_MODULE_ID_WRAP,
	QDF_MODULE_ID_DFS,
	QDF_MODULE_ID_ATF       = 40,
	QDF_MODULE_ID_SPLITMAC,
	QDF_MODULE_ID_IOCTL,
	QDF_MODULE_ID_NAC,
	QDF_MODULE_ID_MESH,
	QDF_MODULE_ID_MBO,
	QDF_MODULE_ID_EXTIOCTL_CHANSWITCH,
	QDF_MODULE_ID_EXTIOCTL_CHANSSCAN,
	QDF_MODULE_ID_TLSHIM    = 48,
	QDF_MODULE_ID_WMI,
	QDF_MODULE_ID_HTT,
	QDF_MODULE_ID_HDD,
	QDF_MODULE_ID_SME,
	QDF_MODULE_ID_PE,
	QDF_MODULE_ID_WMA,
	QDF_MODULE_ID_SYS,
	QDF_MODULE_ID_QDF       = 56,
	QDF_MODULE_ID_SAP,
	QDF_MODULE_ID_HDD_SOFTAP,
	QDF_MODULE_ID_HDD_DATA,
	QDF_MODULE_ID_HDD_SAP_DATA,
	QDF_MODULE_ID_HIF,
	QDF_MODULE_ID_HTC,
	QDF_MODULE_ID_TXRX,
	QDF_MODULE_ID_QDF_DEVICE = 64,
	QDF_MODULE_ID_CFG,
	QDF_MODULE_ID_BMI,
	QDF_MODULE_ID_EPPING,
	QDF_MODULE_ID_QVIT,
	QDF_MODULE_ID_DP,
	QDF_MODULE_ID_SOC,
	QDF_MODULE_ID_OS_IF,
	QDF_MODULE_ID_TARGET_IF,
	QDF_MODULE_ID_SCHEDULER,
	QDF_MODULE_ID_MGMT_TXRX,
	QDF_MODULE_ID_SERIALIZATION,
	QDF_MODULE_ID_PMO,
	QDF_MODULE_ID_P2P,
	QDF_MODULE_ID_POLICY_MGR,
	QDF_MODULE_ID_CONFIG,
	QDF_MODULE_ID_REGULATORY,
	QDF_MODULE_ID_SA_API,
	QDF_MODULE_ID_NAN,
	QDF_MODULE_ID_OFFCHAN_TXRX,
	QDF_MODULE_ID_SON,
	QDF_MODULE_ID_SPECTRAL,
	QDF_MODULE_ID_OBJ_MGR,
	QDF_MODULE_ID_NSS,
	QDF_MODULE_ID_ROAM_DEBUG,
	QDF_MODULE_ID_CDP,
	QDF_MODULE_ID_DIRECT_BUF_RX,
	QDF_MODULE_ID_DISA,
	QDF_MODULE_ID_GREEN_AP,
	QDF_MODULE_ID_FTM,
	QDF_MODULE_ID_EXTAP,
	QDF_MODULE_ID_FD,
	QDF_MODULE_ID_OCB,
	QDF_MODULE_ID_IPA,
	QDF_MODULE_ID_CP_STATS,
	QDF_MODULE_ID_ANY,
	QDF_MODULE_ID_MAX,
} QDF_MODULE_ID;

/**
 * typedef enum QDF_TRACE_LEVEL - Debug verbose level
 * @QDF_TRACE_LEVEL_NONE: no trace will be logged. This value is in place
 *			  for the qdf_trace_setlevel() to allow the user
 *			  to turn off all traces
 * @QDF_TRACE_LEVEL_FATAL: Indicates fatal error conditions
 * @QDF_TRACE_LEVEL_ERROR: Indicates error conditions
 * @QDF_TRACE_LEVEL_WARN: May indicate that an error will occur if action
 *			  is not taken
 * @QDF_TRACE_LEVEL_INFO: Normal operational messages that require no action
 * @QDF_TRACE_LEVEL_INFO_HIGH: High level operational messages that require
 *			       no action
 * @QDF_TRACE_LEVEL_INFO_MED: Middle level operational messages that require
 *			      no action
 * @QDF_TRACE_LEVEL_INFO_LOW: Low level operational messages that require
 *			      no action
 * @QDF_TRACE_LEVEL_DEBUG: Information useful to developers for debugging
 * @QDF_TRACE_LEVEL_ALL: All trace levels
 * @QDF_TRACE_LEVEL_MAX: Max trace level
 */
typedef enum {
	QDF_TRACE_LEVEL_NONE,
	QDF_TRACE_LEVEL_FATAL,
	QDF_TRACE_LEVEL_ERROR,
	QDF_TRACE_LEVEL_WARN,
	QDF_TRACE_LEVEL_INFO,
	QDF_TRACE_LEVEL_INFO_HIGH,
	QDF_TRACE_LEVEL_INFO_MED,
	QDF_TRACE_LEVEL_INFO_LOW,
	QDF_TRACE_LEVEL_DEBUG,
	QDF_TRACE_LEVEL_ALL,
	QDF_TRACE_LEVEL_MAX
} QDF_TRACE_LEVEL;

/**
 * enum QDF_OPMODE - vdev operating mode
 * @QDF_STA_MODE: STA mode
 * @QDF_SAP_MODE: SAP mode
 * @QDF_P2P_CLIENT_MODE: P2P client mode
 * @QDF_P2P_GO_MODE: P2P GO mode
 * @QDF_FTM_MODE: FTM mode
 * @QDF_IBSS_MODE: IBSS mode
 * @QDF_MONITOR_MODE: Monitor mode
 * @QDF_P2P_DEVICE_MODE: P2P device mode
 * @QDF_OCB_MODE: OCB device mode
 * @QDF_EPPING_MODE: EPPING device mode
 * @QDF_QVIT_MODE: QVIT device mode
 * @QDF_NDI_MODE: NAN datapath mode
 * @QDF_WDS_MODE: WDS mode
 * @QDF_BTAMP_MODE: BTAMP mode
 * @QDF_AHDEMO_MODE: AHDEMO mode
 * @QDF_MAX_NO_OF_MODE: Max place holder
 *
 * These are generic IDs that identify the various roles
 * in the software system
 */
enum QDF_OPMODE {
	QDF_STA_MODE,
	QDF_SAP_MODE,
	QDF_P2P_CLIENT_MODE,
	QDF_P2P_GO_MODE,
	QDF_FTM_MODE,
	QDF_IBSS_MODE,
	QDF_MONITOR_MODE,
	QDF_P2P_DEVICE_MODE,
	QDF_OCB_MODE,
	QDF_EPPING_MODE,
	QDF_QVIT_MODE,
	QDF_NDI_MODE,
	QDF_WDS_MODE,
	QDF_BTAMP_MODE,
	QDF_AHDEMO_MODE,
	QDF_MAX_NO_OF_MODE
};

/* for backward compatibility with the legacy definition */
#define tQDF_ADAPTER_MODE QDF_OPMODE

/**
 * enum QDF_GLOBAL_MODE - global mode when driver is loaded.
 *
 * @QDF_GLOBAL_MISSION_MODE: mission mode (STA, SAP...)
 * @QDF_GLOBAL_MONITOR_MODE: Monitor Mode
 * @QDF_GLOBAL_FTM_MODE: FTM mode
 * @QDF_GLOBAL_IBSS_MODE: IBSS mode
 * @QDF_GLOBAL_EPPING_MODE: EPPING mode
 * @QDF_GLOBAL_QVIT_MODE: QVIT global mode
 * @QDF_GLOBAL_MAX_MODE: Max place holder
 */
enum QDF_GLOBAL_MODE {
	QDF_GLOBAL_MISSION_MODE,
	QDF_GLOBAL_MONITOR_MODE = 4,
	QDF_GLOBAL_FTM_MODE = 5,
	QDF_GLOBAL_IBSS_MODE = 6,
	QDF_GLOBAL_COLDBOOT_CALIB_MODE = 7,
	QDF_GLOBAL_EPPING_MODE = 8,
	QDF_GLOBAL_QVIT_MODE = 9,
	QDF_GLOBAL_MAX_MODE
};

/* for backward compatibility with the legacy definition */
#define tQDF_GLOBAL_CON_MODE QDF_GLOBAL_MODE

#define  QDF_IS_EPPING_ENABLED(mode) (mode == QDF_GLOBAL_EPPING_MODE)


/**
 * qdf_trace_msg()- logging API
 * @module: Module identifier. A member of the QDF_MODULE_ID enumeration that
 *	    identifies the module issuing the trace message.
 * @level: Trace level. A member of the QDF_TRACE_LEVEL enumeration indicating
 *	   the severity of the condition causing the trace message to be issued.
 *	   More severe conditions are more likely to be logged.
 * @str_format: Format string. The message to be logged. This format string
 *	       contains printf-like replacement parameters, which follow this
 *	       parameter in the variable argument list.
 *
 * Users wishing to add tracing information to their code should use
 * QDF_TRACE.  QDF_TRACE() will compile into a call to qdf_trace_msg() when
 * tracing is enabled.
 *
 * Return: nothing
 *
 * implemented in qdf_trace.c
 */
void __printf(3, 4) qdf_trace_msg(QDF_MODULE_ID module, QDF_TRACE_LEVEL level,
		   char *str_format, ...);
/**
 * qdf_vtrace_msg() - the va_list version of qdf_trace_msg
 * @module: the calling module's Id
 * @level: the logging level to log using
 * @str_format: the log format string
 * @val: the va_list containing the values to format according to str_format
 *
 * Return: None
 */
void qdf_vtrace_msg(QDF_MODULE_ID module, QDF_TRACE_LEVEL level,
		    char *str_format, va_list val);

#ifdef CONFIG_MCL
#define qdf_print(args...) \
	QDF_TRACE(QDF_MODULE_ID_QDF, QDF_TRACE_LEVEL_ERROR, ## args)

#define qdf_alert(params...) QDF_TRACE_FATAL(QDF_MODULE_ID_QDF, ## params)
#define qdf_err(params...) QDF_TRACE_ERROR(QDF_MODULE_ID_QDF, ## params)
#define qdf_warn(params...) QDF_TRACE_WARN(QDF_MODULE_ID_QDF, ## params)
#define qdf_info(params...) QDF_TRACE_INFO(QDF_MODULE_ID_QDF, ## params)
#define qdf_debug(params...) QDF_TRACE_DEBUG(QDF_MODULE_ID_QDF, ## params)

#else /* CONFIG_MCL */

#define qdf_print printk
#define qdf_alert printk
#define qdf_err printk
#define qdf_warn printk
#define qdf_info printk
#define qdf_debug printk

#endif /* CONFIG_MCL */

#define qdf_vprint    __qdf_vprint
#define qdf_snprint   __qdf_snprint

#ifdef WLAN_OPEN_P2P_INTERFACE
/* This should match with WLAN_MAX_INTERFACES */
#define QDF_MAX_CONCURRENCY_PERSONA  (4)
#else
#define QDF_MAX_CONCURRENCY_PERSONA  (3)
#endif

#define QDF_STA_MASK (1 << QDF_STA_MODE)
#define QDF_SAP_MASK (1 << QDF_SAP_MODE)
#define QDF_P2P_CLIENT_MASK (1 << QDF_P2P_CLIENT_MODE)
#define QDF_P2P_GO_MASK (1 << QDF_P2P_GO_MODE)

#ifdef FEATURE_WLAN_MCC_TO_SCC_SWITCH

/**
 * typedef tQDF_MCC_TO_SCC_SWITCH_MODE - MCC to SCC switch mode.
 * @QDF_MCC_TO_SCC_SWITCH_DISABLE: Disable switch
 * @QDF_MCC_TO_SCC_SWITCH_ENABLE: Enable switch
 * @QDF_MCC_TO_SCC_SWITCH_FORCE: Force switch with SAP restart
 * @QDF_MCC_TO_SCC_SWITCH_FORCE_WITHOUT_DISCONNECTION: Force switch without
 * restart of SAP
 * @QDF_MCC_TO_SCC_SWITCH_WITH_FAVORITE_CHANNEL: Switch using fav channel(s)
 * without SAP restart
 * @QDF_MCC_TO_SCC_SWITCH_FORCE_PREFERRED_WITHOUT_DISCONNECTION: Force switch
 * without SAP restart. MCC is allowed only in below exception cases:
 *	Exception Case-1: When STA is operating on DFS channel.
 *	Exception Case-2: When STA is operating on LTE-CoEx channel.
 *	Exception Case-3: When STA is operating on AP disabled channel.
 *
 * @QDF_MCC_TO_SCC_SWITCH_MAX: max switch
 */
typedef enum {
	QDF_MCC_TO_SCC_SWITCH_DISABLE = 0,
	QDF_MCC_TO_SCC_SWITCH_ENABLE,
	QDF_MCC_TO_SCC_SWITCH_FORCE,
	QDF_MCC_TO_SCC_SWITCH_FORCE_WITHOUT_DISCONNECTION,
	QDF_MCC_TO_SCC_SWITCH_WITH_FAVORITE_CHANNEL,
	QDF_MCC_TO_SCC_SWITCH_FORCE_PREFERRED_WITHOUT_DISCONNECTION,
	QDF_MCC_TO_SCC_SWITCH_MAX
} tQDF_MCC_TO_SCC_SWITCH_MODE;
#endif

#if !defined(NULL)
#ifdef __cplusplus
#define NULL   0
#else
#define NULL   ((void *)0)
#endif
#endif

/**
 * qdf_bool_parse() - parse the given string as a boolean value
 * @bool_str: the input boolean string to parse
 * @out_bool: the output boolean value, populated on success
 *
 * 1, y, Y are mapped to true, 0, n, N are mapped to false.
 * Leading/trailing whitespace is ignored.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS qdf_bool_parse(const char *bool_str, bool *out_bool);

/**
 * qdf_int32_parse() - parse the given string as a 32-bit signed integer
 * @int_str: the input integer string to parse
 * @out_int: the output integer value, populated on success
 *
 * Supports binary (0b), octal (0o), decimal (no prefix), and hexadecimal (0x)
 * encodings via typical prefix notation. Leading/trailing whitespace is
 * ignored.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS qdf_int32_parse(const char *int_str, int32_t *out_int);

/**
 * qdf_uint32_parse() - parse the given string as a 32-bit unsigned integer
 * @int_str: the input integer string to parse
 * @out_int: the output integer value, populated on success
 *
 * Supports binary (0b), octal (0o), decimal (no prefix), and hexadecimal (0x)
 * encodings via typical prefix notation. Leading/trailing whitespace is
 * ignored.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS qdf_uint32_parse(const char *int_str, uint32_t *out_int);

/**
 * qdf_int64_parse() - parse the given string as a 64-bit signed integer
 * @int_str: the input integer string to parse
 * @out_int: the output integer value, populated on success
 *
 * Supports binary (0b), octal (0o), decimal (no prefix), and hexadecimal (0x)
 * encodings via typical prefix notation. Leading/trailing whitespace is
 * ignored.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS qdf_int64_parse(const char *int_str, int64_t *out_int);

/**
 * qdf_uint64_parse() - parse the given string as a 64-bit unsigned integer
 * @int_str: the input integer string to parse
 * @out_int: the output integer value, populated on success
 *
 * Supports binary (0b), octal (0o), decimal (no prefix), and hexadecimal (0x)
 * encodings via typical prefix notation. Leading/trailing whitespace is
 * ignored.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS qdf_uint64_parse(const char *int_str, uint64_t *out_int);

#define QDF_MAC_ADDR_SIZE 6
#define QDF_MAC_ADDR_STR "%02x:%02x:%02x:%02x:%02x:%02x"
#define QDF_MAC_ADDR_ARRAY(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define QDF_MAC_ADDR_BCAST_INIT { { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff } }
#define QDF_MAC_ADDR_ZERO_INIT { { 0, 0, 0, 0, 0, 0 } }

/**
 * struct qdf_mac_addr - A MAC address
 * @bytes: the raw address bytes array
 */
struct qdf_mac_addr {
	uint8_t bytes[QDF_MAC_ADDR_SIZE];
};

/**
 * qdf_mac_parse() - parse the given string as a MAC address
 * @mac_str: the input MAC address string to parse
 * @out_addr: the output MAC address value, populated on success
 *
 * A MAC address is a set of 6, colon-delimited, hexadecimal encoded octets.
 *
 * E.g.
 *	00:00:00:00:00:00 (zero address)
 *	ff:ff:ff:ff:ff:ff (broadcast address)
 *	12:34:56:78:90:ab (an arbitrary address)
 *
 * This implementation also accepts MAC addresses without colons. Historically,
 * other delimiters and groupings have been used to represent MAC addresses, but
 * these are not supported here. Hexadecimal digits may be in either upper or
 * lower case.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS qdf_mac_parse(const char *mac_str, struct qdf_mac_addr *out_addr);

#define QDF_IPV4_ADDR_SIZE 4
#define QDF_IPV4_ADDR_STR "%d.%d.%d.%d"
#define QDF_IPV4_ADDR_ARRAY(a) (a)[0], (a)[1], (a)[2], (a)[3]
#define QDF_IPV4_ADDR_ZERO_INIT { { 0, 0, 0, 0 } }

/**
 * struct qdf_ipv4_addr - An IPV4 address
 * @bytes: the raw address bytes array
 */
struct qdf_ipv4_addr {
	uint8_t bytes[QDF_IPV4_ADDR_SIZE];
};

/**
 * qdf_ipv4_parse() - parse the given string as an IPV4 address
 * @ipv4_str: the input IPV4 address string to parse
 * @out_addr: the output IPV4 address value, populated on success
 *
 * An IPV4 address is a set of 4, dot-delimited, decimal encoded octets.
 *
 * E.g.
 *	0.0.0.0 (wildcard address)
 *	127.0.0.1 (loopback address)
 *	255.255.255.255 (broadcast address)
 *	192.168.0.1 (an arbitrary address)
 *
 * Historically, non-decimal encodings have also been used to represent IPV4
 * addresses, but these are not supported here.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS qdf_ipv4_parse(const char *ipv4_str, struct qdf_ipv4_addr *out_addr);

#define QDF_IPV6_ADDR_SIZE 16
#define QDF_IPV6_ADDR_HEXTET_COUNT 8
#define QDF_IPV6_ADDR_STR "%x:%x:%x:%x:%x:%x:%x:%x"
#define QDF_IPV6_ADDR_ARRAY(a) \
	((a)[0] << 8) + (a)[1], ((a)[2] << 8) + (a)[3], \
	((a)[4] << 8) + (a)[5], ((a)[6] << 8) + (a)[7], \
	((a)[8] << 8) + (a)[9], ((a)[10] << 8) + (a)[11], \
	((a)[12] << 8) + (a)[13], ((a)[14] << 8) + (a)[15]
#define QDF_IPV6_ADDR_ZERO_INIT \
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }

/**
 * struct qdf_ipv6_addr - An IPV6 address
 * @bytes: the raw address bytes array
 */
struct qdf_ipv6_addr {
	uint8_t bytes[QDF_IPV6_ADDR_SIZE];
};

/**
 * qdf_ipv6_parse() - parse the given string as an IPV6 address
 * @ipv6_str: the input IPV6 address string to parse
 * @out_addr: the output IPV6 address value, populated on success
 *
 * A hextet is a pair of octets. An IPV6 address is a set of 8, colon-delimited,
 * hexadecimal encoded hextets. Each hextet may omit leading zeros. One or more
 * zero-hextets may be "compressed" using a pair of colons ("::"). Up to one
 * such zero-compression is allowed per address.
 *
 * E.g.
 *	0:0:0:0:0:0:0:0 (unspecified address)
 *	:: (also the unspecified address)
 *	0:0:0:0:0:0:0:1 (loopback address)
 *	::1 (also the loopback address)
 *	900a:ae7::6 (an arbitrary address)
 *	900a:ae7:0:0:0:0:0:6 (the same arbitrary address)
 *
 * Hexadecimal digits may be in either upper or lower case.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS qdf_ipv6_parse(const char *ipv6_str, struct qdf_ipv6_addr *out_addr);

#define QDF_MAX_NUM_CHAN   (128)

/**
 * struct qdf_tso_frag_t - fragments of a single TCP segment
 * @paddr_low_32: Lower 32 bits of the buffer pointer
 * @paddr_upper_16: upper 16 bits of the buffer pointer
 * @length: length of the buffer
 * @vaddr: virtual address
 *
 * This structure holds the fragments of a single TCP segment of a
 * given jumbo TSO network buffer
 */
struct qdf_tso_frag_t {
	uint16_t length;
	unsigned char *vaddr;
	qdf_dma_addr_t paddr;
};

#define FRAG_NUM_MAX 6
#define TSO_SEG_MAGIC_COOKIE 0x1EED

/**
 * struct qdf_tso_flags_t - TSO specific flags
 * @tso_enable: Enable transmit segmentation offload
 * @tcp_flags_mask: Tcp_flag is inserted into the header based
 * on the mask
 * @l2_len: L2 length for the msdu
 * @ip_len: IP length for the msdu
 * @tcp_seq_num: TCP sequence number
 * @ip_id: IP identification number
 *
 * This structure holds the TSO specific flags extracted from the TSO network
 * buffer for a given TCP segment
 */
struct qdf_tso_flags_t {
	uint32_t tso_enable:1,
			reserved_0a:6,
			fin:1,
			syn:1,
			rst:1,
			psh:1,
			ack:1,
			urg:1,
			ece:1,
			cwr:1,
			ns:1,
			tcp_flags_mask:9,
			reserved_0b:7;

	uint32_t l2_len:16,
			ip_len:16;

	uint32_t tcp_seq_num;

	uint32_t ip_id:16,
			ipv4_checksum_en:1,
			udp_ipv4_checksum_en:1,
			udp_ipv6_checksum_en:1,
			tcp_ipv4_checksum_en:1,
			tcp_ipv6_checksum_en:1,
			partial_checksum_en:1,
			reserved_3a:10;

	uint32_t checksum_offset:14,
			reserved_4a:2,
			payload_start_offset:14,
			reserved_4b:2;

	uint32_t payload_end_offset:14,
			reserved_5:18;
};

/**
 * struct qdf_tso_seg_t - single TSO segment
 * @tso_flags: TSO flags
 * @num_frags: number of fragments
 * @total_len: total length of the packet
 * @tso_frags: array holding the fragments
 *
 * This structure holds the information of a single TSO segment of a jumbo
 * TSO network buffer
 */
struct qdf_tso_seg_t {
	struct qdf_tso_flags_t tso_flags;
	uint32_t num_frags;
	uint32_t total_len;
	struct qdf_tso_frag_t tso_frags[FRAG_NUM_MAX];
};

/**
 * TSO seg elem action caller locations: goes into dbg.history below.
 * Needed to be defined outside of the feature so that
 * callers can be coded without ifdefs (even if they get
 * resolved to nothing)
 */
enum tsoseg_dbg_caller_e {
	TSOSEG_LOC_UNDEFINED,
	TSOSEG_LOC_INIT1,
	TSOSEG_LOC_INIT2,
	TSOSEG_LOC_FREE,
	TSOSEG_LOC_ALLOC,
	TSOSEG_LOC_DEINIT,
	TSOSEG_LOC_GETINFO,
	TSOSEG_LOC_FILLHTTSEG,
	TSOSEG_LOC_FILLCMNSEG,
	TSOSEG_LOC_PREPARETSO,
	TSOSEG_LOC_TXPREPLLFAST,
	TSOSEG_LOC_UNMAPTSO,
	TSOSEG_LOC_UNMAPLAST,
	TSOSEG_LOC_FORCE_FREE,
};
#ifdef TSOSEG_DEBUG

/**
 * WARNING: Don't change the history size without changing the wrap
 *  code in qdf_tso_seg_dbg_record function
 */
#define MAX_TSO_SEG_ACT_HISTORY 16
struct qdf_tso_seg_dbg_history_t {
	uint64_t ts;
	short    id;
};
struct qdf_tso_seg_dbg_t {
	void    *txdesc;  /* owner - (ol_txrx_tx_desc_t *) */
	qdf_atomic_t cur; /* index of last valid entry */
	struct qdf_tso_seg_dbg_history_t h[MAX_TSO_SEG_ACT_HISTORY];
};
#endif /* TSOSEG_DEBUG */

/**
 * qdf_tso_seg_elem_t - tso segment element
 * @seg: instance of segment
 * @next: pointer to the next segment
 */
struct qdf_tso_seg_elem_t {
	struct qdf_tso_seg_t seg;
	uint32_t cookie:13,
		on_freelist:1,
		sent_to_target:1,
		force_free:1;
	struct qdf_tso_seg_elem_t *next;
#ifdef TSOSEG_DEBUG
	struct qdf_tso_seg_dbg_t dbg;
#endif /* TSOSEG_DEBUG */
};

/**
 * struct qdf_tso_num_seg_t - single element to count for num of seg
 * @tso_cmn_num_seg: num of seg in a jumbo skb
 *
 * This structure holds the information of num of segments of a jumbo
 * TSO network buffer.
 */
struct qdf_tso_num_seg_t {
	uint32_t tso_cmn_num_seg;
};

/**
 * qdf_tso_num_seg_elem_t - num of tso segment element for jumbo skb
 * @num_seg: instance of num of seg
 * @next: pointer to the next segment
 */
struct qdf_tso_num_seg_elem_t {
	struct qdf_tso_num_seg_t num_seg;
	struct qdf_tso_num_seg_elem_t *next;
};

/**
 * struct qdf_tso_info_t - TSO information extracted
 * @is_tso: is this is a TSO frame
 * @num_segs: number of segments
 * @tso_seg_list: list of TSO segments for this jumbo packet
 * @curr_seg: segment that is currently being processed
 * @tso_num_seg_list: num of tso seg for this jumbo packet
 * @msdu_stats_idx: msdu index for tso stats
 *
 * This structure holds the TSO information extracted after parsing the TSO
 * jumbo network buffer. It contains a chain of the TSO segments belonging to
 * the jumbo packet
 */
struct qdf_tso_info_t {
	uint8_t is_tso;
	uint32_t num_segs;
	struct qdf_tso_seg_elem_t *tso_seg_list;
	struct qdf_tso_seg_elem_t *curr_seg;
	struct qdf_tso_num_seg_elem_t *tso_num_seg_list;
	uint32_t msdu_stats_idx;
};

/**
 * Used to set classify bit in CE desc.
 */
#define QDF_CE_TX_CLASSIFY_BIT_S   5

/**
 * QDF_CE_TX_PKT_TYPE_BIT_S - 2 bits starting at bit 6 in CE desc.
 */
#define QDF_CE_TX_PKT_TYPE_BIT_S   6

/**
 * QDF_CE_TX_PKT_OFFSET_BIT_S - 12 bits --> 16-27, in the CE desciptor
 *  the length of HTT/HTC descriptor
 */
#define QDF_CE_TX_PKT_OFFSET_BIT_S  16

/**
 * QDF_CE_TX_PKT_OFFSET_BIT_M - Mask for packet offset in the CE descriptor.
 */
#define QDF_CE_TX_PKT_OFFSET_BIT_M   0x0fff0000

/**
 * enum qdf_suspend_type - type of suspend
 * @QDF_SYSTEM_SUSPEND: System suspend triggered wlan suspend
 * @QDF_RUNTIME_SUSPEND: Runtime pm inactivity timer triggered wlan suspend
 */
enum qdf_suspend_type {
	QDF_SYSTEM_SUSPEND,
	QDF_RUNTIME_SUSPEND
};

/**
 * enum qdf_hang_reason - host hang/ssr reason
 * @CDS_REASON_UNSPECIFIED: Unspecified reason
 * @CDS_RX_HASH_NO_ENTRY_FOUND: No Map for the MAC entry for the received frame
 * @CDS_PEER_DELETION_TIMEDOUT: peer deletion timeout happened
 * @CDS_PEER_UNMAP_TIMEDOUT: peer unmap timeout
 * @CDS_SCAN_REQ_EXPIRED: Scan request timed out
 * @CDS_SCAN_ATTEMPT_FAILURES: Consecutive Scan attempt failures
 * @CDS_GET_MSG_BUFF_FAILURE: Unable to get the message buffer
 * @CDS_ACTIVE_LIST_TIMEOUT: Current command processing is timedout
 * @CDS_SUSPEND_TIMEOUT: Timeout for an ACK from FW for suspend request
 * @CDS_RESUME_TIMEOUT: Timeout for an ACK from FW for resume request
 */
enum qdf_hang_reason {
	QDF_REASON_UNSPECIFIED = 0,
	QDF_RX_HASH_NO_ENTRY_FOUND = 1,
	QDF_PEER_DELETION_TIMEDOUT = 2,
	QDF_PEER_UNMAP_TIMEDOUT = 3,
	QDF_SCAN_REQ_EXPIRED = 4,
	QDF_SCAN_ATTEMPT_FAILURES = 5,
	QDF_GET_MSG_BUFF_FAILURE = 6,
	QDF_ACTIVE_LIST_TIMEOUT = 7,
	QDF_SUSPEND_TIMEOUT = 8,
	QDF_RESUME_TIMEOUT = 9,
};

/**
 * enum qdf_stats_verbosity_level - Verbosity levels for stats
 * for which want to have different levels
 * @QDF_STATS_VERBOSITY_LEVEL_LOW: Stats verbosity level low
 * @QDF_STATS_VERBOSITY_LEVEL_HIGH: Stats verbosity level high
 */
enum qdf_stats_verbosity_level {
	QDF_STATS_VERBOSITY_LEVEL_LOW,
	QDF_STATS_VERBOSITY_LEVEL_HIGH
};

/**
 * enum qdf_clock_id - The clock IDs of the various system clocks
 * @QDF_CLOCK_REALTIME: Clock is close to current time of day
 * @QDF_CLOCK_MONOTONIC: Clock is absolute elapsed time
 */
enum qdf_clock_id {
	QDF_CLOCK_REALTIME = __QDF_CLOCK_REALTIME,
	QDF_CLOCK_MONOTONIC = __QDF_CLOCK_MONOTONIC
};

/**
 * enum qdf_hrtimer_mode - Mode arguments of qdf_hrtimer_data_t
 * related functions
 * @QDF_HRTIMER_MODE_ABS: Time value is absolute
 * @QDF_HRTIMER_MODE_REL: Time value is relative to now
 * @QDF_HRTIMER_MODE_PINNED: Timer is bound to CPU
 */
enum qdf_hrtimer_mode {
	QDF_HRTIMER_MODE_ABS = __QDF_HRTIMER_MODE_ABS,
	QDF_HRTIMER_MODE_REL = __QDF_HRTIMER_MODE_REL,
	QDF_HRTIMER_MODE_PINNED =  __QDF_HRTIMER_MODE_PINNED,
};

/**
 * enum qdf_hrtimer_restart_status - Return values for the
 * qdf_hrtimer_data_t callback function
 * @QDF_HRTIMER_NORESTART: Timer is not restarted
 * @QDF_HRTIMER_RESTART: Timer must be restarted
 */
enum qdf_hrtimer_restart_status {
	QDF_HRTIMER_NORESTART = __QDF_HRTIMER_NORESTART,
	QDF_HRTIMER_RESTART = __QDF_HRTIMER_RESTART,
};

/**
 * enum qdf_context_mode - Values for the
 * hrtimer context
 * @QDF_CONTEXT_HARDWARE: Runs in hw interrupt context
 * @QDF_CONTEXT_TASKLET: Runs in tasklet context
 */
enum qdf_context_mode {
	QDF_CONTEXT_HARDWARE = 0,
	QDF_CONTEXT_TASKLET = 1,
};

#endif /* __QDF_TYPES_H */
