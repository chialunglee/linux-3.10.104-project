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

asmlinkage int get_process_session_group(unsigned int *ptr, int SIZE) {
	struct task_struct *empty;
	struct task_struct *ts = current;
	int current_session_id = ts->group_leader->pids[PIDTYPE_SID].pid->numbers[0].nr;
	int counter = 0;
	int level = ts->pids[0].pid->level;
	for_each_process(empty) {
		if(empty->group_leader->pids[PIDTYPE_SID].pid->numbers[0].nr == current_session_id) {
			counter += 1;
			if(counter <= SIZE) {
				*ptr = empty->group_leader->pids[PIDTYPE_PID].pid->numbers[level].nr;
				ptr += 1;
			}
		}
	}
	
	return counter;
}
