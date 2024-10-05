#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INCORRECT 0
#define CORRECT 1
#define EMPTY 0
#define FULL 1
#define FALSE 0
#define TRUE 1
#define SPACE 1
#define SAME_STRING 0
#define FIRST_ELEMENT 0
#define SIGNUP 1
#define LOGIN 2
#define EXIT 3
#define EMPTY_ACCOUNT -1
#define PHONE_NUMBER_NUMBER_DIGITS 11
#define MIN_PASSWORD_CHARACTERS 6
#define INFORMATION_FILE_ADDRESS "information.txt"
typedef struct user_info user;
typedef struct message_info message;
struct user_info
{
	char* username;
	char* phone_number;
	char* password;
	struct tm *date_and_time;
	user *next;
};
struct message_info
{
	char* message;
	char* sender_account;
	char* reciever_account;
	struct tm *date_and_time;
	message *next;
};

int Signup (int*, int*, int*);
int Login(int*, int*);
void SecondMenu( int*);
void Exit(int*);
int CheckPhoneFormat();
int PhoneNumberExist();
int CheckUsername();
int UsernameExist();
int CheckPassword();
void AddUser(int*);
int CheckLoginPhone(int*);
int CheckLoginUsername(int*);
int CheckLoginPassword(int*);
int SendMessage(int*);
void ShowMessages(int*);
int CheckOtherUsername( int *);
int CheckMessageFormat();
void AddMessage(int*, int*); 
void ShowRecievedMessages( int*); 
void ShowSentMessages( int*); 
int PrintMessages(int*, int*);
void GetOut(int*);
void Logout(int*);
void CreateFile();
int ReadFile();

