#include <linux/kernel.h>
#include <linux/sched.h>

asmlinkage void linux_survey_TT(unsigned long *result) {
	// printk("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	struct task_struct *ts = current;
	printk("%d\n", ts->mm->mmap);
}
