all: main
	mkdir -p output
	cat input/a_example.txt | ./main > output/a.txt
	cat input/b_read_on.txt | ./main > output/b.txt
	cat input/c_incunabula.txt | ./main > output/c.txt
	cat input/d_tough_choices.txt | ./main > output/d.txt
	cat input/e_so_many_books.txt | ./main > output/e.txt
	cat input/f_libraries_of_the_world.txt | ./main > output/f.txt

main: main.cpp
	g++ main.cpp -O3 -o main

clean:
	rm -f main
	rm -rf output
