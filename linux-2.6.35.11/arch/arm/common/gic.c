/*
 *  linux/arch/arm/common/gic.c
 *
 *  Copyright (C) 2002 ARM Limited, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Interrupt architecture for the GIC:
 *
 * o There is one Interrupt Distributor, which receives interrupts
 *   from system devices and sends them to the Interrupt Controllers.
 *
 * o There is one CPU Interface per CPU, which sends interrupts sent
 *   by the Distributor, and interrupts generated locally, to the
 *   associated CPU. The base address of the CPU interface is usually
 *   aliased so that the same address points to different chips depending
 *   on the CPU it is accessed from.
 *
 * Note that IRQs 0-31 are special - they are local to each CPU.
 * As such, the enable set/clear, pending set/clear and active bit
 * registers are banked per-cpu for these sources.
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/smp.h>
#include <linux/cpumask.h>
#include <linux/io.h>

#include <asm/irq.h>

#ifdef CONFIG_MSTAR_AMBER3
#include "chip_int.h"
#endif

#include <asm/mach/irq.h>
#include <asm/hardware/gic.h>

static DEFINE_SPINLOCK(irq_controller_lock);

struct gic_chip_data {
	unsigned int irq_offset;
	void __iomem *dist_base;
	void __iomem *cpu_base;
};

#ifndef MAX_GIC_NR
#define MAX_GIC_NR	1
#endif

static struct gic_chip_data gic_data[MAX_GIC_NR];

static inline void __iomem *gic_dist_base(unsigned int irq)
{
	struct gic_chip_data *gic_data = get_irq_chip_data(irq);
	return gic_data->dist_base;
}

static inline void __iomem *gic_cpu_base(unsigned int irq)
{
	struct gic_chip_data *gic_data = get_irq_chip_data(irq);
	return gic_data->cpu_base;
}

static inline unsigned int gic_irq(unsigned int irq)
{
	struct gic_chip_data *gic_data = get_irq_chip_data(irq);
	return irq - gic_data->irq_offset;
}

/*
 * Routines to acknowledge, disable and enable interrupts
 *
 * Linux assumes that when we're done with an interrupt we need to
 * unmask it, in the same way we need to unmask an interrupt when
 * we first enable it.
 *
 * The GIC has a separate notion of "end of interrupt" to re-enable
 * an interrupt after handling, in order to support hardware
 * prioritisation.
 *
 * We can make the GIC behave in the way that Linux expects by making
 * our "acknowledge" routine disable the interrupt, then mark it as
 * complete.
 */

#ifdef CONFIG_MSTAR_AGATE  
extern void agate_irq_ack(unsigned int irq);
extern void agate_irq_mask(unsigned int irq);
extern void agate_irq_unmask(unsigned int irq);
#elif defined(CONFIG_MSTAR_AMBER3)
extern void amber3_irq_ack(unsigned int irq);
extern void amber3_irq_mask(unsigned int irq);
extern void amber3_irq_unmask(unsigned int irq);
#endif
            
static void gic_ack_irq(unsigned int irq)
{
#if defined(CONFIG_MSTAR_AGATE) || defined(CONFIG_MSTAR_AMBER3)
	if(irq < 128 )
	{
		u32 mask = 1 << (irq % 32);
		spin_lock(&irq_controller_lock);
		writel(mask, gic_dist_base(irq) + GIC_DIST_ENABLE_CLEAR + (gic_irq(irq) / 32) * 4);
		writel(gic_irq(irq), gic_cpu_base(irq) + GIC_CPU_EOI);
		spin_unlock(&irq_controller_lock);
	}
	else
	{
		//handle MSTAR IRQ controler signal to GIC		
		spin_lock(&irq_controller_lock);
		#ifdef CONFIG_MSTAR_AGATE  
		//handle MSTAR IRQ controler 
		agate_irq_ack( irq - MSTAR_INT_BASE);
		#elif defined(CONFIG_MSTAR_AMBER3)
		//handle MSTAR IRQ controler 
		amber3_irq_ack( irq - MSTAR_INT_BASE);
		#endif		
		writel(gic_irq(INT_PPI_IRQ), gic_cpu_base(INT_PPI_IRQ) + GIC_CPU_EOI);
		spin_unlock(&irq_controller_lock);

	}
#else
	u32 mask = 1 << (irq % 32);

	spin_lock(&irq_controller_lock);
	writel(mask, gic_dist_base(irq) + GIC_DIST_ENABLE_CLEAR + (gic_irq(irq) / 32) * 4);
	writel(gic_irq(irq), gic_cpu_base(irq) + GIC_CPU_EOI);
	spin_unlock(&irq_controller_lock);
#endif
}

