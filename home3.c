#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct CourseInfo{                                                              //struct to contain course info
    int courseID;
    char courseName[40];
    char courseCode[10];
    char Term[6];
    int courseSections[3];
};
typedef struct CourseInfo courseInfo;
int t, sf, ad, ad = 3;                                                          //global variables
char S[100][200];                                                               //2d array to save to file

void loadCourseInfo(courseInfo *A);
void addCourseInfo(courseInfo *A);
void displayCourseInfo(courseInfo *A);
void searchCourseID(courseInfo *A);
void searchCourseName(courseInfo *A);
void searchCourseTerm(courseInfo *A);
void saveCourseInfo(courseInfo *A);

int main(void){
    /*char *text1 = "programming,03,60,141,1,30,0,W,2015";                      //uncomment first time running program to create file
    char *text2 = "algebra,03,62,102,2,0,0,S,2013";
    char *text3 = "religion,08,98,938,1,30,90,W,2015";*/
    courseInfo A[10];
    FILE * inputfile;
    inputfile = fopen("courseInfo.csv", "r");                                   //****change r to w when creating file****
    if (inputfile == NULL){
        printf("Unable to open the file\n" );
        exit(1);
    }
    //fprintf(inputfile, "%s\n%s\n%s\n", text1, text2, text3);
    fclose(inputfile);
    loadCourseInfo(A);
    int sel;
    char yn[] = "";
    while(2){
        while(2){
            printf("Assignment 3\n------------\n");                             //program menu
            printf("1. Add a new course\n");
            printf("2. Search for a course by course ID\n");
            printf("3. Search for a course by course Name\n");
            printf("4. Search for all courses by term\n");
            printf("5. Display course data\n");
            printf("6. Save course data\n");
            printf("7. Exit\n");
            printf("Please enter a selection: ");
            scanf("%d", &sel);
            if(sel < 1 || sel > 7){
                printf("Invaild Selection!\n");
                continue;
            }
            else{
                break;
            }
        }
        if(sel == 1){
            addCourseInfo(A);
        }
        else if(sel == 2){
            searchCourseID(A);
        }
        else if(sel == 3){
            searchCourseName(A);
        }
        else if(sel == 4){
            searchCourseTerm(A);
        }
        if(sel == 5){
            displayCourseInfo(A);
        }
        else if(sel == 6){
            saveCourseInfo(A);
        }
        else if(sel == 7){
            char yes[] = "Y";
            printf("Do you want to save course data (Y/N): ");
            scanf("%s", yn);
            yn[0] = toupper(yn[0]);
            if(strcmp(yn, yes) == 0){
                saveCourseInfo(A);
                printf("Goodbye.\n");
                break;
            }
            else{
                printf("Goodbye.\n");
                break;
            }
        }
    }
    return 0;
}


void loadCourseInfo(courseInfo *A){                                             //reads info from file then stores into structure
    FILE * fp;
    fp = fopen("courseInfo.csv", "r");
    if (fp == NULL){
        printf("Unable to open the file\n" );
        exit(1);
    }
    fclose(fp);
    FILE * pf;
    pf = fopen("courseInfo.csv", "r+");
    char *token;
    int i = 0;
    char input[200];
    while(fgets(input,400,pf)){                                                 //reads then tokenizes the words to seperate from commas

        A[i].courseID = i + 1;

        token = strtok(input, ",");
        strcpy(A[i].courseName, token);                                         //saves tokenized word into struct
        A[i].courseName[0] = toupper(A[i].courseName[0]);

        token = strtok(NULL, ",");
        strcpy(A[i].courseCode, token);
        token = strtok(NULL, ",");
        strcat(A[i].courseCode, token);
        strcat(A[i].courseCode, "-");
        token = strtok(NULL, ",");
        strcat(A[i].courseCode, token);

        token = strtok(NULL, ",");
        A[i].courseSections[0]=atoi(token);
        token = strtok(NULL, ",");
        A[i].courseSections[1]=atoi(token);
        token = strtok(NULL, ",");
        A[i].courseSections[2]=atoi(token);

        token = strtok(NULL, ",");
        strcpy(A[i].Term, token);
        token = strtok(NULL, ",\n");
        strcat(A[i].Term, token);
        i++;
    }
    ad = i;
    fclose(fp);
}

