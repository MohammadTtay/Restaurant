#include <iostream>

#include <cstring>

#include <conio.h>

using namespace std;

struct Database_UP
{
  char User[20];
  char Pass[20];
};

struct F_PR
{
  char Food_name[30];
  float Price;
};

void Edit(F_PR[], int &);
void Add(F_PR[], int &);
void Remove(F_PR[], int &);
void UP_File(Database_UP[], int);
void Foods_File(F_PR[], int);

int main()
{

  FILE *fptr, *ptr;
  int Count_c = 1, Objects_In_Menu = 6, Check_up = 0, i;

  Database_UP Costumers[500];

  //Costumers[0] is specially for admin

  strcpy(Costumers[0].User, "admin");
  /*Default Pass*/
  strcpy(Costumers[0].Pass, "12345678");

  F_PR List[200];
  F_PR Temp;

  //list[20] , Default list of available foods and their prices . Right now 6 objects are available
  //Default list
  strcpy(List[0].Food_name, "Chicken Biryani");
  strcpy(List[1].Food_name, "Chicken Palao");
  strcpy(List[2].Food_name, "Chicken Rice");
  strcpy(List[3].Food_name, "Chicken Burger");
  strcpy(List[4].Food_name, "Nawabi Pizza");
  strcpy(List[5].Food_name, "2.5 Litre Coke");
  List[0].Price = 2;
  List[1].Price = 1.5;
  List[2].Price = 2.5;
  List[3].Price = 1;
  List[4].Price = 4.5;
  List[5].Price = 1.75;

  fptr = fopen("Food List.txt", "r+");
  if (fptr == NULL)
  { //Save Data When User Start The App For First Time
    fptr = fopen("Food List.txt", "w");
    fprintf(fptr, "%d\n", Objects_In_Menu);
    for (int i = 0; i < Objects_In_Menu; i++)
    {
      fprintf(fptr, "%s\n", List[i].Food_name);
      fprintf(fptr, "%.2f\n", List[i].Price);
    }
    fclose(fptr);
  }
  else
  { //Load Data From 'Food List' File
    fscanf(fptr, "%d", &Objects_In_Menu);
    for (int i = 0; i < Objects_In_Menu; i++)
    {
      fscanf(fptr, " %[^\n]s", List[i].Food_name);
      fscanf(fptr, "%f", &List[i].Price);
    }
    fclose(fptr);
  }

  ptr = fopen("UP Database.txt", "r+");
  if (ptr != NULL)
  { //load Data From'UP Database' ( That Includes All Usernames & Passwords)
    fscanf(ptr, "%d", &Count_c);
    for (int i = 0; i < Count_c; i++)
    {
      fscanf(ptr, " %[^\n]s", Costumers[i].User);
      fscanf(ptr, " %[^\n]s", Costumers[i].Pass);
    }
  }
  fclose(ptr);

Startpage:

  int First_Menu, Second_Menu;
  char Password[20], Username[20];

  cout << "::[ Welcome To Restaurant Management System ]::\n\n"
       << "Menu:\n"
       << "<1> Signup\n"
       << "<2> Login\n\n"
       << "Please Enter A Number: ";
  cin >> First_Menu;

  /*---------------------------------------SignUp---------------------------------*/

  switch (First_Menu)
  {
  case 1:
  Signup:
    char Signup;
    system("cls");

    cout << "::[ Restaurant Management System ]::\n\n";
    cout << "Signup As A User Or Admin? (Enter 'u' Or 'a')\n";
    Signup = getch();
    if (Signup == 'u')
    {
      cout << "\nEnter Your Username: ";
      cin >> Costumers[Count_c].User;

    Check_User:
      for (i = 0; i < Count_c; i++)
      {
        while (strcmp(Costumers[i].User, Costumers[Count_c].User) == 0)
        {
          cout << "The Username Already Exists. Please Use A Different Username\n";
          cout << "-----------------------";
          cout << "\nEnter Your Username: ";
          cin >> Costumers[Count_c].User;
          goto Check_User;
        }
      }
      cout << "Enter Your Password: ";
      cin >> Costumers[Count_c].Pass;

      Count_c++;

      cout << "\nCongratulations! You Have Successfully Signed Up";
    }
    else if (Signup == 'a')
    {
      if (strcmp(Costumers[0].Pass, "12345678") == 0)
      {
        cout << "\nYour Username is 'admin'\nPlease Select A Password: ";
        cin >> Costumers[0].Pass;
        cout << "\nCongratulations! You Have Successfully Signed Up";
      }
      else
      {
        cout << "You Can't Change Password Of 'admin'! ";
      }
    }
    else
    {
      cout << "\nPlease Enter A Valid Digit";
    }

    UP_File(Costumers, Count_c); //Make Database File that includes Username And Passwords.

    cout << "\n\nPress Any Key to Continue...";
    getch();
    system("cls");
    goto Startpage;

    /*---------------------------------------Login---------------------------------*/

  case 2:
  Login_Page:

    cout << "\nEnter Your Username: ";
    cin >> Username;
    cout << "Enter Your Password: ";
    cin >> Password;

    for (i = 0; i <= Count_c; i++)
    {
      if (strcmp(Costumers[i].User, Username) == 0)
      { //Searching Username In Our list
        if (strcmp(Costumers[i].Pass, Password) == 0)
        {
          cout << "\nCongratulations You Have Successfully Logged in";
          cout << "\n\nPress Any Key to Continue...";
          getch();
          system("cls");
        }
        else
        {
          cout << "Password Is Incorrect . Please Try Again\n";
          cout << "-----------------------";
          goto Login_Page;
        }
        break;
      }
    }

    if (i == Count_c + 1)
    {
      cout << "Username Is Not Available . Please Sign Up First ";
      cout << "\n\nPress Any Key to Continue...";
      getch();
      system("cls");
      goto Startpage;
    }
    break;

  default:
    cout << "Please Enter A Valid Number";
    cout << "\n\nPress Any Key to Continue...";
    getch();
    system("cls");
    goto Startpage;
  }

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  if (strcmp("admin", Username) != 0)
  {
  Userpage:
    system("cls");
    cout << "::[ Restaurant Management System ]::\n\n"
         << "<1> See Menu:\n"
         << "<2> Logout\n\n"
         << "Please Enter A Number: ";
    cin >> Second_Menu;
    system("cls");
    cout << "::[ Restaurant Management System ]::\n\n";

    //user mode
    switch (Second_Menu)
    {

    case 1:
      for (int i = 0; i < Objects_In_Menu; i++)
      {
        cout << "(" << i + 1 << ")  " << List[i].Food_name << "-----------> $" << List[i].Price << "  only\n";
      }
      cout << "\n";
      break;
    case 2:
      goto Startpage;
      break;
    default:
      cout << "Please Enter A Valid Number";
      cout << "\n\nPress Any Key to Continue...";
      getch();
      goto Userpage;
    }
    int Ord_Num;
    cout << "Please Select The Order Number: ";
    cin >> Ord_Num;
    while (Ord_Num > Objects_In_Menu)
    {
      cout << "\nNumber Isn't Valid.Select A Valid Number\n";
      cout << "\nPlease Select The Order Number: ";
      cin >> Ord_Num;
    }
    int Num_Of_Deals;
    cout << "Please Enter The Number Of Deals: ";
    cin >> Num_Of_Deals;

    cout << "\n\nOrder: " << List[Ord_Num - 1].Food_name << "\n"
         << "Number Of Deals: " << Num_Of_Deals << "\nPrice Of Each Deal: $" << List[Ord_Num - 1].Price << "  Only\n";
    cout << "Total Price: $" << Num_Of_Deals * List[Ord_Num - 1].Price << "  Only";
    cout << "\n\n--------------------------------------------------";
    cout << "\n---------------Thank You For Coming---------------";
    cout << "\n--------------------------------------------------\n\n";
    cout << "\n\nPress Any Key to Continue...";
    getch();
    goto Userpage;
  }
  else
  { //admin mode
  Admin_Panel:
    system("cls");
    cout << "::[ Restaurant Management System ]::\n\n"
         << "<1> Edit Food Names & Their Prices\n"
         << "<2> Add A Food To Menu\n"
         << "<3> Remove A Food From Menu\n"
         << "<4> Show Menu\n"
         << "<5> Logout\n\n"
         << "Please Enter A Number: ";
    cin >> Second_Menu;
    system("cls");
    cout << "::[ Restaurant Management System ]::\n\n";

    cout << "[----------------------------Editing Panel----------------------------]\n\n\n";
    switch (Second_Menu)
    {
    case 1:
      Edit(List, Objects_In_Menu);
      cout << "\nThe Changes That You Requested Have Been Applied";
      Foods_File(List, Objects_In_Menu);
      cout << "\n\nPress Any Key to Continue...";
      getch();
      goto Admin_Panel;
      break;
    case 2:
      Add(List, Objects_In_Menu);
      cout << "\nThe Changes That You Requested Have Been Applied";
      Foods_File(List, Objects_In_Menu);
      cout << "\n\nPress Any Key to Continue...";
      getch();
      goto Admin_Panel;
      break;
    case 3:
      Remove(List, Objects_In_Menu);
      cout << "\nThe Changes That You Requested Have Been Applied";
      Foods_File(List, Objects_In_Menu);
      cout << "\n\nPress Any Key to Continue...";
      getch();
      goto Admin_Panel;
    case 4:
      for (int i = 0; i < Objects_In_Menu; i++)
      {
        cout << "(" << i + 1 << ")  " << List[i].Food_name << "-----------> $" << List[i].Price << "  only\n";
      }
      cout << "\n";
      cout << "\n\nPress Any Key to Go Back To Admin Panel ...";
      getch();
      goto Admin_Panel;
      break;
    case 5:
      system("cls");
      goto Startpage;
      break;
    default:
      cout << "\nNumber Isn't Valid.Select A Valid Number\n";
      cout << "\n\nPress Any Key to Continue...";
      getch();
      system("cls");
      goto Admin_Panel;
      break;
    }
  }
  system("pause");

  return 0;
}

