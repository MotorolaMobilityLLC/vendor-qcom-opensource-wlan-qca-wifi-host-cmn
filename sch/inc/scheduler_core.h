/*
 * Copyright (c) 2014-2016 The Linux Foundation. All rights reserved.
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
#if !defined(__SCHEDULER_CORE_H)
#define __SCHEDULER_CORE_H

#include <qdf_threads.h>
#include <scheduler_api.h>
#include <qdf_list.h>

#define SCHEDULER_CORE_MAX_MESSAGES 8000
#define SCHEDULER_NUMBER_OF_MSG_QUEUE 5

/**
 * QDF Message queue definition.
 */
struct scheduler_mq_type {
	qdf_spinlock_t mq_lock;
	qdf_list_t mq_list;
	QDF_MODULE_ID qid;
};

struct scheduler_msg_wrapper {
	/* Message node */
	qdf_list_node_t msg_node;
	/* message it is associated to */
	struct scheduler_msg *msg_buf;
};

struct scheduler_mq_ctx {
	/* Messages buffers */
	struct scheduler_msg msg_buffers[SCHEDULER_CORE_MAX_MESSAGES];
	struct scheduler_msg_wrapper msg_wrappers[SCHEDULER_CORE_MAX_MESSAGES];
	struct scheduler_mq_type free_msg_q;
	struct scheduler_mq_type sch_msg_q[SCHEDULER_NUMBER_OF_MSG_QUEUE];
	uint8_t scheduler_msg_qid_to_qidx[QDF_MODULE_ID_MAX];
	QDF_STATUS (*scheduler_msg_process_fn[SCHEDULER_NUMBER_OF_MSG_QUEUE])
					(struct scheduler_msg *msg);
};

struct scheduler_ctx {
	struct scheduler_mq_ctx queue_ctx;
	/* Handle of Event for MC thread to signal startup */
	qdf_event_t sch_start_event;
	qdf_thread_t *sch_thread;
	/* completion object for MC thread shutdown */
	qdf_event_t sch_shutdown;
	/* Wait queue for MC thread */
	qdf_wait_queue_head_t sch_wait_queue;
	unsigned long sch_event_flag;
	/* Completion object to resume Mc thread */
	qdf_event_t resume_sch_event;
	/* lock to make sure that McThread suspend/resume mechanism is insync */
	qdf_spinlock_t sch_thread_lock;
	uint8_t sch_last_qidx;
	hdd_suspend_callback hdd_callback;
	scheduler_msg_process_fn_t legacy_wma_handler;
	scheduler_msg_process_fn_t legacy_sys_handler;
};


/**
 * scheduler_get_context() - to get scheduler context
 *
 * This routine is used retrieve scheduler context
 *
 * Return: Pointer to scheduler context
 */
struct scheduler_ctx *scheduler_get_context(void);
/**
 * scheduler_thread() - spawned thread will execute this routine
 * @arg: pointer to scheduler context
 *
 * Newly created thread will use this routine to perform its duty
 *
 * Return: none
 */
int scheduler_thread(void *arg);

/**
 * scheduler_cleanup_queues() - to clean up the given module's queue
 * @sch_ctx: pointer to scheduler context
 * @idx: index of the queue which needs to be cleanup.
 *
 * This routine  is used to clean the module's queue provided by
 * user through idx field
 *
 * Return: none
 */
void scheduler_cleanup_queues(struct scheduler_ctx *sch_ctx, int idx);
/**
 * scheduler_create_ctx() - to create scheduler context
 *
 * This routine is used to create scheduler context
 *
 * Return: QDF_STATUS based on success or failure
 */
QDF_STATUS scheduler_create_ctx(void);
/**
 * scheduler_destroy_ctx() - to destroy scheduler context
 *
 * This routine is used to destroy scheduler context
 *
 * Return: QDF_STATUS based on success or failure
 */
QDF_STATUS scheduler_destroy_ctx(void);
/**
 * scheduler_mq_init() - initialize scheduler message queue
 * @msg_q: Pointer to the message queue
 *
 * This function initializes the Message queue.
 *
 * Return: qdf status
 */
QDF_STATUS scheduler_mq_init(struct scheduler_mq_type *msg_q);
/**
 * scheduler_mq_deinit() - de-initialize scheduler message queue
 * @msg_q: Pointer to the message queue
 *
 * This function de-initializes scheduler message queue
 *
 *  Return: none
 */
void scheduler_mq_deinit(struct scheduler_mq_type *msg_q);
/**
 * scheduler_mq_put() - put message in the back of queue
 * @msg_q: Pointer to the message queue
 * @msg_wrapper: pointer to message wrapper
 *
 * This function is used to put message in back of provided message
 * queue
 *
 *  Return: none
 */
void scheduler_mq_put(struct scheduler_mq_type *msg_q,
			struct scheduler_msg_wrapper *msg_wrapper);
/**
 * scheduler_mq_put_front() - put message in the front of queue
 * @msg_q: Pointer to the message queue
 * @msg_wrapper: pointer to message wrapper
 *
 * This function is used to put message in front of provided message
 * queue
 *
 *  Return: none
 */
void scheduler_mq_put_front(struct scheduler_mq_type *msg_q,
			struct scheduler_msg_wrapper *msg_wrapper);
/**
 * scheduler_mq_get() - to get message from message queue
 * @msg_q: Pointer to the message queue
 *
 * This function is used to get message from given message queue
 *
 *  Return: none
 */
struct scheduler_msg_wrapper *scheduler_mq_get(struct scheduler_mq_type *msg_q);
/**
 * scheduler_is_mq_empty() - to check if message queue is empty
 * @msg_q: Pointer to the message queue
 *
 * This function is used to check if message queue is empty
 *
 * Return: true or false
 */
bool scheduler_is_mq_empty(struct scheduler_mq_type *msg_q);
/**
 * scheduler_queues_init() - to initialize all the modules' queues
 * @sched_ctx: pointer to scheduler context
 *
 * This function is used to initialize the queues for all the modules
 *
 * Return: QDF_STATUS based on success of failure
 */
QDF_STATUS scheduler_queues_init(struct scheduler_ctx *sched_ctx);
/**
 * scheduler_queues_deinit() - to de-initialize all the modules' queues
 * @sched_ctx: pointer to scheduler context
 *
 * This function is used to de-initialize the queues for all the modules
 *
 * Return: QDF_STATUS based on success of failure
 */
QDF_STATUS scheduler_queues_deinit(struct scheduler_ctx *gp_sch_ctx);
#endif
