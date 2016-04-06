#!/usr/bin/sh


scp -r -P 22000 ./gcc vaillantg@cluster.ig.fpms.ac.be:/home_nfs/vaillantg/grasp_scratch
scp -r -P 22000 ./novect vaillantg@cluster.ig.fpms.ac.be:/home_nfs/vaillantg/grasp_scratch
scp -r -P 22000 ./vect vaillantg@cluster.ig.fpms.ac.be:/home_nfs/vaillantg/grasp_scratch
scp -r -P 22000 ./*.sh vaillantg@cluster.ig.fpms.ac.be:/home_nfs/vaillantg/grasp_scratch
