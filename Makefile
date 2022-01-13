
OBJS=	meowsay.o scanner.o

meowsay: $(OBJS) cats.h
	$(CC) $(CFLAGS) -o $@ $(OBJS)

meowsay.o: cats.h

cats.h: longcat.txt pusheen.txt nyan.txt
	echo $^ | xargs -n1 xxd -i > $@


run: meowsay
	./meowsay
clean:
	rm meowsay $(OBJS) cats.h

.PHONY: run clean
