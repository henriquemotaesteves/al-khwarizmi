set terminal png size 1024,768

set output 'resource/search.png'

set key left top

plot 'build/test/perf/linear-search-test.x.dat' with lines title 'Linear Search'
