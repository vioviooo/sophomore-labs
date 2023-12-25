#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum status_codes {
    OK = 1,
    ERROR = -2,
    INVALID_INPUT = 2,
    INVALID_INPUT_IN_FILE = -6,
    NO_MEMORY = -1,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    FILE_NOT_OPEN = -5,
    EMPTY = -7,
    STOP = 10,
    INVALID_OPTION = -8,
    INVALID_ID = -9,
    TIME_ERROR = -10
};

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

typedef struct {
    char *data;
    int length;
} String;

typedef struct {
    String city;
    String street;
    int house_num;
    String building;
    int apt_num;
    String index;
} Address;

typedef struct {
    Address address_client;
    double weight;
    String id;
    String creation_time;
    String delivery_time;
} Mail;

typedef struct {
    Address post_address;
    Mail *packages;
    int packages_number;
} Post;

int compare_package_time(const void *first, const void *second);
Mail **get_delivered_packages(Post *post, int *cnt);
void get_time(const char *delivery_time, struct tm *delivery_tm);
int delete_package(Post *post, const char *input_id);
int find_mail(Post *post, const char *input_id, Mail ***found_mails);
int add_package(Post *post, Address address_client, double weight, String id, String creation_time,
                String delivery_time);
int get_string(String *str, int flag);
int is_valid_index(const String *str);
int is_valid_id(const String *str);
int is_valid_time(const String *str);
void delete(String *str);
void delete_packages(Post *post);
void print_scs(int state);

void default_menu() {
    printf(
            "Welcome! Choose your pokemon:\n 1. Add package\n 2. Delete package\n 3. Info about package\n 4. "
            "All delivered packages\n 5. All packages\n 6. Exit\n Enter a number: ");
}
void menu() {
    printf("Choose one of the following:\n 1. Back to menu\n 2. Exit\n Enter a number: ");
}

