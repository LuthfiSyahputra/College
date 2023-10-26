#include <stdio.h>



const char* _job_title[] = {
    "Software Engineer",
    "Data Analyst",
    "Product Manager",
    "Graphic Designer"
};

const char* _job_location[] = {
    "New York",
    "San Francisco",
    "Los Angeles",
    "Chicago"
};

const char* _job_type[] = {
    "Full-time",
    "Part-time",
    "Contract"
};

int category[] = {0};

typedef struct job_postings {
    int title;
    int location;
    char* address;

    int job_type;
    int experience;
    int salary;

    int flags;
} job_property;

typedef struct job_postings_str {
    char* title;
    char* location;
    char* job_type;
} job_property_str;

typedef struct user_property {
    char* name;
    int age;
    int domicile;
    char* address;

    job_property last_job;
    job_property desired_job;

} user, applicants;

void printMenu(const char* menu[], int n);
int createAccount();

int main() {


}

void printMenu(const char* menu[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\t[%d] %s\n", i, menu[i]);    
    }
}