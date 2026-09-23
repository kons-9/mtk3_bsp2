/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP 2.0
 *
 *    Copyright (C) 2025 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2025/03.
 *
 *----------------------------------------------------------------------
 */

#include <sys/machine.h>
#if defined(MTKBSP_STM32CUBE) && defined(MTKBSP_CPU_CORE_ARMV8M)
/*
 *	exc_hdr.c (ARMv8-M)
 *	Exception handler
 */

#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include <kernel.h>
#include "sysdepend.h"
#include "cpu_status.h"

#if (USE_EXCEPTION_DBG_MSG && USE_TMONITOR)
	#define EXCEPTION_DBG_MSG(a)	tm_putstring((UB*)a)
#else
	#define EXCEPTION_DBG_MSG(a)
#endif

#if (USE_EXCEPTION_DBG_MSG && USE_TMONITOR)
static void knl_dump_fault(const char *name)
{
	_UW icsr = *(_UW *)0xE000ED04U;
	_UW vtor = *(_UW *)0xE000ED08U;
	_UW cfsr = *(_UW *)SCB_CFSR;
	_UW hfsr = *(_UW *)SCB_HFSR;
	_UW shcsr = *(_UW *)0xE000ED24U;
	_UW mmfar = *(_UW *)0xE000ED34U;
	_UW bfar = *(_UW *)0xE000ED38U;
	_UW ccr = *(_UW *)0xE000ED14U;

	tm_printf((UB *)"*** %s *** ICSR:%x VTOR:%x SHCSR:%x CFSR:%x HFSR:%x MMFAR:%x BFAR:%x CCR:%x\n",
			  name, icsr, vtor, shcsr, cfsr, hfsr, mmfar, bfar, ccr);
}
#endif

/*
 * NMI handler
 */
WEAK_FUNC EXPORT void knl_nmi_handler(void)
{
	EXCEPTION_DBG_MSG("NMI\n");
	while(1);
}

/*
 * Hard fault handler
 */
//WEAK_FUNC EXPORT void knl_hardfault_handler(void)
void knl_hardfault_handler(void)
{
#if (USE_EXCEPTION_DBG_MSG  && USE_TMONITOR)

	ID	ctskid;

	if(knl_ctxtsk != NULL) {
		ctskid = knl_ctxtsk->tskid;
	} else {
		ctskid = 0;
	}

	tm_printf((UB*)"*** Hard fault *** ctxtsk:%d\n", ctskid);
	knl_dump_fault("Hard fault");
#endif
	while(1);
}

/*
 * MPU Fault Handler
 */
WEAK_FUNC EXPORT void knl_memmanage_handler(void)
{
	#if (USE_EXCEPTION_DBG_MSG && USE_TMONITOR)
	knl_dump_fault("MPU Fault");
	#endif
	EXCEPTION_DBG_MSG("MPU Fault\n");
	while(1);
}

/* 
 * Bus Fault Handler
 */
WEAK_FUNC EXPORT void knl_busfault_handler(void)
{
	#if (USE_EXCEPTION_DBG_MSG && USE_TMONITOR)
	knl_dump_fault("Bus Fault");
	#endif
	EXCEPTION_DBG_MSG("Bus Fault\n");
	while(1);
}

/*
 * Usage Fault Handler
 */
//WEAK_FUNC EXPORT void knl_usagefault_handler(void)
EXPORT void knl_usagefault_handler(void)
{
	#if (USE_EXCEPTION_DBG_MSG && USE_TMONITOR)
	knl_dump_fault("Usage Fault");
	#endif
	EXCEPTION_DBG_MSG("Usage Fault\n");
	while(1);
}

/*
 * Svcall
 */
WEAK_FUNC EXPORT void knl_svcall_handler(void)
{
	EXCEPTION_DBG_MSG("SVCall\n");
	while(1);
}

/* 
 * Debug Monitor
 */
WEAK_FUNC EXPORT void knl_debugmon_handler(void)
{
	EXCEPTION_DBG_MSG("Debug Monitor\n");
	while(1);
}

/*
 * Default Handler
 */
WEAK_FUNC EXPORT void knl_default_handler(void)
{
#if (USE_EXCEPTION_DBG_MSG  && USE_TMONITOR)
	INT	i;
	_UW	*icpr;

	icpr = (_UW*)NVIC_ICPR_BASE;

	EXCEPTION_DBG_MSG("Undefine Exceptio ICPR: ");
	for(i=0; i < 8; i++) {
		tm_printf((UB*)"%x ", *icpr++);
	}
	EXCEPTION_DBG_MSG("\n");
#endif
	while(1);
}

#endif /* defined(MTKBSP_STM32CUBE) && defined(MTKBSP_CPU_CORE_ARMV8M) */
