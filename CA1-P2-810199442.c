#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INCORRECT 0
#define CORRECT 1
#define EMPTY 0
#define FULL 1
#define FALSE 0
#define TRUE 1
#define SIGNUP 1
#define LOGIN 2
#define EXIT 3
#define ACCOUNT1 1
#define ACCOUNT2 2
#define ACCOUNT3 3
#define MAX_NUMBER_FOR_PHONE_NUMBER 10000000000
#define MIN_NUMBER_FOR_PHONE_NUMBER 1000000000
#define MAX_NUMBER_FOR_PASSWORD 1000000
#define MIN_NUMBER_FOR_PASSWORD 0
#define THIRTY_SECONDS 30000
#define THREE_ATTEMPTS 3
int SpaceForAccount();
long long Signup();
long long Locker();
int Login();
void SecondMenu();
void Exit();
int CheckPhoneFormat(long long);
int PhoneNumberExist(long long);
int CheckPassword(long long);
int ReEnterPassword(long long, long long);
void AddUser(long long, long long);
int CheckLoginPhone(long long);
int CheckLoginPassword(long long);
void StartLocker();
void Logout();
char c;
clock_t time1, time2;
long long phone_number1 = EMPTY, phone_number2 = EMPTY, phone_number3 = EMPTY, password1 = EMPTY, password2 = EMPTY, password3 = EMPTY; /*Initializing our phone numbers and passwords*/
long long input_for_main_menu = EMPTY, input_for_second_menu = EMPTY, input_for_phone_number = EMPTY, input_for_password = EMPTY, true1 = TRUE, true2 = TRUE, account = EMPTY, lock = FALSE; /*Initializing our inputs*/

