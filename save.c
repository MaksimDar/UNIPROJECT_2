// #include <stdio.h>
// #include <string.h>
// #define MAX_LICENSE_CHAR 15
// #define MAX_STRING_SIZE 50
// #define MAX_VEHICLES 8
// #define MAX_OPERATIONS 10
// // my values
// #define DATABASE_STORAGE 1000
// #define COUNTER_STORAGE 1000

// typedef struct {
//     int reduced_hours;
//     int normal_hours;
//     int peak_hours;
// } Bikes;

// typedef struct {
//     int reduced_hours;
//     int normal_hours;
//     int peak_hours;
// } Cars;

// typedef struct {
//     int reduced_hours;
//     int normal_hours;
//     int peak_hours;
// } Trucks;
// typedef struct {
//     char license[MAX_LICENSE_CHAR];
//     char vehicle_type;
//     int status;
//     int hours;
//     int minutes;
// } Licenses;

// typedef struct {
//     char license[MAX_LICENSE_CHAR];
//     char vehicle_type;
//     int start_hours;
//     int start_minutes;
//     int finish_hours;
//     int finish_minutes;
//     float price;
//     int status;
// } Operation;
// struct Database {
//     Operation operation[DATABASE_STORAGE];
// };

// typedef struct {
//     char license[MAX_LICENSE_CHAR];
//     int counter_entrance;
// } Counter;


// int checkDuplication(Licenses lic[], int count_vehicles, char license[]) {
//     int i = 0;
//     int is_duplication = 0;
//     for (i = 0; i < count_vehicles; i++) {
//         if (strcmp(lic[i].license, license) == 0) {
//             is_duplication = 1;
//             i = count_vehicles;
//         } else {
//             is_duplication = 0;
//         }
//     }
//     return is_duplication;
// };

// int checkTime(Licenses lic[], int minutes, int hours, char license[]) {
//     int i;
//     int time_status;
//     for (i = 0; i < MAX_VEHICLES; i++) {
//         if (strcmp(lic[i].license, license) == 0) {
//             if ((minutes <= lic[i].minutes && hours == lic[i].hours) || hours < lic[i].hours) {
//                 time_status = 3;
//             } else {
//                 time_status = 0;
//             }
//         }
//     };
//     return time_status;
// };

// float operationClosed(Licenses lic[], int count_vehicles, char license[], int hours, int minutes, Bikes bike, Cars car, Trucks truck, struct Database database, int total_counter) {
//     int i,j;
//     int total_minutes;
//     int enter_minutes;
//     int exit_minutes;
//     float price_minute, total_price;
//     for (i = 0; i < count_vehicles; i++) {
//         if (strcmp(lic[i].license, license) == 0) {
//             lic[i].status = 0;
//             enter_minutes = lic[i].hours * 60.0 + lic[i].minutes;
//             exit_minutes = hours * 60.0 + minutes;
//             total_minutes = exit_minutes - enter_minutes;
//             switch (lic[i].vehicle_type) {
//             case 'B':
//                 if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23)) {
//                     price_minute = bike.reduced_hours * 0.01;
//                 } else {
//                     if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19)) {
//                         price_minute = bike.peak_hours * 0.01;
//                     } else {
//                         price_minute = bike.normal_hours * 0.01;
//                     }
//                 }
//                 break;
//             case 'C':
//                 if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23)) {
//                     price_minute = car.reduced_hours * 0.01;
//                 } else {
//                     if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19)) {
//                         price_minute = car.peak_hours * 0.01;
//                     } else {
//                         price_minute = car.normal_hours * 0.01;
//                     }
//                 }
//                 break;
//             case 'T':
//                 if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23)) {
//                     price_minute = truck.reduced_hours * 0.01;
//                 } else {
//                     if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19)) {
//                         price_minute = truck.peak_hours * 0.01;
//                     } else {
//                         price_minute = truck.normal_hours * 0.01;
//                     }
//                 }
//                 break;
//             default:
//                 break;
//             }
//             total_price = total_minutes * price_minute;
//             printf("Operation closed: %.2f euros\n", total_price);
//             lic[i].license[count_vehicles] = '\0';
//             lic[i].vehicle_type = '\0';
//         };
//     };
//     return total_price;
// };

// void checkDatabase(struct Database database, char license[]) {
//     int i;
//     int status = 0;
//     int found_index = -1;
//     for (i = 0; i < DATABASE_STORAGE; i++) {
//         if (strcmp(database.operation[i].license, license) == 0) {
//             found_index = i;
//             status = 1;
//         }
//     }
    
