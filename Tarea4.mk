PUNTO=PuntoNemo.pdf

erase = rm -r -f *.dat a.out *.png *.aux *.log



$(PUNTO): output.dat Plots.py
	python Plots.py

output.dat: geo.x
	./geo.x

geo.x: GeographicPoint.c
	cc GeographicPoint.c -lm -o geo.x


clean :
	$(erase) *.pdf 
