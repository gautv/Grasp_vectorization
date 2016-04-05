echo "========= Original Version ========="
echo "novect================="
cd ./novect/src
time ../bin/foudre $1 $2 $3 0 $5
cd -
echo "vect==================="
cd ./vect/src
time ../bin/foudre $1 $2 $3 0 $5
cd -

echo "========= Vectorized Version ========="
echo "novect================="
cd ./novect/src
time ../bin/foudre $1 $2 $3 1 $5
cd -
echo "vect==================="
cd ./vect/src
time ../bin/foudre $1 $2 $3 1 $5
cd -
