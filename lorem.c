#include <linux/miscdevice.h>
#include <linux/fs.h>

#define DEVICE_NAME "lorem"

#define LOREM_IPSUM                                                 \
    "Lorem ipsum dolor sit amet, consectetur adipisicing elit, "    \
    "sed do eiusmod tempor incididunt ut labore et dolore magna "   \
    "aliqua. Ut enim ad minim veniam, quis nostrud exercitation "   \
    "ullamco laboris nisi ut aliquip ex ea commodo consequat. "     \
    "Duis aute irure dolor in reprehenderit in voluptate velit "    \
    "esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "  \
    "occaecat cupidatat non proident, sunt in culpa qui officia "   \
    "deserunt mollit anim id est laborum. "


#define LOREM_IPSUM_LENGTH (sizeof(LOREM_IPSUM) - 1)

static ssize_t
device_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
    char *ptr;
    ssize_t bytes_read;

    for (ptr = buffer; length --> 0; ptr++) {
        *ptr = LOREM_IPSUM[(*offset + ptr - buffer) % LOREM_IPSUM_LENGTH];
    }

    bytes_read = ptr - buffer;
    *offset += bytes_read;
    return bytes_read;
}

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = device_read,
};

static struct miscdevice lorem_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &fops,
    .mode = S_IRUGO,
};

static int
lorem_init(void)
{
    pr_info("Lorem ipsum will wrap after %lu bytes\n", LOREM_IPSUM_LENGTH);
    return misc_register(&lorem_device);
}

static void
lorem_exit(void)
{
    misc_deregister(&lorem_device);
}

module_init(lorem_init);
module_exit(lorem_exit);
