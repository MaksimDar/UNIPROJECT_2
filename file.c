#include <stdio.h>
#include <string.h>
#define MAX_LICENSE_CHAR 15
#define MAX_STRING_SIZE 50
#define MAX_VEHICLES 8
#define MAX_OPERATIONS 10
// my values
#define DATABASE_STORAGE 1000
#define COUNTER_STORAGE 1000

typedef struct {
    int reduced_hours;
    int normal_hours;
    int peak_hours;
} Bikes;

typedef struct {
    int reduced_hours;
    int normal_hours;
    int peak_hours;
} Cars;

typedef struct {
    int reduced_hours;
    int normal_hours;
    int peak_hours;
} Trucks;
typedef struct {
    char license[MAX_LICENSE_CHAR];
    char vehicle_type;
    int status;
    int hours;
    int minutes;
} Licenses;

typedef struct {
    char license[MAX_LICENSE_CHAR];
    char vehicle_type;
    int start_hours;
    int start_minutes;
    int finish_hours;
    int finish_minutes;
    float price;
    int total_counter;
} Operation;
typedef struct {
    Operation operation;
} Database;

typedef struct {
    char license[MAX_LICENSE_CHAR];
    int counter_entrance;
} Counter;

int checkDuplication(Licenses lic[], int count_vehicles, char license[]) {
    int i = 0;
    int is_duplication = 0;
    for (i = 0; i < count_vehicles; i++) {
        if (strcmp(lic[i].license, license) == 0) {
            is_duplication = 1;
            i = count_vehicles;
        } else {
            is_duplication = 0;
        }
    }
    return is_duplication;
};

int checkTime(Licenses lic[], int minutes, int hours, char license[]) {
    int i;
    int time_status;
    for (i = 0; i < MAX_VEHICLES; i++) {
        if (strcmp(lic[i].license, license) == 0) {
            if ((minutes <= lic[i].minutes && hours == lic[i].hours) || hours < lic[i].hours) {
                time_status = 3;
            } else {
                time_status = 0;
            }
        }
    };
    return time_status;
};

int operationClosed(Licenses lic[], int count_vehicles, char license[], int hours, int minutes, Bikes bike, Cars car, Trucks truck, Database database[], Operation operation[], int total_counter) {
    int i;
    int total_minutes;
    int enter_minutes;
    int exit_minutes;
    float price_minute, total_price;
    for (i = 0; i < count_vehicles; i++) {
        if (strcmp(lic[i].license, license) == 0) {
            lic[i].status = 0;
            enter_minutes = lic[i].hours * 60.0 + lic[i].minutes;
            exit_minutes = hours * 60.0 + minutes;
            total_minutes = exit_minutes - enter_minutes;
            switch (lic[i].vehicle_type) {
            case 'B':
                if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23)) {
                    price_minute = bike.reduced_hours * 0.01;
                } else {
                    if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19)) {
                        price_minute = bike.peak_hours * 0.01;
                    } else {
                        price_minute = bike.normal_hours * 0.01;
                    }
                }
                break;
            case 'C':
                if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23)) {
                    price_minute = car.reduced_hours * 0.01;
                } else {
                    if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19)) {
                        price_minute = car.peak_hours * 0.01;
                    } else {
                        price_minute = car.normal_hours * 0.01;
                    }
                }
                break;
            case 'T':
                if ((lic[i].hours >= 0 && lic[i].hours <= 7) || (lic[i].hours >= 21 && lic[i].hours <= 23)) {
                    price_minute = truck.reduced_hours * 0.01;
                } else {
                    if ((lic[i].hours >= 10 && lic[i].hours <= 12) || (lic[i].hours >= 16 && lic[i].hours <= 19)) {
                        price_minute = truck.peak_hours * 0.01;
                    } else {
                        price_minute = truck.normal_hours * 0.01;
                    }
                }
                break;
            default:
                break;
            }
            total_price = total_minutes * price_minute;
            database[total_counter].operation.vehicle_type = lic[i].vehicle_type;
            database[total_counter].operation.finish_hours = hours;
            database[total_counter].operation.finish_minutes = minutes;
            database[total_counter].operation.price = total_price;
            printf("Operation closed: %.2f euros\n", database[total_counter].operation.price);
            lic[i].license[0] = '\0';
            lic[i].vehicle_type = '\0';
        };
    };
    count_vehicles--;
    return count_vehicles;
};


