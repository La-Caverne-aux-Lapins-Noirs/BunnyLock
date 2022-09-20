## Black Bunnies Cavern -------------    ---  -- --- -    ---  --    - -- -   -
## Hanged Bunny Studio 2014-2022 ----- -- - -- -  -  -- -- - -- --  -- -- -- --
## ----------------------------------- -- -    - - - -- -- - -- ---- -    -- --
## ----------------------------------    -- -- - --- -    ---  --   -- -- -   -
## Bunny Lock -----------------------------------------------------------------

## ----------------------------------------------------------------------------
## Configuration --------------------------------------------------------------

  BIN		=	bunny_lock
  FLAG		=	-W -Wall -I./include/ -g -g3 -ggdb # -O2 -ffast-math

  SRC		=	$(wildcard src/*.c)
  OBJ		=	$(SRC:.c=.o)
  LIB		=	-L$(HOME)/.froot/lib/ -llapin -lsfml-graphics -lsfml-audio -lsfml-window	\
			-lsfml-system -lstdc++ -lm -ldl -lpthread -lavcall

  ## Rules ------------------------------------------------------------------
  all:		bin
  bin:		$(OBJ)
		@gcc $(OBJ) -o $(BIN) $(LIBPATH) $(LIB)
		@echo "[OUT] " $(BIN)
		@echo $(BIN) | tr '[:lower:]' '[:upper:]'
  .c.o:
		@gcc $(FLAG) -c $< -o $@
		@echo "[GCC]" $<
  clean:
		@rm -f $(OBJ)
  fclean:	clean
		@rm -f $(BIN)
  re:		fclean all
  install:
		apt-get install xtrlock
		cp $(BIN) /usr/local/bin
		cp block /usr/local/bin

## ----------------------------------------------------------------------------
## MISC -----------------------------------------------------------------------

  .PHONY: all clean fclean re

  .SUFFIXES: .cpp .o
