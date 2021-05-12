#include <get_proc_info.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main() {
	struct procinfos info;
	
	printf("\nCURRENT PROCESS INFORMATION\n\n");
	if (get_proc_info(-1, &info) == 0) {
		printf("My student ID: %ld\n", info.studentID);
		printf("My PID: %d, name: %s\n", info.proc.pid, info.proc.name);
		printf("My parent PID: %d, name: %s\n", info.parent_proc.pid, info.parent_proc.name);
		printf("My oldest child PID: %d, name: %s\n", info.oldest_child_proc.pid, info.oldest_child_proc.name);
	}
       	else {
		printf("Cannot get information from the process %d\n", info.proc.pid);
	}

	printf("\n\nPARENT PROCESS INFORMATION\n\n");
	if (get_proc_info(info.parent_proc.pid, &info) == 0) {
		printf("My student ID: %ld\n", info.studentID);
		printf("My PID: %d, name: %s\n", info.proc.pid, info.proc.name);
		printf("My parent PID: %d, name: %s\n", info.parent_proc.pid, info.parent_proc.name);
		printf("My oldest child PID: %d, name: %s\n", info.oldest_child_proc.pid, info.oldest_child_proc.name);
	}
	else {
		printf("Cannot get information from the process %d\n", info.proc.pid);
	}

	return 0;
}

