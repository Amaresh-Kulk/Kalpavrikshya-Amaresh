#include "Players_data.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


// typedef struct {
//     int id;
//     const char* name;
//     const char* team;
//     const char* role;
//     int totalRuns;
//     float battingAverage;
//     float strikeRate;
//     int wickets;
//     float economyRate;
// } Player;

//   Batsman: (BattingAverage × StrikeRate) / 100
//   Bowlers: (Wickets × 2) + (100 − EconomyRate)
//   All-Rounders: [(BattingAverage × StrikeRate) / 100] + (Wickets × 2)

int availableIDs[1000];

void copyPlayerInfo(Player *p1, Player p2) {
    *p1 = p2;
}

void mergeSortByID(Player p1[], int l, int m, int r) {
  int leftLen = m - l + 1;
  int rightLen = r - m;

  Player left[leftLen];
  Player right[rightLen];

  for(int i = 0;i < leftLen;i++)  {
    copyPlayerInfo(&left[i], p1[i + l]);
  }

  for(int i = 0;i < rightLen;i++) {
    copyPlayerInfo(&right[i], p1[i + m + 1]);
  }

  int i = 0, j = 0, k = l;
  
  while(i < leftLen && j < rightLen)  {
    if(left[i].id < right[j].id)  {
      copyPlayerInfo(&p1[k++], left[i++]);
    } else  {
      copyPlayerInfo(&p1[k++], right[j++]);
    }
  }

  while(i < leftLen)  copyPlayerInfo(&p1[k++], left[i++]);
  while(j < rightLen) copyPlayerInfo(&p1[k++], right[j++]);
}

void sortByID(Player p1[], int l, int r)  {
  if(l < r) {
    int mid = l + (r - l) / 2;
    sortByID(p1, l, mid);
    sortByID(p1, mid + 1, r);
    mergeSortByID(p1, l, mid, r);
  }
}

int searchID(Player p1[], int id, int n)  {
  

  int start = 0, end = n - 1;

  while(start <= end) {
    int mid = start + (end - start) / 2;

    if(p1[mid].id == id) return mid;
    else if(p1[mid].id > id) end = mid - 1;
    else start = mid + 1;
  }
  return -1;
}

int checkInvalidID(int id)  {
  if(id < 1 || id > 1500) return 1;
  return 0;
}


void giveAvailableIDs()  {
  printf("\nThe available IDs are: ");
  for(int i = 1;i <= 1000;i++)  {
    if(!availableIDs[i])  printf("%d ", i);
  }
}

int getValidID(Player p1[], int n)  {
  int id, flag = 0;
  do
  {
    if(flag)  {
      printf("\nPlease enter and valid unique id\n");
      giveAvailableIDs();
    }

    printf("\nEnter Team ID to add player: ");
    scanf("%d", &id);
    flag = 1;
  } while (searchID(p1, id, n) != -1 && checkInvalidID(id));
 return id; 
}

void displayAll(Player p1[], int n) {
  
  for(int i = 0;i < n;i++) {
    printf("\n%d\t%s\t%s\t%s\t%d\t%f\t%f\t%d\t%f", p1[i].id, p1[i].name, p1[i].team, p1[i].role, p1[i].totalRuns, p1[i].battingAverage, p1[i].economyRate, p1[i].wickets, p1[i].strikeRate);
  }
}

int checkInvalidPlayerName(char name[])  {
  for(int i = 0;name[i] != '\0';i++)  {
    if(name[i] == ' ')  continue;
    
    if(i == 0 || name[i - 1] == ' ')  {
      if(!isupper(name[i]))  return 1;
    }  

    if(!isalpha(name[i])) return 1;
  }

  if(strlen(name) > 50) return 1;
  return 0;
}

void getValidPlayerName(char *name)  {
  int flag = 0;
  do
  { 
    if(flag)  {
      printf("\nName should have following things: ");
      printf("\n1. First name and Last Name should have 1st letter capital and the rest small");
      printf("\n2. Name should not contain non alphabetic letters");
    }
    getchar();
    printf("\nName: ");
    fgets(name, sizeof(name), stdin);
    
    name[strcspn(name, "\n")] = '\0';


  } while (checkInvalidPlayerName(name));
  
}

int checkInvalidTeamName(char *teamName)  {
  for(int i = 0;i < teamCount;i++)  {
    if(strcmp(teams[i], teamName) == 0) return i;
  }
  return -1;
}

