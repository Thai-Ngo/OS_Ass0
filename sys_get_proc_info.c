#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <asm/current.h>
#include <linux/syscalls.h>

struct proc_info {
	pid_t pid;
	char name[16];
};

struct procinfos {
	long studentID;
	struct proc_info proc;
	struct proc_info parent_proc;
	struct proc_info oldest_child_proc;
};

void cp_name(char* name_proc_1, const char* name_proc_2) {
	int i = 0;
	while (i < 16) {
		name_proc_1[i] = name_proc_2[i];
		i = i + 1;
	}
}

SYSCALL_DEFINE2(get_proc_info, pid_t, pid, struct procinfos *, info) 

{
	//printk("PID %d", pid);
	struct task_struct * working_process;
	if (pid == -1) { 
		working_process = current;
		//printk("Current\n");
	}
	else {
		//printk("FindProcess\n");
		working_process = find_task_by_vpid(pid);
		if (working_process == NULL) {
			return EINVAL;
		}
	}


	//Set ID
	info->studentID = 1912046;

	//Set process ID for proc
	info->proc.pid = working_process->pid;
	cp_name(info->proc.name, working_process->comm);

	//Set parent process ID for proc
	info->parent_proc.pid = working_process->parent->pid;
	cp_name(info->parent_proc.name, working_process->parent->comm);

	//Set oldest child process ID for proc
	if (working_process->children.next != &working_process->children) {
		struct task_struct* oldest_child = list_entry(working_process->children.next, struct task_struct, sibling);

		struct list_head* seeker = (working_process->children.next);
		while (seeker != &(working_process->children)) {
			struct task_struct* tmp = list_entry(seeker, struct task_struct, sibling);
			if (tmp->real_start_time < oldest_child->real_start_time) {
				oldest_child = tmp;
			}
			//printk("Child PID: %d, name: %s\n", tmp->pid, tmp->comm);
			//printk("Time: %lld\n", tmp->real_start_time);

			seeker = seeker->next;
		}
		//printk("Smallest time = %lld\n", oldest_child->real_start_time);
		//printk("PID = %d, name = %s\n", oldest_child->pid, oldest_child->comm);
		info->oldest_child_proc.pid = oldest_child->pid;
		cp_name(info->oldest_child_proc.name, oldest_child->comm);
	}
	else {
		info->oldest_child_proc.pid = -1;
		cp_name(info->oldest_child_proc.name, "Not found");
		
	}

	printk("%ld\n", info->studentID);
	//printk("PID: %d, name: %s\n", info->proc.pid, info->proc.name);
	//printk("PPID: %d, name: %s\n", info->parent_proc.pid, info->parent_proc.name);
	//printk("CPID: %d, name: %s\n", info->oldest_child_proc.pid, info->oldest_child_proc.name);

	return 0;
}