//     if (status == 1) {
//         printf("Plate: %s\n", database.operation[found_index].license);
//         if (database.operation[found_index].vehicle_type == 'B') {
//             printf("Type of vehicle: BIKE\n");
//         } else {
//             if (database.operation[found_index].vehicle_type == 'C') {
//                 printf("Type of vehicle: CAR\n");
//             } else {
//                 if (database.operation[found_index].vehicle_type == 'T') {
//                     printf("Type of vehicle: TRUCK\n");
//                 }
//             }
//         }
//     };
// };

// void checkOperations(struct Database database, char license[], int total_counter) {
//     int i;
//     int status = 0;
//     float total_price = 0;
//     for (i = 0; i <= total_counter; i++) {
//         if (strcmp(database.operation[i].license, license) == 0) {
//             status = 1;
//         };
//     };
//     if (status == 1) {
//         printf("Operations:\n");
//         for (i = 0; i <= total_counter; i++) {
//             if (strcmp(database.operation[i].license, license) == 0) {
//                 if (database.operation[i].status == 1) {
//                     printf("        %02d:%02d\t**:**\t(**.** euros)\n", database.operation[i].start_hours, database.operation[i].start_minutes);
//                 } else {
//                     printf("        %02d:%02d\t%02d:%02d\t(%.2f euros)\n", database.operation[i].start_hours, database.operation[i].start_minutes, database.operation[i].finish_hours, database.operation[i].finish_minutes, database.operation[i].price);
//                     total_price += database.operation[i].price;  
//                 } 
//             }
//         };
//         printf("Total paid: %.2f euros\n", total_price);
//     } else {
//         printf(" (ERROR) This vehicle never used the parking\n");
//     } 
// };

// int main() {
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
//     int counter_b = 0;
//     int counter_c = 0;
//     int counter_t = 0;
//     int total_bikes = 0;
//     int total_cars = 0;
//     int total_trucks = 0;
//     int detail_status = 0;
//     int i;
//     int time;
//     float price;
//     int process;
//     int total_counter = 0;
//     Bikes bike;
//     Cars car;
//     Trucks truck;
//     Licenses lic[MAX_VEHICLES - 1];
//     Operation operation[100];
//     struct Database database;
//     Counter counter[100];
//     int personal_counter = 1;
//     int enter_counter;
//     int finish_status = 1;
//     printf("Welcome to Parking LS!\n");
//     printf("Enter tariffs: ");
//     scanf("%s", rates_str);
//     char buffer;
//     scanf("%c", &buffer);
//     rates_length = strlen(rates_str);
//     for (i = 0; i < rates_length; i++) {
//         if (rates_str[i] == 'B' && (rates_str[i - 1] == '#' || i == 0)) {
//             bike.reduced_hours = rates_str[i + 6] - '0';
//             bike.normal_hours = rates_str[i + 8] - '0';
//             bike.peak_hours = rates_str[i + 10] - '0';
//         }
//         if (rates_str[i] == 'C' && (rates_str[i - 1] == '#' || i == 0)) {
//             car.reduced_hours = rates_str[i + 5] - '0';
//             car.normal_hours = rates_str[i + 7] - '0';
//             car.peak_hours = rates_str[i + 9] - '0';
//         };
//         if (rates_str[i] == 'T' && (rates_str[i - 1] == '#' || i == 0)) {
//             truck.reduced_hours = rates_str[i + 7] - '0';
//             if (rates_str[i + 9] == '1' && rates_str[i + 10] == '0') {
//                 truck.normal_hours = 10;
//             };
//             if (rates_str[i + 12] == '1' && rates_str[i + 13] == '2') {
//                 truck.peak_hours = 12;
//             };
//         }
//     };
//     do {
//         printf("\nParking LS> ");
//         fgets(command_string, sizeof(command_string), stdin);
//         if (strcmp(command_string, "quit\n") == 0) {
//             finish_status = 0;
//             printf("See you later!");
//         } else {
//         if (strcmp(command_string, "show occupation\n") == 0) {
//             printf("Vehicles currently in the parking:\n");
//             printf("BIKES: ");
//             int counter_bikes = 0;
//             int counter_cars = 0;
//             int counter_trucks = 0;
//             for (i = 0; i < count_vehicles; i++) {
//                 if (lic[i].vehicle_type == 'B') {
//                     counter_bikes++;
//                 }
//             };
//             if (counter_bikes == 0) {
//                 printf("No bikes");
//             } else {
//                 for (i = 0; i < count_vehicles; i++) {
//                     if (lic[i].vehicle_type == 'B') {
//                         printf("%s", lic[i].license);
//                         if (counter_bikes > 1) {
//                             printf(" - ");
//                         }
//                         counter_bikes--;
//                     }
//                 };
//             }
//             printf("\nCARS: ");
//             for (i = 0; i < count_vehicles; i++) {
//                 if (lic[i].vehicle_type == 'C') {
//                     counter_cars++;
//                 }
//             };
//             if (counter_cars == 0) {
//                 printf("No cars");
//             } else {
//                 for (i = 0; i < count_vehicles; i++) {
//                     if (lic[i].vehicle_type == 'C') {
//                         printf("%s", lic[i].license);
//                         if (counter_cars > 1) {
//                             printf(" - ");
//                         };
//                         counter_cars--;
//                     }
//                 };
//             }
//             printf("\nTRUCKS: ");
//             for (i = 0; i < count_vehicles; i++) {
//                 if (lic[i].vehicle_type == 'T') {
//                     counter_trucks++;
//                 }
//             }
//             if (counter_trucks == 0) {
//                 printf("No trucks\n");
//             } else {
//                 for (i = 0; i < count_vehicles; i++) {
//                     if (lic[i].vehicle_type == 'T') {
//                         printf("%s", lic[i].license);
//                         if (counter_trucks > 1) {
//                             printf(" - ");
//                         } else {
//                             printf("\n");
//                         }
//                         counter_trucks--;
//                     }
//                 };
//             }
//         } else {
//             if (sscanf(command_string, "show detail %s", license)) {
//                 if (sscanf(command_string, "show detail %s", license) != 1) {
//                     printf(" (ERROR) Wrong command\n");
//                 } else {
//                     checkDatabase(database, license);
//                     checkOperations(database, license, total_counter);  
//                 }
//             } else {
//                 if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes)) {
//                     if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes) != 4 || (vechicle_type != 'B' && vechicle_type != 'C' && vechicle_type != 'T')) {
//                         enter_error = 1;
//                     } else {
//                         if (checkDuplication(lic, count_vehicles, license)) {
//                             enter_error = 2;
//                         } else {
//                             if (hours > 23 || hours < 0 || minutes < 0 || minutes > 59) {
//                                 enter_error = 3;
//                             } else {
//                                 enter_error = 4;
//                             }
//                         }
//                     }

