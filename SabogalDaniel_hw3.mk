SabogalDaniel_Resultados_hw3.pdf : SabogalDaniel_Resultados_hw3.tex ODE.pdf PDE.pdf PDE1.pdf PDE2.pdf ODE1.pdf ODE2.pdf ODE3.pdf CORTES1.pdf CORTES2.pdf
	pdflatex SabogalDaniel_Resultados_hw3.tex
ODE.pdf : particula.txt SabogalDaniel_Plots_hw3.py
	python3 SabogalDaniel_Plots_hw3.py
ODE1.pdf : particula.txt SabogalDaniel_Plots_hw3.py
	python3 SabogalDaniel_Plots_hw3.py
ODE2.pdf : particula.txt SabogalDaniel_Plots_hw3.py
	python3 SabogalDaniel_Plots_hw3.py
ODE3.pdf : particula.txt SabogalDaniel_Plots_hw3.py
	python3 SabogalDaniel_Plots_hw3.py
PDE1.pdf : parcial.txt SabogalDaniel_Plots_hw3.py
	python3 SabogalDaniel_Plots_hw3.py
PDE2.pdf : parcial.txt SabogalDaniel_Plots_hw3.py
	python3 SabogalDaniel_Plots_hw3.py
PDE.pdf : parcial.txt SabogalDaniel_Plots_hw3.py
	python3 SabogalDaniel_Plots_hw3.py
CORTES1.pdf : parcial.txt SabogalDaniel_Plots_hw3.py
	python3 SabogalDaniel_Plots_hw3.py
CORTES2.pdf : parcial.txt SabogalDaniel_Plots_hw3.py
	python3 SabogalDaniel_Plots_hw3.py
particula.txt : ODE
	./ODE > particula.txt
parcial.txt : PDE
	./PDE > parcial.txt
ODE : SabogalDaniel_ODE.cpp
	g++ -o ODE SabogalDaniel_ODE.cpp
PDE : SabogalDaniel_PDE.cpp
	g++ -o PDE SabogalDaniel_PDE.cpp