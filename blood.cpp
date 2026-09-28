#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

/*
========================================================
                 HEMOLINK
     BLOOD DONATION & EMERGENCY SUPPORT SYSTEM

              DATA STRUCTURE PROJECT

DATA STRUCTURES USED:

1. Linked List     - Donor Management
2. Queue           - Normal Blood Requests
3. Priority Queue  - Emergency Requests
4. Stack           - Donation History
5. Array           - Blood Stock
6. Linear Search   - Donor Search
7. Bubble Sort     - Donor Sorting

DATABASE NOT USED
ALL DATA IS STORED IN MEMORY
========================================================
*/


// =====================================================
// CONSTANT
// =====================================================

#define MAX 50


// =====================================================
// DONOR STRUCTURE - LINKED LIST
// =====================================================

struct Donor
{
    int id;
    char name[30];
    int age;
    char bloodGroup[5];
    char city[30];
    char phone[15];
    int available;

    Donor *next;
};

Donor *head = NULL;


// =====================================================
// NORMAL BLOOD REQUEST - QUEUE
// =====================================================

struct BloodRequest
{
    int requestId;
    char patientName[30];
    char hospital[40];
    char bloodGroup[5];
    int units;
    char contact[15];
};

BloodRequest requestQueue[MAX];

int front = -1;
int rear = -1;

int requestCounter = 1;


// =====================================================
// EMERGENCY REQUEST - PRIORITY QUEUE
// =====================================================

struct EmergencyRequest
{
    int id;
    char patientName[30];
    char bloodGroup[5];
    char hospital[40];
    int units;
    int priority;
};

EmergencyRequest emergencyQueue[MAX];

int emergencyCount = 0;

int emergencyCounter = 1;


// =====================================================
// DONATION HISTORY - STACK
// =====================================================

struct Donation
{
    int donationId;
    char donorName[30];
    char bloodGroup[5];
    int units;
};

Donation donationStack[MAX];

int top = -1;

int donationCounter = 1;


// =====================================================
// BLOOD STOCK - ARRAY
// =====================================================

char bloodGroups[8][5] =
{
    "A+",
    "A-",
    "B+",
    "B-",
    "AB+",
    "AB-",
    "O+",
    "O-"
};


int bloodStock[8] =
{
    10,
    5,
    12,
    4,
    6,
    3,
    15,
    5
};


// =====================================================
// FUNCTION DECLARATIONS
// =====================================================

// Donor Functions

void donorMenu();

void registerDonor();

void displayDonors();

void searchDonor();

void updateAvailability();

void deleteDonor();

void sortDonors();

int getDonorCount();


// Request Functions

void requestMenu();

void addBloodRequest();

void processBloodRequest();

void displayBloodRequests();


// Emergency Functions

void emergencyMenu();

void addEmergencyRequest();

void processEmergency();

void displayEmergencyRequests();


// Donation Functions

void donationMenu();

void recordDonation();

void undoLastDonation();

void displayDonationHistory();


// Blood Stock Functions

void stockMenu();

void displayBloodStock();

void addBloodStock();

void reduceBloodStock();

int getBloodIndex(char group[]);


// Statistics

void displayStatistics();


// Main Menu

void mainMenu();


// =====================================================
// DONOR MANAGEMENT
// LINKED LIST
// =====================================================


// -----------------------------------------------------
// REGISTER NEW DONOR
// INSERT AT END OF LINKED LIST
// -----------------------------------------------------

void registerDonor()
{
    Donor *newDonor;
    Donor *temp;

    newDonor = new Donor;

    clrscr();

    cout << "\n";
    cout << "==========================================";
    cout << "\n         DONOR REGISTRATION FORM";
    cout << "\n==========================================";

    cout << "\n\nEnter Donor ID: ";
    cin >> newDonor->id;

    cout << "Enter Donor Name: ";
    cin >> newDonor->name;

    cout << "Enter Age: ";
    cin >> newDonor->age;

    if(newDonor->age < 18 || newDonor->age > 65)
    {
        cout << "\nInvalid Age!";
        cout << "\nDonor must be between 18 and 65.";

        delete newDonor;

        getch();

        return;
    }

    cout << "Enter Blood Group: ";
    cin >> newDonor->bloodGroup;

    cout << "Enter City: ";
    cin >> newDonor->city;

    cout << "Enter Phone Number: ";
    cin >> newDonor->phone;

    cout << "\nAvailable for Donation?";
    cout << "\n1. Yes";
    cout << "\n0. No";

    cout << "\nEnter Choice: ";
    cin >> newDonor->available;


    newDonor->next = NULL;


    // First Node

    if(head == NULL)
    {
        head = newDonor;
    }


    // Insert At End

    else
    {
        temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newDonor;
    }


    cout << "\n\n==========================================";
    cout << "\nDonor Registered Successfully!";
    cout << "\n==========================================";

    getch();
}


