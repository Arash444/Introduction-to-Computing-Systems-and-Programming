#include <stdio.h>
#define EMPTY 0
#define FULL 1
#define TRUE 1
#define SIGNUP 1
#define LOGIN 2
#define EXIT 3
#define MAX_NUMBER_FOR_PHONE_NUMBER 10000000000
#define MIN_NUMBER_FOR_PHONE_NUMBER 1000000000
#define MAX_NUMBER_FOR_PASSWORD 1000000
#define MIN_NUMBER_FOR_PASSWORD 0

void main() /*Decription: Creates a new messenger with the options to signup, login and exit with more to come*/
{
	char c;
	long long phone_number_1 = EMPTY, phone_number_2 = EMPTY, phone_number_3 = EMPTY; /*Initializing our phone numbers*/
	long long password_1 = EMPTY, re_entering_password_1, password_2 = EMPTY, re_entering_password_2, password_3 = EMPTY, re_entering_password_3, a; /*Initializing our passwords and the re-entering of them*/
	while (TRUE) /*Shows the main menu*/
	{
		long long input_for_main_menu = EMPTY, input_for_second_menu = EMPTY, input_for_phone_number = EMPTY, input_for_password = EMPTY, true_2 = TRUE; /*Re-initializing our inputs*/
		printf("Welocome to UT messenger.\nPlease choose one of the following options:\n1: Signup\n2: Login\n3: Exit\n");
		a = scanf_s("%lld", &input_for_main_menu);
		while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
		if (input_for_main_menu == SIGNUP) /*Starts the process of creating new accounts.*/
		{
			if (phone_number_1 == EMPTY) /*Starts the process of creating the first account*/
			{
				while (phone_number_1 == EMPTY) /*Starts the process of entering a phone number for our account*/
				{
					printf("Please enter your phone number:\n");
					scanf_s("%lld", &phone_number_1);
					while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
					if (MIN_NUMBER_FOR_PHONE_NUMBER <= phone_number_1 && phone_number_1 < MAX_NUMBER_FOR_PHONE_NUMBER) /*Checks to see if the phone number is 10 digits*/
					{
						while (TRUE) /*Starts the process of creating a password for our account*/
						{
							printf("Enter your password (only use numbers and at most use 6 digits)\n");
							scanf_s("%lld", &password_1);
							while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
							if (MIN_NUMBER_FOR_PASSWORD <= password_1 && MAX_NUMBER_FOR_PASSWORD > password_1) /*Checks to see if the password is less than 6 digits*/
							{
								printf("Re-enter your password please:\n");
								scanf_s("%lld", &re_entering_password_1);
								while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
								if (password_1 == re_entering_password_1) /*Checks to see if we have re entered our password correctly*/
								{
									printf("Your new account is created. You'll now be re-directed to the login page\n");
									input_for_main_menu = LOGIN; /*Goes to the login page*/
									input_for_phone_number = FULL; /*Skips the login process*/
									break; /*Goes out of the loops and takes the user to the second menu.*/
								}
								else
								{
									printf("Error: Your password doesn't match.\n");
								}
							}
							else /*Prints error when the entered password is more than 6 digits*/
							{
								printf("Error: You've exceeded the allowed number of digits\n");
							}
						}
					}
					else /*Prints error when the entered phone number isn't 10 digits*/
					{
						printf("Error: Wrong phone number format.\n");
						phone_number_1 = EMPTY; /*Removes the wrong number.*/
					}
				}
			}
			else if (phone_number_2 == EMPTY) /*Starts the process of creating the second account*/
			{
				while (phone_number_2 == EMPTY) /*Starts the process of entering a phone number for our account*/
				{
					printf("Please enter your phone number:\n");
					scanf_s("%lld", &phone_number_2);
					while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
					if (MIN_NUMBER_FOR_PHONE_NUMBER <= phone_number_2 && phone_number_2 < MAX_NUMBER_FOR_PHONE_NUMBER && phone_number_2 != phone_number_1) /*Checks to see if the phone number is 10 digits and that it doesn't exist*/
					{
						while (TRUE) /*Starts the process of creating a password for our account*/
						{
							printf("Enter your password (only use numbers and at most use 6 digits)\n");
							scanf_s("%lld", &password_2);
							while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
							if (MIN_NUMBER_FOR_PASSWORD <= password_2 && MAX_NUMBER_FOR_PASSWORD > password_2) /*Checks to see if the password is less than 6 digits*/
							{
								printf("Re-enter your password please:\n");
								scanf_s("%lld", &re_entering_password_2);
								while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
								if (password_2 == re_entering_password_2) /*Checks to see if we have re entered our password correctly*/
								{
									printf("Your new account is created. You'll now be re-directed to the login page\n");
									input_for_main_menu = LOGIN; /*Goes to the login page*/
									input_for_phone_number = FULL; /*Skips the login process*/
									break; /*Goes out of the loops and takes the user to the second menu.*/
								}
								else
								{
									printf("Error: Your password doesn't match.\n");
								}
							}
							else /*Prints error when the entered password is exceeds 6 digits*/
							{
								printf("Error: You've exceeded the allowed number of digits.\n");
							}
						}
					}
					else if (phone_number_2 == phone_number_1) /*Prints error when the number entered already existed.*/
					{
						printf("Error: Phone number already exists. Please go to the login page.\n");
						phone_number_2 = EMPTY; /*Removes the wrong number.*/
						break;  /*Goes out of the loop phone number loop so the user can login if they want to do so*/
					}
					else /*Prints error when the entered phone number isn't 10 digits*/
					{
						printf("Error: Wrong phone number format.\n");
						phone_number_2 = EMPTY; /*Removes the wrong number.*/
					}
				}
			}
			else if (phone_number_3 == EMPTY) /*Starts the process of creating the third account*/
			{
				while (phone_number_3 == EMPTY) /*Starts the process of entering a phone number for our account*/
				{
					printf("Please enter your phone number:\n");
					scanf_s("%lld", &phone_number_3);
					while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
					if (MIN_NUMBER_FOR_PHONE_NUMBER <= phone_number_3 && phone_number_3 < MAX_NUMBER_FOR_PHONE_NUMBER && phone_number_3 != phone_number_2 && phone_number_3 != phone_number_1) /*Checks to see if the phone number is 10 digits and that it doesn't exist*/
					{
						while (TRUE) /*Starts the process of creating a password for our account*/
						{
							printf("Enter your password (only use numbers and at most use 6 digits)\n");
							scanf_s("%lld", &password_3);
							while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
							if (MIN_NUMBER_FOR_PASSWORD <= password_3 && MAX_NUMBER_FOR_PASSWORD > password_3)/*Checks to see if the password is less than 6 digits*/
							{
								printf("Re-enter your password please:\n");
								scanf_s("%lld", &re_entering_password_3);
								while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
								if (password_3 == re_entering_password_3) /*Checks to see if we have re entered our password correctly*/
								{
									printf("Your new account is created. You'll now be re-directed to the login page.\n");
									input_for_main_menu = LOGIN; /*Goes to the login page*/
									input_for_phone_number = FULL; /*Skips the login process*/
									break; /*Goes out of the loops and takes the user to the second menu.*/
								}
								else
								{
									printf("Error: Your password doesn't match.\n");
								}
							}
							else /*Prints error when the entered password is more than 6 digits*/
							{
								printf("Error: You've exceeded the allowed number of digits\n");
							}
						}
					}
					else if (phone_number_3 == phone_number_2 || phone_number_3 == phone_number_1) /*Prints error when the number entered already existed.*/
					{
						printf("Error: Phone number already exists. Please go to the login page.\n");
						phone_number_3 = EMPTY; /*Removes the wrong number.*/
						break; /*Goes out of the loop phone number loop so the user can login if they want to do so*/
					}
					else /*Prints error when the entered phone number isn't 10 digits*/
					{
						printf("Error: Wrong phone number format.\n");
						phone_number_3 = EMPTY; /*Removes the wrong number.*/
					}
				}
			}
			else /*If we've already reached 3 accounts, it will notify the user that they can no longer create a new account.*/
			{
				printf("There's no more room in the community!\n");
			}
		}
		if (input_for_main_menu == LOGIN)
		{
			while (input_for_phone_number == EMPTY) /*Starts the login process*/
			{
				printf("Please enter your phone number:\n");
				scanf_s("%lld", &input_for_phone_number);
				while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
				while (input_for_phone_number == phone_number_1) /*Logging in with our first account*/
				{
					printf("Enter your password:\n");
					scanf_s("%lld", &input_for_password);
					while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
					if (input_for_password == password_1) /*Checks to see if the password is correct*/
					{
						printf("You've successfully logged in!\n");
						break; /*Goes to the second menu*/
					}
					else
					{
						printf("Your password was incorrect\n");
					}
				}
				while (input_for_phone_number == phone_number_2) /*Logging in with our second account*/
				{
					printf("Enter your password:\n");
					scanf_s("%lld", &input_for_password);
					while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
					if (input_for_password == password_2) /*Checks to see if the password is correct*/
					{
						printf("You've successfully logged in!\n");
						break; /*Goes to the second menu*/
					}
					else
					{
						printf("Your password was incorrect\n");
					}
				}
				while (input_for_phone_number == phone_number_3) /*Logging in with our third account*/
				{
					printf("Enter your password:\n");
					scanf_s("%lld", &input_for_password);
					while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
					if (input_for_password == password_3) /*Checks to see if the password is correct*/
					{
						printf("You've successfully logged in!\n");
						break; /*Goes to the second menu*/
					}
					else
					{
						printf("Your password was incorrect\n");
					}
				}
				if (input_for_phone_number != phone_number_1 && input_for_phone_number != phone_number_2 && input_for_phone_number != phone_number_3) /*Prints an error when the phone number doesn't exist in our messenger*/
				{
					printf("Error: Phone number doesn't exist.\n");
					true_2 = EMPTY; /*Does not go into the second menu.*/
					break; /*Goes to the main menu so they can ethier login with another account or create a new one.*/
				}
			}
			while (true_2) /*Shows the second menu*/
			{
				printf("Please choose one of the following options:\n1. Send message\n2. Show messages\n3. Create channel\n4. Create group\n5. Log out\n");
				scanf_s("%lld", &input_for_second_menu);
				while ((c = getchar()) != '\n' && c != EOF); /*Prevents the program from not working properly due to the user entering a chararcter*/
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
					printf("You've logged out.\n");
					true_2 = EMPTY; /*Gets out of the second menu loop*/
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
		if (input_for_main_menu == EXIT) /*Exiting the program*/
		{
			printf("Hope to see you again!\n");
			break; /*Goes out of the program*/
		}
		if (input_for_main_menu != SIGNUP && input_for_main_menu != LOGIN &&  input_for_main_menu != EXIT) /*Prints an error if the number inputted was not in the options*/
		{
			printf("Error: Unkown Number. Please try again.\n");
		}
	}
}