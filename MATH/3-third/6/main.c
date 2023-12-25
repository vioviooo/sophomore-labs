#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

#define SIZE 100
#define TIME_SIZE 20

void print_scs(int choice) {
    switch (choice) {
        case INVALID_INPUT:
            printf("\nInvalid input.\n");
            break;
        case OK:
            printf("\nProject finished successfully!\n");
            break;
        case NO_MEMORY:
            printf("\nNo memory left.\n");
            break;
        case OVERFLOW_:
            printf("\nOverflow!\n");
            break;
        case UNDEFINED:
            printf("\nError! What you're trying to calculate IS UNDEFINED or uses complex numbers.\n");
            break;
        case FILE_NOT_OPEN:
            printf("\nCan't open file.\n");
            break;
        case INVALID_INPUT_IN_FILE:
            printf("\nInvalid format of data in file.\n");
            break;
        case EMPTY:
            printf("\nNotice: empty list\n");
            break;
        default:
            break;
    }
}

// B - begin
// M - middle
// E - end

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    List routes;
    routes.head = NULL;

    int size = SIZE;
    double *coord = (double *)malloc(size * sizeof(double));
    if (coord == NULL) {
        return NO_MEMORY;
    }

    int result, cnt = 0;
    for (int i = 1; argv[i] != NULL; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            print_scs(FILE_NOT_OPEN);
            return FILE_NOT_OPEN;
        }
        if ((result = read_file(file, &routes, &coord, &size, &cnt)) != OK) {
            free(coord);
            fclose(file);
            print_scs(result);
            if (routes.head != NULL) {
                free_list(routes.head);
            }
            return result;
        }
        fclose(file);
    }

    if ((result = swap_cmd(&routes, coord, cnt / 2)) != OK) {
        free(coord);
        if (routes.head != NULL) {
            free_list(routes.head);
        }
        print_scs(result);
        return result;
    }

    free(coord);

    if (routes.head != NULL) {
        free_list(routes.head);
    }

    return OK;
}

int longest_path(List *routes, Node **max_stop, Node **min_stop) {
    Node *curr = routes->head;

    int status;
    if ((status = add_stop(curr->stop, min_stop)) != OK) {
        print_scs(status);
        return status;
    }

    if ((status = add_stop(curr->stop, max_stop)) != OK) {
        print_scs(status);
        return status;
    }

    int M, B, E, max_routes = 0, min_routes = SIZE, total;
    char *transport;
    while (curr != NULL) {
        B = M = E = total = 0;
        transport = curr->stop.number;
        Node *temp_curr = curr;
        while (temp_curr != NULL) {
            if (strcmp(temp_curr->stop.number, transport) != 0) {
                if (temp_curr->stop.mark == 'B') {
                    B++;
                } else if (temp_curr->stop.mark == 'M') {
                    M++;
                } else {
                    E++;
                }
            }
            temp_curr = temp_curr->next;
        }

        // total amount of roots
        total = B + M + E;

        if (total >= max_routes) {
            max_routes = total;
            free_list(*max_stop);
            if ((status = add_stop(curr->stop, max_stop)) != OK) {
                print_scs(status);
                return status;
            }
        } 
        
        if (total <= min_routes) {
            min_routes = total;
            free_list(*min_stop);
            if ((status = add_stop(curr->stop, min_stop)) != OK) {
                print_scs(status);
                return status;
            }
        }

        // переход к след сост
        curr = curr->next;
    }

    return OK;
}

int find_longest_route(List *routes, Node **max_stop, Node **min_stop) {
    Node *curr = routes->head;

    int status;
    if ((status = add_stop(curr->stop, min_stop)) != OK) {
        print_scs(status);
        return status;
    }

    if ((status = add_stop(curr->stop, max_stop)) != OK) {
        print_scs(status);
        return status;
    }
    int M, B, E, max_routes = 0, min_routes = SIZE;
    char *transport;
    while (curr != NULL) {
        M = B = E = 0; // изначально все нули
        transport = curr->stop.number;
        Node *temp_curr = curr;
        while (temp_curr != NULL) {
            if (!strcmp(temp_curr->stop.number, transport)) {
                if (temp_curr->stop.mark == 'B') {
                    B++;
                } else if (temp_curr->stop.mark == 'M') {
                    M++;
                } else if (temp_curr->stop.mark == 'E') {
                    E++;
                } else {
                    print_scs(INVALID_INPUT_IN_FILE);
                }
            }
            temp_curr = temp_curr->next;
        }
        if (B == E) { // конец равен началу
            if (M >= max_routes) {
                max_routes = M;
                free_list(*max_stop);
                int status;
                if ((status = add_stop(curr->stop, max_stop)) != OK) {
                    print_scs(status);
                    return status;
                }
            }
            if (M <= min_routes) {
                min_routes = M;
                free_list(*min_stop);
                int status;
                if ((status = add_stop(curr->stop, min_stop)) != OK) {
                    print_scs(status);
                    return status;
                }
            }
        }
        curr = curr->next;
    }
    return OK;
}

