#include <complex.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <time.h>

enum status_codes {
  OK = 1,
  ERROR = -2,
  INVALID_INPUT = -3,
  INVALID_INPUT_FILE = -4,
  NO_MEMORY = -5,
  OVERFLOW_ = -6,
  UNDEFINED = -7,
  FILE_NOT_OPEN = -8,
  EMPTY = -9,
  NO_OPERATIONS = -10,
  ZERO_UNDO = -11
};

enum options {
  NAME = 1,
  LAST_NAME = 2,
  MIDDLE_NAME = 3,
  SALARY = 4,
  GENDER = 5,
  BIRTH_DATE = 6,
};

enum Action {
  ADD = 'A',
  DELETE = 'D',
  CHANGE = 'C',
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
    printf("\nError! What you're trying to calculate IS UNDEFINED or uses "
           "complex numbers.\n");
    break;
  case FILE_NOT_OPEN:
    printf("\nCan't open file.\n");
    break;
  case INVALID_INPUT_FILE:
    printf("\nInvalid format of data in file.\n");
    break;
  case EMPTY:
    printf("\nEmpty list.\n");
    break;
  case ZERO_UNDO:
    printf("\nNothing to undo.\n");
    break;
  default:
    break;
  }
}

typedef struct Liver {
  char name[BUFSIZ];
  char middle_name[BUFSIZ]; // can be empty
  char last_name[BUFSIZ];
  int day;
  int month;
  int year;
  char gender;
  double salary;
  struct Liver *next;
} Liver;

typedef struct UndoNode {
  int cnt;
  char action; // D - delete, A - add, C - change
  char name[BUFSIZ];
  char middle_name[BUFSIZ]; // can be empty
  char last_name[BUFSIZ];
  int day;
  int month;
  int year;
  char gender;
  double salary;
  struct Liver *prev_state;
  struct UndoNode *next;
} UndoNode;

Liver *insert_sorted(Liver *head, Liver *new_liver) {
  Liver *curr = head;
  Liver *previous = NULL;

  while (curr != NULL && curr->year < new_liver->year) {
    previous = curr;
    curr = curr->next;
  }

  if (previous == NULL) {
    new_liver->next = head;
    head = new_liver;
  } else {
    previous->next = new_liver;
    new_liver->next = curr;
  }

  return head;
}

int find_liver(Liver *head) {
  char name[BUFSIZ];
  char sur[BUFSIZ];
  char mid[BUFSIZ];
  int d, m, y;
  char gen;
  double sal;
  if (scanf("%s %s %s %d %d %d %c %lf", sur, name, mid, &d, &m, &y, &gen,
            &sal) != 8) {
    while (getchar() != '\n')
      ;
    return INVALID_INPUT;
  }
  Liver *curr = head;
  while (curr != NULL) {
    if (strcmp(curr->name, name) == 0 && strcmp(curr->middle_name, mid) == 0 &&
        strcmp(curr->last_name, sur) == 0 && curr->day == d &&
        curr->month == m && curr->year == y && curr->gender == gen &&
        fabs(curr->salary - sal) < 1e-6) {
      return 1;
    }
    curr = curr->next;
  }
  return 0;
}

void delete_undo_liver(Liver **head, UndoNode *node) { //////
  Liver *current = *head;
  Liver *previous = NULL;

  while (current != NULL) {
    if (strcmp(current->name, node->name) == 0 &&
        strcmp(current->middle_name, node->middle_name) == 0 &&
        strcmp(current->last_name, node->last_name) == 0 &&
        current->year == node->year && current->day == node->day &&
        current->month == node->month &&
        fabs(current->salary - node->salary) < 1e-6) {
      if (previous == NULL) {
        *head = current->next;
      } else {
        previous->next = current->next;
      }
      free(current);
    }
    previous = current;
    current = current->next;
  }
}

int add_undo_liver(Liver **head, Liver **prev_state, UndoNode *node) {
  Liver *new_liver = (Liver *)malloc(sizeof(Liver));
  if (new_liver == NULL) {
    return NO_MEMORY;
  }

  strcpy(new_liver->name, node->name);
  strcpy(new_liver->middle_name, node->middle_name);
  strcpy(new_liver->last_name, node->last_name);
  new_liver->day = node->day;
  new_liver->month = node->month;
  new_liver->year = node->year;
  new_liver->gender = node->gender;
  new_liver->salary = node->salary;

  new_liver->next = NULL;
  *head = insert_sorted(*head, new_liver);

  // update previous state
  if (*prev_state != NULL) {
    *prev_state = (Liver *)malloc(sizeof(Liver));
    if (*prev_state == NULL) {
      free(new_liver);
      return NO_MEMORY;
    }
    memcpy(*prev_state, new_liver, sizeof(Liver));
  }

  return OK;
}

