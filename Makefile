binary: prod_cons.c
	gcc $< -pthread -o $@

.PHONY: run clean

run:
	./binary

clean:
	rm binary