//                     switch (enter_error) {
//                     case 1:
//                         printf(" (ERROR) Wrong command\n");
//                         break;
//                     case 2:
//                         printf(" (ERROR) This vehicle is already in the parking!\n");
//                         break;
//                     case 3:
//                         printf(" (ERROR) Wrong time format\n");
//                         break;
//                     case 4:
//                         if (count_vehicles >= 0 && count_vehicles <= MAX_VEHICLES - 1) {
//                             int current_index = count_vehicles;
//                             strcpy(lic[current_index].license, license);
//                             lic[current_index].status = 1;
//                             lic[current_index].vehicle_type = vechicle_type;
//                             lic[current_index].hours = hours;
//                             lic[current_index].minutes = minutes;
//                             count_vehicles++;
//                             total_counter++;
//                             strcpy(database.operation[total_counter].license, license);
//                             database.operation[total_counter].start_hours = hours;
//                             database.operation[total_counter].start_minutes = minutes;
//                             database.operation[total_counter].vehicle_type = vechicle_type;
//                             database.operation[total_counter].status = 1;
//                         } else  {
//                             printf(" (ERROR) No more vehicles are accepted\n");
//                         };
//                         break;
//                     default:
//                         break;
//                     }
//                 } else {
//                     if (sscanf(command_string, "exit %s %d:%d", license, &hours, &minutes) != 3) {
//                         exit_error = 1;
//                     } else {
//                         if (!checkDuplication(lic, count_vehicles, license)) {
//                             exit_error = 2;
//                         } else {
//                             time = checkTime(lic, minutes, hours, license);
//                             if (time == 3) {
//                                 exit_error = 3;
//                             } else {
//                                 exit_error = 4;
//                             }
//                         };
//                     };
//                     switch (exit_error) {
//                     case 1:
//                         printf(" (ERROR) Wrong command\n");
//                         break;
//                     case 2:
//                         printf(" (ERROR) This vehicle is not in the parking\n");
//                         break;
//                     case 3:
//                         printf(" (ERROR) Incoherent exit time\n");
//                         break;
//                     case 4:
//                         price = operationClosed(lic, count_vehicles, license, hours, minutes, bike, car, truck, database, total_counter);
//                         count_vehicles--;
//                         database.operation[total_counter].finish_hours = hours;
//                         database.operation[total_counter].finish_minutes = minutes;
//                         database.operation[total_counter].status = 0;
//                         database.operation[total_counter].price = price;
//                         break;
//                     default:
//                         break;
//                     }
//                 };

//             }
//         }
//         }
//     } while (finish_status);
//     return 0;
// }