// -----------------------------------------------------
// DISPLAY ALL DONORS
// TRAVERSAL OF LINKED LIST
// -----------------------------------------------------

void displayDonors()
{
    Donor *temp;

    clrscr();

    cout << "\n";
    cout << "==================================================";
    cout << "\n              REGISTERED DONORS";
    cout << "\n==================================================";

    if(head == NULL)
    {
        cout << "\n\nNo Donors Registered!";

        getch();

        return;
    }


    temp = head;


    while(temp != NULL)
    {
        cout << "\n\n--------------------------------------------";

        cout << "\nDonor ID       : " << temp->id;

        cout << "\nName           : " << temp->name;

        cout << "\nAge            : " << temp->age;

        cout << "\nBlood Group    : " << temp->bloodGroup;

        cout << "\nCity           : " << temp->city;

        cout << "\nPhone          : " << temp->phone;


        if(temp->available == 1)
        {
            cout << "\nStatus         : AVAILABLE";
        }

        else
        {
            cout << "\nStatus         : NOT AVAILABLE";
        }


        temp = temp->next;
    }


    cout << "\n\n--------------------------------------------";

    getch();
}


// -----------------------------------------------------
// SEARCH DONOR
// LINEAR SEARCH
// -----------------------------------------------------

void searchDonor()
{
    Donor *temp;

    char group[5];

    int found = 0;


    clrscr();

    cout << "\n";
    cout << "==========================================";
    cout << "\n           SEARCH BLOOD DONOR";
    cout << "\n==========================================";


    cout << "\n\nEnter Required Blood Group: ";

    cin >> group;


    temp = head;


    while(temp != NULL)
    {
        if(strcmp(temp->bloodGroup, group) == 0
        && temp->available == 1)
        {
            cout << "\n\n--------------------------------";

            cout << "\nName        : " << temp->name;

            cout << "\nAge         : " << temp->age;

            cout << "\nBlood Group : " << temp->bloodGroup;

            cout << "\nCity        : " << temp->city;

            cout << "\nPhone       : " << temp->phone;


            found = 1;
        }


        temp = temp->next;
    }


    if(found == 0)
    {
        cout << "\n\nNo Available Donor Found!";
    }


    getch();
}


// -----------------------------------------------------
// UPDATE DONOR AVAILABILITY
// -----------------------------------------------------

void updateAvailability()
{
    Donor *temp;

    int id;

    int found = 0;


    clrscr();


    cout << "\n";
    cout << "==========================================";
    cout << "\n       UPDATE DONOR AVAILABILITY";
    cout << "\n==========================================";


    cout << "\n\nEnter Donor ID: ";

    cin >> id;


    temp = head;


    while(temp != NULL)
    {
        if(temp->id == id)
        {
            found = 1;


            cout << "\n\nDonor: " << temp->name;


            cout << "\n\n1. Available";

            cout << "\n0. Not Available";


            cout << "\nEnter New Status: ";

            cin >> temp->available;


            cout << "\n\nAvailability Updated Successfully!";


            break;
        }


        temp = temp->next;
    }


    if(found == 0)
    {
        cout << "\nDonor Not Found!";
    }


    getch();
}


// -----------------------------------------------------
// DELETE DONOR
// LINKED LIST DELETION
// -----------------------------------------------------

void deleteDonor()
{
    Donor *temp;

    Donor *previous;

    int id;


    clrscr();


    cout << "\n";
    cout << "==========================================";
    cout << "\n             DELETE DONOR";
    cout << "\n==========================================";


    cout << "\n\nEnter Donor ID: ";

    cin >> id;


    temp = head;

    previous = NULL;


    while(temp != NULL && temp->id != id)
    {
        previous = temp;

        temp = temp->next;
    }


    if(temp == NULL)
    {
        cout << "\n\nDonor Not Found!";
    }


    else
    {
        // Delete First Node

        if(temp == head)
        {
            head = head->next;
        }


        // Delete Middle or Last Node

        else
        {
            previous->next = temp->next;
        }


        delete temp;


        cout << "\n\nDonor Deleted Successfully!";
    }


    getch();
}


