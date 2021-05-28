/* 

 * kernel module helper for testing CMA 

 * 

 * Licensed under GPLv2 or later. 

 */

#define DEBUG

#include <linux/module.h>

#include <linux/device.h>

#include <linux/fs.h>

#include <linux/miscdevice.h>

#include <linux/dma-mapping.h>


#define CMA_NUM 10

static struct device *cma_dev;

static dma_addr_t dma_phys[CMA_NUM];

static void *dma_virt[CMA_NUM];

/* any read request will free coherent memory, eg. 

 * cat /dev/cma_test 

 */

static ssize_t

cma_test_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)

{

    int i;

    for (i = 0; i < CMA_NUM; i++)
    {

        if (dma_virt[i])
        {

            dma_free_coherent(cma_dev, (i + 1) * SZ_1M, dma_virt[i], dma_phys[i]);

            _dev_info(cma_dev, "free virt: %p phys: %p\n", dma_virt[i], (void *)dma_phys[i]);

            dma_virt[i] = NULL;

            break;
        }
    }

    return 0;
}

/* 

 * any write request will alloc coherent memory, eg. 

 * echo 0 > /dev/cma_test 

 */

static ssize_t

cma_test_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)

{

    int i;

    int ret;

    unsigned int ctc = 0;

    for (i = 0; i < CMA_NUM; i++)
    {

        if (!dma_virt[i])
        {

            dma_virt[i] = dma_alloc_coherent(cma_dev, (i + 1) * SZ_1M, &dma_phys[i], GFP_KERNEL);

            if (dma_virt[i])
            {

                void *p;

                /* touch every page in the allocated memory */

                for (p = dma_virt[i]; p < dma_virt[i] + (i + 1) * SZ_1M; p += PAGE_SIZE)
                    *(u32 *)p = ctc++;

                _dev_info(cma_dev, "[%d] alloc virt: %p phys: %p\n", i, dma_virt[i], (void *)dma_phys[i]);
            }
            else
            {

                dev_err(cma_dev, "[%d] no mem in CMA area\n", i);

                ret = -ENOMEM;
            }
            break;
        }
    }

    return count;
}

static const struct file_operations cma_test_fops = {

    .owner = THIS_MODULE,

    .read = cma_test_read,

    .write = cma_test_write,

};

static struct miscdevice cma_test_misc = {

    .name = "cma_test",

    .fops = &cma_test_fops,

};

static int __init cma_test_init(void)

{

    int i = 0;
    int ret = 0;

    ret = misc_register(&cma_test_misc);

    if (unlikely(ret))
    {

        pr_err("failed to register cma test misc device!\n");

        return ret;
    }

    cma_dev = cma_test_misc.this_device;

    cma_dev->coherent_dma_mask = ~0;

    for (i = 0; i < CMA_NUM; i++)
        dma_virt[i] = 0;

    _dev_info(cma_dev, "registered.\n");

    return ret;
}

module_init(cma_test_init);

static void __exit cma_test_exit(void)

{

    misc_deregister(&cma_test_misc);
}

module_exit(cma_test_exit);

MODULE_LICENSE("GPL");

MODULE_AUTHOR("Barry Song <[email protected]>");

MODULE_DESCRIPTION("kernel module to help the test of CMA");

MODULE_ALIAS("CMA test");

/*
cat /dev/cma-test
[  814.607124] cma: cma_release(page c63be800)
[  814.607305] misc cma_test: free virt: c64c0000 phys: 264c0000
[  815.160459] cma: cma_release(page c63c0800)
[  815.160802] misc cma_test: free virt: c65c0000 phys: 265c0000
[  815.594547] cma: cma_release(page c63c4800)
[  815.595052] misc cma_test: free virt: c67c0000 phys: 267c0000

echo 1 > /dev/cma-test
[  816.794816] cma: cma_alloc(cma c0435ef0, count 256, align 4)
[  816.794972] cma: cma_alloc(): returned c63be800
[  816.795484] misc cma_test: [0] alloc virt: c64c0000 phys: 264c0000   --1M
echo 1 > /dev/cma-test
[  817.206446] cma: cma_alloc(cma c0435ef0, count 512, align 4)
[  817.206561] cma: cma_alloc(): returned c63c0800
[  817.207561] misc cma_test: [1] alloc virt: c65c0000 phys: 265c0000   --2M
echo 1 > /dev/cma-test
[  817.542535] cma: cma_alloc(cma c0435ef0, count 768, align 4)
[  817.542809] cma: cma_alloc(): returned c63c4800
[  817.544308] misc cma_test: [2] alloc virt: c67c0000 phys: 267c0000   --3M
echo 1 > /dev/cma-test
[  817.954657] cma: cma_alloc(cma c0435ef0, count 1024, align 4)
[  817.954668] cma: cma_alloc(): returned   (null)
[  817.954678] misc cma_test: [3] no mem in CMA area
*/