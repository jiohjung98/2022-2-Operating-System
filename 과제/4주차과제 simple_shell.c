// 4주차 PDF 16p 를 참고하여 작성하세요.
// Please refer to Week4 PDF 16p and fill the code.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LEN 100 /* The maximum length command */

int main(void) {
  char *args[MAX_LEN / 2 + 1]; /* command line arguments */
  int should_run = 1;          /* flag to determine when to exit program */
  int background = 0;

  char *input;
  int status;

  while (should_run) {
    printf("my_shell> ");
    fflush(stdout);

    // A. 사용자에게 문자열(shell 명령어) 입력을 받는다.
    input = (char *)malloc(MAX_LEN * sizeof(char));
    fgets(input, MAX_LEN, stdin);


    // B. A에서 입력받은 문자열을 " \n" 단위로 쪼갠다. -strtok (goto, while)
    int i = 0;
    args[0] = strtok(input, " \n");
    while (args[i] != NULL) 
    {
	    i++;
	    args[i] = strtok(NULL, " \n");
    }

    if (args[0] == NULL)
	    goto no_input;


    // C. B에서 쪼갠 문자열을 비교한다. -strcmp
    if (strcmp(args[0], "exit") == 0) {
	    break;
    }

    if (strcmp(args[i-1], "&") == 0) {
	    args[i-1] = NULL;
	    background = 1;
    }


    /**
     * D. fork()를 통해 자식 프로세스를 생성한다.
     * (1) 자식 프로세스가 execvp()를 호출하도록 할 것
     * (2) 만약 입력받은 문자에 &가 포함되어 있으면,
     *     부모 프로세스는 wait() 호출하지 않음 (background process)
     */

    // Fork Error에 대한 예외처리
    pid_t pid = fork();
    if (pid < 0) {
      perror("Fork error");
      exit(0);
    }

    if (pid == 0) {
	    sleep(1);
	    if (execvp(args[0], args) < 0) {
		    printf("command error, not found.\n");
	    }
    }

    if (pid > 0) {
	    if (!background) {
		    printf("waiting for child, not a background process\n");

		    waitpid(pid, &status, 0);

		    printf("child process complete\n");
	    } else {
		    printf("background process\n");
		    background = 0;
	    }
    }
no_input:;
  }

  return 0;
}
