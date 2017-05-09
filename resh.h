#ifndef	RESH_H__
#define	RESH_H__

struct rcommand {
	char *argv[16 + 1];
	int argc;
};

#define	NELEM(A)	(sizeof(A) / sizeof((A)[0]))
#define	STREQ(A, B)	(strcmp((A), (B)) == 0)

int tokenizeq(char *str, char *toks[], int maxtoks);
int run_command(char *cmd, int argc, char *argv[]);
char *resh_read(const char *prompt);
int openr(const char *filename);
int spawn(int argc, char *argv[]);
int getch(int fd);
int dynegg(char *cmd);
int navigate(struct rcommand *c);

#endif	/* !RESH_H__ */
