#define FIFO queue_name         //replace queue_name with the actual name of the queue when implemented
#define TEXTFILE filename.txt  //same, with the name of the file once it's created
//it is supposed that filename is opened in read mode for this program

#include <stdio.h>

enum work { READER, STATISTICIAN, WRITTEN };

struct monkey {
   int status ;         //boolean, equals 0 if on strike, 1 if active
   enum work work;      //his activity/role
};

void init_monkeys(struct monkey monkeyz[], int length){
   for (int i=0;i<length;i=i+1) {
      monkeyz[i].status = 1;
      monkeyz[i].work = i ;      //each monkey is initialized with a different activity, granted there is as much or more activities than there are monkeys
   }
}

void filter_active_monkeys(struct monkey monkeyz[], int length){
   for (int i=0;i<length;i=i+1) {
      switch(monkeyz[i].work) {
      case READER :
	 if (fgets("",0,TEXTFILE)==NULL)
	    monkeyz[i].status = 0
	 break;
      case STATISTICIAN :
	 monkeyz[i].status = !isEmpty(FIFO);
	 break;
      case WRITTER :
	 monkeyz[i].status = !isEmpty(FIFO)&&deja_lu(mot);  // !!! penser à définir deja_lu et à demander à Kais comment accéder à mot
      }
   }
}
