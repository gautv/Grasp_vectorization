echo "========= Original Version ========="
echo "novect================="
cd ./novect
time ./bin/foudre 0 $1 
cd -
echo "vect==================="
cd ./vect
time ./bin/foudre 0 $1
cd -

echo "========= Vectorized Version ========="
echo "novect================="
cd ./novect
time ./bin/foudre 1 $1
cd -
echo "vect==================="
cd ./vect
time ./bin/foudre 1 $1
cd -
