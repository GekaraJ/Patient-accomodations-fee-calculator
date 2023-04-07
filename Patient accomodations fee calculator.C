#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATIENTS 10

struct patient {
    char name[50];
    int id;
    char date_admitted[20];
    char date_discharged[20];
    int days_admitted;
    float fee;
};

int is_valid_date(char *date) {
    int day, month, year;
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
        return 0;
    }
    struct tm check_date = {0};
    check_date.tm_year = year - 1900;
    check_date.tm_mon = month - 1;
    check_date.tm_mday = day;
    time_t check_time = mktime(&check_date);
    if (check_time == -1) {
        return 0;
    }
    return 1;
}

int main() {
    struct patient patients[MAX_PATIENTS];
    int i;

    for (i = 0; i < MAX_PATIENTS; i++) {
        printf("Fill in the fields below for the aaccomodation fee of patient %d to be computed:\n", i + 1);

        printf("Name: ");
        fgets(patients[i].name, 50, stdin);
        patients[i].name[strcspn(patients[i].name, "\n")] = 0;

        printf("ID: ");
        scanf("%d", &patients[i].id);

        // Prompt user to enter date admitted and validate input
        do {
            printf("Date Admitted (dd/mm/yyyy): ");
            scanf("%s", patients[i].date_admitted);
            if (patients[i].date_admitted < "00/00/2000" || patients[i].date_admitted > "03/04/2023" || patients[i].date_admitted > "31/12/2023"){
            	printf("You have entered an incorrect date!\nThe fee that will be generated below will be incorrect\nEnsure you have entered the correct date and try again after the program is terminated\n");}
        } while (!is_valid_date(patients[i].date_admitted));

        // Prompt user to enter date discharged and validate input
        do {
            printf("Date Discharged (dd/mm/yyyy): ");
            scanf("%s", patients[i].date_discharged);
            if(patients[i].date_discharged < patients[i].date_admitted || patients[i].date_discharged < "00/00/2000" || patients[i].date_discharged > "04/04/2023" || patients[i].date_discharged > "31/12/2023"){
            	printf("Please confirm that you have entered the correct discharge date\n");}
       
        } while (!is_valid_date(patients[i].date_discharged));
	
	
	
	
	
        // Calculate the number of days the patient was admitted
        int day, month, year;
        sscanf(patients[i].date_admitted, "%d/%d/%d", &day, &month, &year);
        struct tm start_date = {0};
        start_date.tm_year = year - 1900;
        start_date.tm_mon = month - 1;
        start_date.tm_mday = day;

        sscanf(patients[i].date_discharged, "%d/%d/%d", &day, &month, &year);
        struct tm end_date = {0};
        end_date.tm_year = year - 1900;
        end_date.tm_mon = month - 1;
        end_date.tm_mday = day;

        time_t start_time = mktime(&start_date);
        time_t end_time = mktime(&end_date);
        int num_days = (int) difftime(end_time, start_time) / (60 * 60 * 24);
        patients[i].days_admitted = num_days;

        // Calculate the fee based on the number of days admitted
        patients[i].fee = num_days * 100.0;
        if ((patients[i].fee < 0) || (patients[i].fee > 8465000)){
        	printf("Please confirm that you have entered the correct dates!!\n");}
        else{
        printf("The accomodation fee of %s as is %.2f\n",patients[i].name, patients[i].fee);}

        // Clear input buffer to prevent buffer overflow
        while (getchar() != '\n');
    }

    return 0;
}