int addDatabase(int total_counter, Database database[], char license[], int hours, int minutes, char vechicle_type, Counter counter[]) {
    int i;
    int status = 1;
    int found_index = -1;
    int can_update = 1;
    for (i = 0; i < total_counter; i++) {
        if (strcmp(database[i].operation.license, license) == 0) {
            found_index = i;
            status = 2;
            i = total_counter;
        };
    };

    if (status == 1) {
        found_index = total_counter;
    };
    if (counter[found_index].counter_entrance > 10) {
        can_update = 0;
    }
    if (can_update) {
        switch (status) {
        case 1:
            strcpy(database[found_index].operation.license, license);
            database[found_index].operation.start_hours = hours;
            database[found_index].operation.start_minutes = minutes;
            database[found_index].operation.vehicle_type = vechicle_type;
            strcpy(counter[found_index].license, license);
            counter[found_index].counter_entrance = 1;
            break;

        case 2:
            database[found_index].operation.start_hours = hours;
            database[found_index].operation.start_minutes = minutes;
            counter[found_index].counter_entrance++;
            break;
        default:
            break;
        }
    }
    return total_counter;
};

void checkDatabase(Database database[], char license[]) {
    int i;
    int status = 0;
    int found_index = -1;
    for (i = 0; i < DATABASE_STORAGE; i++) {
        if (strcmp(database[i].operation.license, license) == 0) {
            found_index = i;
            status = 1;
        }
    }
    
    if (status == 1) {
        printf("Plate: %s\n", database[found_index].operation.license);
        if (database[found_index].operation.vehicle_type == 'B') {
            printf("Type of vehicle: BIKE\n");
        } else {
            if (database[found_index].operation.vehicle_type == 'C') {
                printf("Type of vehicle: CAR\n");
            } else {
                if (database[found_index].operation.vehicle_type == 'T') {
                    printf("Type of vehicle: TRUCK\n");
                }
            }
        }
    };
};

void chechOperations(Database database[], char license[], int total_counter) {
    int i;
    int status = 0;
    int found_index = -1;
    printf("Operations:\n");
    for (i = 0; i < total_counter; i++) {
        found_index = i;
        if (strcmp(database[found_index].operation.license, license) == 0) {
            printf("        %d:%d\t%d:%d\t%.2f\n", database[found_index].operation.start_hours, database[found_index].operation.start_minutes, database[found_index].operation.finish_hours, database[found_index].operation.finish_minutes, database[found_index].operation.price);
        }
    };
};

