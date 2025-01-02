#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x2ca90791, "module_layout" },
	{ 0x3d8baf3b, "zs_huge_class_size" },
	{ 0xebf1d071, "fs_bio_set" },
	{ 0x3d7b9a95, "kmalloc_caches" },
	{ 0xc341ae6d, "zs_map_object" },
	{ 0xc4f0da12, "ktime_get_with_offset" },
	{ 0xf7f8c781, "__cpuhp_remove_state" },
	{ 0x8d3e9e65, "submit_bio_wait" },
	{ 0x53b954a2, "up_read" },
	{ 0xd580c1, "blk_queue_io_opt" },
	{ 0x84502a47, "blk_status_to_errno" },
	{ 0xde60a620, "bio_alloc_bioset" },
	{ 0x7005463f, "debugfs_create_dir" },
	{ 0x27864d57, "memparse" },
	{ 0x7aa1756e, "kvfree" },
	{ 0x754d539c, "strlen" },
	{ 0x54b1fac6, "__ubsan_handle_load_invalid_value" },
	{ 0x3854774b, "kstrtoll" },
	{ 0xc69b7ee5, "zs_destroy_pool" },
	{ 0xa1ef983, "blk_cleanup_disk" },
	{ 0xb29533ee, "zs_malloc" },
	{ 0x4f3aa892, "blk_queue_io_min" },
	{ 0xb3a318fc, "filp_close" },
	{ 0x228f0228, "alloc_pages" },
	{ 0x949f7342, "__alloc_percpu" },
	{ 0xcabf869c, "file_path" },
	{ 0x720a27a7, "__register_blkdev" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0x999e8297, "vfree" },
	{ 0x86d659a0, "blk_queue_max_write_zeroes_sectors" },
	{ 0x5da67adc, "zs_compact" },
	{ 0xf8f7f9b4, "debugfs_create_file" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0x1d40b6f3, "idr_for_each" },
	{ 0xeca4aee1, "pv_ops" },
	{ 0xc9ec4e21, "free_percpu" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x668b19a1, "down_read" },
	{ 0xaa44a707, "cpumask_next" },
	{ 0xc65b00ae, "fsync_bdev" },
	{ 0x958df3ac, "zs_free" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x17de3d5, "nr_cpu_ids" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x5c3c7387, "kstrtoull" },
	{ 0x994640f2, "bio_init" },
	{ 0x9e683f75, "__cpu_possible_mask" },
	{ 0x1e1e140e, "ns_to_timespec64" },
	{ 0x169938c1, "__sysfs_match_string" },
	{ 0x257c48fb, "default_llseek" },
	{ 0x8e17b3ae, "idr_destroy" },
	{ 0x4c9f47a5, "current_task" },
	{ 0xd8351c7e, "blk_queue_max_discard_sectors" },
	{ 0x5991835b, "del_gendisk" },
	{ 0x77ac52a2, "disk_end_io_acct" },
	{ 0xa50a3da7, "_find_next_bit" },
	{ 0x58b96629, "class_unregister" },
	{ 0x7b959c2, "bio_add_page" },
	{ 0x1174b99e, "__cpuhp_state_add_instance" },
	{ 0x9200f705, "bio_chain" },
	{ 0x364c23ad, "mutex_is_locked" },
	{ 0x5a921311, "strncmp" },
	{ 0xa555f7ee, "debugfs_remove" },
	{ 0x5792f848, "strlcpy" },
	{ 0xbcf1f0e6, "zs_create_pool" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0xe6421230, "set_capacity" },
	{ 0xbed3e927, "blkdev_get_by_dev" },
	{ 0x8c8569cb, "kstrtoint" },
	{ 0xb8f11603, "idr_alloc" },
	{ 0xe45f2742, "simple_open" },
	{ 0x23e09804, "__cpuhp_setup_state" },
	{ 0xce807a25, "up_write" },
	{ 0xaf16f09f, "__class_register" },
	{ 0x57bc19d2, "down_write" },
	{ 0x43f7060b, "bio_endio" },
	{ 0x98cf70f1, "bio_put" },
	{ 0x7665a95b, "idr_remove" },
	{ 0xb5a459dc, "unregister_blkdev" },
	{ 0x599fb41c, "kvmalloc_node" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x6f7f5508, "bio_start_io_acct" },
	{ 0x7c9f83a9, "blk_queue_flag_clear" },
	{ 0x74636f3, "submit_bio" },
	{ 0x40a9b349, "vzalloc" },
	{ 0x3e5f4f0c, "__free_pages" },
	{ 0xc2fedadf, "blkdev_put" },
	{ 0x9606cd6c, "blk_queue_flag_set" },
	{ 0xa916b694, "strnlen" },
	{ 0x6a5cb5ee, "__get_free_pages" },
	{ 0x36259652, "blk_queue_physical_block_size" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x92997ed8, "_printk" },
	{ 0x4af6ddf0, "kstrtou16" },
	{ 0x8990d127, "__cpuhp_state_remove_instance" },
	{ 0x547454e1, "crypto_destroy_tfm" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xcbe56bc2, "zs_get_total_pages" },
	{ 0x5761b6ee, "bio_end_io_acct_remapped" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0x254a0d4e, "crypto_comp_compress" },
	{ 0xa3859b3a, "kmem_cache_alloc_trace" },
	{ 0xba8fbd64, "_raw_spin_lock" },
	{ 0xb19a5453, "__per_cpu_offset" },
	{ 0x4302d0eb, "free_pages" },
	{ 0x37a0cba, "kfree" },
	{ 0x69acdf38, "memcpy" },
	{ 0x7cceaf92, "zs_pool_stats" },
	{ 0x53569707, "this_cpu_off" },
	{ 0x96848186, "scnprintf" },
	{ 0x951a2773, "crypto_has_alg" },
	{ 0x222e7ce2, "sysfs_streq" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x8ee7dbbd, "device_add_disk" },
	{ 0xb0e602eb, "memmove" },
	{ 0xc60d0620, "__num_online_cpus" },
	{ 0x9c4ad988, "crypto_alloc_base" },
	{ 0x877ea794, "blk_queue_logical_block_size" },
	{ 0x7a08b1ac, "param_ops_uint" },
	{ 0x20978fb9, "idr_find" },
	{ 0x924c46f8, "zs_unmap_object" },
	{ 0x86687b7d, "disk_start_io_acct" },
	{ 0x7b4da6ff, "__init_rwsem" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x77b0915a, "page_endio" },
	{ 0xbd4dce49, "crypto_comp_decompress" },
	{ 0xb252567a, "__blk_alloc_disk" },
	{ 0xb1027953, "filp_open" },
	{ 0xd01bf834, "bio_associate_blkg" },
	{ 0x91cafcb3, "set_capacity_and_notify" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "6DFFD712FF62C941E739B6B");