void addCourseInfo(courseInfo *A){                                              //adds new courses into struct
    int k = 0;
    char name[40];
    char B[10];
    char cmp[10];
    char * ptr = name;
    A[ad].courseID = ad+1;
    t = A[ad].courseID;
    printf("Enter course name: ");
    scanf(" %40[^\n]s", name);
    name[0] = toupper(name[0]);                                                 //touppers the first letter in the inputted course name
    strcpy(A[ad].courseName, name);
    *ptr = tolower(*ptr);
    strcpy(S[ad], ptr);
    strcat(S[ad], ",");
    while(2){
        printf("Enter faculty code (format xx): ");
        scanf("%s", B);
        strcpy(cmp, B);                                                         //cmp holds the course code in proper foramt to compare
        strcat(S[ad], B);
        strcat(S[ad], ",");
        printf("Enter subject code (format xx): ");
        scanf("%s", B);
        strcat(cmp, B);
        strcat(S[ad], B);
        strcat(S[ad], ",");
        printf("Enter level code (format xxx): ");
        scanf("%s", B);
        strcat(cmp, "-");
        strcat(cmp, B);
        strcat(S[ad], B);
        strcat(S[ad], ",");
        for(int i = 0; i <= ad; i++){
            if(strcmp(A[i].courseCode,cmp) == 0){                               //compares cmd to previous course codes in the struct
                printf("Invalid: Repeated course code (%s)!\n",A[i].courseCode);
                k = 1;
                break;
            }
        }
        if(k == 1){
            k--;
            continue;
        }
        else{
            strcpy(A[ad].courseCode,cmp);
            break;
        }
    }
    int sec;
    printf("Enter number of sections: ");
    scanf("%d", &sec);
    switch(sec){
        case 1:{
            char case1[5];
            printf("Enter section code 1: ");
            scanf("%s", case1);
            A[ad].courseSections[0] = atoi(case1);
            strcat(S[ad], case1);
            strcat(S[ad], ",");
            A[ad].courseSections[1] = 0;
            strcat(S[ad], "0");
            strcat(S[ad], ",");
            A[ad].courseSections[2] = 0;
            strcat(S[ad], "0");
            strcat(S[ad], ",");
            break;
        }
        case 2:{
            char case2[5];
            char case22[5];
            printf("Enter section code 1: ");
            scanf("%s", case2);
            strcat(case2, ",");
            while(2){
                printf("Enter section code 2: ");
                scanf("%s", case22);
                if(strcmp(case2, case22) == 0){                                 //compares the second code with the first one
                    printf("Invalid: Repeated section code!\n");
                    continue;
                }
                else{
                    break;
                }
            }
            A[ad].courseSections[0] = atoi(case2);                              //saves the codes into the struct
            strcat(S[ad], case2);
            A[ad].courseSections[1] = atoi(case22);
            strcat(S[ad], case22);
            strcat(S[ad], ",");
            A[ad].courseSections[2] = 0;
            strcat(S[ad], "0");
            strcat(S[ad], ",");
            break;
        }
        case 3:{
            char case3[5];
            char case33[5];
            char case34[5];
            printf("Enter section code 1: ");
            scanf("%s", case3);
            strcat(case3, ",");
            while(2){
                printf("Enter section code 2: ");
                scanf("%s", case33);
                strcat(case33, ",");
                if(strcmp(case3, case33) == 0){
                    printf("Invalid: Repeated section code!\n");
                    continue;
                }
                else{
                    break;
                }
            }
            while(2){
                printf("Enter section code 3: ");
                scanf("%s", case34);
                strcat(case34, ",");
                if(strcmp(case33, case34) == 0 || strcmp(case3, case34) == 0){
                    printf("Invalid: Repeated section code!\n");
                    continue;
                }
                else{
                    break;
                }
            }
            A[ad].courseSections[0]=atoi(case3);
            strcat(S[ad], case3);
            A[ad].courseSections[1]=atoi(case33);
            strcat(S[ad], case33);
            A[ad].courseSections[2]=atoi(case34);
            strcat(S[ad], case34);
            break;
        }
    }
    char semyear[15];
    printf("Enter semester (S, F or W): ");
    scanf("%s", semyear);
    semyear[0] = toupper(semyear[0]);                                           //makes sure the semester is Capital
    strcat(S[ad], semyear);
    strcat(S[ad], ",");
    char year[5];
    printf("Enter year (format yyyy): ");
    scanf("%s", year);
    strcat(S[ad], year);
    strcat(semyear, year);
    strcpy(A[ad].Term, semyear);
    strcat(S[ad], "\n");
    printf("Course Added.\n\n");
    sf = ad;
    ad++;
}