// -----------------------------------------------------
// SORT DONORS BY ID
// BUBBLE SORT
// -----------------------------------------------------

void sortDonors()
{
    Donor *i;

    Donor *j;


    int tempId;

    int tempAge;

    int tempAvailable;


    char tempName[30];

    char tempBlood[5];

    char tempCity[30];

    char tempPhone[15];


    if(head == NULL)
    {
        cout << "\nNo Donors Available!";

        getch();

        return;
    }


    for(i = head; i != NULL; i = i->next)
    {
        for(j = i->next; j != NULL; j = j->next)
        {
            if(i->id > j->id)
            {

                // ID

                tempId = i->id;

                i->id = j->id;

                j->id = tempId;


                // Name

                strcpy(tempName, i->name);

                strcpy(i->name, j->name);

                strcpy(j->name, tempName);


                // Age

                tempAge = i->age;

                i->age = j->age;

                j->age = tempAge;


                // Blood Group

                strcpy(tempBlood, i->bloodGroup);

                strcpy(i->bloodGroup, j->bloodGroup);

                strcpy(j->bloodGroup, tempBlood);


                // City

                strcpy(tempCity, i->city);

                strcpy(i->city, j->city);

                strcpy(j->city, tempCity);


                // Phone

                strcpy(tempPhone, i->phone);

                strcpy(i->phone, j->phone);

                strcpy(j->phone, tempPhone);


                // Availability

                tempAvailable = i->available;

                i->available = j->available;

                j->available = tempAvailable;
            }
        }
    }


    cout << "\n\nDonors Sorted Successfully By ID!";


    getch();
}


// -----------------------------------------------------
// GET TOTAL DONORS
// -----------------------------------------------------

int getDonorCount()
{
    Donor *temp;

    int count = 0;


    temp = head;


    while(temp != NULL)
    {
        count++;

        temp = temp->next;
    }


    return count;
}


// =====================================================
// DONOR MENU
// =====================================================

void donorMenu()
{
    int choice;


    do
    {
        clrscr();


        cout << "\n";
        cout << "==========================================";
        cout << "\n           DONOR MANAGEMENT";
        cout << "\n==========================================";


        cout << "\n\n1. Register New Donor";

        cout << "\n2. View All Donors";

        cout << "\n3. Search Donor By Blood Group";

        cout << "\n4. Update Donor Availability";

        cout << "\n5. Delete Donor";

        cout << "\n6. Sort Donors By ID";

        cout << "\n0. Back To Main Menu";


        cout << "\n\nEnter Your Choice: ";


        cin >> choice;


        switch(choice)
        {
            case 1:
                registerDonor();
                break;


            case 2:
                displayDonors();
                break;


            case 3:
                searchDonor();
                break;


            case 4:
                updateAvailability();
                break;


            case 5:
                deleteDonor();
                break;


            case 6:
                sortDonors();
                break;


            case 0:
                break;


            default:

                cout << "\nInvalid Choice!";

                getch();
        }

    }
    while(choice != 0);
}


// =====================================================
// NORMAL BLOOD REQUEST
// QUEUE
// =====================================================


// -----------------------------------------------------
// ENQUEUE REQUEST
// -----------------------------------------------------

void addBloodRequest()
{
    clrscr();


    if(rear == MAX - 1)
    {
        cout << "\nRequest Queue Is Full!";

        getch();

        return;
    }


    if(front == -1)
    {
        front = 0;
    }


    rear++;


    requestQueue[rear].requestId = requestCounter;


    cout << "\n";
    cout << "==========================================";
    cout << "\n          NEW BLOOD REQUEST";
    cout << "\n==========================================";


    cout << "\n\nPatient Name: ";

    cin >> requestQueue[rear].patientName;


    cout << "Hospital Name: ";

    cin >> requestQueue[rear].hospital;


    cout << "Required Blood Group: ";

    cin >> requestQueue[rear].bloodGroup;


    cout << "Required Units: ";

    cin >> requestQueue[rear].units;


    cout << "Contact Number: ";

    cin >> requestQueue[rear].contact;


    requestCounter++;


    cout << "\n\nBlood Request Added Successfully!";

    cout << "\nRequest ID: " << requestQueue[rear].requestId;


    getch();
}