int main() /*Decription: Creates a new messenger with the options to signup, login and exit with the ability to send messages in the second menu*/
{
	FILE *information;
	user user_list;
	message message_list;
	int true_main_menu = TRUE, lock = FALSE;
	if ((information = fopen(INFORMATION_FILE_ADDRESS, "r")) != EMPTY)
	{
		fclose(information);
		ReadFile(phone_number, username, password, messages);
	}
	printf("Welcome to UT Messenger!\nPlease enter your command\n***********\n");
	while (true_main_menu == TRUE) /*Shows the main menu*/
	{
		char *command_line = malloc(sizeof(char)); /*Re-itializing our inputs*/
		char *command;
		int true_second_menu = TRUE, true_login = TRUE, our_account = EMPTY_ACCOUNT, element = EMPTY;; /*Re-itializing our inputs*/
		while (TRUE) /*Command line*/
		{
			command_line[element] = getchar();
			if (command_line[element] == '\n')
			{
				command_line[element] = EMPTY;
				CheckCommand(command_line,command)
				break;
			}
			element++;
			command_line = realloc(command_line, (element + 1) * sizeof(char));
		}
		if (input_for_main_menu == SIGNUP)
		{
			if (SpaceForAccount(phone_number) == FULL) /*Gives the function our accounts phone number information so it can see if we're full or not*/
			{
				printf("There's no more room in the community!\n");
				continue;
			}
			Signup(phone_number, username, password, &true_login, &input_for_main_menu, &our_account); /*Starts signing up and gives the signup function the information of our current acounts so we can add more users and also the address of the login true and input for main menu variabe so we can go straight to the second menu once signup is complete*/
		}
		if (input_for_main_menu == LOGIN)
		{
			if (Locker(&lock, &time_start, &time_later) == TRUE) /*If the locker is still activated, it prints out an error and goes to the main menu again. If not, it goes to the login page*/
			{
				continue;
			}
			if (true_login == TRUE)
			{
				Login(phone_number, username, password, &true_second_menu, &our_account, &lock, &time_start); /*Starts the login process and gives the login function the information of our current acounts so we can login correctly and also the address of the true second menu variable to determine whether or not we should go into the second menu. We'll also give it the address of the time start variable and lock so we can lock the login page if we attepmted to enter our password too many times*/
			}
			if (true_second_menu == TRUE)
			{
				SecondMenu(username, messages, &our_account); /*Gives the address of the account so we can see which account we're in and the usernames so we can send and recieve messages properly*/
			}
		}
		if (input_for_main_menu == EXIT)
		{
			Exit(&true_main_menu); /*Exiting the program*/
		}
		if (input_for_main_menu != SIGNUP && input_for_main_menu != LOGIN &&  input_for_main_menu != EXIT)
		{
			printf("Error: Unkown Number. Please try again.\n");
		}
	}
	CreateFile(phone_number, username, password, messages);
}
int Signup(int *true_login, int *input_for_main_menu, int *our_account)
{
	char input_for_phone_number[PHONE_NUMBER_NUMBER_DIGITS + 2] = { 0 }, input_for_password[MAX_PASSWORD_CHARACTERS + 2] = { 0 }, input_for_username[MAX_USERNAME_CHARACTERS + 2] = { 0 }; /*In addition to the +1 for ending the array, the reason we have another +1 is that we can make sure that the user won't enter a number that has more than 11 digits or a password or a username that has more than 20 characters. The reason for this is that if a bigger string than the one desired is entered, then we'll the length will be bigger and thus we can print an error*/
	printf("Please enter your phone number:\n");
	scanf_s("%12s", input_for_phone_number, PHONE_NUMBER_NUMBER_DIGITS + 2);
	fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
	system("cls"); /*Clears the screen*/
	while (CheckPhoneFormat(input_for_phone_number) == INCORRECT)
	{
		printf("Error! Wrong phone number format. Please try again:\n");
		scanf_s("%12s", input_for_phone_number, PHONE_NUMBER_NUMBER_DIGITS + 2);
		fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
		system("cls"); /*Clears the screen*/
	}
	if (PhoneNumberExist(input_for_phone_number, phone_number) == TRUE) /*Gives the information of our current phone numbers in the accounts and the current input*/
	{
		printf("Error: Phone number already exists. Please go to the login page.\n");
		return INCORRECT;
	}
	printf("Please enter your username (it should be at least 6 characters and at most 20 characters):\n");
	scanf_s("%21s", input_for_username, MAX_USERNAME_CHARACTERS + 2);
	fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
	system("cls"); /*Clears the screen*/
	while (CheckUsername(input_for_username) == INCORRECT)
	{
		printf("Error: Your username is incorrect. Please try again\n");
		scanf_s("%21s", input_for_username, MAX_USERNAME_CHARACTERS + 2);
		fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
		system("cls"); /*Clears the screen*/
	}
	if (UsernameExist(input_for_username, username) == TRUE) /*Gives the information of our current usernames in the accounts and the current input*/
	{
		printf("Error: Username already exists. Please go to the login page.\n");
		return INCORRECT;
	}
	printf("Please enter your password (it should be at least 6 characters and at most 20 characters):\n");
	scanf_s("%21s", input_for_password, MAX_PASSWORD_CHARACTERS + 2);
	fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
	system("cls"); /*Clears the screen*/
	while (CheckPassword(input_for_password) == INCORRECT)
	{
		printf("Error: Your password is incorrect. Please try again\n");
		scanf_s("%21s", input_for_password, MAX_PASSWORD_CHARACTERS + 2);
		fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
		system("cls"); /*Clears the screen*/
	}
	AddUser(input_for_phone_number, input_for_username, input_for_password, phone_number, username, password, our_account);
	printf("Your new account is created. You'll now be re-directed to the login page.\n");
	*input_for_main_menu = LOGIN;
	*true_login = FALSE; /*Does not go into the login page and goes straight to the second menu*/
	return CORRECT;
}
int Login(int *true_second_menu, int *our_account)
{
	int attempt = EMPTY;
	char input_for_phone_number[PHONE_NUMBER_NUMBER_DIGITS + 2] = { 0 }, input_for_password[MAX_PASSWORD_CHARACTERS + 2] = { 0 }, input_for_username[MAX_USERNAME_CHARACTERS + 2] = { 0 }; /*In addition to the +1 for ending the array, the reason we have another +1 is that we can make sure that the user won't enter a number that has more than 11 digits or a password or a username that has more than 20 characters. The reason for this is that if a bigger string than the one desired is entered, then we'll the length will be bigger and thus we can print an error*/
	printf("Please enter your phone number:\n");
	scanf_s("%12s", input_for_phone_number, PHONE_NUMBER_NUMBER_DIGITS + 2);
	fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
	system("cls"); /*Clears the screen*/
	if (CheckLoginPhone(input_for_phone_number, phone_number, our_account) == INCORRECT)
	{
		printf("Error: Phone number doesn't exist.\n");
		*true_second_menu = FALSE; /*Does not go into the second menu.*/
		return INCORRECT; /*Goes to the main menu so they can either login with another account or create a new one.*/
	}
	printf("Please enter your username:\n");
	scanf_s("%21s", input_for_username, MAX_USERNAME_CHARACTERS + 2);
	fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
	system("cls"); /*Clears the screen*/
	if (CheckLoginUsername(input_for_username, username, our_account) == INCORRECT)
	{
		printf("Error: Username doesn't exist or wrong username entered.\n");
		*true_second_menu = FALSE; /*Does not go into the second menu.*/
		return INCORRECT; /*Goes to the main menu so they can either login with another account or create a new one.*/
	}
	printf("Please enter your password:\n");
	scanf_s("%21s", input_for_password, MAX_PASSWORD_CHARACTERS + 2);
	fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
	system("cls"); /*Clears the screen*/
	++attempt; /*coutning the number of attempts for entering the password*/
	while (CheckLoginPassword(input_for_password, password, our_account) == INCORRECT)
	{
		if (attempt == THREE_ATTEMPTS) /*Locking the Login Menu*/
		{
			printf("Too many attempts. Login's locked for 30 seconds.\n");
			StartLocker(time_start, lock, true_second_menu);
			return INCORRECT;
		}
		else
		{
			printf("Your password was incorrect. Please try again:\n");
			scanf_s("%21s", input_for_password, MAX_PASSWORD_CHARACTERS + 2);
			fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
			system("cls"); /*Clears the screen*/
			++attempt; /*coutning the number of attempts for entering the password*/
		}
	}
	printf("You've successfully logged in!\n");
	return CORRECT;
}
void SecondMenu( int *our_account)
{
	int true_second_menu = TRUE, input_for_second_menu = EMPTY;
	char c;
	while (true_second_menu)
	{
		printf("Please choose one of the following options:\n1. Send message\n2. Show messages\n3. Create channel\n4. Create group\n5. Log out\n");
		scanf_s("%d", &input_for_second_menu);
		while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
		system("cls"); /*Clears the screen*/
		switch (input_for_second_menu) /*Creates a swtitch case for the options presented in the second menu*/
		{
		case 1:
		{
			SendMessage(username, message, our_account);
			break;
		}
		case 2:
		{
			ShowMessages(username, message, our_account);
			break;
		}
		case 3:
		case 4:
		{
			printf("Error: Sorry this option is not currently available.\n"); /*Prints an error as these two options don't currently exist.*/
			break;
		}
		case 5:
		{
			Logout(&true_second_menu);
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
void Exit(int *true_main_menu)
{
	printf("Hope to see you again!\n");
	*true_main_menu = FALSE; /*Goes out of the program*/
}
int CheckPhoneFormat()
{
	if (strlen(input_for_phone_number) == PHONE_NUMBER_NUMBER_DIGITS && input_for_phone_number[FIRST_ELEMENT] == '0') /*Checks to see if the phone number is 11 digits and if it starts with 0. If not, it'll return incorrect*/
	{
		for (int i = FIRST_ELEMENT; i < PHONE_NUMBER_NUMBER_DIGITS; i++) /*Checks to see if all of the elements in the array are numbers*/
		{
			if (input_for_phone_number[i] > '9' || input_for_phone_number[i] < '0')
			{
				return INCORRECT;
			}
		}
	}
	else
	{
		return INCORRECT;
	}
	return CORRECT;
}
int PhoneNumberExist() /*Checks to see if the phone number exists*/
{
	if (strcmp(input_for_phone_number, phone_number[FIRST_ACCOUNT]) == SAME_ING || strcmp(input_for_phone_number, phone_number[SECOND_ACCOUNT]) == SAME_STRING || strcmp(input_for_phone_number, phone_number[THIRD_ACCOUNT]) == SAME_STRING || strcmp(input_for_phone_number, phone_number[FOURTH_ACCOUNT]) == SAME_STRING)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
int CheckUsername()
{
	if (strlen(input_for_username) <= MAX_USERNAME_CHARACTERS && strlen(input_for_username) >= MIN_USERNAME_CHARACTERS) /*Checks to see if the array is has more than 6 characters and less than 20 characters*/
	{
		return CORRECT;
	}
	else
	{
		return INCORRECT;
	}
}
int UsernameExist()  /*Checks to see if the username exists*/
{
	if (strcmp(input_for_username, username[FIRST_ACCOUNT]) == SAME_STRING || strcmp(input_for_username, username[SECOND_ACCOUNT]) == SAME_STRING || strcmp(input_for_username, username[THIRD_ACCOUNT]) == SAME_STRING || strcmp(input_for_username, username[FOURTH_ACCOUNT]) == SAME_STRING)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
int CheckPassword()
{
	if (strlen(input_for_password) <= MAX_PASSWORD_CHARACTERS && strlen(input_for_password) >= MIN_PASSWORD_CHARACTERS) /*Checks to see if the array is has more than 6 characters and less than 20 characters*/
	{
		char input_for_re_entering_password[MAX_PASSWORD_CHARACTERS + 2]; /*In addition to the +1 for ending the array, the reason we have another +1 is that we can make sure that the user won't enter a number that has more than 11 digits or a password that has more than 20 characters. The reason for this is that if a bigger string than the one desired is entered, then we'll the length will be bigger and thus we can print an error*/
		printf("Re-enter your password please:\n");
		scanf_s("%21s", input_for_re_entering_password, MAX_PASSWORD_CHARACTERS + 2);
		fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
		system("cls"); /*Clears the screen*/
	}
	else
	{
		return INCORRECT;
	}
}
void AddUser(int *our_account)
{
	if (*phone_number[FIRST_ACCOUNT] == EMPTY) /*Adds the information given by the user into the first account*/
	{
		strcpy_s(phone_number[FIRST_ACCOUNT], PHONE_NUMBER_NUMBER_DIGITS + 1, input_for_phone_number);
		strcpy_s(username[FIRST_ACCOUNT], MAX_USERNAME_CHARACTERS + 1, input_for_username);
		strcpy_s(password[FIRST_ACCOUNT], MAX_PASSWORD_CHARACTERS + 1, input_for_password);
		*our_account = FIRST_ACCOUNT;
	}
	else if (*phone_number[SECOND_ACCOUNT] == EMPTY) /*Adds the information given by the user into the second account*/
	{
		strcpy_s(phone_number[SECOND_ACCOUNT], PHONE_NUMBER_NUMBER_DIGITS + 1, input_for_phone_number);
		strcpy_s(username[SECOND_ACCOUNT], MAX_USERNAME_CHARACTERS + 1, input_for_username);
		strcpy_s(password[SECOND_ACCOUNT], MAX_PASSWORD_CHARACTERS + 1, input_for_password);
		*our_account = SECOND_ACCOUNT;
	}
	else if (*phone_number[THIRD_ACCOUNT] == EMPTY) /*Adds the information given by the user into the third account*/
	{
		strcpy_s(phone_number[THIRD_ACCOUNT], PHONE_NUMBER_NUMBER_DIGITS + 1, input_for_phone_number);
		strcpy_s(username[THIRD_ACCOUNT], MAX_USERNAME_CHARACTERS + 1, input_for_username);
		strcpy_s(password[THIRD_ACCOUNT], MAX_PASSWORD_CHARACTERS + 1, input_for_password);
		*our_account = THIRD_ACCOUNT;
	}
	else if (*phone_number[FOURTH_ACCOUNT] == EMPTY) /*Adds the information given by the user into the fourth account*/
	{
		strcpy_s(phone_number[FOURTH_ACCOUNT], PHONE_NUMBER_NUMBER_DIGITS + 1, input_for_phone_number);
		strcpy_s(username[FOURTH_ACCOUNT], MAX_USERNAME_CHARACTERS + 1, input_for_username);
		strcpy_s(password[FOURTH_ACCOUNT], MAX_PASSWORD_CHARACTERS + 1, input_for_password);
		*our_account = FOURTH_ACCOUNT;
	}
}
int CheckLoginPhone(int *our_account)
{
	if (strcmp(input_for_phone_number, phone_number[FIRST_ACCOUNT]) == SAME_STRING) /*Logging in with our first account*/
	{
		*our_account = FIRST_ACCOUNT;
	}
	else if (strcmp(input_for_phone_number, phone_number[SECOND_ACCOUNT]) == SAME_STRING) /*Logging in with our second account*/
	{
		*our_account = SECOND_ACCOUNT;
	}
	else if (strcmp(input_for_phone_number, phone_number[THIRD_ACCOUNT]) == SAME_STRING) /*Logging in with our third account*/
	{
		*our_account = THIRD_ACCOUNT;
	}
	else if (strcmp(input_for_phone_number, phone_number[FOURTH_ACCOUNT]) == SAME_STRING) /*Logging in with our fourth account*/
	{
		*our_account = FOURTH_ACCOUNT;
	}
	else
	{
		return INCORRECT;
	}
	return CORRECT;
}
int CheckLoginUsername(int *our_account)
{
	if (*our_account == FIRST_ACCOUNT && strcmp(input_for_username, username[FIRST_ACCOUNT]) == SAME_STRING) /*Logging in with our first account*/
	{
		return CORRECT;
	}
	else if (*our_account == SECOND_ACCOUNT && strcmp(input_for_username, username[SECOND_ACCOUNT]) == SAME_STRING) /*Logging in with our second account*/
	{
		return CORRECT;
	}
	else if (*our_account == THIRD_ACCOUNT && strcmp(input_for_username, username[THIRD_ACCOUNT]) == SAME_STRING) /*Logging in with our third account*/
	{
		return CORRECT;
	}
	else if (*our_account == FOURTH_ACCOUNT && strcmp(input_for_username, username[FOURTH_ACCOUNT]) == SAME_STRING) /*Logging in with our fourth account*/
	{
		return CORRECT;
	}
	else
	{
		return INCORRECT;
	}
}
int CheckLoginPassword(int *our_account)
{
	if (*our_account == FIRST_ACCOUNT && strcmp(input_for_Password, password[FIRST_ACCOUNT]) == SAME_STRING) /*Logging in with our first account*/
	{
		return CORRECT;
	}
	else if (*our_account == SECOND_ACCOUNT && strcmp(input_for_Password, password[SECOND_ACCOUNT]) == SAME_STRING) /*Logging in with our second account*/
	{
		return CORRECT;
	}
	else if (*our_account == THIRD_ACCOUNT && strcmp(input_for_Password, password[THIRD_ACCOUNT]) == SAME_STRING) /*Logging in with our third account*/
	{
		return CORRECT;
	}
	else if (*our_account == FOURTH_ACCOUNT && strcmp(input_for_Password, password[FOURTH_ACCOUNT]) == SAME_STRING) /*Logging in with our fourth account*/
	{
		return CORRECT;
	}
	else
	{
		return INCORRECT;
	}
}
int SendMessage(int *our_account)
{
	int reciever_account = EMPTY_ACCOUNT;
	char input_for_username[MAX_USERNAME_CHARACTERS + 2] = { 0 }, input_for_message[MAX_MESSAGE_CHARACTERS + 2] = { 0 }; /*In addition to the +1 for ending the array, the reason we have another +1 is that we can make sure that the user won't enter a message that has more than 30 characters or a username that has more than 20 characters. The reason for this is that if a bigger string than the one desired is entered, then we'll the length will be bigger and thus we can print an error*/
	printf("Who do you want to send it to?\n");
	scanf_s("%21s", input_for_username, MAX_USERNAME_CHARACTERS + 2);
	fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
	system("cls"); /*Clears the screen*/
	while (CheckOtherUsername(input_for_username, username, &reciever_account) == INCORRECT)
	{
		printf("Error. Please enter the username again:\n");
		scanf_s("%21s", input_for_username, MAX_USERNAME_CHARACTERS + 2);
		fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
		system("cls"); /*Clears the screen*/
	}
	if (SpaceForMessage(message, &reciever_account, our_account) == FULL)  /*If we cannot send more messages to a person because we already sent too many, print an error*/
	{
		printf("Error. Too many messages sent to this person.\n");
		return INCORRECT;
	}
	printf("Enter the message you want to send: (It shouldn't be more than 30 characters)\n");
	fgets(input_for_message, MAX_MESSAGE_CHARACTERS + 2, stdin);
	fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
	system("cls"); /*Clears the screen*/
	while (CheckMessageFormat(input_for_message) == INCORRECT)
	{
		printf("Error. You've entered too many characters or you didn't enter any. Please try again:\n");
		fgets(input_for_message, MAX_MESSAGE_CHARACTERS + 2, stdin);
		fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
		system("cls"); /*Clears the screen*/
	}
	AddMessage(input_for_message, message, &reciever_account, our_account);
	printf("Your message has been sent!\n");
	return CORRECT;
}
void ShowMessages(int *our_account)
{
	char c;
	int input_for_third_menu = EMPTY, true_third_menu = TRUE;
	while (true_third_menu)
	{
		printf("Please choose one of the following options:\n1. View Recieved Messages\n2. View Sent Messages\n3. None of them\n");
		scanf_s("%d", &input_for_third_menu);
		while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
		system("cls"); /*Clears the screen*/
		switch (input_for_third_menu) /*Creates a swtitch case for the options presented in the second menu*/
		{
		case 1:
		{
			ShowRecievedMessages(username, message, our_account);
			break;
		}
		case 2:
		{
			ShowSentMessages(username, message, our_account);
			break;
		}
		case 3:
		{
			GetOut(&true_third_menu);
			break;
		}
		default:
		{
			printf("Error: Unkown number. Please try again.\n");
			break;
		}
		}
	}
}
int CheckOtherUsername(int *other_account) /*The other account is ethier the recievers account who we send messages to or the senders account who sends messages to us. We can be both a reciever and a sender*/
{
	if (strcmp(input_for_username, username[FIRST_ACCOUNT]) == SAME_STRING) /*Checking to see if the username inputted is the first user*/
	{
		*other_account = FIRST_ACCOUNT;
	}
	else if (strcmp(input_for_username, username[SECOND_ACCOUNT]) == SAME_STRING) /*Checking to see if the username inputted is the second user*/
	{
		*other_account = SECOND_ACCOUNT;
	}
	else if (strcmp(input_for_username, username[THIRD_ACCOUNT]) == SAME_STRING) /*Checking to see if the username inputted is the third user*/
	{
		*other_account = THIRD_ACCOUNT;
	}
	else if (strcmp(input_for_username, username[FOURTH_ACCOUNT]) == SAME_STRING) /*Checking to see if the username inputted is the fourth user*/
	{
		*other_account = FOURTH_ACCOUNT;
	}
	else
	{
		return INCORRECT;
	}
	return CORRECT;
}
int CheckMessageFormat() /*The reason that we didn't use strlen unlike others is that fgets also gets enter (\n) that we entered and so in special cases it might not work properly with it. We'll also remove the \n as it'll cause problem in the strcpy_s in the add message function when the user enters excatly 30 characters*/
{
	if (input_for_message[FIRST_ELEMENT] != '\n') /*Checks to see if it didn't get any characters*/
	{
		for (int i = FIRST_ELEMENT; i < MAX_MESSAGE_CHARACTERS + 2; i++) /*Checks to see if \n is in the array or not. If it is, then the message has under 30 characters*/
		{
			if (input_for_message[i] == '\n')
			{
				input_for_message[i] = EMPTY; /*Removes the \n so the array works like other arrays that work with scanf_s*/
				return CORRECT;
			}
		}
		return INCORRECT; /*if \n  isn't in the array, then the input message is larger than 30 characters and so it'll print an error*/
	}
	else
	{
		return INCORRECT;
	}
}
void AddMessage( int *reciever_account, int *our_account)
{
	for (int i = FIRST_ELEMENT; i < MAX_NUMBER_OF_MESSAGES; i++) /*Put the input message in the message array */
	{
		if (*message[*our_account][*reciever_account][i] == EMPTY)
		{
			strcpy_s(message[*our_account][*reciever_account][i], MAX_MESSAGE_CHARACTERS + 1, input_for_message);
			break;
		}
	}
}
void ShowRecievedMessages( int *our_account)
{
	char input_for_username[MAX_USERNAME_CHARACTERS + 2] = { 0 }; /*In addition to the +1 for ending the array, the reason we have another +1 is that we can make sure that the user won't enter a message that has more than 30 characters or a username that has more than 20 characters. The reason for this is that if a bigger string than the one desired is entered, then we'll the length will be bigger and thus we can print an error*/
	int sender_account = EMPTY_ACCOUNT;
	printf("Whose messages do you want to see?\n");
	scanf_s("%21s", input_for_username, MAX_USERNAME_CHARACTERS + 2);
	fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
	system("cls"); /*Clears the screen*/
	while (CheckOtherUsername(input_for_username, username, &sender_account) == INCORRECT)
	{
		printf("Error. Please enter the username again:\n");
		scanf_s("%21s", input_for_username, MAX_USERNAME_CHARACTERS + 2);
		fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
		system("cls"); /*Clears the screen*/
	}
	if (PrintMessages(message, our_account, &sender_account) == EMPTY) /*We'll give the function our account as the reciever and the inputted account as the sender*/
	{
		printf("This person hasn't sent you any messages.\n");
	}
}
void ShowSentMessages( int *our_account)
{
	char input_for_username[MAX_USERNAME_CHARACTERS + 2] = { 0 }; /*In addition to the +1 for ending the array, the reason we have another +1 is that we can make sure that the user won't enter a message that has more than 30 characters or a username that has more than 20 characters. The reason for this is that if a bigger string than the one desired is entered, then we'll the length will be bigger and thus we can print an error*/
	int reciever_account = EMPTY_ACCOUNT;
	printf("Whose messages do you want to see?\n");
	scanf_s("%21s", input_for_username, MAX_USERNAME_CHARACTERS + 2);
	fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
	system("cls"); /*Clears the screen*/
	while (CheckOtherUsername(input_for_username, username, &reciever_account) == INCORRECT)
	{
		printf("Error. Please enter the username again:\n");
		scanf_s("%21s", input_for_username, MAX_USERNAME_CHARACTERS + 2);
		fseek(stdin, 0, SEEK_END); /*Prevent scanf_s from not working properly because we entered too many characters*/
		system("cls"); /*Clears the screen*/
	}
	if (PrintMessages(message, &reciever_account, our_account) == EMPTY) /*We'll give the function our account as the sender and the inputted account as the receiver*/
	{
		printf("You haven't sent this person any messages.\n");
	}
}
int PrintMessages( int *reciever_account, int *sender_account) /*This function will get both the recievers and senders account so we can see the messages. One of the accounts can be ours or both depending on what the user wants*/
{
	if (*message[*sender_account][*reciever_account][FIRST_ELEMENT] == EMPTY) /*Checks to see if any messages have been sent or not*/
	{
		return EMPTY;
	}
	else
	{
		for (int i = FIRST_ELEMENT; i < MAX_NUMBER_OF_MESSAGES; i++)
		{
			if (*message[*sender_account][*reciever_account][i] != EMPTY)
			{
				printf("%s\n", message[*sender_account][*reciever_account][i]);
			}
			else
			{
				break;
			}
		}
	}
	return FULL;
}
void GetOut(int *true_third_menu)
{
	printf("You'll be redirected to the second menu.\n");
	*true_third_menu = FALSE; /*Gets out of the third menu loop*/
}
void Logout(int *true_second_menu)
{
	printf("You've logged out.\n");
	*true_second_menu = FALSE; /*Gets out of the second menu loop*/
}
void CreateFile()
{
	FILE *information; /**messages*/
	fopen_s(&information, INFORMATION_FILE_ADDRESS, "w");
	for (int current_account = FIRST_ACCOUNT; current_account < NUMBER_OF_ACCOUNTS && *phone_number[current_account] != EMPTY; current_account++) /*Writes the user's information in a file.*/
	{
		fprintf(information, "%s %s %s ", username[current_account], password[current_account], phone_number[current_account]);
		fprintf(information, "\n");
	}
}
int ReadFile()
{
	FILE *information; /**messages*/
	int count_message_numbers = EMPTY, reciever_account = EMPTY_ACCOUNT, current_account = EMPTY_ACCOUNT;
	fopen_s(&information, INFORMATION_FILE_ADDRESS, "r");
	for (int current_account = FIRST_ACCOUNT; current_account < NUMBER_OF_ACCOUNTS; current_account++) /*Writes the user's information in a file. We also calculate the length of the strings so the fwrite fucntion works properly. We'll also add a space so we can distinguish each of the values*/
	{
		fscanf_s(information, "%s %s %s ", username[current_account], MAX_USERNAME_CHARACTERS + 1, password[current_account], MAX_PASSWORD_CHARACTERS + 1, phone_number[current_account], PHONE_NUMBER_NUMBER_DIGITS + 1);
	}
	fclose(information);
	return CORRECT;
}