int main(void) {
    int option = 0, res = 0, cnt = 0;
    double eps = 1e-9, weight = 0.0;

    Address address_client;

    String id, creation_time, delivery_time, input_id;
    
    /// mail init
    Mail **found_mail = NULL;
    Mail **found_mail_delivered = NULL;

    // post init
    Post post;
    post.packages_number = 0;
    post.packages = NULL;

    bool flag = true;
    while (flag) {
        fflush(stdin);
        default_menu();
        if (!scanf("%d", &option) || option < 1 || option > 6) {
            print_scs(INVALID_OPTION);
            default_menu();
            while (!scanf("%d", &option) || option < 1 || option > 6) {
                fflush(stdin);
                print_scs(INVALID_OPTION);
                default_menu();
            }
        }
        switch (option) {
            case 1: ////////////////////////////////////////////////////
                fflush(stdin);
                printf("Enter city: ");
                res = get_string(&address_client.city, 0);
                if (res == INVALID_INPUT) {
                    print_scs(INVALID_INPUT);
                    option = 0;
                    break;
                } else if (res == NO_MEMORY) {
                    print_scs(NO_MEMORY);
                    flag = false;
                    break;
                }
                fflush(stdin);
                printf("Enter the street: ");
                res = get_string(&address_client.street, 0);
                if (res == INVALID_INPUT) {
                    print_scs(INVALID_INPUT);
                    free(address_client.city.data);
                    option = 0;
                    break;
                } else if (res == NO_MEMORY) {
                    print_scs(NO_MEMORY);
                    free(address_client.city.data);
                    flag = false;
                    break;
                }
                fflush(stdin);
                printf("Enter a number of house_num: ");
                if (!scanf("%d", &address_client.house_num) || address_client.house_num <= 0) {
                    print_scs(INVALID_INPUT);
                    option = 0;
                    break;
                }
                fflush(stdin);
                printf("Enter a building: ");
                res = get_string(&address_client.building, 0);
                if (res == INVALID_INPUT) {
                    print_scs(INVALID_INPUT);
                    option = 0;
                    break;
                } else if (res == NO_MEMORY) {
                    print_scs(NO_MEMORY);
                    free(address_client.city.data);
                    free(address_client.street.data);
                    flag = false;
                    break;
                }
                fflush(stdin);
                printf("Enter № of apt_num: ");
                if (!scanf("%d", &address_client.apt_num) || address_client.apt_num <= 0) {
                    print_scs(INVALID_INPUT);
                    option = 0;
                    break;
                }
                fflush(stdin);
                printf("Enter the index: ");
                res = get_string(&address_client.index, 2);
                if (res != OK) {
                    print_scs(res);
                    if (res == NO_MEMORY) {
                        print_scs(NO_MEMORY);
                        free(address_client.city.data);
                        free(address_client.street.data);
                        free(address_client.building.data);
                        flag = false;
                    } else if (res == INVALID_INPUT) {
                        print_scs(INVALID_INPUT);
                        option = 0;
                    }
                    break;
                }
                fflush(stdin);
                printf("Enter weight of package: ");
                if (!scanf("%lf", &weight) || weight <= eps) {
                    print_scs(INVALID_INPUT);
                    option = 0;
                    break;
                }
                fflush(stdin);
                printf("Enter an id: ");
                res = get_string(&id, 3);
                if (res == INVALID_INPUT) {
                    print_scs(INVALID_INPUT);
                    option = 0;
                    break;
                } else if (res == NO_MEMORY) {
                    print_scs(NO_MEMORY);
                    free(address_client.city.data);
                    free(address_client.street.data);
                    free(address_client.building.data);
                    free(address_client.index.data);
                    flag = false;
                    break;
                }
                fflush(stdin);
                printf("Enter creation time (dd:MM:yyyy hh:mm:ss): ");
                res = get_string(&creation_time, 4);
                if (res == INVALID_INPUT) {
                    print_scs(INVALID_INPUT);
                    option = 0;
                    break;
                } else if (res == NO_MEMORY) {
                    print_scs(NO_MEMORY);
                    free(address_client.city.data);
                    free(address_client.street.data);
                    free(address_client.building.data);
                    free(address_client.index.data);
                    free(id.data);
                    flag = false;
                    break;
                }
                fflush(stdin);
                printf("Enter delivery time (dd:MM:yyyy hh:mm:ss): ");
                res = get_string(&delivery_time, 4);
                if (res == INVALID_INPUT) {
                    print_scs(INVALID_INPUT);
                    option = 0;
                    break;
                } else if (res == NO_MEMORY) {
                    print_scs(NO_MEMORY);
                    free(address_client.city.data);
                    free(address_client.street.data);
                    free(address_client.building.data);
                    free(address_client.index.data);
                    free(id.data);
                    free(creation_time.data);
                    flag = false;
                    break;
                }
                fflush(stdin);
                res = add_package(&post, address_client, weight, id, creation_time, delivery_time);
                if (res == NO_MEMORY) {
                    print_scs(NO_MEMORY);
                    delete_packages(&post);
                    return NO_MEMORY;
                } else if (res == INVALID_ID) {
                    print_scs(INVALID_ID);
                    option = 0;
                    break;
                } else if (res == TIME_ERROR) {
                    print_scs(TIME_ERROR);
                    option = 0;
                    break;
                } else {
                    menu();
                    fflush(stdin);
                    if (!scanf("%d", &option) || option < 1 || option > 2) {
                        print_scs(INVALID_OPTION);
                        menu();
                        while (!scanf("%d", &option) || option < 1 || option > 2) {
                            fflush(stdin);
                            print_scs(INVALID_OPTION);
                            menu();
                        }
                    }
                    if (option == 2) {
                        flag = false;
                    }
                }
                break;
            case 2: ////////////////////////////////////////////////////
                if (post.packages_number == 0) {
                    printf("There are no packages in the system\n");
                } else {
                    fflush(stdin);
                    printf("Input package's id: ");
                    get_string(&input_id, 3);
                    cnt = delete_package(&post, input_id.data);
                    if (cnt == NO_MEMORY) {
                        print_scs(NO_MEMORY);
                        return NO_MEMORY;
                    } else if (cnt == ERROR) {
                        printf("There is no package with this id in the system\n");
                    } else {
                        printf("Success.\n");
                    }
                    delete (&input_id);
                }
                menu();
                fflush(stdin);
                if (!scanf("%d", &option) || option < 1 || option > 2) {
                    print_scs(INVALID_OPTION);
                    menu();
                    while (!scanf("%d", &option) || option < 1 || option > 2) {
                        fflush(stdin);
                        print_scs(INVALID_OPTION);
                        menu();
                    }
                }
                if (option == 2) {
                    flag = false;
                }
                break;
            case 3: ////////////////////////////////////////////////////
                if (post.packages_number == 0) {
                    printf("There are no packages in the system\n");
                } else {
                    fflush(stdin);
                    printf("Input package's id: ");
                    get_string(&input_id, 3);
                    cnt = find_mail(&post, input_id.data, &found_mail);
                    if (cnt == NO_MEMORY) {
                        print_scs(NO_MEMORY);
                        return NO_MEMORY;
                    }
                    if (cnt == 1) {
                        printf("Information about package: \n");
                        printf(
                            "\tAddress: %s city, %s street, house_num %d, building %s, apt_num %d, index %s\n",
                            found_mail[cnt - 1]->address_client.city.data,
                            found_mail[cnt - 1]->address_client.street.data,
                            found_mail[cnt - 1]->address_client.house_num,
                            found_mail[cnt - 1]->address_client.building.data,
                            found_mail[cnt - 1]->address_client.apt_num,
                            found_mail[cnt - 1]->address_client.index.data);
                        printf("\tWeight of package: %lf\n", found_mail[cnt - 1]->weight);
                        printf("\tTime of creation: %s\n", found_mail[cnt - 1]->creation_time.data);
                        printf("\tTime of delivery: %s\n", found_mail[cnt - 1]->delivery_time.data);
                        free(found_mail);
                    } else if (cnt == 0) {
                        printf("There is not any package with this id.\n");
                    }
                    delete (&input_id);
                }
                menu();
                fflush(stdin);
                if (!scanf("%d", &option) || option < 1 || option > 2) {
                    print_scs(INVALID_OPTION);
                    menu();
                    while (!scanf("%d", &option) || option < 1 || option > 2) {
                        fflush(stdin);
                        print_scs(INVALID_OPTION);
                        menu();
                    }
                }
                if (option == 2) {
                    flag = false;
                }
                break;
            case 4: ////////////////////////////////////////////////////
                if (post.packages_number == 0) {
                    printf("There are no packages in the system\n");
                } else {
                    cnt = 0;
                    found_mail_delivered = get_delivered_packages(&post, &cnt);
                    if (found_mail_delivered == NULL) {
                        print_scs(NO_MEMORY);
                        delete_packages(&post);
                        return NO_MEMORY;
                    } else {
                        qsort(found_mail_delivered, cnt, sizeof(Mail *), compare_package_time);
                        for (int i = 0; i < cnt; i++) {
                            printf("Information about package: \n");
                            printf(
                                "\tAddress: %s city, %s street, house_num %d, building %s, apt_num %d, index "
                                "%s\n",
                                found_mail_delivered[i]->address_client.city.data,
                                found_mail_delivered[i]->address_client.street.data,
                                found_mail_delivered[i]->address_client.house_num,
                                found_mail_delivered[i]->address_client.building.data,
                                found_mail_delivered[i]->address_client.apt_num,
                                found_mail_delivered[i]->address_client.index.data);
                            printf("\tWeight of package: %lf\n", found_mail_delivered[i]->weight);
                            printf("\tTime of creation: %s\n", found_mail_delivered[i]->creation_time.data);
                            printf("\tTime of delivery: %s\n", found_mail_delivered[i]->delivery_time.data);
                        }
                        for (int i = 0; i < cnt; i++) {
                            free(found_mail_delivered[i]);
                            found_mail_delivered[i] = NULL;
                        }
                        free(found_mail_delivered);
                    }
                }
                menu();
                if (!scanf("%d", &option) || option < 1 || option > 2) {
                    print_scs(INVALID_OPTION);
                    menu();
                    while (!scanf("%d", &option) || option < 1 || option > 2) {
                        fflush(stdin);
                        print_scs(INVALID_OPTION);
                        menu();
                    }
                }
                if (option == 2) {
                    flag = false;
                }
                break;
            case 5: //////////////////////////
                for (int i = 0; i < post.packages_number; i++) {
                    printf("Information about package: \n");
                    printf("\tAddress: %s city, %s street, house_num %d, building %s, apt_num %d, index %s\n",
                           post.packages[i].address_client.city.data,
                           post.packages[i].address_client.street.data,
                           post.packages[i].address_client.house_num,
                           post.packages[i].address_client.building.data,
                           post.packages[i].address_client.apt_num,
                           post.packages[i].address_client.index.data);
                    printf("\tWeight of package: %lf\n", post.packages[i].weight);
                    printf("\tId of package: %s\n", post.packages[i].id.data);
                    printf("\tTime of creation: %s\n", post.packages[i].creation_time.data);
                    printf("\tTime of delivery: %s\n", post.packages[i].delivery_time.data);
                }
                menu();
                if (!scanf("%d", &option) || option < 1 || option > 2) {
                    print_scs(INVALID_OPTION);
                    menu();
                    while (!scanf("%d", &option) || option < 1 || option > 2) {
                        fflush(stdin);
                        print_scs(INVALID_OPTION);
                        menu();
                    }
                }
                if (option == 2) {
                    flag = false;
                }
                break;
            default:
                flag = false;
                break;
        }
    }
    delete_packages(&post);
    return OK;
}