// -----------------------------------------------------
// DEQUEUE REQUEST
// -----------------------------------------------------

void processBloodRequest()
{
    clrscr();


    if(front == -1 || front > rear)
    {
        cout << "\nNo Pending Blood Requests!";

        getch();

        return;
    }


    cout << "\n";
    cout << "==========================================";
    cout << "\n          PROCESSING REQUEST";
    cout << "\n==========================================";


    cout << "\n\nRequest ID: "
         << requestQueue[front].requestId;


    cout << "\nPatient: "
         << requestQueue[front].patientName;


    cout << "\nBlood Group: "
         << requestQueue[front].bloodGroup;


    cout << "\nUnits: "
         << requestQueue[front].units;


    cout << "\n\nRequest Processed Successfully!";


    front++;


    getch();
}


// -----------------------------------------------------
// DISPLAY QUEUE
// -----------------------------------------------------

void displayBloodRequests()
{
    int i;


    clrscr();


    cout << "\n";
    cout << "==========================================";
    cout << "\n         PENDING BLOOD REQUESTS";
    cout << "\n==========================================";


    if(front == -1 || front > rear)
    {
        cout << "\n\nNo Pending Requests!";

        getch();

        return;
    }


    for(i = front; i <= rear; i++)
    {
        cout << "\n\n--------------------------------";

        cout << "\nRequest ID: "
             << requestQueue[i].requestId;


        cout << "\nPatient: "
             << requestQueue[i].patientName;


        cout << "\nHospital: "
             << requestQueue[i].hospital;


        cout << "\nBlood Group: "
             << requestQueue[i].bloodGroup;


        cout << "\nUnits: "
             << requestQueue[i].units;


        cout << "\nContact: "
             << requestQueue[i].contact;
    }


    getch();
}


// =====================================================
// REQUEST MENU
// =====================================================

void requestMenu()
{
    int choice;


    do
    {
        clrscr();


        cout << "\n";
        cout << "==========================================";
        cout << "\n        BLOOD REQUEST MANAGEMENT";
        cout << "\n==========================================";


        cout << "\n\n1. Add Blood Request";

        cout << "\n2. Process Next Request";

        cout << "\n3. View Pending Requests";

        cout << "\n0. Back To Main Menu";


        cout << "\n\nEnter Choice: ";


        cin >> choice;


        switch(choice)
        {
            case 1:
                addBloodRequest();
                break;


            case 2:
                processBloodRequest();
                break;


            case 3:
                displayBloodRequests();
                break;


            case 0:
                break;


            default:

                cout << "\nInvalid Choice!";

                getch();
        }

    }
    while(choice != 0);
}


// =====================================================
// EMERGENCY REQUEST
// PRIORITY QUEUE
// =====================================================


// -----------------------------------------------------
// ADD EMERGENCY REQUEST
// -----------------------------------------------------

void addEmergencyRequest()
{
    int position;


    clrscr();


    if(emergencyCount == MAX)
    {
        cout << "\nEmergency Queue Is Full!";

        getch();

        return;
    }


    EmergencyRequest newRequest;


    newRequest.id = emergencyCounter;


    cout << "\n";
    cout << "==========================================";
    cout << "\n        EMERGENCY BLOOD REQUEST";
    cout << "\n==========================================";


    cout << "\n\nPatient Name: ";

    cin >> newRequest.patientName;


    cout << "Hospital Name: ";

    cin >> newRequest.hospital;


    cout << "Blood Group Required: ";

    cin >> newRequest.bloodGroup;


    cout << "Required Units: ";

    cin >> newRequest.units;


    cout << "\nPriority Level";

    cout << "\n1. CRITICAL";

    cout << "\n2. HIGH";

    cout << "\n3. NORMAL";


    cout << "\nEnter Priority: ";

    cin >> newRequest.priority;


    emergencyCounter++;


    // Insert according to priority

    position = emergencyCount;


    while(position > 0 &&
          emergencyQueue[position - 1].priority > newRequest.priority)
    {
        emergencyQueue[position] =
        emergencyQueue[position - 1];

        position--;
    }


    emergencyQueue[position] = newRequest;


    emergencyCount++;


    cout << "\n\nEmergency Request Added Successfully!";


    getch();
}


// -----------------------------------------------------
// PROCESS HIGHEST PRIORITY
// -----------------------------------------------------

