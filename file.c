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
    char vehicle_type;
    int status;
    int hours;
    int minutes;
    int counter;
} Licenses;

typedef struct
{
    char license[MAX_LICENSE_CHAR];
    char vehicle_type;
    int start_hours;
    int start_minutes;
    int finish_hours;
    int finish_minutes;
    float price;
} Operation;
typedef struct
{
    int total_counter;
} Counter;
typedef struct
{
    Operation operation;
} Database;

int checkDuplication(Licenses lic[], int count_vehicles, char license[])
{
    int i = 0;
    int is_duplication = 0;
    for (i = 0; i < count_vehicles; i++)
    {
        if (strcmp(lic[i].license, license) == 0)
        {
            is_duplication = 1;
            i = count_vehicles;
        }
        else
        {
            is_duplication = 0;
        }
    }
    return is_duplication;
}

int checkTime(Licenses lic[], int minutes, int hours, char license[])
{
    int i;
    int time_status;
    for (i = 0; i < MAX_VEHICLES; i++)
    {
        if (strcmp(lic[i].license, license) == 0)
        {
            if ((minutes <= lic[i].minutes && hours == lic[i].hours) || hours < lic[i].hours)
            {
                time_status = 3;
            }
            else
            {
                time_status = 0;
            }
        }
    };
    return time_status;
}

int operationClosed(Licenses lic[], int count_vehicles, char license[], int hours, int minutes, Bikes bike, Cars car, Trucks truck, Database database[], Operation operation[], Counter counter)
{
    int i;
    int total_minutes;
    int enter_minutes;
    int exit_minutes;
    float price_minute, total_price;
    for (i = 0; i < count_vehicles; i++)
    {
        if (strcmp(lic[i].license, license) == 0)
        {
            lic[i].status = 0;
            enter_minutes = lic[i].hours * 60.0 + lic[i].minutes;
            exit_minutes = hours * 60.0 + minutes;
            total_minutes = exit_minutes - enter_minutes;
            switch (lic[i].vehicle_type)
            {
            case 'B':
                if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23))
                {
                    price_minute = bike.reduced_hours * 0.01;
                }
                else
                {
                    if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19))
                    {
                        price_minute = bike.peak_hours * 0.01;
                    }
                    else
                    {
                        price_minute = bike.normal_hours * 0.01;
                    }
                }
                break;
            case 'C':
                if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23))
                {
                    price_minute = car.reduced_hours * 0.01;
                }
                else
                {
                    if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19))
                    {
                        price_minute = car.peak_hours * 0.01;
                    }
                    else
                    {
                        price_minute = car.normal_hours * 0.01;
                    }
                }
                break;
            case 'T':
                if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23))
                {
                    price_minute = truck.reduced_hours * 0.01;
                }
                else
                {
                    if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19))
                    {
                        price_minute = truck.peak_hours * 0.01;
                    }
                    else
                    {
                        price_minute = truck.normal_hours * 0.01;
                    }
                }
                break;
            default:
                break;
            }
            total_price = total_minutes * price_minute;
            strcpy(database[i].operation.license, license);
            database[i].operation.vehicle_type = lic[i].vehicle_type;
            database[i].operation.start_hours = lic[i].hours;
            database[i].operation.start_minutes = lic[i].minutes;
            database[i].operation.finish_hours = hours;
            database[i].operation.finish_minutes = minutes;
            database[i].operation.price = total_price;
            lic[i].license[0] = '\0';
            lic[i].vehicle_type = '\0';
            count_vehicles--;
            printf("Operation closed: %.2f euros\n", database[i].operation.price);
        };
    };
    return count_vehicles;
}

