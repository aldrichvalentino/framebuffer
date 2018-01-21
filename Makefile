default:
	@gcc -o frame.exe main.c printChar.c printName.c

run:
	sudo ./frame.exe