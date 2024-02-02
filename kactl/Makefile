LATEXCMD = pdflatex -shell-escape
export max_print_line = 1048576

.PHONY: help
help:
	@echo "This makefile builds KACTL (KTH ACM Contest Template Library)"
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast	- to build the KACTL, quickly (only runs LaTeX once)"
	@echo "	make kactl	- to build the KACTL"
	@echo "	make clean	- to clean up the build process"
	@echo "	make veryclean	- to clean up and remove kactl.pdf"
	@echo "	make help	- to show this information"
	@echo ""
	@echo "For more information see the file 'doc/README'"

.PHONY: fast
fast:
	$(LATEXCMD) kactl.tex </dev/null

.PHONY: kactl
kactl:
	$(LATEXCMD) kactl.tex && $(LATEXCMD) kactl.tex

.PHONY: clean
clean: 
	rm -f kactl.aux kactl.log kactl.tmp kactl.toc kactl.pdf kactl.ptc ../kactl.pdf

.PHONY: veryclean
veryclean: clean
	rm -f kactl.pdf