void processEmergency()
{
    int i;


    clrscr();


    if(emergencyCount == 0)
    {
        cout << "\nNo Emergency Requests!";

        getch();

        return;
    }


    cout << "\n";
    cout << "==========================================";
    cout << "\n       PROCESSING EMERGENCY CASE";
    cout << "\n==========================================";


    cout << "\n\nPatient: "
         << emergencyQueue[0].patientName;


    cout << "\nBlood Group: "
         << emergencyQueue[0].bloodGroup;


    cout << "\nHospital: "
         << emergencyQueue[0].hospital;


    cout << "\nUnits: "
         << emergencyQueue[0].units;


    cout << "\n\nHighest Priority Case Processed!";


    // Shift Remaining Requests

    for(i = 0; i < emergencyCount - 1; i++)
    {
        emergencyQueue[i] =
        emergencyQueue[i + 1];
    }


    emergencyCount--;


    getch();
}


// -----------------------------------------------------
// DISPLAY EMERGENCY REQUESTS
// -----------------------------------------------------

void displayEmergencyRequests()
{
    int i;


    clrscr();


    cout << "\n";
    cout << "==========================================";
    cout << "\n         EMERGENCY REQUEST LIST";
    cout << "\n==========================================";


    if(emergencyCount == 0)
    {
        cout << "\n\nNo Emergency Requests!";

        getch();

        return;
    }


    for(i = 0; i < emergencyCount; i++)
    {
        cout << "\n\n--------------------------------";

        cout << "\nPatient: "
             << emergencyQueue[i].patientName;


        cout << "\nBlood Group: "
             << emergencyQueue[i].bloodGroup;


        cout << "\nHospital: "
             << emergencyQueue[i].hospital;


        cout << "\nUnits: "
             << emergencyQueue[i].units;


        cout << "\nPriority: ";


        if(emergencyQueue[i].priority == 1)
            cout << "CRITICAL";


        else if(emergencyQueue[i].priority == 2)
            cout << "HIGH";


        else
            cout << "NORMAL";
    }


    getch();
}


// =====================================================
// EMERGENCY MENU
// =====================================================

void emergencyMenu()
{
    int choice;


    do
    {
        clrscr();


        cout << "\n";
        cout << "==========================================";
        cout << "\n        EMERGENCY MANAGEMENT";
        cout << "\n==========================================";


        cout << "\n\n1. Add Emergency Request";

        cout << "\n2. Process Highest Priority Case";

        cout << "\n3. View Emergency Requests";

        cout << "\n0. Back To Main Menu";


        cout << "\n\nEnter Choice: ";


        cin >> choice;


        switch(choice)
        {
            case 1:
                addEmergencyRequest();
                break;


            case 2:
                processEmergency();
                break;


            case 3:
                displayEmergencyRequests();
                break;


            case 0:
                break;


            default:

                cout << "\nInvalid Choice!";

                getch();
        }

    }
    while(choice != 0);
}


// =====================================================
// DONATION MANAGEMENT
// STACK
// =====================================================


// -----------------------------------------------------
// PUSH DONATION
// -----------------------------------------------------

void recordDonation()
{
    clrscr();


    if(top == MAX - 1)
    {
        cout << "\nDonation History Is Full!";

        getch();

        return;
    }


    top++;


    donationStack[top].donationId =
    donationCounter;


    cout << "\n";
    cout << "==========================================";
    cout << "\n           RECORD DONATION";
    cout << "\n==========================================";


    cout << "\n\nDonor Name: ";

    cin >> donationStack[top].donorName;


    cout << "Blood Group: ";

    cin >> donationStack[top].bloodGroup;


    cout << "Units Donated: ";

    cin >> donationStack[top].units;


    donationCounter++;


    // Add donated blood to stock

    int index =
    getBloodIndex(donationStack[top].bloodGroup);


    if(index != -1)
    {
        bloodStock[index] =
        bloodStock[index] +
        donationStack[top].units;
    }


    cout << "\n\nDonation Recorded Successfully!";

    cout << "\nBlood Stock Updated.";


    getch();
}


// -----------------------------------------------------
// POP DONATION
// -----------------------------------------------------

