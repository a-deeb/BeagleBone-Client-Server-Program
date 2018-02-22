#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> //inet_addr
#include <netdb.h>
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
	struct sockaddr_in SvrAddr;
	int ClientSocket;

	if ((ClientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return 1;

	struct hostent *host;
	if ((host = gethostbyname("localhost")) == NULL)
	{
		cout << "ERROR:  Failed to resolve local host" << endl;
		return(1);	//terminate the program
	}
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_port = htons(27000);
	
        //SvrAddr.sin_addr.s_addr = in_addr_t("192.168.7.2");
        //SvrAddr.sin_addr.s_addr = inet_addr("192.168.7.2");
       SvrAddr.sin_addr.s_addr = *((unsigned long *)host->h_addr_list[0]);

        bind(ClientSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr));

	//Connect socket to specified server
	if ((connect(ClientSocket, (struct sockaddr *)&SvrAddr, 
sizeof(SvrAddr))) == SOCKET_ERROR)
	{
		close(ClientSocket);
		return 1;
	}

	char TxBuffer[50] = { "\n" };
            char  rxBuffer[128] = { '\0' };



for (;;)
	{
		 

		recv(ClientSocket, rxBuffer, sizeof(rxBuffer), 0);	/* Server asks for the username */
		std::cout << rxBuffer;
		std::cin.getline(TxBuffer, 128);					/* Get the username from the client */
		send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);	/* Send the username to the server for validation */

		memset(rxBuffer, 0, 128);
		recv(ClientSocket, rxBuffer, sizeof(rxBuffer), 0);	/* Server asks for the password - FIRST ATTEMPT */
		std::cout << rxBuffer;
		memset(TxBuffer, 0, 128);

		std::cin.getline(TxBuffer, 128);					/* Get the password from the client */
		send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);

		for (;;)
		{
			memset(rxBuffer, 0, 128);
			recv(ClientSocket, rxBuffer, sizeof(rxBuffer), 0);			/* Get the message from the server - regardless if the password is invalid or not */
			std::cout << rxBuffer;

			if (strcmp(rxBuffer, "Invalid password. Please retry: \0") == 0)
			{
				std::cin.getline(TxBuffer, 128);						/* Get the password from the client as it was incorrect the first time */
				send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);		/* Send the password to the server for validation again */
			}
			else if (strcmp(rxBuffer, "User has successfully authenticated!\0") == 0)		/* The user has been validated properly! Break from the login loop */
			{
				std::cout << std::endl;						/* Format output for easier readability */
				break;
			}
			else if (strcmp(rxBuffer, "Too many invalid password attempts. Connection closing!\0") == 0)
			{
				close(ClientSocket);
				std::cin.get();
				exit(0);
			}
		}

		


	while (1)
	{


                std::cout << "3-Axis beagle-Bone Menu" << std::endl;
                std::cout << "+++++++++++++++++++++++" << std::endl;
                std::cout << "Up    (LED 1) ->  1" << std::endl;
                std::cout << "Down  (LED 2) ->  2" << std::endl;
 	        std::cout << "Left  (LED 3) ->  3" << std::endl;
                std::cout << "Right (LED 4) ->  4" << std::endl;




		cout << "Enter A String (x to terminate)" << endl;
		cin >> TxBuffer;
		

                   

		if (TxBuffer[0] == 'x')
                   {   

			cout << "GoodBye ! ! " << endl;
			break;
			}
  


		send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);	


	}

}

	close(ClientSocket);
}

