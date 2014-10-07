CC = dot

CCFLAGS = -Tpdf

% : %.dot
	$(CC) $(CCFLAGS) $< -o $@.pdf

clean:
	@rm -f *~ *.pdf
