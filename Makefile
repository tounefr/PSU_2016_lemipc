##
## Makefile for  in /home/linder/cours/system unix/PSU_2016_lemipc
## 
## Made by linder
## Login   <linder@epitech.net>
## 
## Started on  Tue Mar 28 10:55:35 2017 linder
## Last update Tue Mar 28 12:01:27 2017 linder
##

LEMIPC_NAME = lemipc

LEMIPC_SHARED_NAME = liblemipc_shared.so

GUI_SDL_NAME = gui_sdl

GUI_CLI_NAME = gui_cli

$(LEMIPC_NAME):
	$(MAKE) -C src/core/ re
	mv src/core/a.out ./$(LEMIPC_NAME)

$(LEMIPC_SHARED_NAME):
	$(MAKE) -C src/common re
	mv src/common/a.out ./$(LEMIPC_SHARED_NAME)

$(GUI_SDL_NAME):
	$(MAKE) -C src/gui/sdl re
	mv src/gui/sdl/a.out ./$(GUI_SDL_NAME)

$(GUI_CLI_NAME):
	$(MAKE) -C src/gui/cli re
	mv src/gui/cli/a.out ./$(GUI_CLI_NAME)

all: re

re: $(LEMIPC_SHARED_NAME) $(LEMIPC_NAME) $(GUI_CLI_NAME)

fclean:
	$(MAKE) -C src/core fclean
	$(MAKE) -C src/common fclean
#	$(MAKE) -C src/gui/sdl fclean
#	$(MAKE) -C src/gui/cli fclean
	rm $(LEMIPC_NAME)
	rm $(LEMIPC_SHARED_NAME)
	rm $(GUI_CLI_NAME)

clean:
	$(MAKE) -C src/core clean
	$(MAKE) -C src/common clean
#	$(MAKE) -C src/gui/sdl clean
#	$(MAKE) -C src/gui/cli clean

.PHONY: re fclean clean
