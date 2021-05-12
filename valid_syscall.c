#include <get_proc_info.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main() {
	pid_t mypid = getppid();
	printf("PID: %d\n", mypid);
	struct procinfos info;

	if (get_proc_info(mypid, &info) == 0) {
		printf("My student ID: %ld\n", info.studentID);
		printf("My PID: %d, name: %s\n", info.proc.pid, info.proc.name);
		printf("Parent PID: %d, name %s\n", info.parent_proc.pid, info.parent_proc.name);
		printf("Child PID: %d, name %s\n", info.oldest_child_proc.pid, info.oldest_child_proc.name);
	} else {
		printf("Cannot get information from the process %d\n", mypid);
	}
	return 0;
}

