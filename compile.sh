./copy.sh

cd ./novect/src/

echo '--- Compiling not vectorized function ---'
make
cd -
cd ./vect/src/
echo "--- Compiling vectorized function ---"
make

echo "--------------------------------------"
read text

scp -r ~/grasp_scratch mic0:
