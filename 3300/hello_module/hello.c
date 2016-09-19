
/* hello world module - Eric McCreath 2005,2006,2008,2010,2012 */
/* to compile use:
    make -C  /usr/src/linux-headers-`uname -r` SUBDIRS=$PWD modules
   to install into the kernel use :
    insmod hello.ko
   to test :
    cat /proc/hello
   to remove :
    rmmod hello
*/

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>

int a = 0;

static int hello_proc_show(struct seq_file *m, void *v)
{
	a++;
	seq_printf(m, "Hello World!\n");
	printk("GG\n");
	printk("%d\n",a);
	return 0;
}

char *msg[100];

//char* msg = (char *)kmalloc(100,GFP_KERNEL);
int len,temp;
/*
int seq_read(struct file *filp,char *buf,size_t count,loff_t *offp ) 
{
if(count>temp)
{
count=temp;
}
temp=temp-count;
copy_to_user(buf,msg, count);
if(count==0)
temp=len;
   
return count;
}

int hello_write(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
copy_from_user(msg,buf,count);
len=count;
temp=len;
return count;
}
*/
static int hello_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, hello_proc_show, NULL);
}

static const struct file_operations hello_proc_fops = {
	.open		= hello_proc_open,
	.read		= seq_read,
//	.write		= hello_write,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_hello_init(void)
{
        printk("init proc hello\n");
	proc_create("hello", 950, NULL, &hello_proc_fops);
	return 0;
}
static void __exit cleanup_hello_module(void)
{
  remove_proc_entry("hello",NULL);
 // kfree(msg);

  printk("cleanup proc hello\n");
}


module_init(proc_hello_init);
module_exit(cleanup_hello_module);



