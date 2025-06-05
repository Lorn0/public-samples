#include "includes.h"

short Sekunden = 0;
short Minuten = 0;
short Stunden = 0;

bool run = true;

void run_timer()
{
	//while Sekunden is greater than -1 so = 0 and / or higher 
	//so if we keep clocking down we will eventually hit -1 on the seconds timer that basically means where done
	//so until this point we gonna count down 
	do
	{
		for (;;)
		{
			//Logic
			//if seconds are 0 and minutes(are not) put seconds to 59 and minute -1 ... same with hours 
			if (Stunden == 0 && Minuten == 0 && Sekunden == 0)
			{
				break;
			}

			if (Sekunden == 0 && Minuten == 0)
			{
				Minuten = 59;
				Stunden--;
			}

			if (Sekunden == 0)
			{
				Sekunden = 59;
				Minuten--;
			}

			system("cls");

			printf("**********************************************************************\n");

			printf("%d", Stunden);
			printf(":");
			
			//if Minutes is less than ten i draw a 0 before so we have 2 numbers ( just for better readability basically)
			if (Minuten < 10)
			{
				printf("0");
				printf("%d", Minuten);
			}
			//if Minutes is already greater than 10 we dont need to put the 0 (we already have 2 numbers)
			if (Minuten >= 10)
			{
				printf("%d", Minuten);
			}
			printf(":");

			//here we just do the same for the seconds greater than ten add a 0 otherwhise ...
			if (Sekunden < 10)
			{
				printf("0");
				printf("%d", Sekunden--);
			}
			if (Sekunden >= 10)
			{
				printf("%d", Sekunden--);
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //1000 ms = 1sek //60000 ms = 1 min

		}

		system("cls");

		Sekunden = -1;

		printf("**********************************************************************\n");
		printf("0:00:00\n*** Timer Done ***\n");

	} while (Sekunden > -1);

	//system("cls");
	//
	//Sekunden = 0;
	//
	//printf("**********************************************************************\n");
	//printf("0:00:00\n*** Timer Done ***\n");

}

int main()
{	
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 600, 400, TRUE); // X width, X height

	do
	{
		system("cls");
		// "user interface" -> ask for the time u want to use in the timer Hours:Minutes:Seconds
		printf("**********************************************************************\n");
		printf("\nHours ... = ");

		//wait for the input for the Hours from the user
		std::cin >> Stunden;

		// input validation
		while (std::cin.fail())
		{
			std::cin.clear(); // clear input buffer to restore cin to a usable state
			std::cin.ignore(INT_MAX, '\n'); // ignore last input
			printf("U can only enter Numbers!\n");
			printf("Hours ... = ");
			std::cin >> Stunden;
		}

		//clear cosnole after the input is given 
		system("cls");

		//"draw" everything again with the "new" information already given -> Hours = ...
		printf("**********************************************************************\n");
		printf("%d", Stunden);
		printf("\n");

		//repeat input until its betwen 59 and 0
		do
		{
			//ask for the input for the Minutes
			printf("Minutes ... = ");

			//get the input for the Minutes from the user
			std::cin >> Minuten;

			// input validation
			while (std::cin.fail())
			{
				std::cin.clear(); // clear input buffer to restore cin to a usable state
				std::cin.ignore(INT_MAX, '\n'); // ignore last input
				printf("U can only enter Numbers!\n");
				printf("Minutes ... = ");
				std::cin >> Minuten;
			}

			system("cls");

		} while (Minuten < 0 || Minuten > 59);

		//clear console again like above 
		system("cls");

		//"draw" everything again with the "new" information already given-> Hours : Minutes = ... : ...
		printf("**********************************************************************\n");
		printf("%d", Stunden);
		printf(":");

		//if Minutes is less than ten i draw a 0 before so we have 2 numbers ( just for better readability basically)
		if (Minuten < 10)
		{
			printf("0");
			printf("%d", Minuten);
		}
		//if Minutes is already greater than 10 we dont need to put the 0 (we already have 2 numbers)
		if (Minuten >= 10)
		{
			printf("%d", Minuten);
		}
		printf("\n");

		//repeat input until its betwen 59 and 0
		do
		{
			//guess what? we ask for the final input our seconds
			printf("Seconds ... = ");

			//we get our final input "seconds" here and whe are done askingg for shit and can move on 
			std::cin >> Sekunden;

			// input validation
			while (std::cin.fail())
			{
				std::cin.clear(); // clear input buffer to restore cin to a usable state
				std::cin.ignore(INT_MAX, '\n'); // ignore last input
				printf("U can only enter Numbers!\n");
				printf("Seconds ... = ");
				std::cin >> Sekunden;
			}

			system("cls");

		} while (Sekunden < 0 || Sekunden > 59);

		//we clear our console for the "last" time 
		system("cls");

		//finally we can "draw" our final "timer interface" that stays the same basically just ticks down till = 0:00:00
		printf("**********************************************************************\n");
		printf("%d", Stunden);
		printf(":");

		//if Minutes is less than ten i draw a 0 before so we have 2 numbers ( just for better readability basically)
		if (Minuten < 10)
		{
			printf("0");
			printf("%d", Minuten);
		}
		//if Minutes is already greater than 10 we dont need to put the 0 (we already have 2 numbers)
		if (Minuten >= 10)
		{
			printf("%d", Minuten);
		}
		printf(":");

		//here we just do the same for the seconds greater than ten add a 0 otherwhise ...
		if (Sekunden < 10)
		{
			printf("0");
			printf("%d", Sekunden);
		}
		if (Sekunden >= 10)
		{
			printf("%d", Sekunden);
		}
		printf("\n");


		//function that is actually running the timer doing the maths and stuff
		run_timer();

		if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
		{
			run = false;
		}

		bool SoundPlayed = PlaySound(MAKEINTRESOURCE(103), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_NODEFAULT);
		//std::cout << "\n\n\nPlayed Sound correctly : " << SoundPlayed;
		
		printf("\n\n\n\n\n\n\n\n\n\n");
		printf("\n\n\n\n\n\n\n\n");

		//wait until any key input 
		system("pause");
		//stop the sound after we press any key
		PlaySound(NULL, NULL, 0);

	}while (run == true);

	return 187;
}