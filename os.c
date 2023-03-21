#include<stdio.h>
#include<stdlib.h>


#define max 100 //maximum queue size


typedef struct process
{
    int p_id;
    int priority;
    int burst_time;
    int remain_time;
    int turnaround_time;
    int waiting_time;
    
}process;

process q0[max], q1[max], q2[max], q3[max];
int size_q0 = 0, size_q1 = 0, size_q2 = 0, size_q3 = 0; 
int total_Time = 0;

//Arrival time of all processes is 0
static int Arrival_Time = 0;

//Enqueue to the queue
void enqueue(process *q, int* size, process p){  
    q[*size] =p;
    (*size)++;
}

//  Dequeue from the queue
process dequeue(process *q, int* size){
   process temp_p = q[0];
   (*size)--;
   for(int i=0 ; i<(*size) ; i++){
    q[i] = q[i+1];
    
   }
   return temp_p;
}

//Implementation of Round Robin scheduling
void Round_Robin(process* q, int *size , int quantum , int switch_time){

    while(switch_time != 0 && *size > 0){
        if( switch_time  >= quantum ) 
        {
          process exe = dequeue( q, size);

          if(exe.remain_time >= quantum){

            exe.remain_time = exe.remain_time - quantum;
            total_Time = total_Time + quantum;
            switch_time  = switch_time - quantum;

           
            if(exe.remain_time == 0)
            {
              exe.turnaround_time =  total_Time - Arrival_Time;
              exe.waiting_time =exe.turnaround_time - exe.burst_time;

              printf("\nQueue: 0    |    Process: %d is finished    |    Remaining time  : %d",exe.p_id,switch_time);
              printf("    |    Turnaround time :%d    |    Waiting time :%d",exe.turnaround_time,exe.waiting_time);
             }
             
            else 
              enqueue(q , size, exe);
              

          }
          //Process's remaining less than quantum
          else{
            switch_time = switch_time - exe.remain_time;
            total_Time = total_Time + exe.remain_time;

            exe.remain_time= 0;
            
            exe.turnaround_time =  total_Time - Arrival_Time;
            exe.waiting_time =exe.turnaround_time - exe.burst_time;

            printf("\nQueue: 0    |    Process: %d is finished    |    Remaining time : %d",exe.p_id,switch_time);
            printf("    |    Turnaround time :%d    |    Waiting time :%d",exe.turnaround_time,exe.waiting_time);
          }
        }
        //switch time < quantum
        else if(switch_time < quantum){
            if(q[0].remain_time <= switch_time){
                switch_time = switch_time - q[0].remain_time;
                total_Time = total_Time + q[0].remain_time;
                q[0].remain_time = 0;

                q[0].turnaround_time = total_Time -  Arrival_Time ;
                q[0].waiting_time =  q[0].turnaround_time- q[0].burst_time;

                printf("\nQueue: 0    |    Process: %d is finished    |    Remaining time : %d",q[0].p_id,switch_time);
                printf("    |    Turnaround time :%d    |    Waiting time :%d",q[0].turnaround_time,q[0].waiting_time);
                dequeue(q, size);

            }
            else{
                q[0].remain_time = q[0].remain_time - switch_time;
                total_Time = total_Time + switch_time;
                switch_time = 0;
              
            }
        }
        
    }
    printf("\n\n===========CPU EXECUTED TO NEXT QUEUE===========");
}

