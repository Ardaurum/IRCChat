# IRCChat
## Authors
* Radosław Paszkowski
* Andrzej Borowski

## Server
### Setup
Run server using ./IRCServer in terminal. 

Server will ask you for ip address and port to use (default: 127.0.0.1 6667).
If you want to setup your server on another ip address or port just write the
ip address and port when asked (after setup ip address and port cannot be changed).

### Basic Commands
* -q => shutdown server (will also logoff all users, clear data and end all threads).
* -u => prints all users that are currently connected to the server.
* -r => prints all currently existing rooms.
* -ur <room name> => prints all users in <room name> room.
* -k <user name> => kicks user <user name> from the room in which he is.
* -b <user name> => kicks user <user name> from server.

## Client
Run client using ./IRCClient in terminal

Enter the server's IP and port number in the appropriate textline.
Enter your user name and click the Connect button. If everything has been entered
correctly you should be welcomed to the server. Then you have a number of options;
Either create a new channel by typing it's name in the appropriate text line, join
an existing one by clicking it's name on the list and pressing the Join channel button,
or quit the server. Once in a channel you can send messages by typing them in the 
appropriate text line and pressing enter.
