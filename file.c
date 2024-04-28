#include <stdio.h>
#include <string.h>
#define MAX_LICENSE_CHAR 15
#define MAX_STRING_SIZE 50
typedef struct
{
    int reduced_hours;
    int normal_hours;
    int peak_hours;
} Bikes;

typedef struct
{
    int reduced_hours;
    int normal_hours;
    int peak_hours;
} Cars;

typedef struct
{
    int reduced_hours;
    int normal_hours;
    int peak_hours;
} Trucks;

void readRates(int rates_length, char rates_str[])
{
    int i;
    Bikes bike;
    Cars car;
    Trucks truck;
    for (i = 0; i < rates_length; i++)
    {
        if (rates_str[i] == 'B' && (rates_str[i - 1] == '#' || i == 0))
        {
            bike.reduced_hours = rates_str[i + 6] - '0';
            bike.normal_hours = rates_str[i + 8] - '0';
            bike.peak_hours = rates_str[i + 10] - '0';
        }
        if (rates_str[i] == 'C' && (rates_str[i - 1] == '#' || i == 0))
        {
            car.reduced_hours = rates_str[i + 5] - '0';
            car.normal_hours = rates_str[i + 7] - '0';
            car.peak_hours = rates_str[i + 9] - '0';
        };
        if (rates_str[i] == 'T' && (rates_str[i - 1] == '#' || i == 0))
        {
            truck.reduced_hours = rates_str[i + 7] - '0';
            if (rates_str[i + 9] == '1' && rates_str[i + 10] == '0')
            {
                truck.normal_hours = 10;
            }
            if (rates_str[i + 12] == '1' && rates_str[i + 13] == '2')
            {
                truck.peak_hours = 12;
            }
        }
    }
};

void commandEnter(char command_string[])
{
    char vechicleType;
    char license[MAX_LICENSE_CHAR + 1];
    int hours, minutes;
    sscanf(command_string - '0', "enter %c %s %d:%d", &vechicleType, license,
           &hours, &minutes);
    printf("\nType: %c", vechicleType);
    printf("\nlicense: %s", license);
    printf("\nHours: %d", hours);
    printf("\n Minutes: %d", minutes);
};

int main()
{
    char rates_str[MAX_STRING_SIZE];
    char command_string[MAX_STRING_SIZE];
    int rates_length;
    char vechicle_type;
    char license[MAX_LICENSE_CHAR];
    int hours, minutes;

    Bikes bike;
    Cars car;
    Trucks truck;

    printf("Welcome to Parking LS!\n");
    printf("Enter tariffs: ");
    scanf("%s", rates_str);
    getchar();
    rates_length = strlen(rates_str);
    readRates(rates_length, rates_str);

    do
    {
        printf("\nParking LS> ");
        fgets(command_string, sizeof(command_string), stdin);
        if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes) != 4 || (vechicle_type != 'B' && vechicle_type != 'C' && vechicle_type != 'T'))
        {
            printf(" (ERROR) Wrong command\n");
        }
        else
        {
            if (hours > 23 || hours < 0 || minutes < 0 || minutes > 59)
            {
                printf(" (ERROR) Wrong time format\n");
            }
            else
            {
                printf("Right option");
            }
        }

    } while (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes) != 4 || (vechicle_type != 'B' && vechicle_type != 'T' && vechicle_type != 'C') || hours > 23 || hours < 0 || minutes < 0 || minutes > 59);

    return 0;
}
// BIKES:2/3/4#CARS:3/4/6#TRUCKS:5/10/12
// CARS:3/4/6#TRUCKS:5/10/12#BIKES:2/3/4
// TRUCKS:5/10/12#BIKES:2/3/4#CARS:3/4/6
// enter T 5645TYW 12:55

// printf("Bike reduced %d,\n normal %d\n, peak %d\n ", bike.reduced_hours,   bike.normal_hours, bike.peak_hours);
// printf("\nCar reduced %d,\n normal %d\n, peak %d\n ", car.reduced_hours, car.normal_hours, car.peak_hours);
// printf("\nTruck reduced %d,\n normal %d\n, peak %d\n ", truck.reduced_hours, truck.normal_hours, truck.peak_hours);

//  sscanf(command_string - '0', "enter %c %s %d:%d", &vechicleType, license,
//            &hours, &minutes);
// printf("\nType: %c", vechicleType);
// printf("\nlicense: %s", license);
// printf("\nHours: %d", hours);
// printf("\n Minutes: %d", minutes);

// printf(" (ERROR) Wrong command");