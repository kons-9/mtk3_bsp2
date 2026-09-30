/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP 2.0
 *
 *    Copyright (C) 2023-2024 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2024/02.
 *
 *----------------------------------------------------------------------
 */

/*
 *	dbgspt.h
 *
 *	micro T-Kernel Debugger Support
 */

#ifndef _MTKBSP_TK_DBGSPT_H_
#define _MTKBSP_TK_DBGSPT_H_

/*
 * BSP2 used to hide the upstream declaration header here.  Keep this
 * wrapper, but expose the actual µT-Kernel/DS API so applications can install
 * td_hok_svc(), td_hok_dsp(), and td_hok_int() hooks.
 */
#include <mtkernel/include/tk/dbgspt.h>

#endif /* _MTKBSP_TK_DBGSPT_H_ */
