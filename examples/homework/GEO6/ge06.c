#include <stdio.h>

#define SIZE 80

typedef struct organization {
    char orgName[SIZE];
    char firstAndLastName[SIZE];
    char purpose[SIZE];
    double goalAmount;
} Organization;

void displayOrganization(Organization org);
void setUpOrganization(Organization *org);

int main(void) {
    Organization org1;

    setUpOrganization(&org1);
    displayOrganization(org1);

    return 0;
}

void displayOrganization(Organization org) {
    printf("Organization name: %s\n", org.orgName);
    printf("First and last name: %s\n", org.firstAndLastName);
    printf("Organization's purpose: %s\n", org.purpose);
    printf("Organization's goal amount: $%.2f\n", org.goalAmount);
}

void setUpOrganization(Organization *org) {
    // handle organization name
    printf("%s", "Please enter organization name: ");
    scanf("%s", org->orgName);

    // handle first and last name
    printf("%s", "Please enter first and last name: ");
    scanf("%s", org->firstAndLastName);

    // handle purpose
    printf("%s", "Please enter your organization's purpose: ");
    scanf("%s", org->purpose);

    // handle goal amount
    printf("%s", "Please enter your organization's goal: ");
    scanf("%lf", &org->goalAmount);
}
