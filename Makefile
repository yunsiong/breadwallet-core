
test:	clean 
	cc -I. -I./support -I./secp256k1 -o $@ bitcoin/*.c bcash/*.c acash/*.c support/*.c

clean:
	rm -f *.o */*.o test

run:	test
	./test
