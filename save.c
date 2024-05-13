// #include <stdio.h>
// #include <string.h>
// #define MAX_LICENSE_CHAR 15
// #define MAX_STRING_SIZE 50
// #define MAX_VEHICLES 8
// #define MAX_OPERATIONS 10
// typedef struct
// {
//     int reduced_hours;
//     int normal_hours;
//     int peak_hours;
// } Bikes;

// typedef struct
// {
//     int reduced_hours;
//     int normal_hours;
//     int peak_hours;
// } Cars;

// typedef struct
// {
//     int reduced_hours;
//     int normal_hours;
//     int peak_hours;
// } Trucks;

// typedef struct
// {
//     char license[MAX_LICENSE_CHAR];
//     char vechicle_type;
//     int status;
//     int hours;
//     int minutes;
// } Licenses;

// int checkDuplication(Licenses lic[], int count_vehicles, char license[])
// {
//     int i = 0;
//     int is_duplication = 0;
//     for (i = 0; i < count_vehicles; i++)
//     {
//         if (strcmp(lic[i].license, license) == 0)
//         {
//             is_duplication = 1;
//             i = count_vehicles;
//         }
//         else
//         {
//             is_duplication = 0;
//         }
//     }
//     return is_duplication;
// }

// int checkTime(Licenses lic[], int minutes, int hours, char license[])
// {
//     int i;
//     int time_status;
//     for (i = 0; i < MAX_VEHICLES; i++)
//     {
//         if (strcmp(lic[i].license, license) == 0)
//         {
//             if ((minutes <= lic[i].minutes && hours == lic[i].hours) || hours < lic[i].hours)
//             {
//                 time_status = 3;
//             }
//             else
//             {
//                 time_status = 0;
//             }
//         }
//     };
//     return time_status;
// }

// int operationClosed(Licenses lic[], int count_vehicles, char license[], int hours, int minutes, Bikes bike, Cars car, Trucks truck)
// {
//     int i;
//     int total_minutes;
//     int enter_minutes;
//     int exit_minutes;

//     float price_minute;
//     float total_price;
//     for (i = 0; i < count_vehicles; i++)
//     {
//         if (strcmp(lic[i].license, license) == 0)
//         {

//             lic[i].status = 0;
//             enter_minutes = lic[i].hours * 60.0 + lic[i].minutes;
//             exit_minutes = hours * 60.0 + minutes;
//             total_minutes = exit_minutes - enter_minutes;
//             switch (lic[i].vechicle_type)
//             {
//             case 'B':
//                 if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23))
//                 {
//                     price_minute = bike.reduced_hours * 0.01;
//                 }
//                 else
//                 {
//                     if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19))
//                     {
//                         price_minute = bike.peak_hours * 0.01;
//                     }
//                     else
//                     {
//                         price_minute = bike.normal_hours * 0.01;
//                     }
//                 }
//                 break;
//             case 'C':
//                 if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23))
//                 {
//                     price_minute = car.reduced_hours * 0.01;
//                 }
//                 else
//                 {
//                     if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19))
//                     {
//                         price_minute = car.peak_hours * 0.01;
//                     }
//                     else
//                     {
//                         price_minute = car.normal_hours * 0.01;
//                     }
//                 }
//                 break;
//             case 'T':
//                 if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23))
//                 {
//                     price_minute = truck.reduced_hours * 0.01;
//                 }
//                 else
//                 {
//                     if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19))
//                     {
//                         price_minute = truck.peak_hours * 0.01;
//                     }
//                     else
//                     {
//                         price_minute = truck.normal_hours * 0.01;
//                     }
//                 }
//                 break;
//             default:
//                 break;
//             }
//             total_price = total_minutes * price_minute;
//             count_vehicles--;
//         }
//     };
//     return printf("Operation closed: %.2f euros\n", total_price);
// }

// int main()
// {
//     char rates_str[MAX_STRING_SIZE];
//     char command_string[MAX_STRING_SIZE];
//     int rates_length;
//     char vechicle_type;
//     char license[MAX_LICENSE_CHAR];
//     char prev_license[MAX_LICENSE_CHAR];
//     int hours, minutes;
//     int count_vehicles = 0;
//     int enter_error = 0;
//     int exit_error = 0;
//     int duplication_error = 0;
//     int i;
//     int time;
//     Bikes bike;
//     Cars car;
//     Trucks truck;
//     Licenses lic[MAX_VEHICLES - 1];