static void gic_mask_irq(unsigned int irq)
{
#if defined(CONFIG_MSTAR_AGATE) || defined(CONFIG_MSTAR_AMBER3)
	if(irq < 128 )
	{
		u32 mask = 1 << (irq % 32);

		spin_lock(&irq_controller_lock);
		writel(mask, gic_dist_base(irq) + GIC_DIST_ENABLE_CLEAR + (gic_irq(irq) / 32) * 4);
		spin_unlock(&irq_controller_lock);
	}
	else
	{
		spin_lock(&irq_controller_lock);
		#ifdef CONFIG_MSTAR_AGATE  
		//handle MSTAR IRQ controler 
		agate_irq_mask(irq - MSTAR_INT_BASE);
		#elif defined(CONFIG_MSTAR_AMBER3)
		//handle MSTAR IRQ controler 
		amber3_irq_mask( irq - MSTAR_INT_BASE);
		#endif
		spin_unlock(&irq_controller_lock);
	}  
#else
	u32 mask = 1 << (irq % 32);

	spin_lock(&irq_controller_lock);
	writel(mask, gic_dist_base(irq) + GIC_DIST_ENABLE_CLEAR + (gic_irq(irq) / 32) * 4);
	spin_unlock(&irq_controller_lock);
#endif
}

#if defined(CONFIG_MSTAR_AGATE) || defined(CONFIG_MSTAR_AMBER3)
static void gic_disable_irq(unsigned int irq)
{
	if(irq < 128 )
	{
		u32 mask = 1 << (irq % 32);

		spin_lock(&irq_controller_lock);
		writel(mask, gic_dist_base(irq) + GIC_DIST_ENABLE_CLEAR + (gic_irq(irq) / 32) * 4);
		spin_unlock(&irq_controller_lock);
	}
	else
	{		
		spin_lock(&irq_controller_lock);
		#ifdef CONFIG_MSTAR_AGATE  
		//handle MSTAR IRQ controler 
		agate_irq_mask(irq - MSTAR_INT_BASE);
		#elif defined(CONFIG_MSTAR_AMBER3)
		//handle MSTAR IRQ controler 
		amber3_irq_mask( irq - MSTAR_INT_BASE);
		#endif
		spin_unlock(&irq_controller_lock);


	}  
}
#endif

static void gic_unmask_irq(unsigned int irq)
{
#if defined(CONFIG_MSTAR_AGATE) || defined(CONFIG_MSTAR_AMBER3)
	if(irq < 128 )
	{
		u32 mask = 1 << (irq % 32);
		spin_lock(&irq_controller_lock);
		writel(mask, gic_dist_base(irq) + GIC_DIST_ENABLE_SET + (gic_irq(irq) / 32) * 4);
		spin_unlock(&irq_controller_lock);
	}
	else
	{
		spin_lock(&irq_controller_lock);
		#ifdef CONFIG_MSTAR_AGATE  
		agate_irq_unmask(irq - MSTAR_INT_BASE);
		#elif defined(CONFIG_MSTAR_AMBER3)
		//handle MSTAR IRQ controler 
		amber3_irq_unmask( irq - MSTAR_INT_BASE);
		#endif
		spin_unlock(&irq_controller_lock);
		//handle MSTAR IRQ controler 

	}
#else
	u32 mask = 1 << (irq % 32);

	spin_lock(&irq_controller_lock);
	writel(mask, gic_dist_base(irq) + GIC_DIST_ENABLE_SET + (gic_irq(irq) / 32) * 4);
	spin_unlock(&irq_controller_lock);
#endif
}

#if defined(CONFIG_MSTAR_AGATE) || defined(CONFIG_MSTAR_AMBER3)
static void gic_enable_irq(unsigned int irq)
{
	if(irq < 128 )
	{
		u32 mask = 1 << (irq % 32);
		spin_lock(&irq_controller_lock);
		writel(mask, gic_dist_base(irq) + GIC_DIST_ENABLE_SET + (gic_irq(irq) / 32) * 4);
		spin_unlock(&irq_controller_lock);
	}
	else
	{
		spin_lock(&irq_controller_lock);
		#ifdef CONFIG_MSTAR_AGATE  
		agate_irq_unmask(irq - MSTAR_INT_BASE);
		#elif defined(CONFIG_MSTAR_AMBER3)
		//handle MSTAR IRQ controler 
		amber3_irq_unmask( irq - MSTAR_INT_BASE);
		#endif
		spin_unlock(&irq_controller_lock);
		//handle MSTAR IRQ controler 

	}

}
#endif

