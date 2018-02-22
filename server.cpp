#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include <cstdlib>
#include <string.h>

using namespace std;
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

int main()
{




char username[128] = "bts530", password[128] = "1234";	/* User name and password to verify */

	struct sockaddr_in SvrAddr;
	int WelcomeSocket, ConnectionSocket;

	//Data buffers
	char RxBuffer[128] = {};

	//create welcoming socket at port and bind local address
	if ((WelcomeSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return 1;

	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = INADDR_ANY;
	SvrAddr.sin_port = htons(27000);

	if ((bind(WelcomeSocket, (struct sockaddr *)&SvrAddr,
sizeof(SvrAddr))) == SOCKET_ERROR)
	{
		close(WelcomeSocket);
		
		return 1;
	}

	//Specify the maximum number of clients that can be queued
	if (listen(WelcomeSocket, 1) == SOCKET_ERROR)
	{
		close(WelcomeSocket);
		return 1;
	}

	std::cout << "Waiting for client connection\n" << std::endl;
	ConnectionSocket = SOCKET_ERROR;

	while (1)
	{

		char tempUsername[128] = { '\0' }, tempPassword[128] = { '\0' };
			int logincounter = 3;


		//wait for an incoming connection from a client
		if ((ConnectionSocket = accept(WelcomeSocket, NULL, NULL)) == SOCKET_ERROR)
		{
			return 1;
		}
		else
		{
			std::cout << "Connection Established" << std::endl;


send(ConnectionSocket, "Enter username: \0", sizeof("Enter username: \0"), 0);

		recv(ConnectionSocket, tempUsername, sizeof(tempUsername), 0);					/* Receive the username */
																						//std::cout << "Username entered: " << tempUsername << std::endl;

		send(ConnectionSocket, "Enter password: \0", sizeof("Enter password: \0"), 0);

		recv(ConnectionSocket, tempPassword, sizeof(tempPassword), 0);					/* Receive the password */
																			
		while (logincounter != 0)
		{
			if ((strcmp(username, tempUsername) == 0) && (strcmp(password, tempPassword) == 0))	/* Does the entered username and password match? */
			{
				send(ConnectionSocket, "User has successfully authenticated!\0", sizeof("User has successfully authenticated!\0"), 0);
				break;
			}
			else
			{
				send(ConnectionSocket, "Invalid password. Please retry: \0", sizeof("Invalid password. Please retry:\0"), 0);
				recv(ConnectionSocket, tempPassword, sizeof(tempPassword), 0);
				logincounter--;
			}
		}

		if (logincounter == 0)					/* The user entered too many incorrect attempts */
		{
			send(ConnectionSocket, "Too many invalid password attempts. Connection closing!\0", sizeof("Too many invalid password attempts. Connection closing!\0"), 0);
			close(ConnectionSocket);		/* Close the first connection socket on the server that's responsible for the main process */
		}
		else
		{


                std::cout << "3-Axis beagle-Bone Menu" << std::endl;
                std::cout << "+++++++++++++++++++++++" << std::endl;
                std::cout << "Up    (LED 1) ->  1" << std::endl;
                std::cout << "Down  (LED 2) ->  2" << std::endl;
 	            std::cout << "Left  (LED 3) ->  3" << std::endl;
                std::cout << "Right (LED 4) ->  4" << std::endl;


          FILE  *LEDHandle = NULL;

	  char  *LED_0 = "/sys/class/leds/beaglebone:green:usr0/brightness";
	  char  *LED_1 = "/sys/class/leds/beaglebone:green:usr1/brightness";
	  char  *LED_2 = "/sys/class/leds/beaglebone:green:usr2/brightness";
	  char  *LED_3 = "/sys/class/leds/beaglebone:green:usr3/brightness";

    


			while (1)
			{
				int n = recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
				std::cout << "Msg Rx: " << RxBuffer << std::endl;

				//Check to see if connection should be terminated
				if (RxBuffer[0] == 'x')
					break;

				if (RxBuffer[0] == '1')
			{
					std::cout << "up" << std::endl;

                 std::cout << "X - axis " << std::endl;

                 FILE *export_file = NULL; //declare pointers
                   FILE *IO_direction = NULL;
                   FILE *IO_value = NULL;
                   char str1[] = "0";
                   char str2[] = "1";
                   char str3[] = "out";
                   char str[] = "60";
                   //this part here exports gpio23
                   export_file = fopen ("/sys/class/gpio/export", "w");
                   fwrite (str, 1, sizeof(str), export_file);
                   fclose (export_file);
                   //this part here sets the direction of the pin
                   IO_direction = fopen("/sys/class/gpio/gpio60/direction", "w");
                   fwrite(str3, 1, sizeof(str3), IO_direction); //set the pin to HIGH
                   fclose(IO_direction);
                   usleep (1000000);

                  // for (int i=0; i<10; i++){ //blink LED 10 times
                        IO_value = fopen ("/sys/class/gpio/gpio60/value", "w");
                        fwrite (str2, 1, sizeof(str2), IO_value); //set the pin to HIGH
                        fclose (IO_value);
                       // usleep (1000000); //delay for a second






  					  if((LEDHandle = fopen(LED_0,"r+")) !=NULL)
  					{

  						fwrite("1", sizeof(char), 1 , LEDHandle);
  						fclose(LEDHandle);

  					}

  					  if((LEDHandle = fopen(LED_1,"r+")) !=NULL)
  							{

  								fwrite("0", sizeof(char), 1 , LEDHandle);
  								fclose(LEDHandle);

  							}

  					  if((LEDHandle = fopen(LED_2,"r+")) !=NULL)
  							{

  								fwrite("0", sizeof(char), 1 , LEDHandle);
  								fclose(LEDHandle);

  							}

  					  if((LEDHandle = fopen(LED_3,"r+")) !=NULL)
  							{

  								fwrite("0", sizeof(char), 1 , LEDHandle);
  								fclose(LEDHandle);

  							}








			};


                if (RxBuffer[0] == '2')
			{

	std::cout << "down" << std::endl;

 std::cout << "Y - axis " << std::endl;




 FILE *export_file = NULL; //declare pointers
   FILE *IO_direction = NULL;
   FILE *IO_value = NULL;
   char str1[] = "0";
   char str2[] = "1";
   char str3[] = "out";
   char str[] = "30";
   //this part here exports gpio23
   export_file = fopen ("/sys/class/gpio/export", "w");
   fwrite (str, 1, sizeof(str), export_file);
   fclose (export_file);
   //this part here sets the direction of the pin
   IO_direction = fopen("/sys/class/gpio/gpio30/direction", "w");
   fwrite(str3, 1, sizeof(str3), IO_direction); //set the pin to HIGH
   fclose(IO_direction);
   usleep (1000000);

  // for (int i=0; i<10; i++){ //blink LED 10 times
        IO_value = fopen ("/sys/class/gpio/gpio30/value", "w");
        fwrite (str2, 1, sizeof(str2), IO_value); //set the pin to HIGH
        fclose (IO_value);
       // usleep (1000000); //delay for a second




	  for(int i = 0 ; i<10; i++)
	  {

		  if((LEDHandle = fopen(LED_1,"r+")) !=NULL)
		{

			fwrite("1", sizeof(char), 1 , LEDHandle);
			fclose(LEDHandle);

		}



		  if((LEDHandle = fopen(LED_0,"r+")) !=NULL)
						{

							fwrite("0", sizeof(char), 1 , LEDHandle);
							fclose(LEDHandle);

						}

				  if((LEDHandle = fopen(LED_2,"r+")) !=NULL)
						{

							fwrite("0", sizeof(char), 1 , LEDHandle);
							fclose(LEDHandle);

						}

				  if((LEDHandle = fopen(LED_3,"r+")) !=NULL)
						{

							fwrite("0", sizeof(char), 1 , LEDHandle);
							fclose(LEDHandle);

						}






	  }
	           };

                if (RxBuffer[0] == '3')
			{

                	std::cout << "left" << std::endl;
 std::cout << "Z - axis " << std::endl;




 FILE *export_file = NULL; //declare pointers
   FILE *IO_direction = NULL;
   FILE *IO_value = NULL;
   char str1[] = "0";
   char str2[] = "1";
   char str3[] = "out";
   char str[] = "51";
   //this part here exports gpio23
   export_file = fopen ("/sys/class/gpio/export", "w");
   fwrite (str, 1, sizeof(str), export_file);
   fclose (export_file);
   //this part here sets the direction of the pin
   IO_direction = fopen("/sys/class/gpio/gpio51/direction", "w");
   fwrite(str3, 1, sizeof(str3), IO_direction); //set the pin to HIGH
   fclose(IO_direction);
   usleep (1000000);

  // for (int i=0; i<10; i++){ //blink LED 10 times
        IO_value = fopen ("/sys/class/gpio/gpio51/value", "w");
        fwrite (str2, 1, sizeof(str2), IO_value); //set the pin to HIGH
        fclose (IO_value);
       // usleep (1000000); //delay for a second


                                       

          		  if((LEDHandle = fopen(LED_2,"r+")) !=NULL)
          		{

          			fwrite("1", sizeof(char), 1 , LEDHandle);
          			fclose(LEDHandle);

          		}

    			  if((LEDHandle = fopen(LED_1,"r+")) !=NULL)
    							{

    								fwrite("0", sizeof(char), 1 , LEDHandle);
    								fclose(LEDHandle);

    							}

    					  if((LEDHandle = fopen(LED_0,"r+")) !=NULL)
    							{

    								fwrite("0", sizeof(char), 1 , LEDHandle);
    								fclose(LEDHandle);

    							}

    					  if((LEDHandle = fopen(LED_3,"r+")) !=NULL)
    							{

    								fwrite("0", sizeof(char), 1 , LEDHandle);
    								fclose(LEDHandle);

    							}




			};

                if (RxBuffer[0] == '4')
			{
                	std::cout << "right" << std::endl;







          		  if((LEDHandle = fopen(LED_3,"r+")) !=NULL)
          		{

          			fwrite("1", sizeof(char), 1 , LEDHandle);
          			fclose(LEDHandle);

          		}


    			  if((LEDHandle = fopen(LED_1,"r+")) !=NULL)
    							{

    								fwrite("0", sizeof(char), 1 , LEDHandle);
    								fclose(LEDHandle);

    							}

    					  if((LEDHandle = fopen(LED_2,"r+")) !=NULL)
    							{

    								fwrite("0", sizeof(char), 1 , LEDHandle);
    								fclose(LEDHandle);

    							}

    					  if((LEDHandle = fopen(LED_0,"r+")) !=NULL)
    							{

    								fwrite("0", sizeof(char), 1 , LEDHandle);
    								fclose(LEDHandle);

    							}




			};



			}

}

			close(ConnectionSocket);
		}
	}

	return 1;
}


