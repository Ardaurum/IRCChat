CCC = g++ -std=c++11 -Wall
BLD = build/
OBJ = $(BLD)obj/
BIN = $(BLD)bin/
SRC = source/
PRO = $(SRC)protocols/

all: IRCServer

IRCServer: main.o Protocol.o EnterProtocol.o ErrorProtocol.o MessageProtocol.o StandardProtocol.o ListProtocol.o IRCManager.o LoginHandler.o User.o Room.o Message.o WRSem.o
	$(CCC) $(OBJ)main.o $(OBJ)Protocol.o $(OBJ)EnterProtocol.o $(OBJ)ErrorProtocol.o $(OBJ)MessageProtocol.o $(OBJ)StandardProtocol.o $(OBJ)ListProtocol.o $(OBJ)IRCManager.o $(OBJ)LoginHandler.o $(OBJ)User.o $(OBJ)Room.o $(OBJ)Message.o $(OBJ)WRSem.o -o $(BIN)IRCServer -lpthread

main.o: $(SRC)main.cpp
	$(CCC) -c $(SRC)main.cpp -o $(OBJ)main.o

Protocol.o: $(PRO)Protocol.cpp
	$(CCC) -c $(PRO)Protocol.cpp -o $(OBJ)Protocol.o

EnterProtocol.o: $(PRO)EnterProtocol.cpp
	$(CCC) -c $(PRO)EnterProtocol.cpp -o $(OBJ)EnterProtocol.o

ErrorProtocol.o: $(PRO)ErrorProtocol.cpp
	$(CCC) -c $(PRO)ErrorProtocol.cpp -o $(OBJ)ErrorProtocol.o

MessageProtocol.o: $(PRO)MessageProtocol.cpp
	$(CCC) -c $(PRO)MessageProtocol.cpp -o $(OBJ)MessageProtocol.o

StandardProtocol.o: $(PRO)StandardProtocol.cpp
	$(CCC) -c $(PRO)StandardProtocol.cpp -o $(OBJ)StandardProtocol.o

ListProtocol.o: $(PRO)ListProtocol.cpp
	$(CCC) -c $(PRO)ListProtocol.cpp -o $(OBJ)ListProtocol.o

IRCManager.o: $(SRC)IRCManager.cpp
	$(CCC) -c $(SRC)IRCManager.cpp -o $(OBJ)IRCManager.o

Room.o: $(SRC)Room.cpp
	$(CCC) -c $(SRC)Room.cpp -o $(OBJ)Room.o

User.o: $(SRC)User.cpp
	$(CCC) -c $(SRC)User.cpp -o $(OBJ)User.o

LoginHandler.o: $(SRC)LoginHandler.cpp 
	$(CCC) -c $(SRC)LoginHandler.cpp -o $(OBJ)LoginHandler.o

Message.o: $(SRC)Message.cpp 
	$(CCC) -c $(SRC)Message.cpp -o $(OBJ)Message.o

WRSem.o: $(SRC)WRSem.cpp
	$(CCC) -c $(SRC)WRSem.cpp -o $(OBJ)WRSem.o

clean:
	rm -rf $(OBJ)*o build/bin/IRCServer