//     printf("Welcome to Parking LS!\n");
//     printf("Enter tariffs: ");
//     scanf("%s", rates_str);
//     char buffer;
//     scanf("%c", &buffer);
//     rates_length = strlen(rates_str);
//     for (i = 0; i < rates_length; i++)
//     {
//         if (rates_str[i] == 'B' && (rates_str[i - 1] == '#' || i == 0))
//         {
//             bike.reduced_hours = rates_str[i + 6] - '0';
//             bike.normal_hours = rates_str[i + 8] - '0';
//             bike.peak_hours = rates_str[i + 10] - '0';
//         }
//         if (rates_str[i] == 'C' && (rates_str[i - 1] == '#' || i == 0))
//         {
//             car.reduced_hours = rates_str[i + 5] - '0';
//             car.normal_hours = rates_str[i + 7] - '0';
//             car.peak_hours = rates_str[i + 9] - '0';
//         };
//         if (rates_str[i] == 'T' && (rates_str[i - 1] == '#' || i == 0))
//         {
//             truck.reduced_hours = rates_str[i + 7] - '0';
//             if (rates_str[i + 9] == '1' && rates_str[i + 10] == '0')
//             {
//                 truck.normal_hours = 10;
//             }
//             if (rates_str[i + 12] == '1' && rates_str[i + 13] == '2')
//             {
//                 truck.peak_hours = 12;
//             }
//         }
//     };

//     do
//     {
//         printf("\nParking LS> ");
//         fgets(command_string, sizeof(command_string), stdin);
//         if (strcmp(command_string, "show occupation\n") == 0)
//         {
//             printf("Welcome");
//         }
//         else
//         {
//             if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes))
//             {
//                 if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes) != 4 || (vechicle_type != 'B' && vechicle_type != 'C' && vechicle_type != 'T'))
//                 {
//                     enter_error = 1;
//                 }
//                 else
//                 {
//                     if (checkDuplication(lic, count_vehicles, license))
//                     {
//                         enter_error = 2;
//                     }

//                     else
//                     {
//                         if (hours > 23 || hours < 0 || minutes < 0 || minutes > 59)
//                         {
//                             enter_error = 3;
//                         }
//                         else
//                         {
//                             enter_error = 4;
//                         }
//                     }
//                 }
//                 switch (enter_error)
//                 {
//                 case 1:
//                     printf(" (ERROR) Wrong command\n");
//                     break;
//                 case 2:
//                     printf(" (ERROR) This vehicle is already in the parking!\n");
//                     break;
//                 case 3:
//                     printf(" (ERROR) Wrong time format\n");
//                     break;
//                 case 4:
//                     if (count_vehicles >= 0 && count_vehicles <= MAX_VEHICLES - 1)
//                     {
//                         strcpy(lic[count_vehicles].license, license);
//                         lic[count_vehicles].status = 1;
//                         lic[count_vehicles].vechicle_type = vechicle_type;
//                         lic[count_vehicles].hours = hours;
//                         lic[count_vehicles].minutes = minutes;
//                         count_vehicles++;
//                     }
//                     else
//                     {
//                         printf(" (ERROR) No more vehicles are accepted\n");
//                     };
//                     break;
//                 default:
//                     break;
//                 }
//             }
//             else
//             {
//                 if (sscanf(command_string, "exit %s %d:%d", license, &hours, &minutes) != 3)
//                 {
//                     exit_error = 1;
//                 }
//                 else
//                 {
//                     if (!checkDuplication(lic, count_vehicles, license))
//                     {
//                         exit_error = 2;
//                     }
//                     else
//                     {
//                         time = checkTime(lic, minutes, hours, license);
//                         if (time == 3)
//                         {
//                             exit_error = 3;
//                         }
//                         else
//                         {
//                             exit_error = 4;
//                         }
//                     }
//                 }
//                 switch (exit_error)
//                 {
//                 case 1:
//                     printf(" (ERROR) Wrong command\n");
//                     break;
//                 case 2:
//                     printf(" (ERROR) This vehicle is not in the parking\n");
//                     break;
//                 case 3:
//                     printf(" (ERROR) Incoherent exit time\n");
//                     break;
//                 case 4:
//                     operationClosed(lic, count_vehicles, license, hours, minutes, bike, car, truck);
//                     break;
//                 default:
//                     break;
//                 }
//             }
//         }
//     } while (1);
//     return 0;
// }