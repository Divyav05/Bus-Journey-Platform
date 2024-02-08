#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>

// Define structures
struct node
{
    int busno, price, seats;
    char source[100], destination[100], date[100];
    struct node *next;
};

struct user_node
{
    int reg_no, age, num_seats;
    char name[100], date[100];
    long phoneno;
    int seat_numbers[30];
    struct user_node *next1;
};

// Global variables
int seats1, bus_no;
int num = 0;
int count = 0;
struct node *start = NULL;
struct user_node *start1 = NULL;
struct user_node *front = NULL;
struct user_node *rear = NULL;
int selected_seats[30] = {0}; 
time_t now;

// Function prototypes
struct node *create_ll(struct node *);
struct node *display(struct node *);
struct user_node *create(struct user_node *);
struct user_node *display1(struct user_node *);
void enqueue(struct user_node *);
struct user_node *dequeue();
void cancel();
void print_ticket();
void display_available_seats();
int is_valid_date_format(const char *date);
int contains_digits(const char *str);
int is_valid_bus_number(int bus_number, struct node *start);
int is_date_greater_or_equal(const char *date, int current_month, int current_day, int current_year);

int main()
{
    int choice, opt;
    printf("Press 1 if you are an admin. Press 2 if you are a user: ");
    scanf("%d", &choice);

    while (choice != 0)
    {
        if (choice == 1)
        {
            do
            {
                printf("\n **Admin Entry**");
                printf("\n 1.To enter details of bus");
                printf("\n 2.To display entered details of bus");
                printf("\n 3.To display passenger information of a bus ");
                printf("\n 4.To exit");
                printf("\n Enter your choice: ");
                scanf("%d", &opt);
                printf("\n");

                switch (opt)
                {
                case 1:
                    start = create_ll(start);
                    printf("\n-----------bus inserted----------\n");
                    break;
                case 2:
                    start = display(start);
                    break;
                case 3:
                    start1 = display1(start1);
                    break;
                case 4:
                    break;
                default:
                    break;
                }
            } while (opt != 4);
        }

        if (choice == 2)
        {
            int option;
            do
            {
                printf("\n **USER MENU** ");
                printf("\n 1.To reserve ticket ");
                printf("\n 2.To cancel ticket");
                printf("\n 3.To exit");
                printf("\n Enter your choice: ");
                scanf("%d", &option);
                printf("\n");

                switch (option)
                {
                case 1:
                    start1 = create(start1);
                    break;
                case 2:
                    cancel();
                    break;
                case 3:
                    break;
                default:
                    break;
                }
            } while (option != 3);
        }

        printf("Press 1 if you are an admin. Press 2 if you are a user. Else, press 0 to exit:  ");
        scanf("%d", &choice);
    }

    return 0;
}

struct node *create_ll(struct node *start)
{
    struct node *new_node, *ptr;
    int busno1, price1;
    char source1[100], destination1[100], date1[100];

    // Get current date
    now = time(NULL);
    struct tm *local = localtime(&now);
    int current_year = local->tm_year + 1900;
    int current_month = local->tm_mon + 1;
    int current_day = local->tm_mday;

    printf(" Enter the bus no. (or press 0 to exit): ");
    scanf("%d", &busno1);

    while (busno1 != 0)
    {
        // Validate bus number
        if (!is_valid_bus_number(busno1, start))
        {
            printf("Bus number already exists or is invalid. Please enter a different and valid bus number.\n");
            printf(" Enter the bus no. (or press 0 to exit): ");
            scanf("%d", &busno1);
            continue;
        }

        printf(" Enter the source: ");
        scanf("%s", source1);
        printf(" Enter the destination: ");
        scanf("%s", destination1);
        printf(" Enter the date of journey: mm/dd/yyyy: ");
        scanf("%s", date1);

        if (!is_valid_date_format(date1))
        {
            printf("Invalid date format. Please enter the date in mm/dd/yyyy format.\n");
            continue; 
        }

        if (!is_date_greater_or_equal(date1, current_month, current_day, current_year))
        {
            printf("Date should be greater than or equal to the current date.\n");
            continue; 
        }

        printf(" Enter the price of one ticket: ");
        scanf("%d", &price1);
        printf(" Enter the total number of seats: ");
        scanf("%d", &seats1);
        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->busno = busno1;
        strcpy(new_node->source, source1);
        strcpy(new_node->destination, destination1);
        strcpy(new_node->date, date1);
        new_node->price = price1;
        new_node->seats = seats1;
        if (start == NULL)
        {
            new_node->next = NULL;
            start = new_node;
        }
        else
        {
            ptr = start;
            while (ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = new_node;
            new_node->next = NULL;
        }
        printf("\n");
        printf(" Enter the bus no. (or press 0 to exit): ");
        scanf("%d", &busno1);
    }
    return start;
}

// Function to check if a bus number is valid (not already used)
int is_valid_bus_number(int bus_number, struct node *start) {
    struct node *ptr = start;
    while (ptr != NULL) {
        if (ptr->busno == bus_number) {
            return 0; 
        }
        ptr = ptr->next;
    }
    return 1; 
}

int is_date_greater_or_equal(const char *date, int current_month, int current_day, int current_year) {
    int mm, dd, yyyy;
    sscanf(date, "%d/%d/%d", &mm, &dd, &yyyy);

    if (yyyy > current_year)
        return 1;
    else if (yyyy == current_year && mm > current_month)
        return 1;
    else if (yyyy == current_year && mm == current_month && dd >= current_day)
        return 1;

    return 0; 
}

int is_valid_date_format(const char *date)
{
    int mm, dd, yyyy;
    if (sscanf(date, "%d/%d/%d", &mm, &dd, &yyyy) != 3)
        return 0; 
    if (mm < 1 || mm > 12 || dd < 1 || dd > 31 || yyyy < 1900 || yyyy > 2100)
        return 0; 

    return 1; 
}

int contains_digits(const char *str)
{
    while (*str)
    {
        if (isdigit(*str))
            return 1;
        str++;
    }
    return 0; 
}

struct node *display(struct node *start)
{
    struct node *ptr;
    ptr = start;
    while (ptr != NULL)
    {
        printf("\n BUS NO: %d", ptr->busno);
        printf("\n SOURCE: %s", ptr->source);
        printf("\n DESTINATION: %s", ptr->destination);
        printf("\n DATE: %s", ptr->date);
        printf("\n PRICE: %d", ptr->price);
        printf("\n TOTAL NUMBER OF SEATS: %d", ptr->seats);
        printf("\n");
        ptr = ptr->next;
    }
    return start;
}

struct user_node *create(struct user_node *start1)
{
    char src[100], dest[100], journey_date[11]; 
    int selected_seat;
    int reserve_more_tickets; 

