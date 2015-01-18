CCC = g++ -std=c++11 -Wall
BLD = build/
OBJ = $(BLD)obj/
BIN = $(BLD)bin/

all: IRCServer

IRCServer: main.o Protocol.o EnterProtocol.o ErrorProtocol.o MessageProtocol.o StandardProtocol.o ListProtocol.o IRCManager.o LoginHandler.o User.o Room.o Message.o WRSem.o
	$(CCC) $(OBJ)main.o $(OBJ)Protocol.o $(OBJ)EnterProtocol.o $(OBJ)ErrorProtocol.o $(OBJ)MessageProtocol.o $(OBJ)StandardProtocol.o $(OBJ)ListProtocol.o $(OBJ)IRCManager.o $(OBJ)LoginHandler.o $(OBJ)User.o $(OBJ)Room.o $(OBJ)Message.o $(OBJ)WRSem.o -o $(BIN)IRCServer -lpthread

main.o: main.cpp
	$(CCC) -c main.cpp -o $(OBJ)main.o

Protocol.o: Protocol.cpp
	$(CCC) -c Protocol.cpp -o $(OBJ)Protocol.o

EnterProtocol.o: EnterProtocol.cpp
	$(CCC) -c EnterProtocol.cpp -o $(OBJ)EnterProtocol.o

ErrorProtocol.o: ErrorProtocol.cpp
	$(CCC) -c ErrorProtocol.cpp -o $(OBJ)ErrorProtocol.o

MessageProtocol.o: MessageProtocol.cpp
	$(CCC) -c MessageProtocol.cpp -o $(OBJ)MessageProtocol.o

StandardProtocol.o: StandardProtocol.cpp
	$(CCC) -c StandardProtocol.cpp -o $(OBJ)StandardProtocol.o

ListProtocol.o: ListProtocol.cpp
	$(CCC) -c ListProtocol.cpp -o $(OBJ)ListProtocol.o

IRCManager.o: IRCManager.cpp
	$(CCC) -c IRCManager.cpp -o $(OBJ)IRCManager.o

Room.o: Room.cpp
	$(CCC) -c Room.cpp -o $(OBJ)Room.o

User.o: User.cpp
	$(CCC) -c User.cpp -o $(OBJ)User.o

LoginHandler.o: LoginHandler.cpp 
	$(CCC) -c LoginHandler.cpp -o $(OBJ)LoginHandler.o

Message.o: Message.cpp 
	$(CCC) -c Message.cpp -o $(OBJ)Message.o

WRSem.o: WRSem.cpp
	$(CCC) -c WRSem.cpp -o $(OBJ)WRSem.o

clean:
	rm -rf $(OBJ)*o build/bin/IRCServer