int find_cnt_route(List *routes, Node **max_stop, Node **min_stop) {
    Node *curr = routes->head;

    int status;
    if ((status = add_stop(curr->stop, min_stop)) != OK) {
        print_scs(status);
        return status;
    }

    if ((status = add_stop(curr->stop, max_stop)) != OK) {
        print_scs(status);
        return status;
    }

    int max_routes = 0, min_routes = SIZE, B, M, E, total;
    char *transport;
    while (curr != NULL) {
        transport = curr->stop.number;
        B = E = 0;
        Node *temp_curr = curr;
        while (temp_curr != NULL) {
            if (!strcmp(temp_curr->stop.number, transport)) {
                if (temp_curr->stop.mark == 'B') {
                    B++;
                } else if (temp_curr->stop.mark == 'E') {
                    E++;
                }
            }
            temp_curr = temp_curr->next;
        }
        if (B == E) {
            if (B >= max_routes) {
                max_routes = B;
                free_list(*max_stop);
                int status;
                if ((status = add_stop(curr->stop, max_stop)) != OK) {
                    print_scs(status);
                    return status;
                }
            }
            if (B <= min_routes) {
                min_routes = B;
                free_list(*min_stop);
                int status;
                if ((status = add_stop(curr->stop, min_stop)) != OK) {
                    print_scs(status);
                    return status;
                }
            }
        }
        curr = curr->next;
    }
    return OK;
}

int find_longest_stop(List *routes, Node **max_stop) {
    Node *curr = routes->head;
    int status;
    if ((status = add_stop(curr->stop, max_stop)) != OK) {
        print_scs(status);
        return status;
    }
    int total, duration, max_sp = get_duration(curr->stop.start_time, curr->stop.stop_time);
    while (curr != NULL) {
        total = 0;
        Node *curr_veh = routes->head;
        while (curr_veh != NULL) {
            if (!strcmp(curr->stop.number, curr_veh->stop.number)) {
                duration = get_duration(curr_veh->stop.start_time, curr_veh->stop.stop_time);
                total += duration;
            }
            curr_veh = curr_veh->next;
        }
        if (total < max_sp) {
            max_sp = total;
            free((*max_stop)->stop.number);
            (*max_stop)->stop.number = strdup(curr->stop.number);
        }
        curr = curr->next;
    }
    return OK;
}

int get_duration(const char *start, const char *stop) {
    time_t start_time = convert_time(start);
    time_t stop_time = convert_time(stop);
    if (start_time != -1 && stop_time != -1) {
        return difftime(stop_time, start_time);
    }
    return -1;
}

int get_time(List *roots, Node **max_stop, Node **min_stop, double x, double y) {
    Node *curr = roots->head;
    int result;
    int max_sp = 0;
    int min_sp = 0;
    while (curr != NULL) {
        if (curr->stop.coord[0] == x && curr->stop.coord[1] == y) {
            if (max_sp == 0) {
                int status;
                if ((status = add_stop(curr->stop, max_stop)) != OK) {
                    print_scs(status);
                    return status;
                }
                if ((status = add_stop(curr->stop, min_stop)) != OK) {
                    print_scs(status);
                    return status;
                }
                max_sp = get_duration(curr->stop.start_time, curr->stop.stop_time);
                min_sp = max_sp;
            }
            result = get_duration(curr->stop.start_time, curr->stop.stop_time);
            if (result < max_sp) {
                max_sp = result;
                free((*max_stop)->stop.number);
                (*max_stop)->stop.number = strdup(curr->stop.number);
            } else if (result > min_sp) {
                min_sp = result;
                free((*min_stop)->stop.number);
                (*min_stop)->stop.number = strdup(curr->stop.number);
            }
        }
        curr = curr->next;
    }
    return OK;
}

