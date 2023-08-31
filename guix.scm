;; guix.scm --- GNU Guix package recipe    -*- coding: utf-8 -*-
;;
;; Copyright (C) 2022-2023 Artyom V. Poptsov <poptsov.artyom@gmail.com>
;;
;; Author: Artyom V. Poptsov <poptsov.artyom@gmail.com>
;; Created: 17 November 2022
;;
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; The program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with the program.  If not, see <http://www.gnu.org/licenses/>.


;;; Commentary:
;;
;; GNU Guix development package. To use as the basis for a development
;; environment, run:
;;
;;  guix shell -D -f ./guix.scm
;;
;; In the new shell, run:
;;
;;  make
;;
;;; Code:


(use-modules (guix gexp)
             (guix packages)
             (guix licenses)
             (guix git-download)
             (guix build-system copy)
             (gnu packages base)
             (gnu packages bash)
             (gnu packages tex)
             (gnu packages texlive)
             (gnu packages inkscape)
             (gnu packages fonts)
             (gnu packages perl)
             (gnu packages python-xyz)
             (gnu packages version-control)
             (gnu packages fontutils)
             (gnu packages music))


(define %source-dir (dirname (current-filename)))


(define-public book-sparc
  (package
   (name "book-sparc")
   (version "git")
   (source (local-file %source-dir
                       #:recursive? #t
                       #:select? (git-predicate %source-dir)))
   (build-system copy-build-system)
   (native-inputs
    (list python-pygments
          bash-minimal
          perl
          which
          fontconfig))
   (inputs
    (list font-liberation
          git
          gnu-make
          inkscape
          lilypond
          texlive-fontspec
          texlive-koma-script
          texlive-trimspaces
          texlive-acronym
          texlive-adjustbox
          texlive-bibtex
          texlive-bibtexperllibs
          texlive-bigfoot
          texlive-circuitikz
          texlive-collection-langcyrillic
          texlive-glossaries
          texlive-glossaries-extra
          texlive-lilyglyphs
          texlive-minted
          texlive-multirow
          texlive-pgf
          texlive-pgfplots
          texlive-subfiles
          texlive-svg
          texlive-t1utils
          texlive-textpos
          texlive-transparent
          texlive-xetex))
   (arguments
    (list #:install-plan #~'(("sparc.pdf" "share/doc/sparc/"))
          #:phases #~(modify-phases %standard-phases
                       (delete 'check)
                       (delete 'configure)
                       (add-before 'install 'build
                         (lambda* (#:key inputs make-flags parallel-build? #:allow-other-keys)
                           (use-modules (ice-9 regex)
                                        (srfi srfi-1))
                           (let* ((src (assoc-ref inputs "source"))
                                  (rx  (make-regexp "/gnu/store/(.*)-SPARC"))
                                  (src-hash (match:substring (regexp-exec rx src) 1))
                                  (random-seed
                                   (fold (lambda (ch prev)
                                           (+ (char->integer ch)
                                              prev))
                                         0
                                         (string->list src-hash))))
                             (setenv "RANDOMSEED" (number->string random-seed))
                             (setenv "REPRODUCIBILITY" "yes"))
                           (invoke "make"
                                   "-j"
                                   (if parallel-build?
                                       (number->string (parallel-job-count))
                                       "1")))))))
   (home-page "https://github.com/artyom-poptsov/SPARC")
   (synopsis "Book on combining art and technology")
   (description
    "Science, Programming, Art and Radioelectronics Club (SPARC) is a book that
explains how to combine the topics mentined in the title to build projects.  The
book can be used to teach programming classes in colleges and to organize
workshops in hackerspaces or other community-driven spaces.  Currently the book
is available only in Russian.")
   (license cc-by-sa4.0)))

book-sparc

;;; guix.scm ends here.
