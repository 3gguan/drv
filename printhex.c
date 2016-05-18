#include <linux/kernel.h>

int printhex(char *src, unsigned int size)
{
    char buf[1024];
    int i;
    int ret = 0;

    buf[0] = '\0';

    for (i = 0; i < size; i++)
    {
        ret += scnprintf(buf + ret, sizeof(buf) - ret, "%02hhx ", *(src + i));
    }

    printk("%s\r\n", buf);

    if (3 * size <= sizeof(buf))
    {
        return ret;
    }
    else
    {
        return -1;
    }
}

EXPORT_SYMBOL(printhex);
