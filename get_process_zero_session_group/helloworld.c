#include<linux/kernel.h>

asmlinkage int get_process_zero_session_group(unsigned int *ptr, int SIZE) {
	struct task_struct *ts;
	int process_zero_session_id;
	int counter = 0;
	for_each_process(ts) {
		if(ts->group_leader->pids[PIDTYPE_PID].pid->number[0].nr == 0) {
			process_zero_session_id = ts->group_leader->pids[PIDTYPE_SID].pid->number[0].nr;
			break;
		}
	}
	for_each_process(ts) {
		if(ts->group_leader->pids[PIDTYPE_SID].pid->number[0].nr == process_zero_session_id) {
			counter += 1;
			if(counter <= SIZE) {
				*ptr = ts->group_leader->pids[PIDTYPE_PID].pid->number[0].nr;
				ptr += 1;
			}
		}
	}
	
	return counter;
}
