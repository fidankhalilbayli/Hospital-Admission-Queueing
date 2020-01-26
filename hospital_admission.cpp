#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <iostream>


using namespace std;


struct queue{
	char patient_name[10];
	int arrive_time;
	int treatment_time;
	char complaint[10];
	int sayac;//determines whether the patient is new to the hospital or not
	int wait;//help to determine which patient is waiting longer
	queue *next;
};

struct Queue {
	queue *newnode;
	queue *q;
	queue *head;
	queue *back;	
	void create();
	void close();
	void read(int );
	int read1();
	void pop();
	void push (queue *);
	bool isempty();	
	FILE *textfile;
	FILE *textfile1;
};


struct queue_red{
	char patient_name[10];
	queue_red *next;
};

struct Queue_red{
	queue_red *head=NULL;
	queue_red *back=NULL;
	void add(char *);
	void pop(void);
}; 


struct queue_yellow{
	char patient_name[10];
	queue_yellow *next;

};

struct Queue_yellow{
	queue_yellow *head=NULL;
	queue_yellow *back=NULL;
	void add(char *);
	void pop(void);
}; 

struct queue_green{
	char patient_name[10];
	queue_green *next;
};

struct Queue_green{
	queue_green *head=NULL;
	queue_green *back=NULL;
	void add(char *);
	void pop(void);
}; 


void Queue::create(){
	head=NULL;
	back=NULL;		
}
	

bool Queue::isempty(){
	return head==NULL;
}

void Queue_red::add(char *toadd){
		queue_red *red= new queue_red;
		strcpy(red->patient_name, toadd);
		red->next=NULL;
		if ( head==NULL ) { 
			back = red;
			head= back;			
		}
		else {
			back->next = red;
			back = red;
		}	
	}

void Queue_yellow::add(char *toadd){
		queue_yellow *yellow= new queue_yellow;
		strcpy(yellow->patient_name, toadd);
		yellow->next=NULL;
		if ( head==NULL ) { 
			back = yellow;
			head= back;			
		}
		else {
			back->next = yellow;
			back = yellow;
		}	
	}	
	
void Queue_green::add(char *toadd){
		queue_green *green= new queue_green;
		strcpy(green->patient_name, toadd);
		green->next=NULL;
		if ( head==NULL ) { 
			back = green;
			head= back;			
		}
		else {
			back->next = green;
			back = green;
		}	
	}
	
	
	
void Queue_red::pop() {
	queue_red *topnode;
	topnode = head;
	head= head->next;
	delete topnode;
}

	
void Queue_yellow::pop() {
	queue_yellow *topnode;
	topnode = head;
	head= head->next;
	delete topnode;
}

	
void Queue_green::pop() {
	queue_green *topnode;
	topnode = head;
	head= head->next;
	delete topnode;
}

void Queue::push(queue* toadd){
	toadd->next = NULL;
	if ( isempty() ) {
		back = toadd;
		head = back;
	}
	else {
		back->next = toadd;
		head = toadd;
	}
}
		
int Queue::read1(){		//the purpose of this function is to find the number of lines in the given text file and return it to the main in order
						// to use it as the number of patients
	if(!(textfile1 = fopen( "patientsInfo.txt", "r+" )))
		if(!(textfile1 = fopen( "patientsInfo.txt", "w+"))){
			cout << "File could not be opened" << endl;
		}
    int counter = 1;
    char  c;
	c = getc(textfile1);
    while (c != EOF)
    {
        if (c == '\n')
        counter ++;
    	c = getc(textfile1);
    }
    fclose(textfile1); 
    return counter-1;
}

void Queue::read(int Counter){//read the text file according to a queue

	struct File_Record{
		char patient_name[10];	
		int arrive_time;
		int time_treat;
		char complaint[10];
		
	};
	File_Record a;
	queue *newnode=new queue;
	q = new queue[Counter];
	int h=0;
	char w[15],x[15],y[15],z[10],s[10],ss[10];
	if(!(textfile = fopen( "patientsInfo.txt", "r+" )))
		if(!(textfile = fopen( "patientsInfo.txt", "w+"))){
			cout << "File could not be opened" << endl;
		}
	
	fseek(textfile, 0, SEEK_SET);
	fscanf(textfile,"%s %s %s %s %s %s ",w,x,y,z,s,ss);
	while(!feof(textfile)){
		fscanf(textfile,"%s %d %d %s",a.patient_name,&a.arrive_time,&a.time_treat,a.complaint);
		strcpy(newnode->patient_name,a.patient_name);//store the read data into a queue
		strcpy(newnode->complaint,a.complaint);
		newnode->arrive_time=a.arrive_time;
		newnode->treatment_time=a.time_treat;
		newnode->next=NULL;
		
		if ( isempty() ) { 
			back = newnode;
			head = back;
		}
		else {
			back->next = newnode;
			head = newnode;
		}
		strcpy(q[h].patient_name,newnode->patient_name);//according to the number of patients(which is obtained by the read1 function
														//store the data of the patients in a queue
		strcpy(q[h].complaint,newnode->complaint);
		q[h].arrive_time=newnode->arrive_time;
		q[h].treatment_time=newnode->treatment_time;	  
		h++;
		if(feof(textfile))
			break;
	}
	fclose(textfile);
}

