#include <linux/kernel.h>
#include <linux/sched.h>

asmlinkage void linux_survey_TT(unsigned long *result) {
	struct task_struct *ts = current;
	struct vm_area_struct *vma = ts->mm->mmap;
	do {
		printk("%lx\n", vma->vm_end);
		printk("%lx\n", vma->vm_start);
	}while(vma->vm_next && (vma = vma->vm_next));
}