    struct node *ptr;
    struct user_node *pptr, *new_node;
    new_node = (struct user_node *)malloc(sizeof(struct user_node));
    new_node->next1 = NULL;
    ptr = start;

    do
    {
        int no = 0;
        int valid_bus = 0; 

        printf(" Enter the source:");
        scanf("%s", src);
        printf(" Enter the destination:");
        scanf("%s", dest);

        printf(" Enter the date of journey (mm/dd/yyyy): "); 
        scanf("%s", journey_date);

        ptr = start; 
        while (ptr != NULL)
        {
            if (strcmp(ptr->source, src) == 0 && strcmp(ptr->destination, dest) == 0 && strcmp(ptr->date, journey_date) == 0)
            {
                no++;
                printf("\n BUS NO: %d", ptr->busno);
                printf("\n SOURCE: %s", ptr->source);
                printf("\n DESTINATION: %s", ptr->destination);
                printf("\n DATE: %s", ptr->date);
                printf("\n PRICE: %d", ptr->price);
                printf("\n TOTAL NUMBER OF SEATS: %d", ptr->seats);
                printf("\n");
            }
            ptr = ptr->next;
        }

        if (no == 0)
        {
            printf("\n No bus is available for the specified date, source, and destination....!!\n");
        }
        else
        {
            printf("\n %d bus(es) is available for the specified date, source, and destination....!!", no);

            do
            {
                printf("\n Enter the bus_no of the bus you wish to book: ");
                scanf("%d", &bus_no);

                ptr = start;
                while (ptr != NULL)
                {
                    if (ptr->busno == bus_no && strcmp(ptr->source, src) == 0 && strcmp(ptr->destination, dest) == 0 && strcmp(ptr->date, journey_date) == 0)
                    {
                        valid_bus = 1; 
                        break;
                    }
                    ptr = ptr->next;
                }

                if (!valid_bus)
                {
                    printf("Invalid bus number. Please select a valid bus number.\n");
                }
            } while (!valid_bus);

            display_available_seats();

            printf("\n Enter your phone number:");
            scanf("%ld", &new_node->phoneno);

            strcpy(new_node->date, journey_date); 

            printf("\n --------Enter your personal details------- ");
            printf("\n Enter your name:");
            scanf("%s", new_node->name);
            printf(" Enter your age:");
            scanf("%d", &new_node->age);

            printf("\n How many seats are you booking? ");
            scanf("%d", &new_node->num_seats);

            printf("\n Select seat number(s): ");
            for (int i = 0; i < new_node->num_seats; i++)
            {
                scanf("%d", &selected_seat);

                if (selected_seat < 1 || selected_seat > ptr->seats || selected_seats[selected_seat - 1] == 1)
                {
                    printf(" Invalid seat number or seat already booked. Please select again.\n");
                    i--; 
                }
                else
                {
                    new_node->seat_numbers[i] = selected_seat;
                    selected_seats[selected_seat - 1] = 1; 
                }
            }

            if (start1 == NULL)
            {
                new_node->reg_no = 1;
                start1 = new_node;
                num++;
                printf("\n Booking Successful...!!!\n Your reg no. is %d \n\n", num);
                print_ticket();
            }
            else
            {
                pptr = start1;
                while (pptr->next1 != NULL)
                    pptr = pptr->next1;
                if (num < seats1)
                {
                    num++;
                    new_node->reg_no = num;
                    pptr->next1 = new_node;
                    printf("\n Booking Successful...!!!\nYour reg no. is %d \n\n", num);
                    print_ticket();
                }
                else
                {
                    enqueue(new_node);
                    printf("\n Booking is full....!!!\nYou are added to Waiting List no is %d \n\n", count);
                }
            }

            printf("\n Do you want to reserve another ticket? (1 for Yes / 0 for No): ");
            scanf("%d", &reserve_more_tickets);
        }

    } while (reserve_more_tickets == 1);

