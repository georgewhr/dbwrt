/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#include "sw.h"
#include "sw_api.h"

#ifdef KVER26 /*Linux Kernel 2.6 */
#define __USER     __user
#else /*Linux Kernel 2.4 */
#include <asm/uaccess.h>
#define __USER
#endif /*KVER26 */

#ifdef KVER34
#include <generated/autoconf.h>
#include <linux/fs.h>
#include <linux/export.h>
#else
#include <linux/fs.h>
#include <linux/export.h>
//#include <net/sock.h>
#endif

#include <linux/kconfig.h>
#include <linux/skbuff.h>
#include <linux/miscdevice.h>
#include "api_access.h"
#include "sw_api_ks.h"
#ifdef KVER32
#include <asm/uaccess.h>
#include <linux/module.h>
#endif
#include <linux/mutex.h>

static int
switch_open(struct inode * inode,struct file * file);

static int
switch_close(struct inode * inode, struct file * file);


#ifdef KVER32      //for linux3.2
static long
switch_ioctl(struct file * file, unsigned int cmd, unsigned long arg);
#else
static long
switch_ioctl(struct inode *inode, struct file * file, unsigned int cmd, unsigned long arg);
#endif

static a_uint32_t *cmd_buf = NULL;

static struct mutex api_ioctl_lock;

static struct file_operations switch_device_fops =
{
    .owner   = THIS_MODULE,
    .read    = NULL,
    .write   = NULL,
    .poll    = NULL,
    .unlocked_ioctl= switch_ioctl,
    .open    = switch_open,
    .release = switch_close
};

static struct miscdevice switch_device =
{
    MISC_DYNAMIC_MINOR,
    "switch_ssdk",
    &switch_device_fops
};

static sw_error_t
input_parser(sw_api_param_t *p, a_uint32_t nr_param, a_uint32_t *args)
{
    a_uint32_t i = 0, buf_head = nr_param;

    for (i = 0; i < nr_param; i++)
    {
        if (p->param_type & SW_PARAM_PTR)
        {
            cmd_buf[i] = (a_uint32_t) & cmd_buf[buf_head];
            buf_head += (p->data_size + 3) / 4;

            if (buf_head > (SW_MAX_API_BUF / 4))
                return SW_NO_RESOURCE;

            if (p->param_type & SW_PARAM_IN)
            {
                if (copy_from_user((a_uint8_t*)(cmd_buf[i]), (void __USER *)args[i + 2], ((p->data_size + 3) >> 2) << 2))
                    return SW_NO_RESOURCE;
            }
        }
        else
        {
            cmd_buf[i] = args[i + 2];
        }
        p++;
    }
    return SW_OK;
}

static sw_error_t
output_parser(sw_api_param_t *p, a_uint32_t nr_param, a_uint32_t *args)
{
    a_uint32_t i =0;

    for (i = 0; i < nr_param; i++)
    {
        if (p->param_type & SW_PARAM_OUT)
        {
            if (copy_to_user
                    ((void __USER *) args[i + 2], (a_uint32_t *) cmd_buf[i], ((p->data_size + 3) >> 2) << 2))
                return SW_NO_RESOURCE;
        }
        p++;
    }

    return SW_OK;
}

static sw_error_t
sw_api_cmd(a_uint32_t * args)
{
    a_uint32_t *p = cmd_buf, api_id = args[0], nr_param = 0;
    sw_error_t(*func) (a_uint32_t, ...);
    sw_api_param_t *pp;
    sw_api_func_t *fp;
    sw_error_t rv;
    sw_api_t sw_api;

    sw_api.api_id = api_id;
    rv = sw_api_get(&sw_api);
    SW_OUT_ON_ERROR(rv);

    fp = sw_api.api_fp;
    pp = sw_api.api_pp;
    nr_param = sw_api.api_nr;

	/* Clean up cmd_buf */
	aos_mem_set(cmd_buf, 0, SW_MAX_API_BUF);
    rv = input_parser(pp, nr_param, args);
    SW_OUT_ON_ERROR(rv);
    func = fp->func;

    switch (nr_param)
    {
        case 1:
            rv = (func) (p[0]);
            break;
        case 2:
            rv = (func) (p[0], p[1]);
            break;
        case 3:
            rv = (func) (p[0], p[1], p[2]);
            break;
        case 4:
            rv = (func) (p[0], p[1], p[2], p[3]);
            break;
        case 5:
            rv = (func) (p[0], p[1], p[2], p[3], p[4]);
            break;
        case 6:
            rv = (func) (p[0], p[1], p[2], p[3], p[4], p[5]);
            break;
        case 7:
            rv = (func) (p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
            break;
        case 8:
            rv = (func) (p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
            break;
        case 9:
            rv = (func) (p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
            break;
        case 10:
            rv = (func) (p[0], p[1], p[2], p[3], p[4], p[5],
                         p[6], p[7], p[8], p[9]);
            break;
        default:
            rv = SW_OUT_OF_RANGE;
    }

    SW_OUT_ON_ERROR(rv);
    rv = output_parser(pp, nr_param, args);

out:
    return rv;
}

static int
switch_open(struct inode * inode,struct file * file)
{
    return SW_OK;
}

static int
switch_close(struct inode * inode, struct file * file)
{
    return SW_OK;
}

#ifdef KVER32
static long
switch_ioctl(struct file * file, unsigned int cmd, unsigned long arg)
#else
static long
switch_ioctl(struct inode *inode, struct file * file, unsigned int cmd, unsigned long arg)
#endif
{
    a_uint32_t args[SW_MAX_API_PARAM], rtn;
    sw_error_t rv = SW_NO_RESOURCE;

    if (copy_from_user(args, (int __user *)arg, sizeof (args)))
    {
        return SW_NO_RESOURCE;
    }

    mutex_lock(&api_ioctl_lock);
    rv = sw_api_cmd(args);
    mutex_unlock(&api_ioctl_lock);

    /* return API result to user */
    rtn = (a_uint32_t) rv;
    if (copy_to_user
            ((void __USER *) args[1], (a_uint32_t *) &rtn, sizeof (a_uint32_t)))
    {
        rv = SW_NO_RESOURCE;
    }

    return SW_OK;
}

sw_error_t
sw_uk_init(a_uint32_t nl_prot)
{
    if (!cmd_buf)
    {
        if((cmd_buf = (a_uint32_t *) aos_mem_alloc(SW_MAX_API_BUF)) == NULL)
        {
            return SW_OUT_OF_MEM;
        }

#if defined UK_MINOR_DEV
        switch_device.minor = UK_MINOR_DEV;
#else
        switch_device.minor = nl_prot;
#endif

        if (misc_register(&switch_device))
        {
            return SW_INIT_ERROR;
        }

        mutex_init(&api_ioctl_lock);
    }

    return SW_OK;
}

sw_error_t
sw_uk_cleanup(void)
{
    if (cmd_buf)
    {
        aos_mem_free(cmd_buf);
        cmd_buf = NULL;

        mutex_destroy(&api_ioctl_lock);
        misc_deregister(&switch_device);
    }

    return SW_OK;
}