Queue defter;
Queue_red Red;
Queue_yellow Yellow;
Queue_green Green;

	
int main(){

	int time=0;
	int frequency=0;
	int counter=0;
    int a,k;
	int p= defter.read1();//returns the number of patients
	defter.read(p);//creates a queue which holds the data of the patients according to the patient number
	for(int f=0;f<p;f++){//initializing both values
		defter.q[f].sayac=0;
		defter.q[f].wait=0;
	}
	
	

	int min=defter.q[0].arrive_time;//initializing the minimum
	for ( int a = 1 ; a < p ; a++ ) //finding the smallest arrive time
    {
		if (defter.q[a].arrive_time < min) 
			 min = defter.q[a].arrive_time;
	  
	}
      
	for(int i=0;i<3;i++)
		time+=defter.q[i].treatment_time;//finding the sum of the total treatment time 	
	
    
    int ss[p];
    int con[p];
    while(counter<time){    
    	if(counter>=min){//if the smallest arrive time starts from 0
    	frequency=0;
    	int freq_red=0;
		int freq_yellow=0;
		int freq_green=0;
   		for( a =0;a<p;a++){
    		if(counter>=defter.q[a].arrive_time&&defter.q[a].treatment_time>0){//finding the frequency of each complaint:if it is more than 1 
    		//I'll use the value in ss[frequency] array if it is equal to 1 I'll use the value stored in k integer
    			ss[frequency]=a;
	    		frequency++;  					
				if(strcmp(defter.q[a].complaint,"RED")==0)//push to the appropriate queues 
					Red.add(defter.q[a].patient_name);	
				else if(strcmp(defter.q[a].complaint,"YELLOW")==0)
					Yellow.add(defter.q[a].patient_name);
				else if(strcmp(defter.q[a].complaint,"GREEN")==0)
					Green.add(defter.q[a].patient_name);
				k=a;	
			}			
		}
		if(frequency ==1){	//if the occurance of each complaint is less than or equal to 1 at the appropriate time slice		
			if(strcmp(defter.q[k].complaint,"RED")==0)//if any of the complaints is red do the following(since red has a color priority it is 
													//checked and processed first
			{
				if((counter+1)<=time)
				cout<<endl<<counter+1<<".time slice "<<defter.q[k].patient_name<<endl;
				counter+=1;//increment the time slice
				defter.q[k].treatment_time--;//decrease the treatment time by one
				Red.pop();//remove the patient from the red queue
				strcpy(defter.q[k].complaint,"YELLOW");//change the complaint from red to yellow
				Yellow.add(defter.q[k].patient_name);//push the patient to the yellow queue
				defter.q[k].sayac++;//increment the sayac(it means that patient is no longer new to the hospital)
				for(int b=0;b<p;b++){
		    		if(b==k)
				    	defter.q[b].wait=0;//the amount of waiting time of a patient is resetted each time its priority of complaint has changed
				    else
				   		defter.q[b].wait++;//the amount of waiting time of other patients is incremented each a time a patient changes its 
				   							//priority of complaint(color)
				}
			}
			// the same as the previous lines 298-316 but here the complaint is changed from yellow to green
			else if(strcmp(defter.q[k].complaint,"YELLOW")==0)
			{
				for(int y=1;y<3;y++){
					if((counter+y)<16)
						cout<<endl<<counter+y<<".time slice "<<defter.q[k].patient_name<<endl;
				}
				counter+=2;		
				defter.q[k].treatment_time-=2;
				Yellow.pop();
				strcpy(defter.q[k].complaint,"GREEN");
			    Green.add(defter.q[k].patient_name);				    
			    defter.q[k].sayac++;
			    for(int b=0;b<p;b++){
			    	if(b==k)
			    		defter.q[b].wait=0;
			    	else
			    		defter.q[b].wait++;
				}
			}
			
			else if(strcmp(defter.q[k].complaint,"GREEN")==0)
			{
				for(int y=1;y<4;y++){
					if((counter+y)<=16)
						cout<<endl<<counter+y<<".time slice "<<defter.q[k].patient_name<<endl;						
				}
				counter+=3;
				defter.q[k].treatment_time-=3;	
				defter.q[k].sayac++;		
				for(int b=0;b<p;b++){
			    	if(b==k)
			    		defter.q[b].wait=0;
			    	else
				    	defter.q[b].wait++;
				}
			}								
		}//end of frequency=1 
			
		else if(frequency>1){//if at the same time slot there are more than 1 same color find the number of each color
			for(int i=0;i<frequency;i++){		
				if(strcmp(defter.q[ss[i]].complaint,"RED")==0)
					freq_red++;
				else if(strcmp(defter.q[ss[i]].complaint,"YELLOW")==0)
					freq_yellow++;
				else if(strcmp(defter.q[ss[i]].complaint,"GREEN")==0)
					freq_green++;
			}
		
			if(freq_red==1){//while there are more than 1 same color if there is only one red color do the following
				for(int i=0;i<frequency;i++){		
					if(strcmp(defter.q[ss[i]].complaint,"RED")==0 &&counter>=defter.q[ss[i]].arrive_time&&defter.q[ss[i]].treatment_time>0){
						cout<<endl<<counter+1<<".time slice "<<defter.q[ss[i]].patient_name<<endl;
						counter+=1;//increment the time slice by one
						defter.q[ss[i]].treatment_time--;//decrement the treatment time by one
						Red.pop();//remove the patient from the red queue
						strcpy(defter.q[ss[i]].complaint,"YELLOW");//change its color code from red to yellow
						Yellow.add(defter.q[ss[i]].patient_name);//add the patient to yellow queue
						defter.q[ss[i]].sayac++;//increment the sayac so it will be known that the patient is not new at the hospital
					 	for(int b=0;b<p;b++){//finding which patients are waiting for how long
				    		if(b==ss[i])
				    			defter.q[b].wait=0;
					    	else
					    		defter.q[b].wait++;
						}				
					}
				}
			}
			
			else if(freq_red>1){//if there are more than one red complaint first check whether the patient is new to the hospitla or not
					for(int i=0;i<frequency;i++){
						if(strcmp(defter.q[ss[i]].complaint,"RED")==0&&defter.q[ss[i]].sayac==0 &&counter>=defter.q[ss[i]].arrive_time&&defter.q[ss[i]].treatment_time>0){
							cout<<endl<<counter+1<<".time slice "<<defter.q[ss[i]].patient_name<<endl;
							counter+=1;							
							defter.q[ss[i]].treatment_time-=1;
							defter.q[ss[i]].sayac++;
						  	for(int b=0;b<p;b++){
						    	if(b==ss[i])
						    		defter.q[b].wait=0;
				    			else
				    				defter.q[b].wait++;
					    	}
						}
						//if the patient is not new to the hospital compare their waiting time		
						else if(strcmp(defter.q[ss[i]].complaint,"RED")==0&&defter.q[ss[i]].sayac!=0 &&counter>=defter.q[ss[i]].arrive_time&&defter.q[ss[i]].treatment_time>0){
							int max=defter.q[ss[i]].wait;//assigning the max integer
							int r;
							for(int t=0;t<frequency;t++){//finding the maximum waiting time among the patients 
								if(max<defter.q[ss[t]].wait&&defter.q[ss[t]].treatment_time>0){								
									max=defter.q[ss[t]].wait;
										r=ss[t];//assigning the patient that waited longest to r
								}
							}
							cout<<endl<<counter+1<<".time slice "<<defter.q[r].patient_name<<endl;
					 		counter+=1;
							defter.q[r].treatment_time-=1;
							defter.q[r].sayac++;
							for(int b=0;b<p;b++){
				    			if(b==r)
				    				defter.q[b].wait=0;
						    	else
				 			   		defter.q[b].wait++;				    	
							}
						}
					}		
				}
				
				
			else if((freq_yellow==1)){//if there is no patient with red complained at the given time slice check the yellow color code
			//these lines are the same as the lines for red 386- 422;so there is no need to write comment lines
				for(int i=0;i<frequency;i++){
					if(strcmp(defter.q[ss[i]].complaint,"YELLOW")==0 &&counter>=defter.q[ss[i]].arrive_time&&defter.q[ss[i]].treatment_time>0){
						for(int y=1;y<3;y++){
							if((counter+y)<=time)
								cout<<endl<<counter+y<<".time slice "<<defter.q[ss[i]].patient_name<<endl;
				 		}
						counter+=2;
						defter.q[ss[i]].treatment_time-=2;
						Yellow.pop();
						strcpy(defter.q[ss[i]].complaint,"GREEN");
						Green.add(defter.q[ss[i]].patient_name);
						defter.q[ss[i]].sayac++;
				 		for(int b=0;b<p;b++){
				    		if(b==ss[i])
				    			defter.q[b].wait=0;
					    	else
					    		defter.q[b].wait++;
						}
					}
				}
			}
			else if(freq_yellow>1){
				for(int i=0;i<frequency;i++){
					if(strcmp(defter.q[ss[i]].complaint,"YELLOW")==0&&defter.q[ss[i]].sayac==0 &&counter>=defter.q[ss[i]].arrive_time&&defter.q[ss[i]].treatment_time>0){
						for(int y=1;y<3;y++){
								if((counter+y)<=time)
									cout<<endl<<counter+y<<".time slice "<<defter.q[ss[i]].patient_name<<endl;
				 		}
						counter+=2;							
						defter.q[ss[i]].treatment_time-=2;
						defter.q[ss[i]].sayac++;
					  	for(int b=0;b<p;b++){
			    			if(b==ss[i])
								defter.q[b].wait=0;
				    		else
				  				defter.q[b].wait++;
			    		}
					}			
					else if(strcmp(defter.q[ss[i]].complaint,"YELLOW")==0&&defter.q[ss[i]].sayac!=0 &&counter>=defter.q[ss[i]].arrive_time&&defter.q[ss[i]].treatment_time>0){
						int max=defter.q[ss[i]].wait;
						int r;
						for(int t=0;t<frequency;t++){
							if(max<defter.q[ss[t]].wait&&defter.q[ss[t]].treatment_time>0){								
								max=defter.q[ss[t]].wait;
									r=ss[t];
							}
						}
						for(int y=1;y<3;y++){
							if((counter+y)<=time)
								cout<<endl<<counter+y<<".time slice "<<defter.q[r].patient_name<<endl;
			 			}
						counter+=2;
						defter.q[r].treatment_time-=2;
						defter.q[r].sayac++;
						for(int b=0;b<p;b++){
			    			if(b==r)
			    				defter.q[b].wait=0;
					    	else
								defter.q[b].wait++;				    	
						}
					}
				}		
			}
			else if((freq_green==1)){
				for(int i=0;i<frequency;i++){
					if(strcmp(defter.q[ss[i]].complaint,"GREEN")==0 &&counter>=defter.q[ss[i]].arrive_time&&defter.q[ss[i]].treatment_time>0 ){
						for(int y=1;y<4;y++){
							if((counter+y)<=time)
								cout<<endl<<counter+y<<".time slice "<<defter.q[ss[i]].patient_name<<endl;
			 			}
						counter+=3;					
						defter.q[ss[i]].treatment_time-=3;
						defter.q[ss[i]].sayac++;
					 	for(int b=0;b<p;b++){
				    		if(b==ss[i])
					    		defter.q[b].wait=0;
				    		else
				    			defter.q[b].wait++;
						}
					}					
				}
			}
			else if(freq_green>1){
				for(int i=0;i<frequency;i++){
					if(strcmp(defter.q[ss[i]].complaint,"GREEN")==0&&defter.q[ss[i]].sayac==0 &&counter>=defter.q[ss[i]].arrive_time&&defter.q[ss[i]].treatment_time>0){
						for(int y=1;y<4;y++){
							if((counter+y)<=time)
								cout<<endl<<counter+y<<".time slice "<<defter.q[ss[i]].patient_name<<endl;
				 		}
						counter+=3;							
						defter.q[ss[i]].treatment_time-=3;
						defter.q[ss[i]].sayac++;
					  	for(int b=0;b<p;b++){
					    	if(b==ss[i])
					    		defter.q[b].wait=0;
				    		else
				    			defter.q[b].wait++;
					   	}
					}			
					else if(strcmp(defter.q[ss[i]].complaint,"GREEN")==0&&defter.q[ss[i]].sayac!=0 &&counter>=defter.q[ss[i]].arrive_time&&defter.q[ss[i]].treatment_time>0){
						int max=defter.q[ss[i]].wait;
						int r;
						for(int t=0;t<frequency;t++){
							if(max<defter.q[ss[t]].wait&&defter.q[ss[t]].treatment_time>0){								
								max=defter.q[ss[t]].wait;
									r=ss[t];
							}
						}
						for(int y=1;y<4;y++){
							if((counter+y)<=time)
								cout<<endl<<counter+y<<".time slice "<<defter.q[r].patient_name<<endl;
			 			}	
						counter+=3;
						defter.q[r].treatment_time-=3;
						defter.q[r].sayac++;
						for(int b=0;b<p;b++){
			    			if(b==r)
			    				defter.q[b].wait=0;
					    	else
			 			   		defter.q[b].wait++;				    	
						}
					}
				}		
			}				
		}//end of frequency>1
		}			
		else if(counter<min){//if the smallest arrive time is greater than 0 print the numbers of the times slots that are empty
			for(int t=0;t<min;t++){
				cout<<t<<".time slot is empty";
				t++;
			}	
		}
	
}//end of while loop
	return 0;
}//end of main