int swap_cmd(List *routes, double *coord, int cnt) {
    int i = 0, choice = 0, number;
    double x, y;
    Node *max_stop;
    Node *min_stop;
    bool flag = true;
    while (flag) {
        choice = 0;

        default_menu();
        if (!scanf("%d", &choice) || choice < 1 || choice > 7) {
            print_scs(INVALID_INPUT);
            default_menu();
            fflush(stdin);
            while (!scanf("%d", &choice) || choice < 1 || choice > 7) {
                fflush(stdin);
                print_scs(INVALID_INPUT);
                default_menu();
            }
        }

        switch (choice) {
            case 1: ////////////////////////////////////////
                if (routes->head == NULL) {
                    print_scs(EMPTY);
                } else {
                    if (find_cnt_route(routes, &max_stop, &min_stop) == NO_MEMORY) {
                        free_list(max_stop);
                        free_list(min_stop);
                        return NO_MEMORY;
                    }
                    printf("Transport with most routes: %s\n", max_stop->stop.number);
                    printf("Transport with least routes: %s\n", min_stop->stop.number);
                    free_list(max_stop);
                    free_list(min_stop);
                }
                menu();
                fflush(stdin);
                if (!scanf("%d", &choice) || choice < 1 || choice > 2) {
                    print_scs(INVALID_INPUT);
                    menu();
                    fflush(stdin);
                    while (!scanf("%d", &choice) || choice < 1 || choice > 2) {
                        fflush(stdin);
                        print_scs(INVALID_INPUT);
                        menu();
                    }
                }
                if (choice == 2) {
                    flag = false;
                }
                break;
            case 2: ////////////////////////////////////////
                if (routes->head == NULL) {
                    print_scs(EMPTY);
                } else {
                    if (longest_path(routes, &max_stop, &min_stop) == NO_MEMORY) {
                        free_list(max_stop);
                        free_list(min_stop);
                        return NO_MEMORY;
                    }
                    printf("\nTransport with the longest way: %s\n", max_stop->stop.number);
                    printf("Transport with the shortest way: %s\n", min_stop->stop.number);
                    free_list(max_stop);
                    free_list(min_stop);
                }
                menu();
                fflush(stdin);
                if (!scanf("%d", &choice) || choice < 1 || choice > 2) {
                    print_scs(INVALID_INPUT);
                    menu();
                    fflush(stdin);
                    while (!scanf("%d", &choice) || choice < 1 || choice > 2) {
                        fflush(stdin);
                        print_scs(INVALID_INPUT);
                        menu();
                    }
                }
                if (choice == 2) {
                    flag = false;
                }
                break;
            case 3: ////////////////////////////////////////
                if (routes->head == NULL) {
                    print_scs(EMPTY);
                } else {
                    if (find_longest_route(routes, &max_stop, &min_stop) == NO_MEMORY) {
                        free_list(max_stop);
                        free_list(min_stop);
                        return NO_MEMORY;
                    }
                    printf("\nTransport with the longest route: %s\n", max_stop->stop.number);
                    printf("Transport with the shortest route: %s\n", min_stop->stop.number);
                    free_list(max_stop);
                    free_list(min_stop);
                }
                menu();
                fflush(stdin);
                if (!scanf("%d", &choice) || choice < 1 || choice > 2) {
                    print_scs(INVALID_INPUT);
                    menu();
                    fflush(stdin);
                    while (!scanf("%d", &choice) || choice < 1 || choice > 2) {
                        fflush(stdin);
                        print_scs(INVALID_INPUT);
                        menu();
                    }
                }
                if (choice == 2) {
                    flag = false;
                }
                break;
            case 4: ////////////////////////////////////////
                if (routes->head == NULL) {
                    print_scs(EMPTY);
                } else {
                    while (cnt != 0) {
                        x = coord[i];
                        y = coord[i + 1];
                        cnt--;
                        i += 2;
                        if (get_time(routes, &max_stop, &min_stop, x, y) == NO_MEMORY) {
                            free_list(max_stop);
                            free_list(min_stop);
                            return NO_MEMORY;
                        }
                        printf("Stop %lf %lf:", x, y);
                        printf("\nTransport with the longest stop: %s\n", max_stop->stop.number);
                        printf("Transport with the shortest stop: %s\n", min_stop->stop.number);
                        free_list(max_stop);
                        free_list(min_stop);
                    }
                }
                menu();
                fflush(stdin);
                if (!scanf("%d", &choice) || choice < 1 || choice > 2) {
                    print_scs(INVALID_INPUT);
                    menu();
                    fflush(stdin);
                    while (!scanf("%d", &choice) || choice < 1 || choice > 2) {
                        fflush(stdin);
                        print_scs(INVALID_INPUT);
                        menu();
                    }
                }
                if (choice == 2) {
                    flag = false;
                }
                break;
            case 5: ////////////////////////////////////////
                if (routes->head == NULL) {
                    print_scs(EMPTY);
                } else {
                    if (find_longest_stop(routes, &max_stop) == NO_MEMORY) {
                        free_list(max_stop);
                        return NO_MEMORY;
                    }
                    printf("\nTransport with the longest stop: %s\n", max_stop->stop.number);
                    free_list(max_stop);
                }
                menu();
                fflush(stdin);
                if (!scanf("%d", &choice) || choice < 1 || choice > 2) {
                    print_scs(INVALID_INPUT);
                    menu();
                    fflush(stdin);
                    while (!scanf("%d", &choice) || choice < 1 || choice > 2) {
                        fflush(stdin);
                        print_scs(INVALID_INPUT);
                        menu();
                    }
                }
                if (choice == 2) {
                    flag = false;
                }
                break;
            case 6: ////////////////////////////////////////
                if (routes->head == NULL) {
                    print_scs(EMPTY);
                } else {
                    print_routes(routes);
                }
                menu();
                fflush(stdin);
                if (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
                    print_scs(INVALID_INPUT);
                    menu();
                    fflush(stdin);
                    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
                        fflush(stdin);
                        print_scs(INVALID_INPUT);
                        menu();
                    }
                }
                if (choice == 2) {
                    flag = false;
                }
                break;
            case 7: ////////////////////////////////////////
                flag = false;
                break;
            default: 
                break;
        }
    }
    return OK;
}

