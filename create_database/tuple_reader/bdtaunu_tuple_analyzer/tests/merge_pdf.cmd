ls -l *.gv | sed s'/^.*\(sp[0-9]*.*\.gv\).*$/\1/' | sed s'/\(.*\)\.gv/dot -Tpdf \1.gv -o \1.pdf/' > tmp.cmd; source tmp.cmd; rm tmp.cmd; pdftk *.pdf cat output merged.pdf
