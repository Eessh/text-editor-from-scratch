build:
	g++ -std=c++17 -O3 -g -Wall \
	main.cpp src/*.cpp \
	-o main \
	-lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives

run:
	./main

clean:
	rm ./main

build_run:
	g++ -c -std=c++17 -O3 -g -Wall \
	main.cpp src/*.cpp \
	&& \
	g++ *.o -o main \
	-lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives \
	&& \
	./main

default:
	g++ -std=c++17 -O3 -g -Wall \
	main.cpp src/*.cpp \
	-lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives \
	-o ./main \
	&& \
	./main \
	&& \
	rm ./main

build_simple:
	g++ -std=c++17 -O3 -g -Wall \
	main.cpp \
	-o main \
	-lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives