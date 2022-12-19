compile:
	g++ -I ./headers main.cpp -o casting -lsfml-graphics -lsfml-window -lsfml-system && echo "Build completed Successfully"

run:
	./casting