int compare_package_time(const void *first, const void *second) {
    Mail *mail_first = *(Mail **)first;
    Mail *mail_second = *(Mail **)second;

    struct tm tm_first, tm_second;
    get_time(mail_first->creation_time.data, &tm_first);
    get_time(mail_second->creation_time.data, &tm_second);

    time_t time_first = mktime(&tm_first);
    time_t time_second = mktime(&tm_second);

    if (difftime(time_first, time_second) < 0) {
        return -1;
    } else if (difftime(time_first, time_second) > 0) {
        return 1;
    } else {
        return 0;
    }
}

Mail **get_delivered_packages(Post *post, int *cnt) {
    time_t cur_time;
    time(&cur_time);
    Mail **temp = NULL;

    for (int i = 0; i < post->packages_number; i++) {
        struct tm delivery_tm;
        get_time(post->packages[i].delivery_time.data, &delivery_tm);
        time_t d_t = mktime(&delivery_tm);
        if (d_t <= cur_time) {
            (*cnt)++;
            Mail **new_temp = (Mail **)realloc(temp, (*cnt) * sizeof(Mail *));
            if (new_temp == NULL) {
                free(temp);
                return NULL;
            }
            temp = new_temp;
            temp[(*cnt) - 1] = malloc(sizeof(Mail));
            if (temp[(*cnt) - 1] == NULL) {
                free(temp);
                return NULL;
            }
            memcpy(temp[(*cnt) - 1], &post->packages[i], sizeof(Mail));
        }
    }
    return temp;
}