void print_routes(List *routes) {
    Node *curr = routes->head;
    while (curr != NULL) {
        printf("Route №%s, start time: %s, stop time: %s; stop: %lf %lf, mark: %c\n", curr->stop.number,
               curr->stop.start_time, curr->stop.stop_time, curr->stop.coord[0], curr->stop.coord[1],
               curr->stop.mark);
        curr = curr->next;
    }
}

int add_stop(Info stop, Node** res) { // TODO: везде проверить маллоки
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NO_MEMORY;
    }
    new_node->stop = stop;
    // дублируем строки
    new_node->stop.number = strdup(stop.number);
    new_node->stop.start_time = strdup(stop.start_time);
    new_node->stop.stop_time = strdup(stop.stop_time);
    new_node->next = NULL;
    *res = new_node;
    return OK;
}

time_t convert_time(const char *time) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    sscanf(time, "%d.%d.%d %d:%d:%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year, &tm.tm_hour, &tm.tm_min,
           &tm.tm_sec);
    tm.tm_year -= 1900;
    tm.tm_mon--;
    return mktime(&tm);
}

void insert(Node **head, Info stop) {
    Node *new_node;
    int status;
    if ((status = add_stop(stop, &new_node)) != OK) {
        print_scs(status);
        return;
    }
    if (*head == NULL || convert_time(stop.stop_time) < convert_time((*head)->stop.stop_time)) {
        new_node->next = *head;
        *head = new_node;
    } else {
        Node *curr = *head;
        while (curr->next != NULL && convert_time(stop.stop_time) > convert_time(curr->stop.stop_time)) {
            curr = curr->next;
        }
        new_node->next = curr->next;
        curr->next = new_node;
    }
}

// TODO: валидировать датф и время!!!
int validate(int day_stop, int month_stop, int year_stop, int hour_stop, int min_stop, int sec_stop,
              int day_start, int month_start, int year_start, int hour_start, int min_start, int sec_start) {
    if (year_start < year_stop) {
        return ERROR;
    }

    if (year_start == year_stop && month_start < month_stop) {
        return ERROR;
    }

    if (year_start == year_stop && month_start == month_stop && day_start < day_stop) {
        return ERROR;
    }

    if (year_start == year_stop && month_start == month_stop && day_start == day_stop && hour_start < hour_stop) {
        return ERROR;
    }

    if (year_start == year_stop && month_start == month_stop && day_start == day_stop && hour_start == hour_stop &&
        min_start < min_stop) {
        return ERROR;
    }

    if (year_start == year_stop && month_start == month_stop && day_start == day_stop && hour_start == hour_stop &&
        min_start == min_stop && sec_start < sec_stop) {
        return ERROR;
    }

    return OK;
}


