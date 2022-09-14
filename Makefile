all: main.pdf

main.pdf: main.tex
	pdflatex $<

.PHONY: clean

clean:
	rm main.pdf
