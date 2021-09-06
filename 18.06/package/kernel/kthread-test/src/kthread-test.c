/* 
 * kernel module helper for testing kthread 
 * 
 * Licensed under GPLv2 or later. 
 */

#define DEBUG

#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

static struct device *kthread_dev;
static struct task_struct *kthd_test;
static unsigned int glb_counter = 0;

#ifndef SLEEP_MILLI_SEC  
#define SLEEP_MILLI_SEC(nMilliSec)\
    do { \
        long timeout = (nMilliSec) * HZ /1000;\
        while (timeout > 0)\
        {\
            timeout = schedule_timeout(timeout);\
        }\
    }while (0);  
#endif 

/*
 cat /dev/kthread_test 
*/
static ssize_t
kthread_test_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    int ret = 0;
    printk(KERN_INFO "ktest thread read %u\n", count);
    ret = copy_to_user(buf, &glb_counter, sizeof(glb_counter));

    return ret;
}

/* 
 * echo 0 > /dev/kthread_test 
 */
static ssize_t
kthread_test_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    glb_counter = 0;
    printk(KERN_INFO "ktest thread write %u\n", count);
    return count;
}

static int ktest_thread(void *arg)
{
    while(1) {
        set_current_state(TASK_INTERRUPTIBLE);
        if(kthread_should_stop())
            break;

        glb_counter++;
        SLEEP_MILLI_SEC(5000);
        //msleep(5000);
        //mdelay(10);
        //printk(KERN_INFO "ktest thread run %u\n", glb_counter);
    }

    return 0;
}

static int __init ktest_thread_init(void)
{
	kthd_test = kthread_create(ktest_thread, NULL, "kthd_test");
	if (IS_ERR(kthd_test))
	{
		printk(KERN_EMERG "Create ktest thread fail\n");
		return PTR_ERR(kthd_test);
	}
	wake_up_process(kthd_test);

    printk(KERN_INFO "ktest thread init and start\n");
	
    return 0;
}

static void __exit ktest_thread_exit(void)
{
	kthread_stop(kthd_test);
    printk(KERN_INFO "ktest thread exit\n");
	return;
}

static const struct file_operations kthread_test_fops = {
    .owner = THIS_MODULE,
    .read = kthread_test_read,
    .write = kthread_test_write,
};

static struct miscdevice kthread_test_misc = {
    .name = "kthread_test",
    .fops = &kthread_test_fops,
};

static int __init kthread_test_init(void)
{
    int ret = 0;
    ret = misc_register(&kthread_test_misc);
    if (unlikely(ret)) {
        pr_err("failed to register kthread test misc device!\n");
        return ret;
    }

    kthread_dev = kthread_test_misc.this_device;

    _dev_info(kthread_dev, "registered.\n");

    ktest_thread_init();

    return ret;
}

static void __exit kthread_test_exit(void)
{
    misc_deregister(&kthread_test_misc);
    ktest_thread_exit();
}

module_init(kthread_test_init);
module_exit(kthread_test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wind");
MODULE_DESCRIPTION("kernel module to help the test of kthread");
MODULE_ALIAS("kthread test");
