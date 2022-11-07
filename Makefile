all: main.pdf

out/sections/introduction.tex: sections/introduction.tex
	lilypond-book --output out/sections/ --pdf sections/introduction.tex

out/main.tex: main.tex out/sections/introduction.tex
	lilypond-book --output out --pdf main.tex

main.pdf: main.tex out/main.tex
	cd out &&	xelatex --shell-escape main.tex && xelatex --shell-escape main.tex && cp main.pdf ../

.PHONY: clean

clean:
	rm -rf out
	rm main.pdf
