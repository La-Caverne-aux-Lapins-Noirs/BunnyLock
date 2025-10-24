## Black Bunnies Cavern -------------    ---  -- --- -    ---  --    - -- -   -
## Hanged Bunny Studio 2014-2022 ----- -- - -- -  -  -- -- - -- --  -- -- -- --
## ----------------------------------- -- -    - - - -- -- - -- ---- -    -- --
## ----------------------------------    -- -- - --- -    ---  --   -- -- -   -
## Bunny Lock -----------------------------------------------------------------

## ----------------------------------------------------------------------------
## Configuration --------------------------------------------------------------

  BIN		=	bunny_lock
  FLAG		=	-W -Wall -I./include/ -I../LibLapin/include/  -O2 -ffast-math # -g -g3 -ggdb #

  SRC		=	$(wildcard src/*.c)
  OBJ		=	$(SRC:.c=.o)

  ## Rules ------------------------------------------------------------------
  all:		bin
  bin:		$(OBJ)
		@bcc $(OBJ) -o $(BIN) $(LIBPATH) $(LIB)
		@echo "[OUT] " $(BIN)
		@echo $(BIN) | tr '[:lower:]' '[:upper:]'
  .c.o:
		@bcc $(FLAG) -c $< -o $@
		@echo "[GCC]" $<
  clean:
		@rm -f $(OBJ)
  fclean:	clean
		@rm -f $(BIN)
  re:		fclean all
  install:
		cp $(BIN) /usr/local/bin
		cp block /usr/local/bin
  package:
		dpkg-buildpackage -us -uc

## ----------------------------------------------------------------------------
## MISC -----------------------------------------------------------------------

  .PHONY: all clean fclean re

  .SUFFIXES: .cpp .o
