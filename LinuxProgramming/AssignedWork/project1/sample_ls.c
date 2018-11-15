#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/types.h>
#include<dirent.h>

struct file_item
{
	int colNum;
	char **data;
	struct file_item *next;
};

struct item_table
{
	int num;
	struct file_item *head;
};

static bool flag_l, flag_R, flag_a, flag_i, flag_d;
const static size_t MAX_DIRCHAR_BUFSIZE = 100;

struct item_table genPwdTable(char *path); 

int main(int argc, char *argv[])
{
	/* 1. Init flags */
	printf("This program received %d args \n", argc);
        int i = 0;
        for(i = 0; i < argc; i++)
        {
                printf("\t- arg%d = %s \n", i, argv[i]);
        }
        // int getopt(int argc, char *argv, char* optstring) Get the detail of args.
        extern char *optarg;
        extern int optind, opterr, optopt;
        char opt = 0;
		char final_args[50] = {0}; // TODO MAX_SIZE = 50
        while((opt = getopt(argc, argv, ":lRaid")) != -1)
        {
                if(opt == '?')
                        printf("\t- Unknown option %c\n", optopt);
                else if(opt == ':')
                        printf("\t- Arg %c needs operand\n", optopt);
                else
				{
					printf("\t- Received option %c, with %s\n",opt,optarg);
					char c[] = {'-', opt, ' ', '\0'};
					strcat(final_args, c);
					switch(opt)
					{
					case 'l': flag_l = true; break;
					case 'R': flag_R = true; break;
					case 'a': flag_a = true; break;
					case 'i': flag_i = true; break;
					case 'd': flag_d = true; break;
					default: break;
					}
				}
        }
	printf("----------------------------\n");
	printf("final_args = %s \n", final_args);
	char cmd[] = "ls ";
	strcat(cmd, final_args);
	
	char dir_args[100] = {'\0'}; // TODO MAX_SIZE = 100
	for(; optind < argc; optind++)
	{
		printf("Direct argument: %s\n", argv[optind]);
		strcat(dir_args, argv[optind]);
		char c[] = {' ', '\0'};
		strcat(dir_args, c);
	}
	strcat(cmd, dir_args);
	printf("final cmd = %s\n", cmd);	

	printf("---------------------------- \n");
	genPwdTable("/home/ourck");

	return 0;
}

struct item_table genPwdTable(char *path)
{
	// 1. cd to current directory.
	chdir(path);
	char cwd[MAX_DIRCHAR_BUFSIZE];
	if(NULL == getcwd(cwd, MAX_DIRCHAR_BUFSIZE))
	{ printf(" [!] ERROR: MAX_DIRCHAR_BUFSIZE too small!\n"); exit(1); }

	// 2. open this dir.
	DIR *p_cd;
	p_cd = opendir(cwd); // TODO NULL if fail.
	
	// 3. scan current directory.
	struct dirent *dir_item;
	while((dir_item = readdir(p_cd)) != NULL)
	{
		char abs_path[MAX_DIRCHAR_BUFSIZE];
		strcpy(abs_path, cwd);
		strcat(abs_path, "/");
		strcat(abs_path, dir_item->d_name); // TODO Filter '..' & '.' ?
		printf("inode = %ld, name = %s\n", dir_item->d_ino, abs_path); // TODO Link?
	}
	
	// X. CLOSE DIR
	closedir(p_cd);
}















