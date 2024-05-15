all: 
	$(MAKE) -C myReadKey
	$(MAKE) -C myBigChars
	$(MAKE) -C myTerm
	$(MAKE) -C mySimpleComputer
	$(MAKE) -C console

clean:
	$(MAKE) clean -C myReadKey
	$(MAKE) clean -C myBigChars
	$(MAKE) clean -C myTerm
	$(MAKE) clean -C mySimpleComputer
	$(MAKE) clean -C console

run:
	./console/bin/console
build:
	$(MAKE) run -C simplebasic
	$(MAKE) run -C simpleassembler