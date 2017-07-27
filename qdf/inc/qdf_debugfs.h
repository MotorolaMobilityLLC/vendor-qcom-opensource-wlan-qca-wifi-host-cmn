/*
 * Copyright (c) 2017-2018 The Linux Foundation. All rights reserved.
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
 * DOC: qdf_debugfs.h
 * This file provides OS abstraction for debug filesystem APIs.
 */

#ifndef _QDF_DEBUGFS_H
#define _QDF_DEBUGFS_H

#include <qdf_status.h>
#include <i_qdf_debugfs.h>

#ifdef WLAN_DEBUGFS

/* qdf file modes */
#define QDF_FILE_USR_READ	00400
#define QDF_FILE_USR_WRITE	00200

#define QDF_FILE_GRP_READ	00040
#define QDF_FILE_GRP_WRITE	00020

#define QDF_FILE_OTH_READ	00004
#define QDF_FILE_OTH_WRITE	00002

/**
 * qdf_debugfs_init() - initialize debugfs
 *
 * Return: QDF_STATUS
 */
QDF_STATUS qdf_debugfs_init(void);

/**
 * qdf_debugfs_exit() - cleanup debugfs
 *
 * Return: QDF_STATUS
 */
QDF_STATUS qdf_debugfs_exit(void);

#else

static inline QDF_STATUS qdf_debugfs_init(void)
{
	return QDF_STATUS_E_NOSUPPORT;
}

static inline QDF_STATUS qdf_debugfs_exit(void)
{
	return QDF_STATUS_E_NOSUPPORT;
}

#endif /* WLAN_DEBUGFS */
#endif /* _QDF_DEBUGFS_H */