void get_time(const char *delivery_time, struct tm *delivery_tm) {
    sscanf(delivery_time, "%d:%d:%d %d:%d:%d", &delivery_tm->tm_mday, &delivery_tm->tm_mon,
           &delivery_tm->tm_year, &delivery_tm->tm_hour, &delivery_tm->tm_min, &delivery_tm->tm_sec);
    delivery_tm->tm_year -= 1900;
    delivery_tm->tm_mon -= 1;
}

int delete_package(Post *post, const char *input_id) {
    int cnt = -1;

    for (int i = 0; i < post->packages_number; i++) {
        if (!strcmp(post->packages[i].id.data, input_id)) {
            cnt = i;
            break;
        }
    }
    if (cnt == -1) {
        return ERROR;
    }

    delete (&post->packages[cnt].address_client.city);
    delete (&post->packages[cnt].address_client.street);
    delete (&post->packages[cnt].address_client.building);
    delete (&post->packages[cnt].address_client.index);
    delete (&post->packages[cnt].id);
    delete (&post->packages[cnt].creation_time);
    delete (&post->packages[cnt].delivery_time);

    for (int i = cnt; i < post->packages_number - 1; i++) {
        post->packages[i] = post->packages[i + 1];
    }

    post->packages_number--;

    Mail *temp = (Mail *)realloc(post->packages, post->packages_number * sizeof(Mail));

    if (temp == NULL && post->packages_number > 0) {
        return NO_MEMORY;
    }

    post->packages = temp;

    return OK;
}

int find_mail(Post *post, const char *input_id, Mail ***found_mails) {
    Mail **temp = NULL;
    int cnt = 0;

    for (int i = 0; i < post->packages_number; i++) {
        if (!strcmp(post->packages[i].id.data, input_id)) {
            cnt++;
            Mail **new_temp = (Mail **)realloc(temp, cnt * sizeof(Mail *));
            if (new_temp == NULL) {
                for (int j = 0; j < cnt - 1; j++) {
                    free(temp[j]);
                }
                free(temp);
                return NO_MEMORY;
            }
            temp = new_temp;
            temp[cnt - 1] = &(post->packages[i]);
        }
    }
    *found_mails = temp;
    return cnt;
}

