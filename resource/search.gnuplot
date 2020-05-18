set terminal png size 1024,768

set output 'resource/search.png'

set key left top

set xlabel 'Items'
set ylabel 'Total Instruction Fetch Cost'

plot 'build/test/perf/linear-search-test.x.dat' with lines title 'Linear Search', \
     'build/test/perf/binary-search-test.x.dat' with lines title 'Binary Search'