int check_date(int day, int month, int year, int hour, int min, int sec) {
    if (day > 31 || day < 1) {
        return ERROR;
    }
    if (month > 12 || month < 1) {
        return ERROR;
    }
    if (month == 2 && day > 29) {
        return ERROR;
    }
    if (year < 0) {
        return ERROR;
    }
    if (hour > 23 || hour < 0) {
        return ERROR;
    }
    if (min > 59 || min < 0) {
        return ERROR;
    }
    if (sec > 59 || sec < 0) {
        return ERROR;
    }
    return OK;
}

int read_file(FILE *input, List *routes, double **coord, int *size, int *cnt) {
    char *line = NULL;
    size_t len = 0;
    double coord_x, coord_y;
    if (getline(&line, &len, input) != -1) {
        if (sscanf(line, "%lf %lf", &coord_x, &coord_y) != 2) {
            free(line);
            return INVALID_INPUT;
        }
    } else {
        free(line);
        return INVALID_INPUT;
    }

    (*coord)[*cnt] = coord_x;
    (*cnt)++;
    (*coord)[*cnt] = coord_y;
    (*cnt)++;

    char *number = (char *)malloc(TIME_SIZE * sizeof(char));
    if (number == NULL) {
        free(line);
        return NO_MEMORY;
    }
    int day_stop, month_stop, year_stop, hour_stop, min_stop, sec_stop, day_start, month_start, year_start,
        hour_start, min_start, sec_start;
    char mark;

    char *start_time = (char *)malloc(TIME_SIZE * sizeof(char));
    if (start_time == NULL) {
        free(line);
        free(number);
        return NO_MEMORY;
    }
    start_time[TIME_SIZE] = '\0';

    char *stop_time = (char *)malloc(TIME_SIZE * sizeof(char));
    if (stop_time == NULL) {
        free(line);
        free(start_time);
        free(number);
        return NO_MEMORY;
    }
    stop_time[TIME_SIZE] = '\0';
    if (*cnt == SIZE) {
        (*size) *= 2;
        double *temp = (double *)realloc(*coord, (*size) * sizeof(double));
        if (temp == NULL) {
            free(number);
            free(start_time);
            free(stop_time);
            free(line);
            return NO_MEMORY;
        }
        *coord = temp;
    }

    Info stop; // TODO: у сканф чекать возвращаемое число чтобы валидировать
    while (getline(&line, &len, input) != -1) {
        if (sscanf(line, "%s %d.%d.%d %d:%d:%d %d.%d.%d %d:%d:%d %c", number, &day_stop, &month_stop,
                   &year_stop, &hour_stop, &min_stop, &sec_stop, &day_start, &month_start, &year_start,
                   &hour_start, &min_start, &sec_start, &mark) != 14) {
            continue;
        } else {
            if (check_date(day_stop, month_stop, year_stop, hour_stop, min_stop, sec_stop) == ERROR) {
                continue;
            }
            if (check_date(day_start, month_start, year_start, hour_start, min_start, sec_start) == ERROR) {
                continue; 
            }
            if (validate(day_stop, month_stop, year_stop, hour_stop, min_stop, sec_stop, day_start,
                          month_start, year_start, hour_start, min_start, sec_start) == ERROR) {
                continue; 
            }
            if (mark != 'B' && mark != 'E' && mark != 'M') {
                continue;
            }
            sprintf(stop_time, "%d.%d.%d %d:%d:%d", day_stop, month_stop, year_stop, hour_stop, min_stop,
                    sec_stop);
            sprintf(start_time, "%d.%d.%d %d:%d:%d", day_start, month_start, year_start, hour_start,
                    min_start, sec_start);

            stop.coord[0] = coord_x;
            stop.coord[1] = coord_y;
            stop.start_time = strdup(start_time);
            stop.stop_time = strdup(stop_time);
            stop.mark = mark;
            stop.number = strdup(number);

            insert(&routes->head, stop);
        }
    }

    free(number);
    free(start_time);
    free(stop_time);
    free(line);

    return OK;
}

void free_list(Node *head) {
    Node *curr = head;
    Node *next;
    while (curr != NULL) {
        next = curr->next;
        free(curr->stop.start_time);
        free(curr->stop.stop_time);
        free(curr->stop.number);
        free(curr);

        curr = next;
    }
}

void menu() { printf("\nChoose your choice:\n 1. Back to menu\n 2. Exit\nEnter a number: "); }
void default_menu() {printf("\n\tMAIN MENU\n 1.Find the most/least number of routes\n 2.Find the longest/shortest way\n 3.Find the longest/shortest rout\n 4.Find the longest/shortest stop\n 5.The longest stand\n 6.Print list\n 7.Exit\nEnter a number: ");}
