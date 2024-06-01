#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <net/net_namespace.h>

#define NETLINK_USER 31

struct sock *nl_sk = NULL;

static void hello_nl_recv_msg(struct sk_buff *skb)
{
    struct nlmsghdr *nlh;
    int pid;
    struct sk_buff *skb_out;
    int msg_size;
    char msg[32];
    int res;

    pr_info("netlink: Message entering \n");

    msg_size = strlen(msg);

    nlh = (struct nlmsghdr *)skb->data;
    pr_info("netlink: Netlink received msg payload: %s\n", (char *)nlmsg_data(nlh));
    strcpy(msg,  (char *)nlmsg_data(nlh));
    pid = nlh->nlmsg_pid; 

    skb_out = nlmsg_new(msg_size, 0);

    if (!skb_out)
    {
        pr_err("netlink: Failed to allocate new skb\n");
        return;
    }

    nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
    NETLINK_CB(skb_out).dst_group = 0;
    
    strncpy(nlmsg_data(nlh), msg, msg_size);

    res = nlmsg_unicast(nl_sk, skb_out, pid);

    if (res < 0)
        pr_info("netlink: Error while sending bak to user\n");
}

struct netlink_kernel_cfg cfg = {
   .groups  = 1,
   .input = hello_nl_recv_msg,
};

static int __init hello_init(void)
{
    nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);

    if (!nl_sk)
    {
        printk(KERN_ALERT "netlink: Error creating socket.\n");
        return -10;
    }

    pr_info("netlink: ON!");
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("netlink: OFF!\n");
    netlink_kernel_release(nl_sk);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Loychenko");
MODULE_DESCRIPTION("The program that using NETLINK");
module_init(hello_init);
module_exit(hello_exit);