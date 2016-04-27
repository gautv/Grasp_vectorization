data_path=./data_local_search

for job in $(seq 20 10 400) ;do
    for machine  in $(seq 20 1 100) ; do

        echo J=$job M=$machine

# path_to_job_binary NUMBER_JOBS NUMBER_MACHINES 1=VECTORIZED/0=NOT_VECTORIZED NUMBER_ITERATIONS

        # Vectorized Version / Vectorized by the compiler
        /usr/bin/time ./vect/bin/foudre ${job} ${machine} 1 1 |& grep user > $data_path/VV_${job}_${machine}.dat


        # Vectorized Version / Not Vectorized by the compiler
        /usr/bin/time ./novect/bin/foudre ${job} ${machine} 1 1 |& grep user > $data_path/VN_${job}_${machine}.dat


        # Not Vectorized Version / Vectorized by the compiler
        /usr/bin/time ./vect/bin/foudre ${job} ${machine} 0 1 |& grep user > $data_path/NV_${job}_${machine}.dat


        # Not Vectorized Version /Not Vectorized by the compiler
        /usr/bin/time ./novect/bin/foudre ${job} ${machine} 0 1 |& grep user > $data_path/NN_${job}_${machine}.dat

    done
done
