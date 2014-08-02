#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>


#define MAXLENDATA 60

enum{
	SUM,
	SUB,
	MUL,
	DIV,
	MAX_FUN
} FUNS;

typedef int FUNC(int, int, int);
typedef ssize_t WRITE(int fd, const void *buf, size_t count);

typedef struct obj{
	int *data;
	FUNC *functions[MAX_FUN];
	WRITE *write;
	int numofdata;
} obj;

int sum(int a,int b, int mod){
	return (a+b) % mod;
}

int sub(int a,int b, int mod){
	return (a-b) % mod;
}

int mul(int a,int b, int mod){
	return (a*b) % mod;
}

int divi(int a,int b, int mod){
	return (a/b) % mod;
}

void init(obj *o){
	o->functions[SUM] = &sum;
	o->functions[SUB] = &sub;
	o->functions[MUL] = &mul;
	o->functions[DIV] = &divi;
	o->write = &write;
	o->numofdata = 0;
}

int readData(obj *o){
	char i = 0;
	char buf[13];
	printf("How many data?\n");
	fflush(stdout);
	scanf("%d", &(o->numofdata));
	if(o->numofdata > MAXLENDATA+1){
		printf("Error maximum data excided\n");
		fflush(stdout);
		return;
	}
	for(i =0; i < o->numofdata; ++i){
		int tmp;
		read(0,buf,12);
		buf[12] = '\0';

		tmp = atoi(buf);
		o->data[i] = tmp; 
	}
	return 0;
}

int printAll(obj *o){
	int i = 0;
	for(i =0; i < o->numofdata; i++){
		printf("%x\n", o->data[i]);
		fflush(stdout);
	}
	return 0;
}

void printOne(obj *o, int i){
	printf("%d\n", o->data[i]);
	fflush(stdout);
}

void menu(obj *o){
	char *msg="Choose an option:\n 1) Input data\n 2) Read All data\n 3) Read a sample\n 4) Make an operation\n 0) Exit\n";
	o->write(1,msg,strlen(msg));
}

int reduce(obj *o, int operation, int mod){
	if(operation < 0 || operation >= MAX_FUN){
		printf("Operation error\n");
		fflush(stdout);
		return -1;
	}
	int result = o->data[0];
	int i = 0;
	for(i = 1; i < o->numofdata; ++i){
		result = o->functions[operation](result,o->data[i], mod);
	}
	return result;
}


int main2(int argc, char const *argv[])
{
	obj *o;
	void *space;
	space = malloc(sizeof(int)*MAXLENDATA+sizeof(obj));

	mprotect(space, sizeof(int)*MAXLENDATA+sizeof(obj), PROT_WRITE);

	o = space+sizeof(int)*MAXLENDATA;
	o->data = space;
	init(o);
	char *welcome = "Welcome!\n";
	o->write(1,welcome,strlen(welcome));
	int num;
	int index;
	int mod;
	while(1){
		menu(o);
		scanf("%d",&num);
		if (num == 0){
				return 0;
			}
		else if(num == 1)
				readData(o);
		else if(num == 2)
				printAll(o);
		else if (num == 3){
				printf("Insert an index:\n");
				fflush(stdout);
				scanf("%d",&index);
				if (index < 0 && index > MAXLENDATA){
					printf("index error\n");
					fflush(stdout);
				}
				else
					printOne(o,index);
			}
		else if(num ==4){
				printf("Insert an operation:\n 0) Sum\n 1) Subtraction\n 2) Multiplication\n 3) division\n");
				fflush(stdout);
				scanf("%d",&index);
				printf("Choose a Module\n");
				fflush(stdout);
				scanf("%d",&mod);
				printf("Result: %d\n", reduce(o,index,mod));
				fflush(stdout);
				}
		else {
				printf("invalid operation\n");
				fflush(stdout);
			}
		
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	main2(argc, argv);
	return 0;
}