void getValidTeamName(char *team) {
  int flag = 0;
  do
  {
    if(flag)  printf("\nTeam entered doesn't exists");
    printf("\nEnter team Name: ");
    getchar();
    fgets(team, sizeof(team), stdin);
    
    team[strcspn(team, "\n")] = '\0';
    flag = 1;
  } while (checkInvalidTeamName(team) == -1);
}

void getValidRole(char *role) {
  int choice;

  while(1)  {
    printf("\n Role (1-Batsman, 2-Bowler, 3-All-rounder): ");
    scanf("%d", &choice);
    switch(choice)  {
      case 1: strcpy(role, "Batsman"); return;
      case 2: strcpy(role, "Bowler"); return;
      case 3: strcpy(role, "All-rounder");  return;
      default: printf("\nPlease enter valid choice");
    }
  }
}

int checkInvalidTotalRuns(int runs) {
  if(runs < 0)  return 1;
  return 0;
}

int getValidTotalRuns() {
  int flag = 0, runs;

  do
  {
    if(flag)  printf("\nPlease enter valid total runs");

    printf("\n Total Runs: ");
    scanf("%d", &runs);

    flag = 1;
  } while (checkInvalidTotalRuns(runs));
  return runs;
}

int checkInvalidAVG(float avg)  {
  if(avg < 0) return 1;
  return 0;
}

float getValidBattingAVG()  {
  int flag = 0;
  float avg;

  do
  {
    if(flag)  printf("\nEnter valid average");

    printf("\nBatting Average: ");
    scanf("%f", &avg);

    flag = 1;
  } while (checkInvalidAVG(avg));
  
  return avg;
}

int checkInvalidStrikeRate(float rate)  {
  if(rate < 0)  return 1;
  return 0;
}

float getValidStrikeRate()  {
  int flag = 0;
  float rate;
  
  do
  {
    if(flag)  printf("\nPlease enter valid strike rate");

    printf("\nStrike Rate: ");
    scanf("%f", &rate);

    flag = 1;
  } while (checkInvalidStrikeRate(rate));
  
  return rate;
}

int checkInvalidWickets(int wicket) {
  if(wicket < 0)  return 1;
  return 0;
}

int getValidWickets() {
  int flag = 0, wicket;

  do
  {
    if(flag)  printf("\nEnter valid number of wickets");

    printf("\nWickets: ");
    scanf("%d", &wicket);

    flag = 1;
  } while (checkInvalidWickets(wicket));
  
  return wicket;
}

int checkValidEconomy(float economy)  {
  if(economy < 0) return 1;
  return 0;
}

float getValidEconomy() {
  int flag = 0;
  float economy;

  do
  {
    if(flag)  printf("\nEnter valid economy rate");

    printf("\n Economy Rate: ");
    scanf("%f", &economy);

    flag = 1;
  } while (checkValidEconomy(economy));
  
  return economy;
}


void addPlayer(Player **p1, int *n)  {
  
  sortByID(*p1, 0, *n - 1);
  //displayAll(p1);

  char *name = malloc(50 * sizeof(char)), *team = malloc(50 * sizeof(char)), *role = malloc(50 * sizeof(char));
  getValidPlayerName(name);
  getValidTeamName(team);
  getValidRole(role);
  Player newPlayer = {getValidID(*p1, *n), name, team, role, getValidTotalRuns(), getValidBattingAVG(), getValidStrikeRate(), getValidWickets(), getValidEconomy()};
  
  
  *p1 = realloc(*p1, (*n + 1) * sizeof(Player));
  copyPlayerInfo(&((*p1)[*n]), newPlayer);
  *n = *n + 1;
  //displayAll(*p1, *n);
  free(name);
  free(team);
  free(role);

  availableIDs[newPlayer.id] = 1;
}

void mergeSortByTeamName(Player p1[], int l, int m, int r) {
  int leftLen = m - l + 1;
  int rightLen = r - m;

  Player left[leftLen];
  Player right[rightLen];

  for(int i = 0;i < leftLen;i++)  {
    copyPlayerInfo(&left[i], p1[i + l]);
  }

  for(int i = 0;i < rightLen;i++) {
    copyPlayerInfo(&right[i], p1[i + m + 1]);
  }

  int i = 0, j = 0, k = l;
  
  while(i < leftLen && j < rightLen)  {
    if(strcmp(left[i].team, right[j].team) < 0)  {
      copyPlayerInfo(&p1[k++], left[i++]);
    } else  {
      copyPlayerInfo(&p1[k++], right[j++]);
    }
  }

  while(i < leftLen)  copyPlayerInfo(&p1[k++], left[i++]);
  while(j < rightLen) copyPlayerInfo(&p1[k++], right[j++]);
}

