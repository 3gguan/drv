#include <linux/init.h>
#include <linux/module.h>

int my_test_add(int a, int b)
{
	return a + b;
}
EXPORT_SYMBOL(my_test_add);

static int hello_init(void)
{
	int k = 10;
	printk("hello module\r\n");
	printk("%p\r\n", &k);
	printk("%p\r\n", hello_init);

	return 0;
}

static void hello_exit(void)
{
	int ret = 0;
	ret = my_test_add(11, 11);
	printk("bye module%d\r\n", ret);

	return;
}

module_init(hello_init);
module_exit(hello_exit);
