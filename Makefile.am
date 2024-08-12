## Makefile.am -- Config file for GNU Automake.
##
## Copyright (C) 2024 Artyom V. Poptsov <poptsov.artyom@gmail.com>
##
## This file is part of SPARC book.
##
## This program is free software: you can redistribute it and/or
## modify it under the terms of the GNU General Public License as
## published by the Free Software Foundation, either version 3 of the
## License, or (at your option) any later version.
##
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

ACLOCAL_AMFLAGS = -I build-aux

SUBDIRS = .

all: sparc.pdf sparc.en.pdf

SECTIONS = \
	src/ru/sections/commands.tex	\
	src/ru/sections/introduction.tex	\
	src/ru/sections/electronics-voltage.tex	\
	src/ru/sections/electronics-circuits.tex \
	src/ru/sections/electronics-potential-difference.tex	\
	src/ru/sections/electronics-resistance.tex	\
	src/ru/sections/electronics-building-circuits.tex \
	src/ru/sections/dialogues-with-computer-title-image.tex \
	src/ru/sections/dialogues-with-computer-introduction.tex \
	src/ru/sections/dialogues-with-computer-algorithms.tex \
	src/ru/sections/dialogues-with-computer-arduino.tex \
	src/ru/sections/dialogues-with-computer-multimeter.tex \
	src/ru/sections/dialogues-with-computer-breadboard.tex \
	src/ru/sections/dialogues-with-computer-memory.tex \
	src/ru/sections/dialogues-with-computer-control-flow.tex \
	src/ru/sections/dialogues-with-computer-arduino-ide.tex \
	src/ru/sections/dialogues-with-computer-program-structure.tex \
	src/ru/sections/white-noise-introduction.tex \
	src/ru/sections/white-noise-analog-ports.tex \
	src/ru/sections/white-noise-serial-port.tex	\
	src/ru/sections/white-noise-signal-types.tex	\
	src/ru/sections/white-noise-adc.tex \
	src/ru/sections/white-noise-voltage-divider.tex	\
	src/ru/sections/pwm-intro.tex \
	src/ru/sections/pwm-duty-cycle.tex \
	src/ru/sections/pwm-wavelength.tex	\
	src/ru/sections/pwm-tasks.tex \
	src/ru/sections/music-and-technology-synthesis-sound.tex \
	src/ru/sections/music-and-technology-synthesis-speaker.tex \
	src/ru/sections/music-and-technology-synthesis-rhythm.tex \
	src/ru/sections/music-and-technology-synthesis-harmony.tex \
	src/ru/sections/music-and-technology-synthesis-octave-system.tex \
	src/ru/sections/music-and-technology-synthesis-simple-melodies.tex \
	src/ru/sections/music-and-technology-synthesis-arrays.tex \
	src/ru/sections/music-and-technology-synthesis-two-dimensional-arrays.tex \
	src/ru/sections/music-and-technology-synthesis-staff.tex \
	src/ru/sections/music-and-technology-synthesis-rest.tex \
	src/ru/sections/music-and-technology-synthesis-dotted-notes.tex	\
	src/ru/sections/music-and-technology-synthesis-flats-and-sharps.tex	\
	src/ru/sections/music-and-technology-synthesis-musical-scale.tex	\
	src/ru/sections/music-and-technology-synthesis-bass-clef.tex \
	src/ru/sections/music-and-technology-synthesis-music-band.tex \
	src/ru/sections/communication-intro.tex \
	src/ru/sections/communication-serial-port.tex \
	src/ru/sections/communication-i2c.tex \
	src/ru/sections/game-dev-intro.tex \
	src/ru/sections/game-dev-lcd.tex	\
	src/ru/sections/game-dev-genre-and-plot.tex	\
	src/ru/sections/game-dev-player.tex	\
	src/ru/sections/game-dev-buttons.tex	\
	src/ru/sections/game-dev-game-map.tex	\
	src/ru/sections/game-dev-sounds.tex	\
	src/ru/sections/game-dev-graphics.tex	\
	src/ru/sections/game-dev-animation.tex	\
	src/ru/sections/game-dev-logic.tex	\
	src/ru/sections/appendix-octaves.tex	\
	src/ru/sections/appendix-prostokvashino-score.tex \
	src/ru/sections/appendix-twinkle-twinkle-little-star-01.tex \
	src/ru/sections/appendix-twinkle-twinkle-little-star-02.tex