void sortByTeamName(Player p1[], int l, int r)  {
  if(l < r) {
    int mid = l + (r - l) / 2;
    sortByTeamName(p1, l, mid);
    sortByTeamName(p1, mid + 1, r);
    mergeSortByTeamName(p1, l, mid, r);
  }
}

int searchFirstOccurance(Player p1[], int n, char team[])  {
  int start = 0, end = n - 1, res = -1;
  while(start <= end) {
    int mid = start + (end - start) / 2;
    if(strcmp(p1[mid].team, team) == 0) {
      res = mid;
      end = mid - 1;
    } else if(strcmp(p1[mid].team, team) < 0) start = mid + 1;
    else end = mid - 1;
  }
  return res;
}

int searchLastOccurance(Player p1[], int n, char team[])  {
  int start = 0, end = n - 1, res = -1;
  while(start <= end) {
    int mid = start + (end - start) / 2;
    if(strcmp(p1[mid].team, team) == 0) {
      res = mid;
      start = mid + 1;
    } else if(strcmp(p1[mid].team, team) < 0) start = mid + 1;
    else end = mid - 1;
  }
  return res;
}

void displaySpecificTeamPlayers(Player p1[], int n) {
  
  sortByTeamName(p1, 0, n - 1);
  printf("\nEnter team name: ");
  getchar();
  char team[50];
  fgets(team, sizeof(team), stdin);
  team[strcspn(team, "\n")] = '\0';
  int start = searchFirstOccurance(p1, n, team);
  int end = searchLastOccurance(p1, n, team);

  int total = 0;
  float avgStrikeRate = 0.0;
  int i = start;
  printf("\n ====================================================================================\n");
  printf("\nID\tName\tRole\tRuns\tAvg\tSR\tWkts\tER\tPerf.Index\n");
  printf("\n ====================================================================================\n");

  while(i <= end) {
    printf("\n%d\t%s\t%s\t%s\t%d\t%f\t%f\t%d\t%f", p1[i].id, p1[i].name, p1[i].team, p1[i].role, p1[i].totalRuns, p1[i].battingAverage, p1[i].economyRate, p1[i].wickets, p1[i].strikeRate);
    i++;
    total++;
    avgStrikeRate += p1[i].strikeRate;
  }

  avgStrikeRate /= total;

  printf("\nTotal Number Of Players: %d", total);
  printf("\nAverage strike rate: %f", avgStrikeRate);
  //displayAll(p1, n);
}

typedef struct BattingStrikeRate  {
  int id;
  char name[50];
  float avgSR;
  int total;
}BattingStrikeRate;

void copyBattingInfo(BattingStrikeRate *b1, BattingStrikeRate b2) {
  *b1 = b2;
}

void mergeSortByAVGSR(BattingStrikeRate b1[], int l, int m, int r)  {
  int leftLen = m - l + 1;
  int rightLen = r - m;

  BattingStrikeRate left[leftLen];
  BattingStrikeRate right[rightLen];

  for(int i = 0;i < leftLen;i++)  {
    copyBattingInfo(&left[i], b1[i + l]);
  }

  for(int i = 0;i < rightLen;i++) {
    copyBattingInfo(&right[i], b1[i + m + 1]);
  }

  int i = 0, j = 0, k = l;
  
  while(i < leftLen && j < rightLen)  {
    if(left[i].avgSR > right[j].avgSR)  {
      copyBattingInfo(&b1[k++], left[i++]);
    } else  {
      copyBattingInfo(&b1[k++], right[j++]);
    }
  }

  while(i < leftLen)  copyBattingInfo(&b1[k++], left[i++]);
  while(j < rightLen) copyBattingInfo(&b1[k++], right[j++]);
}

void sortByAVGSR(BattingStrikeRate b1[], int l, int r) {
  if(l < r) {
    int m = l + (r - l) / 2;
    sortByAVGSR(b1, l, m);
    sortByAVGSR(b1, m + 1, r);
    mergeSortByAVGSR(b1, l, m, r);
  }
}

