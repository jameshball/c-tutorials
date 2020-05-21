all:	lecture.pdf lecture-handout.pdf

clean:
	/bin/rm -f *.log *.aux *.dvi *.pdf *.eps *.ps *.out *.nav *.snm *.toc *.vrb

#lecture.ps:	lecture.pdf
#	pdftops lecture.pdf lecture.ps
#	cp -p lecture.ps ..

img/diagram-0.pdf:	img/diagram.fig
	cd img; fig2mpdf -l -m diagram.fig 

lecture.pdf:	lecture.tex img/diagram-0.pdf
	pdflatex lecture
	cp -p lecture.pdf ..

lecture-handout.tex:	lecture.tex
	sed -e 's/\documentclass\[aspectratio=169/\documentclass[handout/g' -e 's/\documentclass{/\documentclass[handout]{/g' -e '/\documentclass/a\\\usepackage{pgfpages}\\\pgfpagesuselayout{4 on 1}[a4paper,landscape,border shrink=5mm]' lecture.tex > lecture-handout.tex

lecture-handout.pdf:	lecture-handout.tex
	pdflatex lecture-handout
	pdflatex lecture-handout
	cp -p lecture-handout.pdf ..
 
#lecture-handout.ps:	lecture-handout.pdf
#	pdftops lecture-handout.pdf lecture-handout.ps
#	cp -p lecture-handout.ps ..
