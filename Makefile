NAME = ruben


all: personalDir OpenMp.c
	cd build_for_$(NAME); \
	gcc ../OpenMp.c -o OpenMp_$(NAME) -fopenmp 

personalDir: 
	mkdir build_for_$(NAME)

clean: 
	rm -rf build_for_$(NAME)
