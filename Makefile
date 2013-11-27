nop:
	@echo "why not 'make all' huh? :)"

all: 
	g++ src/trojan/main.cpp -lwsock32 -s -mwindows -o build/trojan.exe
	g++ src/controller/main.cpp -lwsock32 -o build/controller.exe