void checkDatabase(Database database[], Counter counter, char license[])
{
    int i;
    char machine_type = '\0';
    int found = 0;
    for (i = 0; i < counter.total_counter; i++)
    {
        if (strcmp(database[i].operation.license, license))
        {
            database[i].operation.vehicle_type = machine_type;
            found = 1;
        };
    };
    printf("Plate: %s\n", license);
    if (found == 1)
    {
        if (machine_type == 'B')
        {
            printf("Type of vehicle: BIKE\n");
        }
        else
        {
            if (machine_type == 'C')
            {
                printf("Type of vehicle: CAR\n");
            }
            else
            {
                if (machine_type == 'T')
                {
                    printf("Type of vehicle: TRUCK\n");
                }
            }
        }
    }
};

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
    int enter_error = 0;
    int exit_error = 0;
    int duplication_error = 0;
    int counter_b = 0;
    int counter_c = 0;
    int counter_t = 0;
    int total_bikes = 0;
    int total_cars = 0;
    int total_trucks = 0;
    int detail_status = 0;

    int i;
    int time;
    int process;
    Bikes bike;
    Cars car;
    Trucks truck;
    Licenses lic[MAX_VEHICLES - 1];
    Operation operation[100];
    Database database[100];
    Counter counter;
    int personal_counter = 0;

    printf("Welcome to Parking LS!\n");
    printf("Enter tariffs: ");
    scanf("%s", rates_str);
    char buffer;
    scanf("%c", &buffer);
    rates_length = strlen(rates_str);
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
    };

    do
    {
        printf("\nParking LS> ");
        fgets(command_string, sizeof(command_string), stdin);
        if (strcmp(command_string, "show occupation\n") == 0)
        {
            printf("Vehicles currently in the parking:\n");
            printf("BIKES: ");
            int counter_bikes = 0;
            int counter_cars = 0;
            int counter_trucks = 0;
            for (i = 0; i < count_vehicles; i++)
            {
                if (lic[i].vehicle_type == 'B')
                {
                    counter_bikes++;
                }
            };
            if (counter_bikes == 0)
            {
                printf("No bikes");
            }
            else
            {
                for (i = 0; i < count_vehicles; i++)
                {
                    if (lic[i].vehicle_type == 'B')
                    {
                        printf("%s", lic[i].license);
                        if (counter_bikes > 1)
                        {
                            printf(" - ");
                        }
                        counter_bikes--;
                    }
                };
            }
            printf("\nCARS: ");
            for (i = 0; i < count_vehicles; i++)
            {
                if (lic[i].vehicle_type == 'C')
                {
                    counter_cars++;
                }
            };
            if (counter_cars == 0)
            {
                printf("No cars");
            }
            else
            {
                for (i = 0; i < count_vehicles; i++)
                {
                    if (lic[i].vehicle_type == 'C')
                    {
                        printf("%s", lic[i].license);
                        if (counter_cars > 1)
                        {
                            printf(" - ");
                        };
                        counter_cars--;
                    }
                };
            }
            printf("\nTRUCKS: ");
            for (i = 0; i < count_vehicles; i++)
            {
                if (lic[i].vehicle_type == 'T')
                {
                    counter_trucks++;
                }
            }
            if (counter_trucks == 0)
            {
                printf("No trucks\n");
            }
            else
            {
                for (i = 0; i < count_vehicles; i++)
                {
                    if (lic[i].vehicle_type == 'T')
                    {
                        printf("%s", lic[i].license);
                        if (counter_trucks > 1)
                        {
                            printf(" - ");
                        }
                        else
                        {
                            printf("\n");
                        }
                        counter_trucks--;
                    }
                };
            }
        }
        else
        {
            if (sscanf(command_string, "show detail %s", license))
            {
                if (counter.total_counter == 0)
                {
                    printf(" (ERROR) This vehicle never used the parking\n");
                }
                else
                {
                    for (i = 0; i < counter.total_counter; i++)
                    {
                        if (strcmp(database[i].operation.license, license) == 0)
                        {
                            detail_status = 1;
                        }
                        else
                        {
                            detail_status = 2;
                        }
                    }

                    switch (detail_status)
                    {
                    case 1:
                        checkDatabase(database, counter, license);
                        break;
                    case 2:
                        printf(" (ERROR) This vehicle never used the parking\n");
                        break;
                    default:
                        break;
                    }
                }
            }
            else
            {
                if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes))
                {
                    if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes) != 4 || (vechicle_type != 'B' && vechicle_type != 'C' && vechicle_type != 'T'))
                    {
                        enter_error = 1;
                    }
                    else
                    {
                        if (checkDuplication(lic, count_vehicles, license))
                        {
                            enter_error = 2;
                        }

                        else
                        {
                            if (hours > 23 || hours < 0 || minutes < 0 || minutes > 59)
                            {
                                enter_error = 3;
                            }
                            else
                            {
                                enter_error = 4;
                            }
                        }
                    }
                    switch (enter_error)
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
                            lic[count_vehicles].vehicle_type = vechicle_type;
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
                        exit_error = 1;
                    }
                    else
                    {
                        if (!checkDuplication(lic, count_vehicles, license))
                        {
                            exit_error = 2;
                        }
                        else
                        {
                            time = checkTime(lic, minutes, hours, license);
                            if (time == 3)
                            {
                                exit_error = 3;
                            }
                            else
                            {
                                exit_error = 4;
                            }
                        }
                    }
                    switch (exit_error)
                    {
                    case 1:
                        printf(" (ERROR) Wrong command\n");
                        break;
                    case 2:
                        printf(" (ERROR) This vehicle is not in the parking\n");
                        break;
                    case 3:
                        printf(" (ERROR) Incoherent exit time\n");
                        break;
                    case 4:
                        process = operationClosed(lic, count_vehicles, license, hours, minutes, bike, car, truck, database, operation, counter);
                        personal_counter++;
                        counter.total_counter = personal_counter;
                        break;
                    default:
                        break;
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

// enter C 5109GTY 9:23
// enter B 7743BWQ 6:49
// exit 5109GTY 13:14
// exit 7743BWQ 21:05

// 3-rd part check
// enter B 6754BBV 11:15
// enter C 8788CDF 13:27
// enter C 9910FSD 14:25
// enter C 9078FRS 17:19
// exit 9910FSD 19:17
// enter C 1909HJK 20:20
// show occupation

// 4-th check
// enter C 5646GTH 12:15
// show detail 5634GFT

// 5-th check
// enter C 3454FFR 12:35
// exit 3454FFR 13:47
// enter C 3454FFR 16:20
// exit 3454FFR 20:00
// enter C 3454FFR 20:55
// exit 3454FFR 23:23
// show detail 3454FFR

// check the work of database

// printf("License is %s", operation.license);
//             printf("Start time %d:%d", operation.start_hours, operation.start_minutes);
//             printf("Finish time %d:%d", operation.finish_hours, operation.finish_minutes);
