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
	sections/music-and-technology-synthesis-rhythm.tex \
	sections/music-and-technology-synthesis-harmony.tex \
	sections/music-and-technology-synthesis-octave-system.tex \
	sections/music-and-technology-synthesis-simple-melodies.tex \
	sections/music-and-technology-synthesis-arrays.tex \
	sections/music-and-technology-synthesis-two-dimensional-arrays.tex \
	sections/music-and-technology-synthesis-rest.tex \
	sections/music-and-technology-synthesis-dotted-notes.tex	\
	sections/music-and-technology-synthesis-flats-and-sharps.tex	\
	sections/music-and-technology-synthesis-musical-scale.tex	\
	sections/music-and-technology-synthesis-bass-clef.tex \
	sections/music-and-technology-synthesis-music-band.tex \
	sections/game-dev-intro.tex \
	sections/game-dev-lcd.tex	\
	sections/game-dev-genre-and-plot.tex	\
	sections/game-dev-player.tex	\
	sections/game-dev-buttons.tex	\
	sections/game-dev-game-map.tex	\
	sections/game-dev-sounds.tex	\
	sections/game-dev-graphics.tex	\
	sections/game-dev-animation.tex	\
	sections/game-dev-logic.tex	\
	sections/appendix-octaves.tex	\
	sections/appendix-melody-00.tex

COMMIT = $(shell git rev-parse HEAD)


SECTIONS_OUT = \
	$(foreach section, $(SECTIONS), out/$(section))

out/version.tex: version.tex.in
	@echo "GEN $@" && sed "s/@COMMIT@/${COMMIT}/g" $< > $@

out/sections:
	@[ -d out/sections ] || mkdir -p out/sections

out/sections/%.tex: sections/%.tex
	@echo "GEN $@" \
		&& lilypond-book --output out/sections/ --pdf $< > $@.log 2>&1

out/sparc.tex: sparc.tex $(SECTIONS_OUT) out/version.tex
	@echo "GEN out/sparc.tex" \
		&& lilypond-book --output out --pdf sparc.tex > out/sparc.tex.log 2>&1

make_glossary: out/sparc.aux
	@echo "GLS sparc" \
		&& cd out \
		&& makeglossaries sparc > makeglossaries.log 2>&1

make_index: out/sparc.aux
	@echo "IDX sparc" \
		&& cd out \
		&& makeindex sparc > makeindex.log 2>&1

out/sparc.aux: sparc.tex out/sparc.tex out/version.tex
	@echo "XELATEX out/sparc.tex" \
		&& cd out \
		&& xelatex --interaction=batchmode --shell-escape sparc.tex > sparc.pdf.log.1 2>&1 \
		|| exit 0

out/sparc.pdf: out/sparc.aux make_glossary make_index
	@echo "XELATEX out/sparc.pdf" \
	  && cd out \
    && xelatex --shell-escape sparc.tex > sparc.pdf.log.2 2>&1

sparc.pdf: out/sparc.pdf
	@echo "COPY sparc.pdf" && cp out/sparc.pdf sparc.pdf

.PHONY: clean

clean:
	rm -rf out
	rm sparc.pdf