static int gic_set_type(unsigned int irq, unsigned int type)
{
	void __iomem *base = gic_dist_base(irq);
	unsigned int gicirq = gic_irq(irq);
	u32 enablemask = 1 << (gicirq % 32);
	u32 enableoff = (gicirq / 32) * 4;
	u32 confmask = 0x2 << ((gicirq % 16) * 2);
	u32 confoff = (gicirq / 16) * 4;
	bool enabled = false;
	u32 val;

	/* Interrupt configuration for SGIs can't be changed */
	if (gicirq < 16)
		return -EINVAL;

	if (type != IRQ_TYPE_LEVEL_HIGH && type != IRQ_TYPE_EDGE_RISING)
		return -EINVAL;

	spin_lock(&irq_controller_lock);

	val = readl(base + GIC_DIST_CONFIG + confoff);
	if (type == IRQ_TYPE_LEVEL_HIGH)
		val &= ~confmask;
	else if (type == IRQ_TYPE_EDGE_RISING)
		val |= confmask;

	/*
	 * As recommended by the spec, disable the interrupt before changing
	 * the configuration
	 */
	if (readl(base + GIC_DIST_ENABLE_SET + enableoff) & enablemask) {
		writel(enablemask, base + GIC_DIST_ENABLE_CLEAR + enableoff);
		enabled = true;
	}

	writel(val, base + GIC_DIST_CONFIG + confoff);

	if (enabled)
		writel(enablemask, base + GIC_DIST_ENABLE_SET + enableoff);

	spin_unlock(&irq_controller_lock);

//	if ((type & IRQ_TYPE_EDGE_RISING) && gicirq > 31)
//	 __set_irq_handler_unlocked(irq, handle_edge_irq);

	return 0;
}

#ifdef CONFIG_SMP
static int gic_set_cpu(unsigned int irq, const struct cpumask *mask_val)
{
	void __iomem *reg = gic_dist_base(irq) + GIC_DIST_TARGET + (gic_irq(irq) & ~3);
	unsigned int shift = (irq % 4) * 8;
	unsigned int cpu = cpumask_first(mask_val);
	u32 val;
#if defined(CONFIG_MSTAR_AGATE) || defined(CONFIG_MSTAR_AMBER3)
        spin_lock(&irq_controller_lock);
	irq_desc[irq].node = cpu;
#else
	struct irq_desc *desc;

	spin_lock(&irq_controller_lock);
	desc = irq_to_desc(irq);
	if (desc == NULL) {
		spin_unlock(&irq_controller_lock);
		return -EINVAL;
	}
	desc->node = cpu;
#endif
	val = readl(reg) & ~(0xff << shift);
	val |= 1 << (cpu + shift);
	writel(val, reg);
	spin_unlock(&irq_controller_lock);

	return 0;
}
#endif

static void gic_handle_cascade_irq(unsigned int irq, struct irq_desc *desc)
{
	struct gic_chip_data *chip_data = get_irq_data(irq);
	struct irq_chip *chip = get_irq_chip(irq);
	unsigned int cascade_irq, gic_irq;
	unsigned long status;

	/* primary controller ack'ing */
	chip->ack(irq);

	spin_lock(&irq_controller_lock);
	status = readl(chip_data->cpu_base + GIC_CPU_INTACK);
	spin_unlock(&irq_controller_lock);

	gic_irq = (status & 0x3ff);
	if (gic_irq == 1023)
		goto out;

	cascade_irq = gic_irq + chip_data->irq_offset;
	if (unlikely(gic_irq < 32 || gic_irq > 1020 || cascade_irq >= NR_IRQS))
		do_bad_IRQ(cascade_irq, desc);
	else
		generic_handle_irq(cascade_irq);

 out:
	/* primary controller unmasking */
	chip->unmask(irq);
}

static struct irq_chip gic_chip = {
	.name		= "GIC",
	.ack		= gic_ack_irq,
	.mask		= gic_mask_irq,
	.unmask		= gic_unmask_irq,
#if defined(CONFIG_MSTAR_AGATE) || defined(CONFIG_MSTAR_AMBER3)
        .enable         = gic_enable_irq,
        .disable        = gic_disable_irq,
#endif
	.set_type	= gic_set_type,
#ifdef CONFIG_SMP
	.set_affinity	= gic_set_cpu,
#endif
};

