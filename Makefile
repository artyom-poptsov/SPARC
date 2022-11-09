all: main.pdf

out/sections/electronics-circuits.tex: sections/electronics-circuits.tex
	lilypond-book --output out/sections/ --pdf sections/electronics-circuits.tex

out/sections/electronics-voltage.tex: sections/electronics-voltage.tex
	lilypond-book --output out/sections/ --pdf sections/electronics-voltage.tex

out/sections/appendix-octaves.tex: sections/appendix-octaves.tex
	lilypond-book --output out/sections/ --pdf sections/appendix-octaves.tex

out/sections/introduction.tex: sections/introduction.tex
	lilypond-book --output out/sections/ --pdf sections/introduction.tex

out/main.tex: main.tex out/sections/introduction.tex out/sections/appendix-octaves.tex out/sections/electronics-voltage.tex out/sections/electronics-circuits.tex
	lilypond-book --output out --pdf main.tex

main.pdf: main.tex out/main.tex
	cd out &&	xelatex --shell-escape main.tex && xelatex --shell-escape main.tex && cp main.pdf ../

.PHONY: clean

clean:
	rm -rf out
	rm main.pdf
