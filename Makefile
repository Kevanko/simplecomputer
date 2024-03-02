all: 
	$(MAKE) -C mySimpleComputer
	$(MAKE) -C console

clean:
	$(MAKE) clean -C mySimpleComputer
	$(MAKE) clean -C console