#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200

typedef enum { READY, RUNNING, WAITING, TERMINATED } state_t;

typedef struct PCB{
    char name[50];
    int pid;

    int cpu_burst;
    int io_start;
    int io_duration;

    int executed_cpu;
    int io_remaining;
    int total_io_done;

    int io_start_tick;       // Tick at which IO actually begins
    int arrival_time;
    int completion_time;

    int killed_at;

    state_t state;
} PCB;

typedef struct Node {
    int idx;
    struct Node *next;
} Node;

typedef struct Queue{
    Node *head, *tail;
} Queue;

void q_init(Queue *q) { q->head = q->tail = NULL; }

void q_push(Queue *q, int idx) {
    Node *n = malloc(sizeof(Node));
    n->idx = idx; n->next = NULL;
    if (!q->tail) q->head = q->tail = n;
    else { q->tail->next = n; q->tail = n; }
}

int q_pop(Queue *q) {
    if (!q->head) return -1;
    Node *n = q->head;
    int v = n->idx;
    q->head = n->next;
    if (!q->head) q->tail = NULL;
    free(n);
    return v;
}

int q_empty(Queue *q) { return q->head == NULL; }

typedef struct KILL {
    int pid, t;
    struct KILL *next;
} KILL;

void add_kill(KILL **h, int pid, int t) {
    KILL *k = malloc(sizeof(KILL));
    k->pid = pid; k->t = t; k->next = *h;
    *h = k;
}

int main() {
    PCB P[MAX];
    int n = 0;

    KILL *kills = NULL;

    char line[200];

    while (fgets(line, sizeof(line), stdin)) {
        char w1[50];
        if (sscanf(line, "%s", w1) != 1) continue;

        if (strcmp(w1, "KILL") == 0) {
            int pid, t;
            sscanf(line, "%*s %d %d", &pid, &t);
            add_kill(&kills, pid, t);
            continue;
        }

        char name[50], s_io1[10], s_io2[10];
        int pid, cpu;

        sscanf(line, "%s %d %d %s %s", name, &pid, &cpu, s_io1, s_io2);

        int io_start = -1, io_dur = 0;

        if (strcmp(s_io1, "-") != 0) {
            io_start = atoi(s_io1);
            io_dur = atoi(s_io2);
        }

        strcpy(P[n].name, name);
        P[n].pid = pid;

        P[n].cpu_burst = cpu;
        P[n].io_start = io_start;
        P[n].io_duration = io_dur;

        P[n].executed_cpu = 0;
        P[n].io_remaining = 0;
        P[n].total_io_done = 0;
        P[n].io_start_tick = -1;

        P[n].arrival_time = 0;
        P[n].completion_time = -1;
        P[n].killed_at = -1;

        P[n].state = READY;

        n++;
    }

    Queue ready, waiting;
    q_init(&ready);
    q_init(&waiting);

    for (int i = 0; i < n; i++)
        q_push(&ready, i);

    int time = 0;
    int running = -1;
    int term_count = 0;

    while (term_count < n) {

        // 1. Apply kills
        KILL *k = kills;
        while (k) {
            if (k->t == time) {
                for (int i = 0; i < n; i++) {
                    if (P[i].pid == k->pid && P[i].state != TERMINATED) {
                        P[i].state = TERMINATED;
                        P[i].completion_time = time;
                        P[i].killed_at = time;

                        if (running == i)
                            running = -1;

                        term_count++;
                    }
                }
            }
            k = k->next;
        }

        // 2. If no running, pick from READY
        if (running == -1) {
            while (!q_empty(&ready)) {
                int idx = q_pop(&ready);
                if (P[idx].state == READY) {
                    running = idx;
                    P[idx].state = RUNNING;
                    break;
                }
            }
        }

        // 3. Execute CPU tick
        if (running != -1) {
            PCB *R = &P[running];
            R->executed_cpu++;

            // CPU finished?
            if (R->executed_cpu == R->cpu_burst) {
                R->state = TERMINATED;
                R->completion_time = time + 1;
                running = -1;
                term_count++;
            }
            else if (R->io_start != -1 && R->executed_cpu == R->io_start) {
                // Move to waiting
                R->state = WAITING;
                R->io_remaining = R->io_duration;
                R->io_start_tick = time + 1;   // IO begins next tick
                q_push(&waiting, running);
                running = -1;
            }
        }

        // 4. IO tick for WAITING processes
        Node *cur = waiting.head;
        while (cur) {
            PCB *W = &P[cur->idx];
            if (W->state == WAITING &&
                W->io_start_tick != -1 &&
                time >= W->io_start_tick &&
                W->io_remaining > 0)
            {
                W->io_remaining--;
                W->total_io_done++;

                // IO finished?
                if (W->io_remaining == 0) {
                    W->state = READY;
                    q_push(&ready, cur->idx);
                }
            }
            cur = cur->next;
        }

        time++;
    }

    // OUTPUT
    printf("PID\tName\tCPU\tIO\tStatus\tTurnaround\tWaiting\n");

    for (int i = 0; i < n; i++) {
        PCB *p = &P[i];

        if (p->killed_at != -1) {
            printf("%d\t%s\t%d\t%d\tKILLED at %d\t-\t-\n",
                p->pid, p->name, p->cpu_burst, p->total_io_done, p->killed_at);
        }
        else {
            int turn = p->completion_time - p->arrival_time;
            int wait = turn - p->cpu_burst - p->total_io_done;
            if (wait < 0) wait = 0;

            printf("%d\t%s\t%d\t%d\tOK\t%d\t%d\n",
                p->pid, p->name, p->cpu_burst, p->total_io_done, turn, wait);
        }
    }

    return 0;
}
