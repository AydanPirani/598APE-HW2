commit=$(git rev-parse HEAD)
./genetic_benchmark diabetes > data/$commit.dat
./genetic_benchmark cancer >> data/$commit.dat
./genetic_benchmark housing >> data/$commit.dat
