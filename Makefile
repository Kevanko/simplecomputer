all: 
	$(MAKE) -C myTerm
	$(MAKE) -C mySimpleComputer
	$(MAKE) -C console

clean:
	$(MAKE) clean -C myTerm
	$(MAKE) clean -C mySimpleComputer
	$(MAKE) clean -C console