void main() /*Decription: Creates a new messenger with the options to signup, login and exit with more to come*/
{
	while (true1 == TRUE) /*Shows the main menu*/
	{
		printf("Welocome to UT messenger.\nPlease choose one of the following options:\n1: Signup\n2: Login\n3: Exit\n");
		scanf_s("%lld", &input_for_main_menu);
		while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
		system("cls"); /*Clears the screen*/
		if (input_for_main_menu == SIGNUP) /*Starts the process of creating new accounts.*/
		{
			if (SpaceForAccount() == FULL) /*If we've already reached 3 accounts, it will notify the user that they can no longer create a new account.*/
			{
				printf("There's no more room in the community!\n");
				continue;
			}
			Signup(); /*Starts signing up*/
		}
		if (input_for_main_menu == LOGIN)
		{
			if (Locker() == TRUE) /*If the locker is still activated, it prints out an error and goes to the main menu again. If not, it goes to the login page*/
			{
				continue;
			}
			Login();
			SecondMenu(); 
		}
		if (input_for_main_menu == EXIT) /*Exiting the program*/
		{
			Exit();
		}
		if (input_for_main_menu != SIGNUP && input_for_main_menu != LOGIN &&  input_for_main_menu != EXIT) /*Prints an error if the number inputted was not in the options*/
		{
			printf("Error: Unkown Number. Please try again.\n");
		}
		input_for_main_menu = EMPTY, input_for_second_menu = EMPTY, input_for_phone_number = EMPTY, input_for_password = EMPTY, true2 = TRUE, account = EMPTY; /*Re-itializing our inputs*/
	}
}
int SpaceForAccount()
{
	if (phone_number1 != EMPTY && phone_number2 != EMPTY && phone_number3 != EMPTY) 
	{
		return FULL;
	}
	else
	{
		return EMPTY;
	}
}
long long Signup()
{
	printf("Please enter your phone number:\n");
	scanf_s("%lld", &input_for_phone_number);
	while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
	system("cls"); /*Clears the screen*/
	while (CheckPhoneFormat(input_for_phone_number) == INCORRECT) /*Prints error when the entered phone number isn't 10 digits*/
	{
		printf("Error: Wrong phone number format. Please try again;\n");
		scanf_s("%lld", &input_for_phone_number);
		while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
		system("cls"); /*Clears the screen*/
	}
	if (PhoneNumberExist(input_for_phone_number) == TRUE) /*Prints error when the number entered already existed.*/
	{
		printf("Error: Phone number already exists. Please go to the login page.\n");
		input_for_phone_number = EMPTY; /*Removes the input number so it can go into the login loop if the user wants to login*/
		return EMPTY;
	}
	printf("Enter your password (only use numbers and at most use 6 digits)\n");
	scanf_s("%lld", &input_for_password);
	while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
	system("cls"); /*Clears the screen*/
	while (CheckPassword(input_for_password) == INCORRECT) /*Prints error when the entered password is more than 6 digits*/
	{
		printf("Error: Your password is incorrect. Please try again\n");
		scanf_s("%lld", &input_for_password);
		while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
		system("cls"); /*Clears the screen*/
	}
	AddUser(input_for_phone_number, input_for_password);
	printf("Your new account is created. You'll now be re-directed to the login page.\n");
	return input_for_main_menu = LOGIN; /*Goes to the login page and the second menu*/
}
long long Locker()
{
	if (lock == TRUE)
	{
		time2 = clock(); /*The current time*/
		if ((time2 - time1) >= THIRTY_SECONDS) /*Checks if 30 seconds have passed or not*/
		{
			lock = FALSE;
			return FALSE;
		}
		else
		{
			int time_left = 30 - ((time2 - time1) / CLOCKS_PER_SEC); /*Calculates the remaining time*/
			printf("Login is locked. Please try again after %d seconds.\n", time_left);
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}
int Login()
{
	int attempt = EMPTY;
	while (input_for_phone_number == EMPTY) /*Starts the login process*/
	{
		printf("Please enter your phone number:\n");
		scanf_s("%lld", &input_for_phone_number);
		while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
		system("cls"); /*Clears the screen*/
		if (CheckLoginPhone(input_for_phone_number) == INCORRECT)
		{
			printf("Error: Phone number doesn't exist.\n");
			input_for_phone_number = EMPTY; /*Removes input number*/
			true2 = FALSE; /*Does not go into the second menu.*/
			break; /*Goes to the main menu so they can either login with another account or create a new one.*/
		}
		else if (CheckLoginPhone(input_for_phone_number) == CORRECT)
		{
			printf("Enter your password:\n");
			scanf_s("%lld", &input_for_password);
			while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
			system("cls"); /*Clears the screen*/
			++attempt;
			while (CheckLoginPassword(input_for_password) == INCORRECT)
			{
				if (attempt == THREE_ATTEMPTS) /*Locking the Login Menu*/
				{
					StartLocker();
					return INCORRECT;
				}
				else
				{
					printf("Your password was incorrect. Please try again:\n");
					scanf_s("%lld", &input_for_password);
					while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
					system("cls"); /*Clears the screen*/
					++attempt;
				}
			}
			printf("You've successfully logged in!\n");
			return CORRECT;
		}
	}
	return INCORRECT;
}
void SecondMenu()
{
	while (true2)
	{
		printf("Please choose one of the following options:\n1. Send message\n2. Show messages\n3. Create channel\n4. Create group\n5. Log out\n");
		scanf_s("%lld", &input_for_second_menu);
		while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
		system("cls"); /*Clears the screen*/
		switch (input_for_second_menu) /*Creates a swtitch case for the options presented in the second menu*/
		{
			case 1:
			case 2:
			case 3:
			case 4:
			{
				printf("Error: Sorry this option is not currently available.\n"); /*Prints an error as no option other than logout currently exists.*/
				break;
			}
			case 5:
			{
				Logout();
				break;
			}
			default: /*Prints an error if the number inputted was not in the options*/
			{
				printf("Error: Unkown number. Please try again.\n");
				break;
			}
		}
	}
}
void Exit()
{
	printf("Hope to see you again!\n");
	true1 = FALSE; /*Goes out of the program*/
}
int CheckPhoneFormat(long long input_for_phone_number) /*Checks to see if the phone number is 10 digits*/
{
	if (MIN_NUMBER_FOR_PHONE_NUMBER <= input_for_phone_number && input_for_phone_number < MAX_NUMBER_FOR_PHONE_NUMBER)
	{
		return CORRECT;
	}
	else
	{
		return INCORRECT;
	}
}
int PhoneNumberExist(long long input_for_phone_number)
{
	if ((input_for_phone_number == phone_number1 && phone_number1 != EMPTY) || (input_for_phone_number == phone_number2 && phone_number2 != EMPTY) || (input_for_phone_number == phone_number3 && phone_number3 != EMPTY)) /*Checks to see if the phone number exists*/
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
int CheckPassword(long long input_for_password) /*Checks to see if the password is 6 digits or less*/
{
	if (MIN_NUMBER_FOR_PASSWORD <= input_for_password && MAX_NUMBER_FOR_PASSWORD > input_for_password)
	{
		long long input_for_re_entering_password;
		printf("Re-enter your password please:\n");
		scanf_s("%lld", &input_for_re_entering_password);
		while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
		system("cls"); /*Clears the screen*/
		if (ReEnterPassword(input_for_password, input_for_re_entering_password) == CORRECT)
		{
			return CORRECT;
		}
		else if (ReEnterPassword(input_for_password, input_for_re_entering_password) == INCORRECT)
		{
			return INCORRECT;
		}
	}
	else
	{
		return INCORRECT;
	}
	return INCORRECT;
}
int ReEnterPassword(long long input_for_password, long long input_for_re_entering_password)
{
	if (input_for_password == input_for_re_entering_password) /*Checks to see if we have re entered our password correctly*/
	{
		return CORRECT;
	}
	else
	{
		return INCORRECT;
	}
}
void AddUser(long long input_for_phone_number, long long input_for_password)
{
	if (phone_number1 == EMPTY) /*Adds the input number for phone number and password into the first account*/
	{
		phone_number1 = input_for_phone_number;
		password1 = input_for_password;
	}
	else if (phone_number2 == EMPTY) /*Adds the input number for phone number and password into the second account*/
	{
		phone_number2 = input_for_phone_number;
		password2 = input_for_password;
	}
	else if (phone_number3 == EMPTY) /*Adds the input number for phone number and password into the third account*/
	{
		phone_number3 = input_for_phone_number;
		password3 = input_for_password;
	}
}
int CheckLoginPhone(long long input_for_phone_number)
{
	if (phone_number1 == input_for_phone_number) /*Logging in with our first account*/
	{
		account = ACCOUNT1;
		return CORRECT;
	}
	if (phone_number2 == input_for_phone_number) /*Logging in with our second account*/
	{
		account = ACCOUNT2;
		return CORRECT;
	}
	if (phone_number3 == input_for_phone_number) /*Logging in with our third account*/
	{
		account = ACCOUNT3;
		return CORRECT;
	}
	else  
	{
		return INCORRECT;
	}
}
int CheckLoginPassword(long long input_for_password)
{
	if (account == ACCOUNT1 && input_for_password == password1) /*Logging in with our first account*/
	{
		return CORRECT;
	}
	else if (account == ACCOUNT2 && input_for_password == password2) /*Logging in with our second account*/
	{
		return CORRECT;
	}
	else if (account == ACCOUNT3 && input_for_password == password3) /*Logging in with our third account*/
	{
		return CORRECT;
	}
	else
	{
		return INCORRECT;
	}
}
void StartLocker()
{
	printf("Too many attempts. Login's locked for 30 seconds.\n");
	time1 = clock(); /*The start of locking time*/
	lock = TRUE;
	true2 = FALSE; /*Does not go into the second menu.*/
}
void Logout()
{
	printf("You've logged out.\n");
	true2 = FALSE; /*Gets out of the second menu loop*/
}