TEX = pdflatex
OPTS = -file-line-error

PANDOC = pandoc

# Do not use make's built-in rules and variables
MAKEFLAGS += -rR

ifeq ("$(origin O)", "command line")
  OUTPUT = $(O)
endif
ifdef OUTPUT
  OPTS += -output-directory $(O) 
endif

all: listing uml markdown markdown_without lualatex

lualatex: lualatex.pdf

lualatex.pdf: lualatex.tex
	lualatex lualatex.tex
	lualatex lualatex.tex

listing: listing.tex
	$(TEX) $(OPTS) listing.tex

uml: uml.tex
	$(TEX) $(OPTS) uml.tex

markdown: markdown.md
	$(PANDOC) --toc --highlight-style=kate markdown.md -o markdown.pdf

markdown_without: markdown_without.md
	$(PANDOC) -s -N --template=template.tex markdown_without.md -o markdown_without.pdf

clean: 
	rm -rf *.aux *.toc *.log *.lol

distclean: clean
	rm -rf *.pdf
