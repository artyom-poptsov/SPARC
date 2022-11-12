all: out/sections main.pdf

SECTIONS = \
	sections/commands.tex	\
	sections/introduction.tex	\
	sections/electronics-voltage.tex	\
	sections/electronics-circuits.tex \
	sections/electronics-potential-difference.tex	\
	sections/electronics-resistance.tex	\
	sections/electronics-building-circuits.tex \
	sections/dialogues-with-computer-introduction.tex \
	sections/appendix-octaves.tex

SECTIONS_OUT = \
	$(foreach section, $(SECTIONS), out/$(section))

out/sections:
	@[ -d out/sections ] || mkdir -p out/sections

out/sections/%.tex: sections/%.tex
	@echo "GEN $@" && lilypond-book --output out/sections/ --pdf $< > $@.log 2>&1

out/main.tex: main.tex $(SECTIONS_OUT)
	@echo "GEN out/main.tex" && lilypond-book --output out --pdf main.tex > out/main.tex.log 2>&1

main.pdf: main.tex out/main.tex
	@echo "PDF main.pdf" \
		&& cd out \
		&& ( xelatex --interaction=batchmode --shell-escape main.tex; xelatex --shell-escape main.tex > main.pdf.log 2>&1 ) \
		&& cp main.pdf ../

.PHONY: clean

clean:
	rm -rf out
	rm main.pdf