COMMIT = $(shell git rev-parse HEAD)


SECTIONS_OUT = \
	$(foreach section, $(SECTIONS), out/$(section))

out/src/ru/references.bib: src/references.bib
	@echo "CP        $< -> $@" \
		&& cp $< $@

out/src/ru/sparc-blx.bib: out/src/ru/references.bib out/src/ru/sparc.aux
	@echo "BIBTEX    $@" \
		&& cd out/src/ru/ \
		&& bibtex sparc

out/src/ru/version.tex: src/ru/version.tex.in
	@echo "GEN       $@" \
		&& sed "s/@COMMIT@/${COMMIT}/g; s/@VERSION@/$(PACKAGE_VERSION)/g" $< > $@

out/src/ru/sections/%.tex: src/ru/sections/%.tex
	@[ -d $(abs_top_srcdir)/out/src/ru/sections ] \
		|| mkdir -p $(abs_top_srcdir)/out/src/ru/sections
	@echo "LILYPOND  $< -> $@" \
		&& lilypond-book \
			--include $(abs_top_srcdir)/out/src/ru/ \
			--output $(abs_top_srcdir)/out/src/ru/sections/ \
			--pdf $< > $@.log 2>&1 \
		|| (cat $@.log; exit 1)

out/src/ru/sparc.tex: src/ru/sparc.tex $(SECTIONS_OUT) out/src/ru/version.tex
	@echo "LILYPOND  sparc.tex -> out/sparc.tex" \
		&& lilypond-book \
			--include $(abs_top_srcdir)/out/src/ru/ \
			--output $(abs_top_srcdir)/out/src/ru/ \
			--pdf $(abs_top_srcdir)/src/ru/sparc.tex > sparc.tex.log 2>&1 \
		|| (cat sparc.tex.log; exit 1)

make_glossary: out/src/ru/sparc.aux
	@echo "GLOSSARY  sparc" \
		&& cd out/src/ru/ \
		&& makeglossaries sparc > makeglossaries.log 2>&1 \
		|| (cat makeglossaries.log; exit 1)

make_index: out/src/ru/sparc.aux
	@echo "INDEX     sparc" \
		&& cd out/src/ru/ \
		&& makeindex sparc > makeindex.log 2>&1

out/src/ru/sparc.aux: src/ru/sparc.tex out/src/ru/sparc.tex out/src/ru/version.tex
	@echo "XELATEX   out/sparc.tex -> out/sparc.xdv" \
		&& cd out/src/ru/ \
		&& xelatex --interaction=batchmode --draftmode --no-pdf --shell-escape sparc.tex > sparc.pdf.log.1 2>&1 \
		|| (echo "---- sparc.pdf.log.1 ----"; cat sparc.pdf.log.1; echo "---- sparc.log ----"; cat sparc.log) && exit 0

out/src/ru/sparc.pdf: out/src/ru/sparc.aux make_glossary make_index out/src/ru/sparc-blx.bib
	@echo "XELATEX   out/sparc.tex -> out/sparc.pdf" \
	  && cd out/src/ru/ \
    && xelatex --shell-escape sparc.tex > sparc.pdf.log.2 2>&1 \
		|| cat sparc.pdf.log.2 && exit 0

sparc.pdf: out/src/ru/sparc.pdf
	@echo "COPY      sparc.pdf" \
		&& [ -e out/src/ru/sparc.pdf ] && cp out/src/ru/sparc.pdf sparc.pdf \
		|| ( echo "ERROR: File 'out/src/ru/sparc.pdf' not found" \
	       && exit 1 )

################################################################################
### English version