void displayTeamsAVGStrikeRate(Player p1[], int n)  {
  BattingStrikeRate b1[teamCount];
  sortByTeamName(p1, 0, n - 1);
  for(int i = 0;i < teamCount;i++)  {
    char team[50];
    strcpy(team, teams[i]);
    int start = searchFirstOccurance(p1, n, team), end = searchLastOccurance(p1, n, team);

    float avgSR = 0;
    int total = 0;
    while(start <= end) {
      if(strcmp(p1[start].role, "Bowler") != 0) {
        avgSR += p1[start].strikeRate;
        total++;
      }
      
      start++;
    }

    b1[i].id = i;
    strcpy(b1[i].name, team);
    b1[i].avgSR = avgSR / total;
    b1[i].total = total;
  }
  sortByAVGSR(b1, 0, teamCount - 1);

  printf("\nTeams Sorted by Average Batting Strike Rate");
  printf("\n =========================================================\n");

  printf("\n ID\tTeam Name\tAvg Bat SR\tTotal Players");
  printf("\n =========================================================\n");

  for(int i = 0;i < teamCount;i++)  {
    printf("\n%d\t%s\t%f\t%d", b1[i].id, b1[i].name, b1[i].avgSR, b1[i].total);
  }
}

typedef struct playerPerformance  {
    int id;
    char name[50];
    char team[50];
    char role[50];
    int totalRuns;
    float battingAverage;
    float strikeRate;
    int wickets;
    float economyRate;
    float perfIdx;
}playerPerformance;

void copyPerformanceInfo(playerPerformance *p1, playerPerformance p2) {
  *p1 = p2;
}

void mergeSortByRolePerformance(playerPerformance p1[], int l, int m, int r)  {
  int leftLen = m - l + 1;
  int rightLen = r - m;

  playerPerformance left[leftLen];
  playerPerformance right[rightLen];

  for(int i = 0;i < leftLen;i++)  {
    copyPerformanceInfo(&left[i], p1[i + l]);
  }

  for(int i = 0;i < rightLen;i++) {
    copyPerformanceInfo(&right[i], p1[i + m + 1]);
  }

  int i = 0, j = 0, k = l;
  
  while(i < leftLen && j < rightLen)  {
    int cmp = strcmp(left[i].role, right[j].role);
    if(cmp < 0 || (cmp == 0 && left[i].perfIdx > right[j].perfIdx))  {
      copyPerformanceInfo(&p1[k++], left[i++]);
    } else  {
      copyPerformanceInfo(&p1[k++], right[j++]);
    }
  }

  while(i < leftLen)  copyPerformanceInfo(&p1[k++], left[i++]);
  while(j < rightLen) copyPerformanceInfo(&p1[k++], right[j++]);
}

void sortByRolePerformance(playerPerformance p1[], int l, int r) {
  if(l < r) {
    int m = l + (r - l) / 2;
    sortByRolePerformance(p1, l, m);
    sortByRolePerformance(p1, m + 1, r);
    mergeSortByRolePerformance(p1, l, m, r);
  }
}

int giveRoles(int choice, char role[]) {
  switch(choice)  {
    case 1: strcpy(role, "Batsman");
            break;
    case 2: strcpy(role, "Bowler");
            break;
    case 3: strcpy(role, "All-rounder");
            break;
    default: printf("Invalid choice");
            return - 1;
  }
  return 1;
}

int searchFirstOccuranceRole(playerPerformance p1[], int start, int end, int choice) {
  char role[50];
  
  if(giveRoles(choice, role) == -1) return -1;

  int res = -1;
  while(start <= end) {
    int mid = start + (end - start) / 2;
    if(strcmp(p1[mid].role, role) == 0) {
      res = mid;
      end = mid - 1;
    } else if(strcmp(p1[mid].role, role) > 0) end = mid - 1;
    else  start = mid + 1;
  }

  return res;
}

int searchLastOccuranceRole(playerPerformance p1[], int start, int end, int choice) {
  char role[50];
  
  if(giveRoles(choice, role) == -1) return -1;

  int res = -1;
  while(start <= end) {
    int mid = start + (end - start) / 2;
    if(strcmp(p1[mid].role, role) == 0) {
      res = mid;
      start = mid + 1;
    } else if(strcmp(p1[mid].role, role) > 0) end = mid - 1;
    else  start = mid + 1;
  }

  return res;
}


void addDetailsInPlayerPerformance(Player p1[], playerPerformance per[], int start, int end)  {
    for(int i = start, k = 0;i <= end;i++, k++) {
    per[k].battingAverage = p1[i].battingAverage;
    per[k].economyRate = p1[i].economyRate;
    per[k].id = p1[i].id;
    strcpy(per[k].name, p1[i].name);
    strcpy(per[k].role, p1[i].role);
    strcpy(per[k].team, p1[i].team);
    per[k].strikeRate = p1[i].strikeRate;
    per[k].totalRuns = p1[i].totalRuns;
    per[k].wickets = p1[i].wickets;
    
    if(strcmp(per[k].role, "Batsman") == 0) {
      per[k].perfIdx = ((float)per[k].battingAverage * per[k].strikeRate) / 100;
    } else if(strcmp(per[k].role, "Bowler") == 0) {
      per[k].perfIdx = (per[k].wickets * 2) + (100 - per[k].economyRate);
    } else  {
      per[k].perfIdx = (((float)per[k].battingAverage * per[k].strikeRate) / 100) + (per[k].wickets * 2);
    }
  }
}

