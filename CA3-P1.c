#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#define INCORRECT 0
#define CORRECT 1
#define EMPTY 0
#define FULL 1
#define FALSE 0
#define TRUE 1
#define SAME_STRING 0
#define FIRST_ELEMENT 0
#define PHONE_NUMBER_NUMBER_DIGITS 11
#define MIN_PASSWORD_CHARACTERS 6
#define NULL_CHARACTER 1
#define INFORMATION_FILE_ADDRESS "information.txt"
typedef struct user_info user;
typedef struct message_info message;
typedef struct tm date_time;
char* EnterCommand(char*, int*);
void Signup(user*, char*, int*);
void Login(user*, message*, char*, int*);
void Logout(char*, int*);
void EditUsername(char*, int*, user*, message*);
void EditPassword(char*, int, user*);
void SendMessage(message*, char*, int);
void Information(user*);
void About(user*);
void ShowRecievedMessages(char*, int, message*);
void ShowSentMessages(char*, int, message*);
void CloseProgram(int*);
int CheckPasswordFormat(int);
int CheckPhoneFormat(char*, int);
void EditPasswordUserList(char*, char*, int, user*);
void EditUsernameUserList(char*, char*, int, user*);
void EditUsernameMessage(char*, char*, int, message*);
int CheckLoginUsername(char*, user*);
int CheckLoginPassword(char*, user*, char*);
void ShowUnreadMessages(char*, message*);
int UsernameExist(char*, user*);
int PhoneNumberExist(char*, user*);
void AddUser(char*, char*, char*, int, int, int, char*, int*, user*);
void AddMessage(char*, char*, char*, int, int, int, message*);
char* GetInput(char*, int*, int*);
char* GetLastInput(char*, int*, int*);
struct user_info
{
	char* username;
	char* phone_number;
	char* password;
	date_time *date_and_time;
	user *next;
};
struct message_info
{
	char* message;
	char* sender_account;
	char* reciever_account;
	int message_read; /*This is a flag so we can see whether or not has a message been read*/
	date_time *date_and_time;
	message *next;
};
int main()
{
	user *head_user = malloc(sizeof(user));
	head_user->next = NULL; /*Creates the user's link list*/
	message *head_message = malloc(sizeof(message));
	head_message->next = NULL; /*Creates the message's link list*/
	char *current_account; /*We save the username of our current acount that's logged. It'll make things that has to do with things like messages easier*/
	current_account = malloc(sizeof(char));
	int true_command = TRUE /*This is for our loop*/, command_finished /*Saves the state of our command so we can check it it's finished or not*/, count_current_account = EMPTY /*Saves the number of characters in our current account in case we need it*/;
	while (true_command == TRUE)
	{
		char *command = malloc(sizeof(char));
		printf(">> ");
		command = EnterCommand(command, &command_finished);
		if (strcmp(command, "signup") == SAME_STRING && command_finished == FALSE)
		{
			Signup(head_user, current_account, &count_current_account);
		}
		else if (strcmp(command, "login") == SAME_STRING && command_finished == FALSE)
		{
			Login(head_user, head_message, current_account, &count_current_account);
		}
		else if (strcmp(command, "logout") == SAME_STRING  && command_finished == TRUE)
		{
			Logout(current_account, &count_current_account);
		}
		else if (strcmp(command, "edit_username") == SAME_STRING && command_finished == FALSE)
		{
			EditUsername(current_account, &count_current_account, head_user, head_message);
		}
		else if (strcmp(command, "edit_pass") == SAME_STRING && command_finished == FALSE)
		{
			EditPassword(current_account, count_current_account, head_user);
		}
		else if (strcmp(command, "send") == SAME_STRING && command_finished == FALSE)
		{
			SendMessage(head_message, current_account, count_current_account);
		}
		else if (strcmp(command, "info") == SAME_STRING && command_finished == TRUE)
		{
			Information(head_user);
		}
		else if (strcmp(command, "about") == SAME_STRING && command_finished == FALSE)
		{
			About(head_user);
		}
		else if (strcmp(command, "show_recieved") == SAME_STRING && command_finished == FALSE)
		{
			ShowRecievedMessages(current_account, count_current_account, head_message); //check to see if you can create a single function
		}
		else if (strcmp(command, "show_sent") == SAME_STRING && command_finished == FALSE)
		{
			ShowSentMessages(current_account, count_current_account, head_message);
		}
		else if (strcmp(command, "close") == SAME_STRING && command_finished == TRUE)
		{
			CloseProgram(&true_command);
		}
		else
		{
			printf("Wrong command format. Please try again:\n");
		}
		fseek(stdin, EMPTY, SEEK_END); /*We have this in order to prevent get char from getting wrong command and messing with our messenger*/
	}
	return 0;
}
char* EnterCommand(char *command, int *command_finished)
{
	int element = EMPTY;
	while (TRUE)
	{
		command[element] = getchar();
		if (command[element] == ' ')
		{
			command[element] = '\0';
			*command_finished = FALSE;
			return command;
		}
		else if (command[element] == '\n')
		{
			command[element] = '\0';
			*command_finished = TRUE;
			return command;
		}
		element++;
		command = realloc(command, (element + 1) * sizeof(char));
	}
}
void Signup(user* head_user, char* current_account, int *count_current_account)
{
	int count_username = EMPTY, count_password = EMPTY, count_phone_number = EMPTY, command_correct = TRUE; /*We save the number of elements in our input arrays so we can use strcpy_s better*/
	char *input_for_username = malloc(sizeof(char));
	char *input_for_password = malloc(sizeof(char));
	char *input_for_phone_number = malloc(sizeof(char));
	input_for_username = GetInput(input_for_username, &count_username, &command_correct); /*Gets the input for username*/
	if (command_correct == FALSE) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	input_for_password = GetInput(input_for_password, &count_password, &command_correct); /*Gets the input for password*/
	if (command_correct == FALSE) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	input_for_phone_number = GetLastInput(input_for_phone_number, &count_phone_number, &command_correct); /*Gets the input for phone number*/
	if (command_correct == FALSE) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	if (CheckPasswordFormat(count_password) == INCORRECT)
	{
		printf("Error: Wrong password format. Please try again\n");
		return;
	}
	if (CheckPhoneFormat(input_for_phone_number, count_phone_number) == INCORRECT)
	{
		printf("Error! Wrong phone number format. Please try again:\n");
		return;
	}
	if (UsernameExist(input_for_username, head_user) == TRUE) /*Gives the information of our current usernames in the accounts and the current input*/
	{
		printf("Error: Username already exists.\n");
		return;
	}
	if (PhoneNumberExist(input_for_phone_number, head_user) == TRUE) /*Gives the information of our current phone numbers in the accounts and the current input*/
	{
		printf("Error: Phone number already exists.\n");
		return;
	}
	AddUser(input_for_username, input_for_password, input_for_phone_number, count_username, count_password, count_phone_number, current_account, count_current_account, head_user);
	printf("Your new account is created.\n");
}
void Login(user* head_user, message* head_message, char* current_account, int *count_current_account)
{
	int count_username = EMPTY, count_password = EMPTY, command_correct = TRUE; /*We save the number of elements in our input arrays so we can use strcpy_s better*/
	char *input_for_username = malloc(sizeof(char)), *input_for_password = malloc(sizeof(char));
	input_for_username = GetInput(input_for_username, &count_username, &command_correct); /*Gets the input for username*/
	if (command_correct == FALSE) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	input_for_password = GetLastInput(input_for_password, &count_password, &command_correct); /*Gets the input for password*/
	if (command_correct == FALSE) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	if (CheckLoginUsername(input_for_username, head_user) == INCORRECT)
	{
		printf("Error: Wrong username entered\n");
		return;
	}
	current_account = malloc((count_username + NULL_CHARACTER) * sizeof(char));
	strcpy_s(current_account, count_username + NULL_CHARACTER, input_for_username); /*Sets our current account to the new account which we logged in*/
	*count_current_account = count_username + NULL_CHARACTER;
	if (CheckLoginPassword(input_for_password, head_user, current_account) == INCORRECT)
	{
		printf("Error: Wrong password entered\n");
		return;
	}
	printf("You've successfully logged in!\n");
	ShowUnreadMessages(current_account, head_message);
}
void Logout(char *current_account, int *count_current_account)
{
	if (*count_current_account == EMPTY) /*If we haven't logged in with an account, then the number of characters in our username is zero since we don't have any currently*/
	{
		printf("Error: You haven't logged in with any account!\n");
		return;
	}
	printf("You've succsefully logged out!\n");
	*count_current_account = EMPTY;
}
void EditUsername(char* current_account, int *count_current_account, user *head_user, message *head_message)
{
	int count_username = EMPTY, command_correct = TRUE; /*We save the number of elements in our input arrays so we can use strcpy_s better*/
	char *input_for_username = malloc(sizeof(char));
	if (*count_current_account == EMPTY) /*If we haven't logged in with an account, then the number of characters in our username is zero since we don't have any currently*/
	{
		printf("Error: You haven't logged in with any account!\n");
		return;
	}
	input_for_username = GetLastInput(input_for_username, &count_username, &command_correct); /*Gets the input for username*/
	if (command_correct == INCORRECT) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	if (UsernameExist(input_for_username, head_user) == TRUE) /*Gives the information of our current usernames in the accounts and the current input*/
	{
		printf("Error: Username already exists.\n");
		return;
	}
	EditUsernameUserList(current_account, input_for_username, count_username, head_user);
	EditUsernameMessage(current_account, input_for_username, count_username, head_message);
	current_account = malloc((count_username + +NULL_CHARACTER) * sizeof(char));
	*count_current_account = count_username + NULL_CHARACTER; /*Saves the number of characters in our current account in case we need it*/
	strcpy_s(current_account, count_username + NULL_CHARACTER, input_for_username); /*Changes the username our current account to the new one inputted by the user*/
	*count_current_account = count_username;
}
void EditPassword(char* current_account, int count_current_account, user *head_user)
{
	int count_password = EMPTY, command_correct = TRUE; /*We save the number of elements in our input arrays so we can use strcpy_s better*/
	char *input_for_password = malloc(sizeof(char));
	if (count_current_account == EMPTY) /*If we haven't logged in with an account, then the number of characters in our username is zero since we don't have any currently*/
	{
		printf("Error: You haven't logged in with any account!\n");
		return;
	}
	input_for_password = GetLastInput(input_for_password, &count_password, &command_correct); /*Gets the input for username*/
	if (command_correct == FALSE)  /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	if (CheckPasswordFormat(count_password) == INCORRECT)
	{
		printf("Error: Wrong password format. Please try again\n");
		return;
	}
	EditPasswordUserList(current_account, input_for_password, count_password, head_user);
}
void SendMessage(message* head_message, char* current_account, int count_current_account)
{
	int count_message = EMPTY, count_reciever_username = EMPTY, command_correct = TRUE; /*Saves the number of characters in the arrays so we can save them easier using strcpy_s*/
	char* input_for_message = malloc(sizeof(char)), *input_for_reciever_account = malloc(sizeof(char));
	if (count_current_account == EMPTY) /*If we haven't logged in with an account, then the number of characters in our username is zero since we don't have any currently*/
	{
		printf("Error: You haven't logged in with any account!\n");
		return;
	}
	input_for_message = GetInput(input_for_reciever_account, &count_reciever_username, &command_correct); /*Gets the input for the reciever's account*/
	if (command_correct == FALSE) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	input_for_reciever_account = GetLastInput(input_for_message, &count_message, &command_correct);/*Gets the input for the message*/
	if (command_correct == FALSE) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}

	AddMessage(input_for_message, input_for_reciever_account, current_account, count_message, count_reciever_username, count_current_account, head_message);
}
void Information(user* head_user)
{
	user *current_user = head_user->next;
	while (current_user != NULL) /*Tries to go through our account one by one*/
	{
		printf("%s\n", current_user->username); /*Prints the usernames*/
		current_user = current_user->next;
	}
}
void About(user* head_user)
{
	user *current_user = head_user->next;
	int command_correct = TRUE, count_username = EMPTY; /*We only need xoutn username for our input function otherwise it serves no purpose*/
	char* input_for_username = malloc(sizeof(char));
	input_for_username = GetLastInput(input_for_username, &count_username, &command_correct); /*Gets the username*/
	if (command_correct == FALSE) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	while (current_user != NULL) /*Tries to find our account in the list*/
	{
		if (strcmp(current_user->username, input_for_username) == SAME_STRING) /*Checks to see if we've found our account*/
		{
			printf("%s\n%s\n", current_user->username, current_user->phone_number); /*Prints the username and phone number*/
			return;
		}
		current_user = current_user->next;
	}
}
void ShowRecievedMessages(char* current_account, int count_current_account, message *head_message)
{
	message *current_message = head_message->next;
	char* input_for_sender_username = malloc(sizeof(char));
	int count_sender_username = EMPTY; /*We only need this for our input function otherwise it serves no purpose*/
	int count = EMPTY; /*this count is to see if we've recieved any messages from this person if not, then we'll print and error*/
	int command_correct = TRUE;
	if (count_current_account == EMPTY) /*If we haven't logged in with an account, then the number of characters in our username is zero since we don't have any currently*/
	{
		printf("Error: You haven't logged in with any account!\n");
		return;
	}
	input_for_sender_username = GetLastInput(input_for_sender_username, &count_sender_username, &command_correct); /*Gets the sender username*/
	if (command_correct == FALSE) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	while (current_message != NULL) /*Tries to go through all the messages one by one*/
	{
		if (strcmp(current_message->reciever_account, current_account) == SAME_STRING && strcmp(current_message->sender_account, input_for_sender_username) == SAME_STRING) /*Checks to see if we've found our account and the sender's account*/
		{
			printf("message from: %s\n %s\n", current_message->sender_account, current_message->message); /*Prints the message and the date and who sent it*/
			count++;
		}
		current_message = current_message->next;
	}
	if (count == EMPTY)
	{
		printf("This person hasn't sent you any messages");
	}
}
void ShowSentMessages(char* current_account, int count_current_account, message *head_message)
{
	message *current_message = head_message->next;
	char* input_for_reciever_username;
	input_for_reciever_username = malloc(sizeof(char));
	int count_reciever_username = EMPTY; /*We only need this for our input function otherwise it serves no purpose*/
	int count = EMPTY; /*this count is to see if we've recieved any messages from this person if not, then we'll print and error*/
	int command_correct = TRUE;
	if (count_current_account == EMPTY) /*If we haven't logged in with an account, then the number of characters in our username is zero since we don't have any currently*/
	{
		printf("Error: You haven't logged in with any account!\n");
		return;
	}
	input_for_reciever_username = GetLastInput(input_for_reciever_username, &count_reciever_username, &command_correct); /*Gets the sender username*/
	if (command_correct == FALSE) /*Checks to see if the command was entered correctly*/
	{
		printf("Wrong command format. Please try again:\n");
		return;
	}
	while (current_message != NULL) /*Tries to go through all the messages one by one*/
	{
		if (strcmp(current_message->sender_account, current_account) == SAME_STRING && strcmp(current_message->reciever_account, input_for_reciever_username) == SAME_STRING) /*Checks to see if we've found our account and the reciever's account*/
		{
			printf("message to: %s\n%s\n", current_message->reciever_account, current_message->message); /*Prints the message and the date and who recieved it*/
			count++;
		}
		current_message = current_message->next;
	}
	if (count == EMPTY)
	{
		printf("You haven't sent this person any messages");
	}
}
void CloseProgram(int *true_command)
{
	printf("Please come back again!\n");
	*true_command = FALSE;
}
int CheckPasswordFormat(int count_password)
{
	if (count_password >= MIN_PASSWORD_CHARACTERS)
	{
		return CORRECT;
	}
	else
	{
		return INCORRECT;
	}
}
int CheckPhoneFormat(char* input_for_phone_number, int count_phone_number)
{
	if (count_phone_number == PHONE_NUMBER_NUMBER_DIGITS && input_for_phone_number[FIRST_ELEMENT] == '0')
	{
		for (int i = FIRST_ELEMENT; i < PHONE_NUMBER_NUMBER_DIGITS; i++)
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
void EditPasswordUserList(char* current_account, char* input_for_password, int count_password, user *head_user)
{
	user *current_user = head_user->next;
	while (current_user != NULL) /*Tries to find our account in the list*/
	{
		if (strcmp(current_user->username, current_account) == SAME_STRING) /*Checks to see if we've found our account*/
		{
			free(current_user->password); /*Removes the old password*/
			current_user->username = malloc((count_password + NULL_CHARACTER) * sizeof(char));
			strcpy_s(current_user->username, count_password + NULL_CHARACTER, input_for_password); /*Saves the new password*/
			return;
		}
		current_user = current_user->next;
	}
}
void EditUsernameUserList(char* current_account, char *input_for_username, int count_username, user *head_user)
{
	user *current_user = head_user->next;
	while (current_user != NULL) /*Tries to find our account in the list*/
	{
		if (strcmp(current_user->username, current_account) == SAME_STRING) /*Checks to see if we've found our account*/
		{
			current_user->username = malloc((count_username + NULL_CHARACTER) * sizeof(char));
			strcpy_s(current_user->username, count_username + NULL_CHARACTER, input_for_username); /*Saves the new username*/
			return;
		}
		current_user = current_user->next;
	}
}
void EditUsernameMessage(char* current_account, char *input_for_username, int count_username, message *head_message)
{
	message *current_message = head_message->next;
	while (current_message != NULL) /*Tries to go through the messages one by one*/
	{
		if (strcmp(current_message->reciever_account, current_account) == SAME_STRING) /*checks to see if the reciever account is our account*/
		{
			current_message->reciever_account = malloc((count_username + NULL_CHARACTER) * sizeof(char));
			strcpy_s(current_message->reciever_account, count_username + NULL_CHARACTER, input_for_username); /*Saves the new username*/
		}
		if (strcmp(current_message->sender_account, current_account) == SAME_STRING) /*checks to see if the sender account is our account*/
		{
			current_message->sender_account = malloc((count_username + NULL_CHARACTER) * sizeof(char));
			strcpy_s(current_message->sender_account, count_username + NULL_CHARACTER, input_for_username); /*Saves the new username*/
			return;
		}
		current_message = current_message->next;
	}
}
int CheckLoginUsername(char *input_for_username, user *head_user)
{
	user *current_user = head_user->next;
	while (current_user != NULL)
	{
		if (strcmp(current_user->username, input_for_username) == SAME_STRING)
		{
			return CORRECT;
		}
		current_user = current_user->next;
	}
	return FALSE;
}
int CheckLoginPassword(char *input_for_password, user *head_user, char *current_account)
{
	user *current_user = head_user->next;
	while (current_user != NULL)
	{
		if (strcmp(current_user->username, current_account) == SAME_STRING)
		{
			if (strcmp(current_user->password, input_for_password) == SAME_STRING)
			{
				return CORRECT;
			}
		}
		current_user = current_user->next;
	}
	return FALSE;
}
void ShowUnreadMessages(char *current_account, message *head_message)
{
	int count = EMPTY; /*We have this count so we can see whether or not did we have any new messages so if we didn't we can print out an error*/
	message *current_message = head_message->next;
	printf("Unread messages:\n");
	while (current_message != NULL)
	{
		if (strcmp(current_message->reciever_account, current_account) == SAME_STRING && current_message->message_read == FALSE)
		{
			printf("Message from: %s\n at t in: d\n", current_message->sender_account);
			current_message->message_read = TRUE;
			count++;
		}
	}
	if (count == EMPTY)
	{
		printf("No new messages.\n");
	}
}
int UsernameExist(char *input_for_username, user *head_user)
{
	user *current_user = head_user->next;
	while (current_user != NULL)
	{
		if (strcmp(current_user->username, input_for_username) == SAME_STRING)
		{
			return TRUE;
		}
		current_user = current_user->next;
	}
	return FALSE;
}
int PhoneNumberExist(char *input_for_phone_number, user *head_user)
{
	user *current_user = head_user->next;
	while (current_user != NULL)
	{
		if (strcmp(current_user->phone_number, input_for_phone_number) == SAME_STRING)
		{
			return TRUE;
		}
		current_user = current_user->next;
	}
	return FALSE;
}
void AddUser(char *input_for_username, char *input_for_password, char *input_for_phone_number, int count_username, int count_password, int count_phone_number, char* current_account, int* count_current_account, user* head_user)
{
	user *new = malloc(sizeof(user));
	new->username = malloc((count_username + NULL_CHARACTER) * sizeof(char));
	new->password = malloc((count_password + NULL_CHARACTER) * sizeof(char));
	new->phone_number = malloc((count_phone_number + NULL_CHARACTER) * sizeof(char));
	strcpy_s(new->username, count_username + NULL_CHARACTER, input_for_username); /*Saves the new username*/
	strcpy_s(new->password, count_password + NULL_CHARACTER, input_for_password); /*Saves the new password*/
	strcpy_s(new->phone_number, count_phone_number + NULL_CHARACTER, input_for_phone_number); /*Saves the new phone number*/
	user *current_user = head_user->next;
	user *previous_user = head_user;
	while (current_user != NULL)
	{
		previous_user = current_user;
		current_user = current_user->next;
	}
	previous_user->next = new;
	new->next = NULL;
	current_account = malloc((count_username + NULL_CHARACTER) * sizeof(char));
	*count_current_account = count_username; /*Saves the number of characters in our current account in case we need it*/
	strcpy_s(current_account, count_username + NULL_CHARACTER, new->username); /*Sets our current account to the new account created*/
}
void AddMessage(char *input_for_message, char *input_for_reciever_username, char *sender_account, int count_message, int count_reciever_account, int count_sender_account, message* head_message)
{
	message *current_message = head_message->next;
	message *previous_message = head_message;
	current_message->message = malloc((count_message + NULL_CHARACTER) * sizeof(char));
	current_message->reciever_account = malloc((count_reciever_account + NULL_CHARACTER) * sizeof(char));
	current_message->sender_account = malloc((count_sender_account + NULL_CHARACTER) * sizeof(char));
	while (current_message != NULL)
	{
		previous_message = current_message;
		current_message = current_message->next;
	}
	previous_message->next = current_message;
	current_message->next = NULL;
	strcpy_s(current_message->message, count_message + NULL_CHARACTER, input_for_message); /*Saves the message*/
	strcpy_s(current_message->reciever_account, count_reciever_account + NULL_CHARACTER, input_for_reciever_username); /*Saves the reciever's account*/
	strcpy_s(current_message->sender_account, count_sender_account + NULL_CHARACTER, sender_account); /*Saves the sender's account*/
}
char* GetInput(char *input, int *count, int *command_correct) /*The reason we have two diffrent type of functions for input is that if there should be more input, then we can print an error if the command has finished*/
{
	while (TRUE)
	{
		input[*count] = getchar();
		if (input[*count] == '\n')
		{
			*command_correct = FALSE;
			return NULL;
		}
		if (input[*count] == ' ')
		{
			if (*count == EMPTY) /*If they just put 2 spaces with one of them being the input, then we don't have an input so this will fix that problem*/
			{
				command_correct = FALSE;
				return NULL;
			}
			input[*count] = '\0';
			*command_correct = TRUE;
			return input;
		}
		(*count)++;
		input = realloc(input, ((*count) + 1) * sizeof(char));
	}
}
char* GetLastInput(char *input, int *count, int *command_correct) /*The reason we have two diffrent type of functions for input is that if there shouldn't be more input, then we can print an error if the command hasn't finished yet*/
{
	while (TRUE)
	{
		input[*count] = getchar();
		if (input[*count] == ' ')
		{
			*command_correct = FALSE;
			return NULL;
		}
		if (input[*count] == '\n')
		{
			input[*count] = '\0';
			*command_correct = TRUE;
			return input;
		}
		(*count)++;
		input = realloc(input, ((*count) + 1) * sizeof(char));
	}
}