void undoLastDonation()
{
    int index;


    clrscr();


    if(top == -1)
    {
        cout << "\nNo Donation History Available!";

        getch();

        return;
    }


    cout << "\n";
    cout << "==========================================";
    cout << "\n          UNDO LAST DONATION";
    cout << "\n==========================================";


    cout << "\n\nLast Donation: ";

    cout << "\nDonor: "
         << donationStack[top].donorName;


    cout << "\nBlood Group: "
         << donationStack[top].bloodGroup;


    cout << "\nUnits: "
         << donationStack[top].units;


    // Reduce stock because donation is undone

    index =
    getBloodIndex(donationStack[top].bloodGroup);


    if(index != -1)
    {
        bloodStock[index] =
        bloodStock[index] -
        donationStack[top].units;
    }


    top--;


    cout << "\n\nLast Donation Removed Successfully!";


    getch();
}


// -----------------------------------------------------
// DISPLAY STACK
// -----------------------------------------------------

void displayDonationHistory()
{
    int i;


    clrscr();


    cout << "\n";
    cout << "==========================================";
    cout << "\n          DONATION HISTORY";
    cout << "\n==========================================";


    if(top == -1)
    {
        cout << "\n\nNo Donation Records!";

        getch();

        return;
    }


    // Top to Bottom

    for(i = top; i >= 0; i--)
    {
        cout << "\n\n--------------------------------";

        cout << "\nDonation ID: "
             << donationStack[i].donationId;


        cout << "\nDonor Name: "
             << donationStack[i].donorName;


        cout << "\nBlood Group: "
             << donationStack[i].bloodGroup;


        cout << "\nUnits: "
             << donationStack[i].units;
    }


    getch();
}


// =====================================================
// DONATION MENU
// =====================================================

void donationMenu()
{
    int choice;


    do
    {
        clrscr();


        cout << "\n";
        cout << "==========================================";
        cout << "\n          DONATION MANAGEMENT";
        cout << "\n==========================================";


        cout << "\n\n1. Record New Donation";

        cout << "\n2. Undo Last Donation";

        cout << "\n3. View Donation History";

        cout << "\n0. Back To Main Menu";


        cout << "\n\nEnter Choice: ";


        cin >> choice;


        switch(choice)
        {
            case 1:
                recordDonation();
                break;


            case 2:
                undoLastDonation();
                break;


            case 3:
                displayDonationHistory();
                break;


            case 0:
                break;


            default:

                cout << "\nInvalid Choice!";

                getch();
        }

    }
    while(choice != 0);
}


// =====================================================
// BLOOD STOCK MANAGEMENT
// ARRAY
// =====================================================


// -----------------------------------------------------
// FIND BLOOD GROUP INDEX
// -----------------------------------------------------

int getBloodIndex(char group[])
{
    int i;


    for(i = 0; i < 8; i++)
    {
        if(strcmp(bloodGroups[i], group) == 0)
        {
            return i;
        }
    }


    return -1;
}


// -----------------------------------------------------
// DISPLAY BLOOD STOCK
// -----------------------------------------------------

void displayBloodStock()
{
    int i;


    clrscr();


    cout << "\n";
    cout << "==========================================";
    cout << "\n             BLOOD STOCK";
    cout << "\n==========================================";


    cout << "\n\nBlood Group\tAvailable Units";

    cout << "\n--------------------------------";


    for(i = 0; i < 8; i++)
    {
        cout << "\n"
             << bloodGroups[i]
             << "\t\t"
             << bloodStock[i];
    }


    cout << "\n--------------------------------";


    getch();
}


// -----------------------------------------------------
// ADD BLOOD STOCK
// -----------------------------------------------------

void addBloodStock()
{
    char group[5];

    int units;

    int index;


    clrscr();


    cout << "\n";
    cout << "==========================================";
    cout << "\n           ADD BLOOD STOCK";
    cout << "\n==========================================";


    cout << "\n\nEnter Blood Group: ";

    cin >> group;


    index = getBloodIndex(group);


    if(index == -1)
    {
        cout << "\nInvalid Blood Group!";

        getch();

        return;
    }


    cout << "Enter Units To Add: ";

    cin >> units;


    bloodStock[index] =
    bloodStock[index] + units;


    cout << "\n\nBlood Stock Updated Successfully!";


    getch();
}


// -----------------------------------------------------
// REDUCE BLOOD STOCK
// -----------------------------------------------------