void __init gic_cascade_irq(unsigned int gic_nr, unsigned int irq)
{
	if (gic_nr >= MAX_GIC_NR)
		BUG();
	if (set_irq_data(irq, &gic_data[gic_nr]) != 0)
		BUG();
	set_irq_chained_handler(irq, gic_handle_cascade_irq);
}

void __init gic_dist_init(unsigned int gic_nr, void __iomem *base,
			  unsigned int irq_start)
{
	unsigned int gic_irqs, irq_limit, i;
	u32 cpumask = 1 << smp_processor_id();

	if (gic_nr >= MAX_GIC_NR)
		BUG();

	cpumask |= cpumask << 8;
	cpumask |= cpumask << 16;

	gic_data[gic_nr].dist_base = base;
	gic_data[gic_nr].irq_offset = (irq_start - 1) & ~31;

	writel(0, base + GIC_DIST_CTRL);

	/*
	 * Find out how many interrupts are supported.
	 * The GIC only supports up to 1020 interrupt sources.
	 */
#if defined(CONFIG_MSTAR_AGATE) || defined(CONFIG_MSTAR_AMBER3)
        gic_irqs=256;
#else
	gic_irqs = readl(base + GIC_DIST_CTR) & 0x1f;
	gic_irqs = (gic_irqs + 1) * 32;
	if (gic_irqs > 1020)
		gic_irqs = 1020;
#endif
	/*
	 * Set all global interrupts to be level triggered, active low.
	 */
	for (i = 32; i < gic_irqs; i += 16)
		writel(0, base + GIC_DIST_CONFIG + i * 4 / 16);

	/*
	 * Set all global interrupts to this CPU only.
	 */
	for (i = 32; i < gic_irqs; i += 4)
		writel(cpumask, base + GIC_DIST_TARGET + i * 4 / 4);

	/*
	 * Set priority on all global interrupts.
	 */
	for (i = 32; i < gic_irqs; i += 4)
		writel(0xa0a0a0a0, base + GIC_DIST_PRI + i * 4 / 4);

	/*
	 * Disable all interrupts.  Leave the PPI and SGIs alone
	 * as these enables are banked registers.
	 */
	for (i = 32; i < gic_irqs; i += 32)
		writel(0xffffffff, base + GIC_DIST_ENABLE_CLEAR + i * 4 / 32);

	/*
	 * Limit number of interrupts registered to the platform maximum
	 */
	irq_limit = gic_data[gic_nr].irq_offset + gic_irqs;
	if (WARN_ON(irq_limit > NR_IRQS))
		irq_limit = NR_IRQS;

	/*
	 * Setup the Linux IRQ subsystem.
	 */
	for (i = irq_start; i < irq_limit; i++) {
		set_irq_chip(i, &gic_chip);
		set_irq_chip_data(i, &gic_data[gic_nr]);
		set_irq_handler(i, handle_level_irq);
		set_irq_flags(i, IRQF_VALID | IRQF_PROBE);
	}

	writel(1, base + GIC_DIST_CTRL);
}

void __cpuinit gic_cpu_init(unsigned int gic_nr, void __iomem *base)
{
	void __iomem *dist_base;
	int i;

	if (gic_nr >= MAX_GIC_NR)
		BUG();

	dist_base = gic_data[gic_nr].dist_base;
	BUG_ON(!dist_base);

	gic_data[gic_nr].cpu_base = base;

	/*
	 * Deal with the banked PPI and SGI interrupts - disable all
	 * PPI interrupts, ensure all SGI interrupts are enabled.
	 */
	writel(0xffff0000, dist_base + GIC_DIST_ENABLE_CLEAR);
	writel(0x0000ffff, dist_base + GIC_DIST_ENABLE_SET);

	/*
	 * Set priority on PPI and SGI interrupts
	 */
	for (i = 0; i < 32; i += 4)
		writel(0xa0a0a0a0, dist_base + GIC_DIST_PRI + i * 4 / 4);

	writel(0xf0, base + GIC_CPU_PRIMASK);
	writel(1, base + GIC_CPU_CTRL);
}

#ifdef CONFIG_SMP
void gic_raise_softirq(const struct cpumask *mask, unsigned int irq)
{
	unsigned long map = *cpus_addr(*mask);

	/* this always happens on GIC0 */
	writel(map << 16 | irq, gic_data[0].dist_base + GIC_DIST_SOFTINT);
}
#endif