//Implementation of shortest job first scheduling
void SJF(process *q, int *size, int switch_time){
    while( switch_time != 0 && *size>0){
        int shortest_id = 0;
        for(int i=0 ; i< *size ; i++){
            if( q[i].remain_time < q[shortest_id].remain_time){
                shortest_id = i;
            }
        }
        process exe = dequeue((q + shortest_id) , size);


        if(exe.remain_time >= switch_time){
            exe.remain_time = exe.remain_time- switch_time;
            total_Time = total_Time + switch_time;
            switch_time = 0;

            if(exe.remain_time == 0)
             {
               exe.turnaround_time =  total_Time - Arrival_Time;
               exe.waiting_time =exe.turnaround_time - exe.burst_time;
               printf("\nQueue: 1 or 2    |    Process: %d is finished    |    Remaining time: %d",exe.p_id,switch_time);
               printf("    |    Turnaround time :%d    |    Waiting time :%d",exe.turnaround_time,exe.waiting_time); 
             }
            else
               enqueue(q , size , exe);  
            
        }
        else{
            switch_time = switch_time - exe.remain_time;
             total_Time = total_Time + exe.remain_time;
             exe.remain_time = 0;

             exe.turnaround_time =  total_Time - Arrival_Time;
             exe.waiting_time =exe.turnaround_time - exe.burst_time;
            
            printf("\nQueue: 1 or 2    |    Process: %d is finished    |    Remaining time: %d",exe.p_id,switch_time);
            printf("    |    Turnaround time :%d    |    Waiting time :%d",exe.turnaround_time,exe.waiting_time); 

             }
        }
        printf("\n\n===========CPU EXECUTED TO NEXT QUEUE===========");

 }

//Implementation of first come first serve scheduling
void FCFS(process *q, int *size, int switch_time){
    while( switch_time !=0 && *size > 0){
        if( q[0].remain_time > switch_time){
           q[0].remain_time = q[0].remain_time - switch_time;
           total_Time = total_Time + switch_time;
           switch_time = 0;
        }
        else{
            switch_time = switch_time - q[0].remain_time;
            total_Time = total_Time + q[0].remain_time;
            q[0].remain_time = 0;

            q[0].turnaround_time = total_Time -  Arrival_Time ;
            q[0].waiting_time =  q[0].turnaround_time- q[0].burst_time;
 
            printf("\nQueue: 3    |    Process: %d is finished    |    Remaining time: %d",q[0].p_id,switch_time); 
            printf("    |    Turnaround time :%d    |    Waiting time :%d",q[0].turnaround_time,q[0].waiting_time);

            dequeue(q , size);

        }
    }
     printf("\n\n===========CPU EXECUTED TO NEXT QUEUE===========");
    

}

//driver code
int main(){

    int switch_time = 20;
    int quantum =20;

    int no_of_process;
    printf("Enter the no.of process you want:");
    scanf("%d",&no_of_process);

   
    printf("\nEnter Processs' Priority and Burst time: " );
    for(int i=1 ; i<= no_of_process; i++){
        process new_process;
        new_process.p_id = i;

        printf("\n\t Process p%d ->",i);
        printf("\n\t\tBurst Time:");
        scanf("%d",&new_process.burst_time);

        printf("\n\t\tPriority:");
        scanf("%d",&new_process.priority);
      
        new_process.remain_time = new_process.burst_time;
        
        switch( new_process.priority)
        {
        case 0:
           
            enqueue(q0, &size_q0, new_process);
            break;
        
        case 1:
            enqueue(q1, &size_q1, new_process);
            break;
        
        case 2:
            enqueue(q2, &size_q2, new_process);
            break;
        
        case 3:
            enqueue(q3, &size_q3, new_process);
            break;
        
        
        }
       
    }

  
    while(size_q0 > 0 || size_q1 > 0 || size_q2 > 0 || size_q3 > 0  )
    {
        if(size_q0 > 0 ){
            Round_Robin(q0, &size_q0, quantum, switch_time );
        }
        else if(size_q1 > 0){
            SJF(q1, &size_q1, switch_time );
        }
        else if(size_q2 > 0){
            SJF(q2, &size_q2, switch_time );
        }
        else if(size_q3 > 0){
            FCFS (q3, &size_q3,switch_time );
        }

    }
    printf("\n\t\t********Execution of all queues are over*********");
    printf("\nTotal Processes=========>> %d",no_of_process);
    printf("\nTotal Execution Time=======>> %d",total_Time);

    return 0;
}    

