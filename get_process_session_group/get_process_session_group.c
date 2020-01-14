#include<linux/kernel.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<linux/delay.h>
#include<asm-generic/delay.h>

asmlinkage int get_process_session_group(unsigned int *ptr, int SIZE) {
	struct task_struct *empty;
	struct task_struct *ts = current;
	int current_session_id = ts->group_leader->pids[PIDTYPE_SID].pid->numbers[0].nr;
	int counter = 0;
	
	for_each_process(empty) {
		if(empty->group_leader->pids[PIDTYPE_SID].pid->numbers[0].nr == current_session_id) {
			int level = empty->pids[0].pid->level;
			counter += 1;
			if(counter <= SIZE) {
				*ptr = empty->pids[PIDTYPE_PID].pid->numbers[level].nr;
				ptr += 1;
			}
		}
	}
	msleep(1000);
	return counter;
}
