#include <linux/kernel.h>
#include <linux/module.h>

//#error Are we building this file?

static int __init hello_init (void)
{
    printk(KERN_ALERT "Hello, world\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Guilherme Araujo Floriano");
MODULE_DESCRIPTION("A simple Hello World module");
MODULE_VERSION("1.0");