void Edit(F_PR List[200], int &Objects_In_Menu)
{
  int Option;
  char yes_or_no, Yes = 'Y', yes = 'y', No = 'N', no = 'n', New_Food[30], New_Price;

  for (int i = 0; i < Objects_In_Menu; i++)
  {
    cout << "(" << i + 1 << ")  " << List[i].Food_name << "-----------> $" << List[i].Price << "\n";
  }
  cout << "\n\nWhich Item Do You Want To Change?";
  cout << "\nPlease Choose It's Number: ";
  cin >> Option;

  while (Option > Objects_In_Menu)
  {
    cout << "\nPlease Choose An Available Item: ";
    cin >> Option;
  }

  cout << "\nDo You Want to Change It's Name (Y/N)";
  yes_or_no = getch();

  if (yes_or_no == 'y' || yes_or_no == 'Y')
  {
    cout << "\nPlease Enter A New Food Name: ";
    scanf(" %[^\n]s", &New_Food);
    strcpy(List[Option - 1].Food_name, New_Food);
  }

  cout << "\nDo You Want to Change It's Price (Y/N)";
  yes_or_no = getch();
  if (yes_or_no == 'y' || yes_or_no == 'Y')
  {
    cout << "\nPlease Enter A New Price: ";
    cin >> List[Option - 1].Price;
  }
}

