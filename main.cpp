#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <sys/wait.h>

double f(double x, int level);

double ref(double x, int level) {
	return sin(x);
}

void drawFn(FILE* pipe, double start, double end, double step, double (*fn)(double, int), int level) {
	double current = start;
	while(current <= end) {
		fprintf(pipe, "%.2f %.2f\n", current, fn(current, level));

		current += step;
	}

	fprintf(pipe, "e\n");
}

int main() {
	int pipefd[2];
	int status;

	pipe(pipefd);
	pid_t pid = fork();
	if(pid == 0) {
		//close(pipefd[0]);
		dup2(pipefd[0], STDIN_FILENO);
		//dup2(pipefd[1], STDOUT_FILENO);
		//dup2(pipefd[1], STDERR_FILENO);
		close(pipefd[1]);

		execl("/usr/bin/gnuplot", "/usr/bin/gnuplot", (char*) NULL);
		perror("gnuplot failed: ");
		return 2;
	}

	close(pipefd[0]);
	FILE* pipe = fdopen(pipefd[1], "w");

	fprintf(pipe, "set terminal wx size 1024,768\nset yrange [-3:3]\nset xrange [-10:10]\n"); //set nokey\n
	fprintf(pipe, "set arrow from -6.28,100 to -6.28,-100 nohead\nset arrow from 6.28,100 to 6.28,-100 nohead\n");
	fprintf(pipe, "set yzeroaxis\nset xzeroaxis\n");

	double step = 0.1;
	double start = -50;
	double end = 50;

	int level = 1;
	do {
		fprintf(pipe, "plot '-' with lines title 'sin(x)', '-' [1:3] with lines title 'taylor series of %d elements\n", level);

		drawFn(pipe, start, end, step, ref, level);
		drawFn(pipe, start, end, step, f, level);
		fflush(pipe);

		sleep(1);

		level++;
	} while(1);

	waitpid(pid, &status, 0);

	return 0;
}
