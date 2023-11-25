// This is the code for "Preemptive Priority Scheduling Algorithm" 

// Here I have taken input from user for Arrival Time (AT), Burst Time (BT) & Priority for each process 


// Here the Priority Preference Order which is used is: Smaller The Number, Higher The Priority.


#include <stdio.h>

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))


struct process{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

int main(){
    int n;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilization;
    float throughput;

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;

    int burst_remaining[100];
    int is_completed[100] = {0};


    printf("\n");
    printf("# Enter the number of processes: ");
    scanf("%d", &n);
    printf("\n");

    if(n>100){
        printf("\n");
        printf("---> Input value for \"No. of processes\" cannot me more than 100. \n");
        printf("\n");
        return 0;
    }
    else if(n<0){
        printf("\n");
        printf("---> You have entered the input for \"No. of processes\" as a -ve number. \n");
        printf("---> \"No. of processes\" cannot be -ve, therefore this code has stopped it's execution. \n");
        printf("---> Try Again!! By giving input for \"No. of processes\" as a +ve number. \n");
        printf("\n");
        return 0;
    }
    else if(n==0){
        printf("\n");
        printf("---> You have entered the input for \"No. of processes\" as 0. \n");
        printf("---> So, there are no processes in the ready queue which has to be processed by the scheduling algorithm, therefore this code has stopped it's execution. \n");
        printf("\n");
        return 0;
    }


    for (int i = 0; i < n; i++){
        int x, y, z;

        printf("* Enter arrival time of process %d: ", i + 1);
        scanf("%d", &x);

        if(x>=0){
            p[i].arrival_time = x;
        }
        else{
            printf("\n");
            printf("---> You have entered a -ve no. as a input in arrival time's field. \n");
            printf("---> & Arrival time cannot be negative. \n");
            printf("---> So, Try Again!! And this time for successful execution of code, Either give 0 or a +ve no. as a input in arrival time's field. \n");
            printf("\n");
            return 0;
        }

        printf("* Enter burst time of process %d: ", i + 1);
        scanf("%d", &y);

        if(y>=1){
            p[i].burst_time = y;
        }
        else if(y==0){
            printf("\n");
            printf("---> You have entered 0 as a input in burst time's field. \n");
            printf("---> & if a process wants to get processed by the scheduling algorithm than it cannot have 0 as it's burst time. \n");
            printf("---> Because having 0 as a burst time simply means that the process has already completed it's execution. \n");
            printf("---> So, Try Again!! And this time for successful execution of code, Either give 1 or any other +ve no. as a input in burst time's field. \n");
            printf("\n");
            return 0;
        }
        else{
            printf("\n");
            printf("---> You have entered a -ve no. as a input in burst time's field. \n");
            printf("---> & Burst time cannot be negative. \n");
            printf("---> So, Try Again!! And this time for successful execution of code, Either give 1 or any other +ve no. as a input in burst time's field. \n");
            printf("\n");
            return 0;
        }

        printf("* Enter priority of the process %d: ", i + 1);
        scanf("%d", &z);

        if(z>10000000){
            printf("\n");
            printf("---> You have entered a no. greater than \"10000000\" as a input in priority's field. \n");
            printf("---> & Priority cannot be more than \"10000000\" for this code in case of \"Priority Preference Order: Smaller The Number, Higher The Priority.\" \n");
            printf("---> So, Try Again!! And this time for successful execution of code, Either give 0 or a +ve no. in the range of 1 to 10000000 as a input in priority's field. \n");
            printf("\n");
            return 0;
        }
        else if(z>=0){
            p[i].priority = z;
        }
        else{
            printf("\n");
            printf("---> You have entered a -ve no. as a input in priority's field. \n");
            printf("---> & Priority cannot be negative. \n");
            printf("---> So, Try Again!! And this time for successful execution of code, Either give 0 or a +ve no. in the range of 1 to 10000000 as a input in priority's field. \n");
            printf("\n");
            return 0;
        }

        p[i].pid = i + 1;

        burst_remaining[i] = p[i].burst_time;
        printf("\n");
    }


    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while (completed != n){
        int idx = -1;
        int mx = 10000000;

        for (int i = 0; i < n; i++){

            if (p[i].arrival_time <= current_time && is_completed[i] == 0){

                if (p[i].priority < mx){

                    mx = p[i].priority;
                    idx = i;
                }

                if (p[i].priority == mx){

                    if (p[i].arrival_time < p[idx].arrival_time){

                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1){

            if (burst_remaining[idx] == p[idx].burst_time){

                p[idx].start_time = current_time;
                total_idle_time = total_idle_time + p[idx].start_time - prev;
            }

            burst_remaining[idx] = burst_remaining[idx] - 1;
            current_time++;
            prev = current_time;

            if (burst_remaining[idx] == 0){

                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time = total_turnaround_time + p[idx].turnaround_time;
                total_waiting_time = total_waiting_time + p[idx].waiting_time;
                total_response_time = total_response_time + p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        }

        else{
            current_time++;
        }
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;

    for (int i = 0; i < n; i++){

        min_arrival_time = min(min_arrival_time, p[i].arrival_time);
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_utilization = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    throughput = (float) n / (max_completion_time - min_arrival_time);

    printf("#PID\t  AT\t  BT\t  Pri.\t  ST\t  CT\t  TAT\t  WT\t  RT\t  \n");

    for (int i = 0; i < n; i++){
        printf("%d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  \n", i + 1, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].start_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time, p[i].response_time);
    }

    printf("\n");

    printf("@ Average Turnaround Time = %.2f \n", avg_turnaround_time);
    printf("@ Average Waiting Time = %.2f \n", avg_waiting_time);
    printf("@ Average Response Time = %.2f \n", avg_response_time);
    printf("@ CPU Utilization = %.2f%% \n", cpu_utilization);
    printf("@ Throughput = %.2f processes/unit time \n", throughput);

    printf("\n");

    return 0;
}
