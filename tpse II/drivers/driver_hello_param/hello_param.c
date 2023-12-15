#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple hello world driver with parameters");
MODULE_VERSION("1.0");

static char *name = "world";
module_param(name, charp, 0644);
MODULE_PARM_DESC(name, "The name to display in the message");

static int count = 1;
module_param(count, int, 0644);
MODULE_PARM_DESC(count, "The number of times to display the message");

static int __init hello_init(void) {
    int i;
    for (i = 0; i < count; i++) {
        printk(KERN_INFO "Hello, %s!\n", name);
    }
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, %s!\n", name);
}

module_init(hello_init);
module_exit(hello_exit);
