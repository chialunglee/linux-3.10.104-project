#include<linux/kernel.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<linux/delay.h>
#include<asm-generic/delay.h>
#include<linux/syscalls.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/proc_fs.h>
#include<linux/mm.h>
#include<linux/mm_types.h>
#include<linux/highmem.h>
#include<linux/string.h>
#include<asm/io.h>

asmlinkage int get_process_zero_session_group(unsigned int *ptr, int SIZE) {
	struct task_struct *ts;
	int process_zero_session_id=0;
	int counter = 0;
	for_each_process(ts) {
		if(ts->group_leader->pids[PIDTYPE_SID].pid->numbers[0].nr == process_zero_session_id) {
			counter += 1;
			if(counter <= SIZE) {
				*ptr = ts->group_leader->pids[PIDTYPE_PID].pid->numbers[0].nr;
				ptr += 1;
			}
		}
	}
	
	return counter;
}
