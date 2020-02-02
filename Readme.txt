Command to install libraries :
sudo apt-get install mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev

To compile:
g++ file_name.cpp -o gl -lGL -lGLU -lglut

To run:
./gl
