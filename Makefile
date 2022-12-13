all: out/sections sparc.pdf

SECTIONS = \
	sections/commands.tex	\
	sections/introduction.tex	\
	sections/electronics-voltage.tex	\
	sections/electronics-circuits.tex \
	sections/electronics-potential-difference.tex	\
	sections/electronics-resistance.tex	\
	sections/electronics-building-circuits.tex \
	sections/dialogues-with-computer-introduction.tex \
	sections/dialogues-with-computer-algorithms.tex \
	sections/dialogues-with-computer-arduino.tex \
	sections/dialogues-with-computer-memory.tex \
	sections/dialogues-with-computer-control-flow.tex \
	sections/dialogues-with-computer-arduino-ide.tex \
	sections/dialogues-with-computer-program-structure.tex \
	sections/white-noise-introduction.tex \
	sections/white-noise-analog-ports.tex \
	sections/white-noise-serial-port.tex	\
	sections/white-noise-signal-types.tex	\
	sections/white-noise-adc.tex \
	sections/white-noise-voltage-divider.tex	\
	sections/pwm-intro.tex \
	sections/pwm-duty-cycle.tex \
	sections/pwm-wavelength.tex	\
	sections/music-and-technology-synthesis-sound.tex \
	sections/music-and-technology-synthesis-speaker.tex \
	sections/music-and-technology-synthesis-bass-clef.tex \
	sections/appendix-octaves.tex

SECTIONS_OUT = \
	$(foreach section, $(SECTIONS), out/$(section))

out/sections:
	@[ -d out/sections ] || mkdir -p out/sections

out/sections/%.tex: sections/%.tex
	@echo "GEN $@" && lilypond-book --output out/sections/ --pdf $< > $@.log 2>&1

out/sparc.tex: sparc.tex $(SECTIONS_OUT)
	@echo "GEN out/sparc.tex" && lilypond-book --output out --pdf sparc.tex > out/sparc.tex.log 2>&1

sparc.pdf: sparc.tex out/sparc.tex
	@echo "PDF sparc.pdf" \
		&& cd out \
		&& ( xelatex --interaction=batchmode --shell-escape sparc.tex > sparc.pdf.log.1 2>&1; makeglossaries sparc; xelatex --shell-escape sparc.tex > sparc.pdf.log.2 2>&1 ) \
		&& cp sparc.pdf ../sparc.pdf

.PHONY: clean

clean:
	rm -rf out
	rm sparc.pdf