SECTIONS_EN = \
	src/en/sections/commands.tex \
	src/en/sections/introduction.tex \
	src/en/sections/electronics-introduction.tex

SECTIONS_OUT_EN = \
	$(foreach section, $(SECTIONS_EN), out/$(section))

out/src/en/references.bib: src/references.bib
	@echo "CP        $< -> $@" \
		&& cp $< $@

out/src/en/sparc-blx.bib: out/src/en/references.bib out/src/en/sparc.aux
	@echo "BIBTEX    $@" \
		&& cd out/src/en/ \
		&& bibtex sparc

out/src/en/version.tex: src/en/version.tex.in
	@[ -d $(abs_top_srcdir)/out/src/en/ ] \
		|| mkdir -p $(abs_top_srcdir)/out/src/en/ \
	@echo "GEN       $@" \
		&& sed "s/@COMMIT@/${COMMIT}/g;  s/@VERSION@/$(PACKAGE_VERSION)/g" $< > $@

make_glossary_en: out/src/en/sparc.aux
	@echo "GLOSSARY  sparc" \
		&& cd out/src/en/ \
		&& makeglossaries sparc > makeglossaries.log 2>&1 \
		|| (cat makeglossaries.log; exit 1)

make_index_en: out/src/en/sparc.aux
	@echo "INDEX     sparc.en" \
		&& cd out/src/en/ \
		&& makeindex sparc > makeindex.log 2>&1

out/src/en/sections/%.tex: src/en/sections/%.tex
	@[ -d $(abs_top_srcdir)/out/src/en/sections ] \
		|| mkdir -p $(abs_top_srcdir)/out/src/en/sections
	@echo "LILYPOND  $< -> $@" \
		&& lilypond-book \
			--include $(abs_top_srcdir)/out/src/en/ \
			--output $(abs_top_srcdir)/out/src/en/sections/ \
			--pdf $< > $@.log 2>&1 \
		|| (cat $@.log; exit 1)

out/src/en/sparc.tex: src/en/sparc.tex $(SECTIONS_OUT_EN) out/src/en/version.tex
	@echo "LILYPOND  src/en/sparc.tex -> out/src/en/sparc.tex" \
		&& lilypond-book \
			--include $(abs_top_srcdir)/out/src/en/ \
			--output $(abs_top_srcdir)/out/src/en/ \
			--pdf $(abs_top_srcdir)/src/en/sparc.tex > sparc.tex.log 2>&1 \
	|| (cat sparc.tex.log; exit 1)

out/src/en/sparc.aux: src/en/sparc.tex out/src/en/sparc.tex out/src/en/version.tex
	@echo "XELATEX   out/en/sparc.tex -> out/en/sparc.xdv" \
		&& cd out/src/en/ \
		&& xelatex \
			--interaction=batchmode \
			--draftmode \
			--no-pdf \
			--shell-escape sparc.tex > sparc.pdf.log.1 2>&1 \
		|| (echo "---- sparc.pdf.log.1 ----"; \
			cat sparc.pdf.log.1; \
			echo "---- sparc.log ----"; \
			cat sparc.log) \
		&& exit 0

out/src/en/sparc.pdf: out/src/en/sparc.aux make_glossary make_index out/src/en/sparc-blx.bib
	@echo "XELATEX   out/src/en/sparc.tex -> out/src/en/sparc.pdf" \
		&& cd out/src/en/ \
		&& xelatex --shell-escape sparc.tex > sparc.pdf.log.2 2>&1 \
		|| cat sparc.pdf.log.2 && exit 0

sparc.en.pdf: out/src/en/sparc.pdf
	@echo "COPY      sparc.en.pdf" \
		&& [ -e out/src/en/sparc.pdf ] && cp out/src/en/sparc.pdf sparc.en.pdf \
		|| ( echo "ERROR: File 'out/src/en/sparc.pdf' not found" \
			&& exit 1 )

.PHONY: clean-local

clean-local:
	rm -rf out
	rm sparc.pdf