int add_package(Post *post, Address address_client, double weight, String id, String creation_time,
                String delivery_time) {
    struct tm tm_creation, tm_delivery;
    get_time(creation_time.data, &tm_creation);
    get_time(delivery_time.data, &tm_delivery);
    time_t time_creation = mktime(&tm_creation);
    time_t time_delivery = mktime(&tm_delivery);
    if (difftime(time_delivery, time_creation) < 0) {
        return TIME_ERROR;
    }
    for (int i = 0; i < post->packages_number; i++) {
        if (!strcmp(post->packages[i].id.data, id.data)) {
            return INVALID_ID;
        }
    }

    Mail new_mail;
    new_mail.address_client = address_client;
    new_mail.weight = weight;
    new_mail.id = id;
    new_mail.creation_time = creation_time;
    new_mail.delivery_time = delivery_time;

    int index = 0;
    int check_index = 0;
    int check_id = 0;
    while (index < post->packages_number) {
        Mail *cur_mail = &post->packages[index];
        check_index = strcmp(new_mail.address_client.index.data, cur_mail->address_client.index.data);
        if (check_index < 0) {
            break;
        } else if (check_index == 0) {
            check_id = strcmp(new_mail.id.data, cur_mail->id.data);
            if (check_id < 0) {
                break;
            }
        }
        index++;
    }
    post->packages_number++;
    Mail *temp_packages = (Mail *)realloc(post->packages, post->packages_number * sizeof(Mail));
    if (temp_packages == NULL) {
        return NO_MEMORY;
    }
    post->packages = temp_packages;
    for (int i = post->packages_number - 1; i > index; i--) {
        post->packages[i] = post->packages[i - 1];
    }
    post->packages[index] = new_mail;

    return OK;
}

int get_string(String *str, int flag) {
    int length = 2;
    int i = 0;
    char *temp = (char *)malloc(length * sizeof(char));
    if (temp == NULL) {
        return NO_MEMORY;
    }
    char *temp_str;
    char symbol = getchar();
    while (symbol != '\n' && symbol != EOF) {
        temp[i] = symbol;
        i++;
        if (i >= length) {
            length *= 2;
            temp_str = (char *)realloc(temp, length * sizeof(char));
            if (temp_str == NULL) {
                free(temp);
                return NO_MEMORY;
            }
            temp = temp_str;
        }
        symbol = getchar();
    }
    temp[i] = '\0';
    str->length = strlen(temp);
    str->data = (char *)malloc((str->length + 1) * sizeof(char));
    if (str->data == NULL) {
        return NO_MEMORY;
    }
    strcpy(str->data, temp);
    free(temp);

    if (flag == 2 && is_valid_index(str) == ERROR) {
        return INVALID_INPUT;
    } else if (flag == 3 && is_valid_id(str) == ERROR) {
        return INVALID_INPUT;
    } else if (flag == 4 && is_valid_time(str) == ERROR) {
        return INVALID_INPUT;
    }
    return OK;
}

int is_valid_time(const String *str) {
    if (str->length != 19) {
        return ERROR;
    }
    for (int i = 0; i < 19; i++) {
        if (str->data[i] == ' ' && i != 10) {
            return ERROR;
        }
        if ((str->data[i] > '3' || !isdigit(str->data[i])) && i == 0) {
            return ERROR;
        }
        if ((str->data[i] > '1' || !isdigit(str->data[i])) && i == 3) {
            return ERROR;
        }
        if (((str->data[i - 1] == '1' && str->data[i] > '2') || !isdigit(str->data[i])) && i == 4) {
            return ERROR;
        }
        if ((str->data[i] > '2' || !isdigit(str->data[i])) && i == 11) {
            return ERROR;
        }
        if ((str->data[i] > '5' || !isdigit(str->data[i])) && (i == 14 || i == 17)) {
            return ERROR;
        }
        if (i == 2 || i == 5 || i == 13 || i == 16) {
            if (str->data[i] != ':') {
                return ERROR;
            }
        } else if (!isdigit(str->data[i]) && i != 10) {
            return ERROR;
        }
    }
    return OK;
}

int is_valid_id(const String *str) {
    if (str->length != 14) {
        return INVALID_INPUT;
    }
    for (int i = 0; i < 14; i++) {
        if (!isdigit(str->data[i])) {
            return INVALID_INPUT;
        }
    }
    return OK;
}

int is_valid_index(const String *str) {
    if (str->length != 6) {
        return ERROR;
    }
    for (int i = 0; i < 6; i++) {
        if (!isdigit(str->data[i])) {
            return ERROR;
        }
    }
    return OK;
}

void delete(String *str) {
    if (str->data != NULL) {
        free(str->data);
        str->data = NULL;
    }
}

void delete_packages(Post *post) {
    if (post->packages != NULL) {
        for (int i = 0; i < post->packages_number; i++) {
            delete(&post->packages[i].address_client.city);
            delete(&post->packages[i].address_client.street);
            delete(&post->packages[i].address_client.building);
            delete(&post->packages[i].address_client.index);
            delete(&post->packages[i].id);
            delete(&post->packages[i].creation_time);
            delete(&post->packages[i].delivery_time);
        }
        free(post->packages);
        post->packages = NULL;
        post->packages_number = 0;
    }
}