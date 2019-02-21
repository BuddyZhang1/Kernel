/*
 * Virtual address
 *
 * (C) 2018.11.10 BiscuitOS <buddy.zhang@aliyun.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/head.h>
#include <linux/malloc.h>
#include <demo/debug.h>

#ifdef CONFIG_DEBUG_VA_KERN_LEG_TEXT
/*
 * Kernel .text section
 */
static int kernel_text_section_entence(void)
{
    /* first executable instruction address. */
    extern char __executable_start[];
    extern char etext[], _etext[], __etext[];

    printk("__executable_start: %#x\n", (unsigned int)__executable_start);
    printk("etext:   %#x\n_etext:  %#x\n__etext: %#x\n",
           (unsigned int)etext, (unsigned int)_etext, (unsigned int)__etext);

    return 0;
}
late_debugcall(kernel_text_section_entence);
#endif

#ifdef CONFIG_DEBUG_VA_KERN_LEG_TEXT_SECTION
typedef int (*Scall_t)(void);
/*
 * Scalls are now grouped by functionality into separate
 * subsections. Ordering inside the subsections is determined
 * by link order.
 * For backwards compatibilty, Scall() puts the call in the
 * device ini subsection.
 *
 * The 'id' arg to __define_Scall() is needed so that multiple
 * debugcalls can point at the same hander without causing duplicate-
 * symbol build errors.
 */
#define __Scall(fn,id) \
    static Scall_t __Scall_##fn##id __used \
        __attribute__((__section__(".debug"#id".priv"))) = fn;

/* Invoke function from private text section */
#define Scall(fn) \
    __asm__ ("call *%0" :: "r" (fn))

#define private_text_call(fn)     __Scall(fn,text)

/*
 * Establish a private text section, and some function defined in here. Then
 * invoke these function from outside.
 */

static int demo_private_section_invoke(void)
{
    printk("Hello BiscuitOS\n");

    return 0;
}
private_text_call(demo_private_section_invoke);

static int demo_private_section2(void)
{
    printk("Hello World\n");

    return 0;
}
private_text_call(demo_private_section2);

/*
 * Establish a private text section
 */
static int kernel_text_private_section_entence(void)
{
    /* Private text section address */
    extern char __debug_text_priv[];
    extern char __debug_etext_priv[];
    Scall_t *fn;

    printk("Private .text section: %#x -- %#x\n", 
                            (unsigned int)__debug_text_priv,
                            (unsigned int)__debug_etext_priv);

    /* Invoke function on private section */ 
    for (fn = (Scall_t *)__debug_text_priv; 
                          fn < (Scall_t *)__debug_etext_priv; fn++) {
        Scall(*fn);
    }

    return 0;
}
late_debugcall(kernel_text_private_section_entence);
#endif

#ifdef CONFIG_DEBUG_VA_KERN_LEG_DATA
static int kernel_data_section_entence(void)
{
    extern char _edata[];
    extern char _etext[];

    printk("Kernel Data section: %#x -- %#x\n", 
                          (unsigned int)_etext, (unsigned int)_edata);

    return 0;
}
late_debugcall(kernel_data_section_entence);
#endif

#ifdef CONFIG_DEBUG_VA_KERN_LEG_DATA_SECTION
/*
 * Import data into private .data segment.
 */

typedef int *Sdata_t;

#define EXPORT_DATA(data) \
    static Sdata_t __Sdata_##data __used \
        __attribute__((__section__(".debugdata.priv"))) = \
                                            (Sdata_t)&data;

#define Sdata(data) \
                 *((Sdata_t)data)

static int private_data = 0x20;
EXPORT_DATA(private_data);

static int private_datb = 0x89;
EXPORT_DATA(private_datb);

static int kernel_data_private_section_entence(void)
{
    extern char __debug_data_priv[];
    extern char __debug_edata_priv[];
    Sdata_t data;

    printk("Private .data section: %#x -- %#x\n",
                          (unsigned int)__debug_data_priv,
                          (unsigned int)__debug_edata_priv);

    for (data = (Sdata_t)__debug_data_priv; 
                             data < (Sdata_t)__debug_edata_priv; data++)
        printk("Data: %#x\n", Sdata(*data));
    

    return 0;
}
late_debugcall(kernel_data_private_section_entence);
#endif

#ifdef CONFIG_DEBUG_VA_KERN_LEG_BSS
static int kernel_bss_section_entence(void)
{
    extern char _edata[];
    extern char end[];

    printk("Kernel .bss section: %#x - %#x\n",
                              (unsigned int)_edata, (unsigned int)end);

    return 0;
}
late_debugcall(kernel_bss_section_entence);
#endif

#ifdef CONFIG_DEBUG_VA_KERN_LEG_STACK
/*
 * Kernel stack.
 */
static int kernel_stack_section_entence(void)
{
    unsigned short SS;
    unsigned long base;
    struct desc_struct *desc;

    __asm__ ("mov %%ss, %0" : "=m" (SS));

    /* Obtain Stack segment descriptor */
    if ((SS >> 2) & 0x1)
        desc = current->ldt + (SS >> 3);
    else
        desc = gdt + (SS >> 3);

    base = get_base(*desc);
    printk("Stack segment base: %#lx ESP: %#x\n", base, (unsigned int)&base);

    return 0;
}
late_debugcall(kernel_stack_section_entence);
#endif

#ifdef CONFIG_DEBUG_VA_KERN_LEG_KMALLOC
static int kernel_kmalloc_section_entence(void)
{
    unsigned long *kmalloc_data = NULL;

    kmalloc_data = 
              (unsigned long *)kmalloc(sizeof(unsigned long), GFP_KERNEL);

    printk("Kmallo data: %#x\n", (unsigned int)kmalloc_data);

    kfree(kmalloc_data);

    return 0;
}
late_debugcall(kernel_kmalloc_section_entence);
#endif

#ifdef CONFIG_DEBUG_VA_KERN_LEG_VMALLOC
static int kernel_vmalloc_section_entence(void)
{
    unsigned long *vmalloc_data = NULL;

    vmalloc_data = vmalloc(PAGE_SIZE);

    printk("Vmalloc data: %#x\n", (unsigned int)vmalloc_data);

    vfree(vmalloc_data);

    return 0;
}
late_debugcall(kernel_vmalloc_section_entence);
#endif