int main() {
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
    int total_counter = 0;
    Bikes bike;
    Cars car;
    Trucks truck;
    Licenses lic[MAX_VEHICLES - 1];
    Operation operation[100];
    Database database[DATABASE_STORAGE];
    Counter counter[100];
    int personal_counter = 1;
    int enter_counter;
    printf("Welcome to Parking LS!\n");
    printf("Enter tariffs: ");
    scanf("%s", rates_str);
    char buffer;
    scanf("%c", &buffer);
    rates_length = strlen(rates_str);
    for (i = 0; i < rates_length; i++) {
        if (rates_str[i] == 'B' && (rates_str[i - 1] == '#' || i == 0)) {
            bike.reduced_hours = rates_str[i + 6] - '0';
            bike.normal_hours = rates_str[i + 8] - '0';
            bike.peak_hours = rates_str[i + 10] - '0';
        }
        if (rates_str[i] == 'C' && (rates_str[i - 1] == '#' || i == 0)) {
            car.reduced_hours = rates_str[i + 5] - '0';
            car.normal_hours = rates_str[i + 7] - '0';
            car.peak_hours = rates_str[i + 9] - '0';
        };
        if (rates_str[i] == 'T' && (rates_str[i - 1] == '#' || i == 0)) {
            truck.reduced_hours = rates_str[i + 7] - '0';
            if (rates_str[i + 9] == '1' && rates_str[i + 10] == '0') {
                truck.normal_hours = 10;
            };
            if (rates_str[i + 12] == '1' && rates_str[i + 13] == '2') {
                truck.peak_hours = 12;
            };
        }
    };
    do {
        printf("\nParking LS> ");
        fgets(command_string, sizeof(command_string), stdin);
        if (strcmp(command_string, "show occupation\n") == 0) {
            printf("Vehicles currently in the parking:\n");
            printf("BIKES: ");
            int counter_bikes = 0;
            int counter_cars = 0;
            int counter_trucks = 0;
            for (i = 0; i < count_vehicles; i++) {
                if (lic[i].vehicle_type == 'B') {
                    counter_bikes++;
                }
            };
            if (counter_bikes == 0) {
                printf("No bikes");
            } else {
                for (i = 0; i < count_vehicles; i++) {
                    if (lic[i].vehicle_type == 'B') {
                        printf("%s", lic[i].license);
                        if (counter_bikes > 1) {
                            printf(" - ");
                        }
                        counter_bikes--;
                    }
                };
            }
            printf("\nCARS: ");
            for (i = 0; i < count_vehicles; i++) {
                if (lic[i].vehicle_type == 'C') {
                    counter_cars++;
                }
            };
            if (counter_cars == 0) {
                printf("No cars");
            } else {
                for (i = 0; i < count_vehicles; i++) {
                    if (lic[i].vehicle_type == 'C') {
                        printf("%s", lic[i].license);
                        if (counter_cars > 1) {
                            printf(" - ");
                        };
                        counter_cars--;
                    }
                };
            }
            printf("\nTRUCKS: ");
            for (i = 0; i < count_vehicles; i++) {
                if (lic[i].vehicle_type == 'T') {
                    counter_trucks++;
                }
            }
            if (counter_trucks == 0) {
                printf("No trucks\n");
            } else {
                for (i = 0; i < count_vehicles; i++) {
                    if (lic[i].vehicle_type == 'T') {
                        printf("%s", lic[i].license);
                        if (counter_trucks > 1) {
                            printf(" - ");
                        } else {
                            printf("\n");
                        }
                        counter_trucks--;
                    }
                };
            }
        } else {
            if (sscanf(command_string, "show detail %s", license)) {
                for (i = 0; i < DATABASE_STORAGE; i++) {
                    if (strcmp(counter[i].license, license) == 0) {
                        detail_status = 1;
                    };
                }

                if (detail_status == 1) {
                    checkDatabase(database, license);
                    chechOperations(database, license, total_counter);
                } else {
                    if (detail_status == 0) {
                        printf(" (ERROR) This vehicle never used the parking\n");
                    };
                }
            } else {
                if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes)) {
                    if (sscanf(command_string, "enter %c %s %d:%d", &vechicle_type, license, &hours, &minutes) != 4 || (vechicle_type != 'B' && vechicle_type != 'C' && vechicle_type != 'T')) {
                        enter_error = 1;
                    } else {
                        if (checkDuplication(lic, count_vehicles, license)) {
                            enter_error = 2;
                        } else {
                            if (hours > 23 || hours < 0 || minutes < 0 || minutes > 59) {
                                enter_error = 3;
                            } else {
                                enter_error = 4;
                            }
                        }
                    }

                    switch (enter_error) {
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
                        if (count_vehicles >= 0 && count_vehicles <= MAX_VEHICLES - 1) {
                            int current_index = count_vehicles;
                            strcpy(lic[current_index].license, license);
                            lic[current_index].status = 1;
                            lic[current_index].vehicle_type = vechicle_type;
                            lic[current_index].hours = hours;
                            lic[current_index].minutes = minutes;
                            count_vehicles++;
                            total_counter++;
                            addDatabase(total_counter, database, license, hours, minutes, vechicle_type, counter);
                        } else  {
                            printf(" (ERROR) No more vehicles are accepted\n");
                        };
                        break;
                    default:
                        break;
                    }
                } else {
                    if (sscanf(command_string, "exit %s %d:%d", license, &hours, &minutes) != 3) {
                        exit_error = 1;
                    } else {
                        if (!checkDuplication(lic, count_vehicles, license)) {
                            exit_error = 2;
                        } else {
                            time = checkTime(lic, minutes, hours, license);
                            if (time == 3) {
                                exit_error = 3;
                            } else {
                                exit_error = 4;
                            }
                        };
                    };
                    switch (exit_error) {
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
                        process = operationClosed(lic, count_vehicles, license, hours, minutes, bike, car, truck, database, operation, total_counter);
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


// FIRST STRING
// BIKES:2/3/4#CARS:3/4/6#TRUCKS:5/10/12
// CARS:3/4/6#TRUCKS:5/10/12#BIKES:2/3/4
// TRUCKS:5/10/12#BIKES:2/3/4#CARS:3/4/6



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


// enter C 6756FGT 12:55
// exit  6756FGT 12:55

// enter C 6756FGT 13:15
// exit  6756FGT 14:14

// enter C 6756FGT 14:28
// exit  6756FGT 14:56

// enter C 6756FGT 15:55
// exit  6756FGT 16:30

// enter C 6756FGT 16:55
// exit  6756FGT 17:30

// enter C 6756FGT 17:55
// exit  6756FGT 18:30

// enter C 6756FGT 18:55
// exit  6756FGT 19:30

// enter C 6756FGT 19:55
// exit  6756FGT 20:30

// enter C 6756FGT 20:55
// exit  6756FGT 21:30

// enter C 6756FGT 21:55
// exit  6756FGT 22:30

// enter C 6756FGT 22:55
// exit  6756FGT 23:30
