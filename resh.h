#ifndef	RESH_H__
#define	RESH_H__

struct rcommand {
	char *argv[16 + 1];
	int argc;
};

#define	NELEM(A)	(sizeof(A) / sizeof((A)[0]))
#define	STREQ(A, B)	(strcmp((A), (B)) == 0)

struct rcommand *resh_parse(char *str);
int tokenizeq(char *str, char *toks[], int maxtoks);
int run_command(const char *cmd, int argc, char *argv[]);
char *resh_read(const char *prompt);
int openr(const char *filename);
int spawn(int argc, char *argv[]);
int getch(int fd);
int dynegg(char *cmd);
int navigate(const char *cmd, int argc, char *argv[]);
char *estrdup(const char *s);
char *getvar(const char *name);
void setvar(const char *name, const char *value);
void unsetvar(const char *name);

#endif	/* !RESH_H__ */
