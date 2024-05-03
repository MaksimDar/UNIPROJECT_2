#include <stdio.h>
#include <string.h>
#define MAX_LICENSE_CHAR 15
#define MAX_STRING_SIZE 50
#define MAX_VEHICLES 8
#define MAX_OPERATIONS 10
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

typedef struct
{
    char license[MAX_LICENSE_CHAR];
    char vechicle_type;
    int status;
    int hours;
    int minutes;
} Licenses;

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

int checkDuplication(Licenses lic[], int count_vehicles, char license[])
{
    int i = 0;
    int isDuplication = 0;
    for (i = 0; i < count_vehicles; i++)
    {
        if (strcmp(lic[i].license, license) == 0)
        {
            isDuplication = 1;
            i = count_vehicles;
        }
        else
        {
            isDuplication = 0;
        }
    }
    return isDuplication;
}

int main()
{
    char rates_str[MAX_STRING_SIZE];
    char command_string[MAX_STRING_SIZE];
    int rates_length;
    char vechicle_type;
    char license[MAX_LICENSE_CHAR];
    char prev_license[MAX_LICENSE_CHAR];
    int hours, minutes;
    int count_vehicles = 0;
    int error = 0;
    int duplication_error = 0;
    int i;
    Bikes bike;
    Cars car;
    Trucks truck;
    Licenses lic[MAX_VEHICLES - 1];

    printf("Welcome to Parking LS!\n");
    printf("Enter tariffs: ");
    scanf("%s", rates_str);
    char buffer;
    scanf("%c", &buffer);
    rates_length = strlen(rates_str);
    readRates(rates_length, rates_str);

    do
    {
        printf("\nParking LS> ");
        fgets(command_string, sizeof(command_string), stdin);
        if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes))
        {
            if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes) != 4 || (vechicle_type != 'B' && vechicle_type != 'C' && vechicle_type != 'T'))
            {
                error = 1;
            }
            else
            {
                if (checkDuplication(lic, count_vehicles, license))
                {
                    error = 2;
                }

                else
                {
                    if (hours > 23 || hours < 0 || minutes < 0 || minutes > 59)
                    {
                        error = 3;
                    }
                    else
                    {
                        error = 4;
                    }
                }
            }
            switch (error)
            {
            case 1:
                printf(" (ERROR) Wrong command\n");
                break;
            case 2:
                printf(" (ERROR) This vehicle is already in the parking!\n");
                break;
            case 3:
                printf(" (ERROR) Wrong time format\n");
                break;
            case 4:
                if (count_vehicles >= 0 && count_vehicles <= MAX_VEHICLES - 1)
                {
                    strcpy(lic[count_vehicles].license, license);
                    lic[count_vehicles].status = 1;
                    lic[count_vehicles].vechicle_type = vechicle_type;
                    lic[count_vehicles].hours = hours;
                    lic[count_vehicles].minutes = minutes;
                    count_vehicles++;
                }
                else
                {
                    printf(" (ERROR) No more vehicles are accepted\n");
                };
                break;
            default:
                break;
            }
        }
        else
        {
            if (sscanf(command_string, "exit %s %d:%d", license, &hours, &minutes) != 3)
            {
                printf(" (ERROR) Wrong command\n");
            }
            else
            {
                if (!checkDuplication(lic, count_vehicles, license))
                {
                    printf(" (ERROR) This vehicle is not in the parking\n");
                }
                else
                {
                    for (i = 0; i < MAX_VEHICLES; i++)
                    {
                        if (strcmp(license, lic[i].license))
                        {
                            printf("%s", lic[i].license);
                        }
                    }
                }
            }
        }

    } while (1);
    return 0;
}
// FIRST STRING
// BIKES:2/3/4#CARS:3/4/6#TRUCKS:5/10/12
// CARS:3/4/6#TRUCKS:5/10/12#BIKES:2/3/4
// TRUCKS:5/10/12#BIKES:2/3/4#CARS:3/4/6

// ENTER STRING
// enter C 6756FGT 12:55
// enter B 1234TTT 13:34
// enter T 1122BGT 13:46
// enter T 8986GTT 17:00
// enter T 1900FRW 19:25
// enter C 1999FTW 20:20
// enter B 1112TRW 21:25
// enter C 6767BBX 21:39
// enter C 9871CDF 22:23

// EXIT STRING
// exit 5109GTY 13:14

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

// printf(" (ERROR) This vehicle is already in the parking!");