void Add(F_PR List[200], int &Objects_In_Menu)
{
  char New_Food[30], New_Price;
  cout << "\nPlease Enter A New Food Name: ";
  scanf(" %[^\n]s", &List[Objects_In_Menu].Food_name);
  cout << "\nPlease Enter It's Price: ";
  cin >> List[Objects_In_Menu].Price;
  Objects_In_Menu++;
}
void Remove(F_PR List[200], int &Objects_In_Menu)
{
  int Option;

  for (int i = 0; i < Objects_In_Menu; i++)
  {
    cout << "(" << i + 1 << ")  " << List[i].Food_name << "-----------> $" << List[i].Price << "\n";
  }
  cout << "\n\nWhich Item Do You Want To Remove From Menu?";
  cout << "\nPlease Choose It's Number: ";
  cin >> Option;
  for (int i = Option; i < Objects_In_Menu; i++)
  {
    strcpy(List[i - 1].Food_name, List[i].Food_name);
    List[i - 1].Price = List[i].Price;
  }

  Objects_In_Menu--;
}

void UP_File(Database_UP Costumers[500], int Count_c)
{
  FILE *fptr;
  fptr = fopen("UP Database.txt", "w");
  fprintf(fptr, "%d\n", Count_c);
  for (int i = 0; i < Count_c; i++)
  {
    fprintf(fptr, "%s\n", Costumers[i].User);
    fprintf(fptr, "%s\n", Costumers[i].Pass);
  }
  fclose(fptr);
}

void Foods_File(F_PR List[200], int Objects_In_Menu)
{
  FILE *fptr;
  fptr = fopen("Food List.txt", "w");
  fprintf(fptr, "%d\n", Objects_In_Menu);
  for (int i = 0; i < Objects_In_Menu; i++)
  {
    fprintf(fptr, "%s\n", List[i].Food_name);
    fprintf(fptr, "%.2f\n", List[i].Price);
  }
  fclose(fptr);
}