void displayPlayerPerformance(playerPerformance per[], int start, int k, int choice) {
  char role[50];
  if(giveRoles(choice, role) == -1) return;
  
  printf("\n====================================================================================\n");
  printf("\nID\tName\tRole\tRuns\tAvg\tSR\tWkts\tER\tPerf.Index\n");
  printf("\n====================================================================================\n");
  
  for(int i = start;i < start + k && strcmp(per[i].role, role) == 0;i++)  {
    printf("\n%d\t%s\t%s\t%d\t%f\t%f\t%d\t%f\t%f", per[i].id, per[i].name, per[i].role, per[i].totalRuns, per[i].battingAverage, per[i].strikeRate, per[i].wickets, per[i].economyRate, per[i].perfIdx);
  }
}

void displayTopKPlayers(Player p1[], int n) {
  sortByTeamName(p1, 0, n - 1);

  char team[50];
  printf("\nEnter team Name: ");
  getchar();
  fgets(team, sizeof(team), stdin);
  
  team[strcspn(team, "\n")] = '\0';

  int start = searchFirstOccurance(p1, n, team);
  int end = searchLastOccurance(p1, n, team);

  playerPerformance per[end - start + 1];
  
  addDetailsInPlayerPerformance(p1, per, start, end);
  


  sortByRolePerformance(per, 0, (end - start));
  int choice;
  printf("\nEnter Role (1-Batsman, 2-Bowler, 3-All-rounder): ");
  scanf("%d", &choice);



  int k;
  printf("\nEnter number of players: ");
  scanf("%d", &k);

  if(k > end - start + 1) k = end - start + 1;
  start = searchFirstOccuranceRole(per, 0, end - start + 1, choice);
  
  if(start == -1) return;


  displayPlayerPerformance(per, start, k, choice);

}

void displayAllPlayersSpecificRole(Player p1[], int n)  {
  int choice;
  printf("\nEnter Role (1-Batsman, 2-Bowler, 3-All-rounder): ");
  scanf("%d", &choice);

  // char role[50];
  // if(giveRoles(choice, role) == -1) return;
  
  playerPerformance *per = (playerPerformance *)malloc(n * sizeof(playerPerformance));
  addDetailsInPlayerPerformance(p1, per, 0, n - 1);
  //printf("\n\n\n\n%s\n\n\n\n", per[0].name);
  sortByRolePerformance(per, 0, n - 1);
  //printf("\n\n\n\n%s\n\n\n\n", per[0].name);
  int start = searchFirstOccuranceRole(per, 0, n - 1, choice);
  int end = searchLastOccuranceRole(per, 0, n - 1, choice);
  displayPlayerPerformance(per, start, end + 1, choice);

  free(per);
}

int main()  {
  
  
  Player *p1 = (Player *)malloc(playerCount * sizeof(Player));
  
  for(int i = 0;i < playerCount;i++)  {
    copyPlayerInfo(&p1[i], players[i]);
    availableIDs[p1[i].id] = 1;
  }

  int numPlayers = playerCount;

  


  
  int choice;
  
  while(1)  {
    printf("\n==============================================================================\n");
    printf("\n ICC ODI Player Performance Analyzer\n");
    printf("\n==============================================================================\n");
    printf("\n 1. Add Player to Team");
    printf("\n 2. Display Players of a Specific Team");
    printf("\n 3. Display Teams by Average Batting Strike Rate");
    printf("\n 4. Display Top K Players of a Specific Team by Role");
    printf("\n 5. Display all Players of specific role Across All Teams by performance index");
    printf("\n 6. Exit");
    printf("\n==============================================================================\n");
    printf("\n Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)  {
      case 1: addPlayer(&p1, &numPlayers);
              break;
      case 2: displaySpecificTeamPlayers(p1, numPlayers);
              break;
      case 3: displayTeamsAVGStrikeRate(p1, numPlayers);
              break;
      case 4: displayTopKPlayers(p1, numPlayers);
              break;
      case 5: displayAllPlayersSpecificRole(p1, numPlayers);
              break;
      case 6: free(p1); 
              exit(0);
    }
  }

  return 0;
}