    return start1;
}

int reserve_another_ticket()
{
    int choice;
    printf("\n Do you want to reserve another ticket? (1 for Yes / 0 for No): ");
    scanf("%d", &choice);
    return choice == 1;
}


void display_available_seats()
{
    printf("\n Available seats: ");
    for (int i = 1; i <= seats1; i++)
    {
        if (selected_seats[i - 1] == 0)
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void enqueue(struct user_node *new_node)
{
    if (rear == NULL)
    {
        rear = new_node;
        rear->next1 = NULL;
        front = rear;
    }
    else
    {
        struct user_node *ptr;
        ptr = new_node;
        rear->next1 = ptr;
        ptr->next1 = NULL;
        rear = new_node;
    }
    count++;
}

struct user_node *dequeue()
{
    if (front == NULL)
    {
        printf("\n Waiting list is empty...");
        return NULL;
    }
    else
    {
        count--;
        struct user_node *temp;
        temp = front;
        front = front->next1;
        temp->next1 = NULL;
        return temp;
    }
}

void cancel()
{
    int reg;
    printf("\n Enter the reg no to be canceled: ");
    scanf("%d", &reg);

    if (reg > num)
    {
        printf(" INVALID NO....!!");
    }
    else
    {
        struct user_node *ptr, *preptr, *new_node;
        ptr = start1;

        if (start1 == NULL)
            printf(" INVALID NO....!!");
        if (ptr->next1 == NULL && ptr->reg_no == reg)
        {
            start1 = NULL;
            num--;
            free(ptr);
            printf(" Reservation canceled Successfully...!!");
        }
        else
        {
            while (ptr->next1 != NULL && ptr->reg_no != reg)
            {
                preptr = ptr;
                ptr = ptr->next1;
            }
            if (ptr == NULL && ptr->reg_no != reg)
                printf(" INVALID NO....!!");
            else
                preptr->next1 = ptr->next1;
            free(ptr);
            new_node = dequeue();
            while (preptr->next1 != NULL)
                preptr = preptr->next1;
            preptr->next1 = new_node;
            num--;
            printf(" Reservation canceled Successfully...!!");
        }
    }
}

struct user_node *display1(struct user_node *start)
{
    struct user_node *ptr;
    ptr = start1;
    printf("\n bus no %d passenger details: ", bus_no);
    while (ptr != NULL)
    {
        printf("\n Registration no: %d", ptr->reg_no);
        printf("\n Name: %s", ptr->name);
        printf("\n Age: %d", ptr->age);
        printf("\n Seat Numbers: ");
        for (int i = 0; i < ptr->num_seats; i++)
        {
            printf("%d ", ptr->seat_numbers[i]);
        }
        printf("\n");
        ptr = ptr->next1;
    }
    return start1;
}

void print_ticket()
{
    struct node *ptr;
    struct user_node *user_ptr;
    ptr = start;

    while (ptr != NULL)
    {
        if (ptr->busno == bus_no)
        {
            printf("\n ** YOUR TICKET IS ***");
            printf("\n -------------------------------------------");
            printf("\n| BUS NO: %d |", ptr->busno);
            printf("\n| SOURCE: %s |", ptr->source);
            printf("\n| DESTINATION: %s |", ptr->destination);
            printf("\n| DATE: %s |", ptr->date);
            printf("\n| PRICE: %d |", ptr->price);
            printf("\n| AVAILABLE SEATS: ");
            display_available_seats();

            user_ptr = start1;
            while (user_ptr != NULL && user_ptr->reg_no != num)
            {
                user_ptr = user_ptr->next1;
            }

            if (user_ptr != NULL)
            {
                printf("\n| CUSTOMER NAME: %s |", user_ptr->name);
                printf("\n| PHONE NUMBER: %ld |", user_ptr->phoneno);
                printf("\n| SEAT NUMBERS: ");
                for (int i = 0; i < user_ptr->num_seats; i++)
                {
                    printf("%d ", user_ptr->seat_numbers[i]);
                }
                printf("|");
                printf("\n| TOTAL PRICE: %d |", user_ptr->num_seats * ptr->price);
            }

            printf("\n-------------------------------------------");
            printf("\n Thank you for choosing our service!\n");
            printf(" Do you want to reserve another ticket? (1 for Yes / 0 for No): ");
            int reserveAnother;
            scanf("%d", &reserveAnother);
            if (reserveAnother == 0) {
                exit(0); 
            }
        }
    }
}
