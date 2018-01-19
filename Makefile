default:
	@gcc -o frame.exe frame.c printChar.c printName.c

run:
	sudo ./frame.exe