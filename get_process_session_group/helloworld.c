#include<linux/kernel.h>

asmlinkage int get_process_zero_session_group(unsigned int *ptr, int SIZE) {
	struct task_struct *empty;
	struct task_struct *ts = current;
	int current_session_id = ts->group_leader->pids[PIDTYPE_SID].pid->number[0].nr;
	int counter = 0;
	int level = ts->pids[0].pid->level;
	for_each_process(empty) {
		if(empty->group_leader->pids[PIDTYPE_SID].pid->number[0].nr == current_session_id) {
			counter += 1;
			if(counter <= SIZE) {
				*ptr = empty->group_leader->pids[PIDTYPE_PID].pid->number[level].nr;
				ptr += 1;
			}
		}
	}
	
	return counter;
}
