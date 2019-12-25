#include<linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/proc_fs.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<linux/mm.h>
#include<linux/mm_types.h>
#include<linux/highmem.h>
#include<linux/string.h>
#include<asm/io.h>

static unsigned long vaddr2paddr(struct task_struct* tsk,unsigned long vaddr) {
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	struct page *page=NULL;
	unsigned long paddr = 0;
	pgd = pgd_offset(tsk->mm, vaddr);
	if (pgd_none(*pgd)) {
		return 0;
	}
	pmd = pmd_offset((pmd_t*)pgd, vaddr);
	if (pmd_none(*pmd)) {
		return 0;
	}
	if (!(pte = pte_offset_map(pmd, vaddr))) return 0;
	if (!(page = pte_page(*pte))) return 0;
	paddr = page_to_phys(page);
	pte_unmap(pte);

	return paddr;
}

asmlinkage void linux_survey_TT(unsigned long *result) {
	struct task_struct *ts = current;
	struct vm_area_struct *vma = ts->mm->mmap;
	do {
		unsigned long page;
		// printk("%lx\n", vma->vm_start);
		*result = vma->vm_start;
		result += 1;
		// printk("%lx\n", vma->vm_end);
		*result = vma->vm_end;
		result += 1;
		page = vma->vm_start;
		do {
			printk("0x%lx\n", vaddr2paddr(ts, page));
			page += 0x1000;
		}while(page != vm->end);
	}while(vma->vm_next && (vma = vma->vm_next));
}
