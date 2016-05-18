#include <linux/init.h>
#include <linux/module.h>
#include <linux/socket.h>
#include <uapi/linux/uio.h>
#include <net/net_namespace.h>
#include <linux/netlink.h>

#include "printhex.h"

#define NETLINK_KERNEL_TEST 28

static struct sock *sk = NULL;

static void netlink_kernel_input(struct sk_buff *skb)
{
    printk("netlink_kernel_input test\r\n");

    printk("sk_buff:%lu truesize:%u\r\n", sizeof(*skb), skb->truesize);
    printk("count:%d head:%p data:%p tail:%u end:%u\r\n", skb->users.counter, skb->head, skb->data, skb->tail, skb->end);

    printhex(skb->data, 100);

    return;
}

static int netlink_kernel_init(void)
{
    struct netlink_kernel_cfg nkc = {
        .input = netlink_kernel_input,
    };

    printk("netlink kernel init\r\n");

    sk = netlink_kernel_create(&init_net, NETLINK_KERNEL_TEST, &nkc);

    if (NULL == sk)
    {
        printk("netlink create failed\r\n");
        return -ENOMEM;
    }

    return 0;
}

static void netlink_kernel_exit(void)
{
    printk("netlink kernel fini\r\n");

    if (NULL != sk)
    {
        netlink_kernel_release(sk);
    }

    return;
}

module_init(netlink_kernel_init);
module_exit(netlink_kernel_exit);

/*
static void netlink_kernel_input(struct sk_buff *skb)
{
    struct nlmsghdr *msg = NULL;
    char *buf = NULL;
    char i;

    printk("netlink_kernel_input test\r\n");

    msg = (struct nlmsghdr *)skb->data;
    buf = msg + 1;
    printk("%u\r\n", skb->truesize);
    printk("%p %p\r\n", msg, buf);

    printk("%u, %hu, %hu, %u, %u\r\n", msg->nlmsg_len, msg->nlmsg_type, msg->nlmsg_flags, msg->nlmsg_seq, msg->nlmsg_pid);

    for (i = 0; i < 100; i ++)
    {
        printk("%hhu ", *(buf + i));
    }
}
*/
