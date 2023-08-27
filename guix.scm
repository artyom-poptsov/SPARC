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
             (guix build-system gnu)
             (gnu packages base)
             (gnu packages bash)
             (gnu packages tex)
             (gnu packages texlive)
             (gnu packages inkscape)
             (gnu packages fonts)
             (gnu packages perl)
             (gnu packages python-xyz)
             (gnu packages version-control)
             (gnu packages music))


(define %source-dir (dirname (current-filename)))


(package
 (name "sparc-book")
 (version "git")
 (source (local-file %source-dir
                     #:recursive? #t
                     #:select? (git-predicate %source-dir)))
 (build-system gnu-build-system)
 (native-inputs
  (list python-pygments
        bash-minimal
        perl
        which))
 (inputs
  (list gnu-make
        git
        texlive
        texlive-latex-fonts
        texlive-minted
        texlive-bibtex
        texlive-xetex
        texlive-collection-langcyrillic
        texlive-t1utils
        texlive-ttfutils
        texlive-bibtexperllibs
        inkscape
        lilypond
        font-liberation))
 (arguments
  (list #:phases
        #~(modify-phases %standard-phases
            (delete 'configure))))
 (home-page "https://github.com/artyom-poptsov/SPARC")
 (synopsis "Book on combining art and technology")
 (description
  "Science, Programming, Art and Radioelectronics Club (SPARC) is a book that
explains how to combine the topics mentined in the title to build projects.  The
book can be used to teach programming classes in colleges and to organize
workshops in hackerspaces or other community-driven spaces.  Currently the book
is available only in Russian.")
 (license cc-by-sa4.0))

;;; guix.scm ends here.
