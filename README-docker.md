# Concord-BFT: Docker image

This Dockerfile (and the script file provided with it) follows the build recipe of Concord-BFT project (see [README](https://github.com/vmware/concord-bft/blob/master/README.md)).

This Docker image's aims to provide a quick test and build tool.

Build the image
----

    docker build -t concord-bft -f docker/Dockerfile .

Run the image
----

    docker run --rm -it concord-bft /bin/bash

Try out some examples
----

Once in the docker container, examples provided with Concord-BFT can be directly executed.

    cd /concord-bft/build/bftengine/tests/simpleTest/scripts
    ./testReplicasAndClient.sh

Alternatively you can run `runReplicas.sh` and `runClient.sh`.