void reduceBloodStock()
{
    char group[5];

    int units;

    int index;


    clrscr();


    cout << "\n";
    cout << "==========================================";
    cout << "\n         ISSUE BLOOD FROM STOCK";
    cout << "\n==========================================";


    cout << "\n\nEnter Blood Group: ";

    cin >> group;


    index = getBloodIndex(group);


    if(index == -1)
    {
        cout << "\nInvalid Blood Group!";

        getch();

        return;
    }


    cout << "Enter Required Units: ";

    cin >> units;


    if(units > bloodStock[index])
    {
        cout << "\n\nInsufficient Blood Stock!";

        cout << "\nAvailable Units: "
             << bloodStock[index];
    }


    else
    {
        bloodStock[index] =
        bloodStock[index] - units;


        cout << "\n\nBlood Issued Successfully!";

        cout << "\nRemaining Units: "
             << bloodStock[index];
    }


    getch();
}


// =====================================================
// STOCK MENU
// =====================================================

void stockMenu()
{
    int choice;


    do
    {
        clrscr();


        cout << "\n";
        cout << "==========================================";
        cout << "\n        BLOOD STOCK MANAGEMENT";
        cout << "\n==========================================";


        cout << "\n\n1. View Blood Stock";

        cout << "\n2. Add Blood Stock";

        cout << "\n3. Issue Blood";

        cout << "\n0. Back To Main Menu";


        cout << "\n\nEnter Choice: ";


        cin >> choice;


        switch(choice)
        {
            case 1:
                displayBloodStock();
                break;


            case 2:
                addBloodStock();
                break;


            case 3:
                reduceBloodStock();
                break;


            case 0:
                break;


            default:

                cout << "\nInvalid Choice!";

                getch();
        }

    }
    while(choice != 0);
}


// =====================================================
// SYSTEM STATISTICS
// =====================================================

void displayStatistics()
{
    int availableDonors = 0;

    Donor *temp;


    temp = head;


    while(temp != NULL)
    {
        if(temp->available == 1)
        {
            availableDonors++;
        }


        temp = temp->next;
    }


    clrscr();


    cout << "\n";
    cout << "==========================================";
    cout << "\n          HEMOLINK STATISTICS";
    cout << "\n==========================================";


    cout << "\n\nTotal Registered Donors: "
         << getDonorCount();


    cout << "\nAvailable Donors: "
         << availableDonors;


    if(front == -1 || front > rear)
    {
        cout << "\nPending Blood Requests: 0";
    }

    else
    {
        cout << "\nPending Blood Requests: "
             << rear - front + 1;
    }


    cout << "\nEmergency Requests: "
         << emergencyCount;


    cout << "\nDonation Records: "
         << top + 1;


    cout << "\n\n==========================================";


    getch();
}


// =====================================================
// MAIN MENU
// =====================================================

void mainMenu()
{
    int choice;


    do
    {
        clrscr();


        cout << "\n\n";


        cout << "==================================================";

        cout << "\n";

        cout << "                 H E M O L I N K";

        cout << "\n";

        cout << "       BLOOD DONATION & EMERGENCY SUPPORT";

        cout << "\n";

        cout << "==================================================";


        cout << "\n\n";

        cout << "1. Donor Management";


        cout << "\n\n";

        cout << "2. Blood Request Management";


        cout << "\n\n";

        cout << "3. Emergency Blood Request";


        cout << "\n\n";

        cout << "4. Donation Management";


        cout << "\n\n";

        cout << "5. Blood Stock Management";


        cout << "\n\n";

        cout << "6. System Statistics";


        cout << "\n\n";

        cout << "0. Exit System";


        cout << "\n\n";

        cout << "--------------------------------------------------";


        cout << "\n";

        cout << "Enter Your Choice: ";


        cin >> choice;


        switch(choice)
        {
            case 1:

                donorMenu();

                break;


            case 2:

                requestMenu();

                break;


            case 3:

                emergencyMenu();

                break;


            case 4:

                donationMenu();

                break;


            case 5:

                stockMenu();

                break;


            case 6:

                displayStatistics();

                break;


            case 0:

                clrscr();

                cout << "\n\n";

                cout << "==========================================";

                cout << "\n";

                cout << "       THANK YOU FOR USING HEMOLINK";

                cout << "\n";

                cout << "       CONNECTING DONORS - SAVING LIVES";

                cout << "\n";

                cout << "==========================================";

                getch();

                break;

            default:

                cout << "\nInvalid Choice!";

                getch();
        }

    }
    while(choice != 0);
}


// =====================================================
// MAIN FUNCTION
// =====================================================

void main()
{
    clrscr();

    mainMenu();

    getch();
}