int add_undo(UndoNode **undo_head, char action, const Liver *data,
             Liver *prev) {
  UndoNode *new_undo = (UndoNode *)malloc(sizeof(UndoNode));
  if (new_undo == NULL) {
    return NO_MEMORY;
  }

  new_undo->action = action;
  strcpy(new_undo->name, data->name);
  strcpy(new_undo->middle_name, data->middle_name);
  strcpy(new_undo->last_name, data->last_name);
  new_undo->day = data->day;
  new_undo->month = data->month;
  new_undo->year = data->year;
  new_undo->gender = data->gender;
  new_undo->salary = data->salary;
  new_undo->next = *undo_head;

  if (prev != NULL) {
    new_undo->prev_state = prev;
  }

  free(prev);

  *undo_head = new_undo;

  return OK;
}

int delete_liver(Liver **head, UndoNode **undo_head) {
  printf("Please, enter liver's parameters: ");

  char name[BUFSIZ];
  char sur[BUFSIZ];
  char mid[BUFSIZ];
  int d, m, y;
  char gen;
  double sal;

  if (scanf("%s %s %s %d %d %d %c %lf", sur, name, mid, &d, &m, &y, &gen,
            &sal) != 8) {
    while (getchar() != '\n')
      ;
    return INVALID_INPUT;
  }

  Liver *current = *head;
  Liver *previous = NULL;

  int status;
  while (current != NULL) {
    if (strcmp(current->name, name) == 0 &&
        strcmp(current->middle_name, mid) == 0 &&
        strcmp(current->last_name, sur) == 0 && current->year == y &&
        current->day == d && current->month == m &&
        fabs(current->salary - sal) < 1e-6) {
      if ((status = add_undo(undo_head, DELETE, current, NULL)) != OK) {
        return NO_MEMORY;
      }
      (*undo_head)->cnt++; // ADD CNT!!!

      if (previous == NULL) {
        *head = current->next;
      } else {
        previous->next = current->next;
      }
      free(current);

      return 1;
    }
    previous = current;
    current = current->next;
  }

  return 0;
}

int add_liver(Liver **head, Liver **prev_state, UndoNode **undo_head) {
  char name[BUFSIZ];
  char sur[BUFSIZ];
  char mid[BUFSIZ];
  int d, m, y;
  char gen;
  double sal;
  if (scanf("%s %s %s %d %d %d %c %lf", name, sur, mid, &d, &m, &y, &gen,
            &sal) != 8 ||
      m > 12 || d > 31 || m < 1 || d < 1 || y < 1 ||
      (tolower(gen) != 'w' && tolower(gen) != 'm') || fabs(sal - 1e-6) < 0.0) {
    while (getchar() != '\n')
      ;
    return INVALID_INPUT;
  }

  Liver *new_liver = (Liver *)malloc(sizeof(Liver));
  if (new_liver == NULL) {
    return NO_MEMORY;
  }

  strcpy(new_liver->name, name);
  strcpy(new_liver->middle_name, mid);
  strcpy(new_liver->last_name, sur);
  new_liver->day = d;
  new_liver->month = m;
  new_liver->year = y;
  new_liver->gender = gen;
  new_liver->salary = sal;

  add_undo(undo_head, ADD, new_liver, NULL);
  (*undo_head)->cnt++;

  new_liver->next = NULL;
  *head = insert_sorted(*head, new_liver);

  // update previous state
  if (*prev_state != NULL) {
    *prev_state = (Liver *)malloc(sizeof(Liver));
    if (*prev_state == NULL) {
      free(new_liver);
      return NO_MEMORY;
    }
    memcpy(*prev_state, new_liver, sizeof(Liver));
  }

  return OK;
}

int load_data(const char *filename, Liver **head) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return FILE_NOT_OPEN;
  }

  *head = NULL;
  Liver *curr = NULL;

  char line[BUFSIZ];
  while (fgets(line, sizeof(line), file) != NULL) {
    Liver *new_liver = (Liver *)malloc(sizeof(Liver));
    if (new_liver == NULL) {
      fclose(file);
      return NO_MEMORY;
    }

    if (sscanf(line, "%s %s %s %d %d %d %c %lf", new_liver->last_name,
               new_liver->name, new_liver->middle_name, &new_liver->day,
               &new_liver->month, &new_liver->year, &new_liver->gender,
               &new_liver->salary) != 8 ||
        new_liver->salary < 1e-6 || new_liver->day < 1 || new_liver->day > 31 ||
        new_liver->month < 1 || new_liver->month > 12 ||
        (tolower(new_liver->gender) != 'w' &&
         tolower(new_liver->gender) != 'm')) {
      fclose(file);
      free(new_liver);
      return INVALID_INPUT_FILE;
    }

    new_liver->next = NULL;
    *head = insert_sorted(*head, new_liver);
    curr = new_liver;
  }

  fclose(file);
  return OK;
}

