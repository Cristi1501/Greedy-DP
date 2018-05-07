
build: frati ursi planificare numaratoare

frati:
	g++ -Wall -std=c++11 frati.cpp -o frati

ursi:
	g++ -Wall -std=c++11 ursi.cpp -o ursi

planificare:
	g++ -Wall -std=c++11 planificare.cpp -o planificare

numaratoare:
	g++ -Wall -std=c++11 numaratoare.cpp -o numaratoare

run-p1:
	./frati

run-p2:
	./ursi

run-p3:
	./planificare

run-p4:
	./numaratoare

clean:
	rm -rf frati ursi planificare numaratoare