void displayCourseInfo(courseInfo *A){                                          //displays the contents of the struct to the screen
    printf("\nID  Name\t  Code\t\tTerm\tSections\n");
    printf("------------------------------------------------\n");
    for(int j = 0; j < ad; j++){
        printf("%d   %s\t  %s\t%s\t%d", A[j].courseID, A[j].courseName, A[j].courseCode, A[j].Term, A[j].courseSections[0]);
        if(A[j].courseSections[1] > 0){
            printf(",%d", A[j].courseSections[1]);
        }
        if(A[j].courseSections[2] > 0){
            printf(",%d", A[j].courseSections[2]);
        }
        puts(" ");
    }
    printf("------------------------------------------------\n\n");
}

void searchCourseID(courseInfo *A){                                             //searches for courses by ID
    int ID, b, k = 0;
    printf("Enter course ID: ");
    scanf("%d", &ID);
    printf("------------------------------------------------\n");
    for(int c = 0; c < ad; c++){
        if(ID == A[c].courseID){                                                //compares the search to every value in the struct
            printf("Course ID %d was found!\n", ID);
            printf("\nID  Name\t  Code\t\tTerm\tSections\n");
            printf("------------------------------------------------\n");
            printf("%d   %s\t  %s\t%s\t%d", A[c].courseID, A[c].courseName, A[c].courseCode, A[c].Term, A[c].courseSections[0]);
            if(A[c].courseSections[1] > 0){
                printf(",%d", A[c].courseSections[1]);
            }
            if(A[c].courseSections[2] > 0){
                printf(",%d", A[c].courseSections[2]);
            }
            puts(" ");
            b = 1;
            break;
        }
        k++;
        if(k == ad){
            break;
        }
    }
    if(b != 1){
        printf("Course ID %d was not found.\n", ID);
    }
    printf("------------------------------------------------\n\n");
}

void searchCourseName(courseInfo *A){                                           //searches for the courses by name
    int b, k = 0;
    char name[40];
    printf("Enter course name: ");
    scanf(" %40[^\n]s", name);
    name[0] = toupper(name[0]);
    printf("------------------------------------------------\n");
    for(int c = 0; c < ad; c++){
        if(strcmp(A[c].courseName, name) == 0){                                 //comapres the input with names saved in the struct
            printf("Course name %s was found!\n", name);
            printf("\nID  Name\t  Code\t\tTerm\tSections\n");
            printf("------------------------------------------------\n");
            printf("%d   %s\t  %s\t%s\t%d", A[c].courseID, A[c].courseName, A[c].courseCode, A[c].Term, A[c].courseSections[0]);
            if(A[c].courseSections[1] > 0){
                printf(",%d", A[c].courseSections[1]);
            }
            if(A[c].courseSections[2] > 0){
                printf(",%d", A[c].courseSections[2]);
            }
            puts(" ");
            b = 1;
            break;
        }
        k++;
        if(k == ad){
            break;
        }
    }
    if(b != 1){
        printf("\nCourse name %s was not found.\n", name);
    }
    printf("------------------------------------------------\n\n");

}

void searchCourseTerm(courseInfo *A){                                           //seacrhes for courses by term
    int n = 0, p = 1, k = 0;
    char semyear[10];
    printf("Enter semester (S, F or W): ");
    scanf("%s", semyear);
    semyear[0] = toupper(semyear[0]);
    char year[5];
    printf("Enter year (format yyyy): ");
    scanf("%s", year);
    strcat(semyear, year);
    printf("------------------------------------------------\n");
    for(int c = 0; c < ad; c++){
        if(strcmp(A[c].Term, semyear) == 0){                                    //compares input to terms saved in the struct
            if(p == 1){
                printf("\nID  Name\t  Code\t\tTerm\tSections\n");
                printf("------------------------------------------------\n");
                p++;
            }
            printf("%d   %s\t  %s\t%s\t%d", A[c].courseID, A[c].courseName, A[c].courseCode, A[c].Term, A[c].courseSections[0]);
            if(A[c].courseSections[1] > 0){
                printf(",%d", A[c].courseSections[1]);
            }
            if(A[c].courseSections[2] > 0){
                printf(",%d", A[c].courseSections[2]);
            }
            puts(" ");
            n = 1;
        }
        k++;
        if(k == ad){
            break;
        }
    }
    if(n == 0){
        printf("Course term %s was not found.\n", semyear);
    }
    printf("------------------------------------------------\n\n");
}

void saveCourseInfo(courseInfo *A){                                             //saves any added courses to the file
    FILE * fp;
    fp = fopen("courseInfo.csv", "a");
    if (fp == NULL){
        printf("Unable to open the file\n" );
        exit(1);
    }
    for(int i = 0; i < ad; i++){                                                //writes the contents of the 2d array to the file
        fprintf(fp, "%s", S[i]);
    }
    fclose(fp);
    puts("All course information is saved.");
}