void print_list(Liver *head, FILE *fptr) {
  Liver *curr = head;
  while (curr != NULL) {
    fprintf(fptr, "%s %s %s %d %d %d %c %.2lf\n", curr->last_name, curr->name,
            curr->middle_name, curr->day, curr->month, curr->year, curr->gender,
            curr->salary);
    curr = curr->next;
  }
}

void print_menu_change() {
  printf("\n[edit mode] Choose your action:\n");
  printf("1. Change name\n");
  printf("2. Change last name\n");
  printf("3. Change middle name\n");
  printf("4. Change salary\n");
  printf("5. Change gender\n");
  printf("6. Change date of birth\n");
  printf("0. Exit\n");
  printf("Please, enter: ");
}

// !!!
int change_undo_liver(Liver **head, UndoNode *node, Liver *prev_node) {
  Liver *current = *head;
  while (current != NULL) {
    if (strcmp(current->name, node->name) == 0 &&
        strcmp(current->middle_name, node->middle_name) == 0 &&
        strcmp(current->last_name, node->last_name) == 0 &&
        current->year == node->year && current->day == node->day &&
        current->month == node->month &&
        fabs(current->salary - node->salary) < 1e-6) {
      strcpy(current->name, prev_node->name);
      strcpy(current->middle_name, prev_node->middle_name);
      strcpy(current->last_name, prev_node->last_name);
      current->day = prev_node->day;
      current->month = prev_node->month;
      current->year = prev_node->year;
      current->gender = prev_node->gender;
      current->salary = prev_node->salary;
      break;
    }
    current = current->next;
  }

  return OK;
}

int change_liver(Liver **head, int *cnt_oper, UndoNode **undo_head) {
  char name[BUFSIZ];
  char sur[BUFSIZ];
  char mid[BUFSIZ];
  int d, m, y;
  char gen;
  double sal;

  if (scanf("%s %s %s %d %d %d %c %lf", sur, name, mid, &d, &m, &y, &gen,
            &sal) != 8) {
    while (getchar() != '\n')
      ;
    return INVALID_INPUT;
  }

  Liver *current = *head;

  bool flag = true;
  while (current != NULL) {
    if (strcmp(current->name, name) == 0 &&
        strcmp(current->middle_name, mid) == 0 &&
        strcmp(current->last_name, sur) == 0 && current->year == y &&
        current->day == d && current->month == m &&
        fabs(current->salary - sal) < 1e-6) {
      char buf[BUFSIZ];
      int d_, m_, y_;
      char gender;
      double salary;
      while (flag) {
        print_menu_change();
        int choice;
        scanf("%d", &choice);
        printf("Please, enter the change: ");
        switch (choice) {
        case NAME:
          scanf("%s", buf);
          strcpy(current->name, buf);
          break;
        case LAST_NAME:
          scanf("%s", buf);
          strcpy(current->last_name, buf);
          break;
        case MIDDLE_NAME:
          scanf("%s", buf);
          strcpy(current->middle_name, buf);
          break;
        case SALARY:
          if (scanf("%lf", &salary) != 1) {
            return INVALID_INPUT;
          } else {
            current->salary = salary;
          }
          break;
        case GENDER:
          if (tolower(current->gender) == 'm') {
            current->gender = 'w';
          } else {
            current->gender = 'm';
          }
          break;
        case BIRTH_DATE:
          if (scanf("%d %d %d", &d_, &m_, &y_) != 3) {
            return INVALID_INPUT;
          } else {
            current->day = d_;
            current->month = m_;
            current->year = y_;
          }
          break;
        case 0:
          flag = false;
          break;
        default:
          print_scs(INVALID_INPUT);
          break;
        }
      }

      (*cnt_oper)++;

      Liver *prev_liver = (Liver *)malloc(sizeof(Liver));
      if (prev_liver == NULL) {
        return NO_MEMORY;
      }

      strcpy(prev_liver->name, name);
      strcpy(prev_liver->middle_name, mid);
      strcpy(prev_liver->last_name, sur);
      prev_liver->day = d;
      prev_liver->month = m;
      prev_liver->year = y;
      prev_liver->salary = sal;
      prev_liver->gender = gen;

      add_undo(undo_head, CHANGE, current, prev_liver); // !!!
      (*undo_head)->cnt++;

      return 1;
    }
    current = current->next;
  }

  return 0;
}

int do_undo(UndoNode **undo_head, Liver **head) {
  if (undo_head == NULL || (*undo_head)->action == '-') {
    return EMPTY;
  }

  UndoNode *last_undo = *undo_head;
  *undo_head = (*undo_head)->next;

  Liver *prev_state = NULL;
  int status;
  switch (last_undo->action) {
  case ADD:
    delete_undo_liver(head, last_undo);
    break;
  case DELETE:
    prev_state = *head;
    if ((status = add_undo_liver(head, &prev_state, last_undo)) != OK) {
      print_scs(status);
    }
    break;
  case CHANGE:
    if ((status = change_undo_liver(head, last_undo, last_undo->prev_state)) !=
        OK) {
      print_scs(status);
    }
    break;
  default:
    break;
  }

  free(last_undo);

  return OK;
}

void print_menu() {
  printf("\nChoose your action:\n");
  printf("1. Print livers\n");        //
  printf("2. Add liver\n");           //
  printf("3. Find liver\n");          //
  printf("4. Save data to a file\n"); //
  printf("5. Undo\n");
  printf("6. Delete liver\n");        //
  printf("7. Change liver's info\n"); //
  printf("0. Exit\n");                //
}

void free_undo_list(UndoNode *head) {
  while (head != NULL) {
    UndoNode *temp = head;
    head = head->next;

    if (temp->prev_state != NULL) {
      free(temp->prev_state);
    }

    free(temp);
  }
}

///////

int main(int argc, char *argv[]) {
  if (argc != 2) {
    print_scs(INVALID_INPUT);
    return INVALID_INPUT;
  }

  Liver *head = NULL;
  Liver *prev_state = NULL;
  UndoNode *undo_head = (UndoNode *)malloc(sizeof(UndoNode));
  if (undo_head == NULL) {
    print_scs(NO_MEMORY);
    return NO_MEMORY;
  }
  undo_head->cnt = 0;
  undo_head->action = '-';

  int status;
  if ((status = load_data(argv[1], &head)) != OK) {
    print_scs(status);
    return status;
  }

  char filename[256];
  bool flag = true;
  int choice = -1, cnt_oper = 0, cnt_undo = 0;
  while (flag) {
    print_menu();
    printf("Enter your choice: ");
    printf("Here: %d\n", cnt_oper);

    if (scanf("%d", &choice) != 1) {
      choice = -1;
    }

    switch (choice) {
    case 1:
      if (head == NULL) {
        print_scs(EMPTY);
      } else {
        print_list(head, stdout);
      }
      break;
    case 2:
      prev_state = head;
      printf("Please, enter the liver info: ");
      if ((status = add_liver(&head, &prev_state, &undo_head)) != OK) {
        print_scs(status);
        prev_state = NULL;
      } else {
        cnt_oper++;
      }
      break;
    case 3:
      if (head == NULL) {
        print_scs(EMPTY);
      } else {
        printf("Please, enter paramteres of a liver: ");
        if ((status = find_liver(head)) < 0) {
          print_scs(status);
        } else {
          printf("%s\n", (status == 1) ? "Found." : "Not found.");
        }
      }
      break;
    case 4:
      printf("Please, enter filename: ");
      if (scanf("%255s", filename) != 1) {
        print_scs(INVALID_INPUT);
      } else {
        FILE *fptr = fopen(filename, "w");
        if (fptr == NULL) {
          print_scs(FILE_NOT_OPEN);
          break;
        }
        print_list(head, fptr);
        fclose(fptr);
      }
      break;
    case 5: // undo operations
      cnt_undo = cnt_oper / 2;
      if (cnt_undo == 0) {
        print_scs(ZERO_UNDO);
      } else {
        while (cnt_undo != 0) {
          if ((status = do_undo(&undo_head, &head)) != OK) {
            print_scs(status);
            break;
          } else {
            cnt_undo--;
          }
        }
        cnt_oper = 0;
      }
      break;
    case 6: // delete liver
      if (head == NULL) {
        print_scs(EMPTY);
      } else {
        if ((status = delete_liver(&head, &undo_head)) < 0) {
          print_scs(status);
        } else {
          cnt_oper++;
          printf("%s\n", (status == 1) ? "Deleted." : "Liver not found.");
        }
      }
      break;
    case 7:
      if (head == NULL) {
        print_scs(EMPTY);
      } else {
        printf("Please, enter liver's parameters: ");
        if ((status = change_liver(&head, &cnt_oper, &undo_head)) < 0) {
          print_scs(status);
        } else {
          printf("%s\n", (status == 1) ? "Changed." : "Liver not found.");
        }
      }
      break;
    case 0:
      flag = false;
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }

  if (prev_state != NULL) {
    free(prev_state);
  }

  while (head != NULL) {
    Liver *tmp = head;
    head = head->next;
    free(tmp);
  }

  free_undo_list(undo_head);

  return 0;
}

// поиск жителя с заданными параметрами
// изменение жителя
// выгрузка в файл с стдин
// отменить N/2 операций, N - колво операций с самого начала