# imec_task
## SAXPY Algorithm
The SAXPY algorithm, short for "Single-precision A·X Plus Y", is a simple operation that performs a vector-vector operation on two arrays. The operation is defined as:

B = C*A + B

where A is a scalar, and A and B are vectors of the same length. The SAXPY algorithm performs this operation on all elements of the vectors x and y.

## SST-Elements Implementation
This repository contains an implementation of the SAXPY algorithm as part of SST-Elements. SST-Elements is a collection of simulation models that are used to simulate the behavior of computer systems and networks.

In this repository, the SAXPY algorithm has been added to the Miranda generator as part of SST-Elements.
## Usage
To run the SAXPY algorithm simulation, you will need to install SST-CORE and SST-Elements. 

- First, you need to install SST-CORE. Follow the instructions on this link: 

http://sst-simulator.org/SSTPages/SSTBuildAndInstall_12dot1dot0_SeriesDetailedBuildInstructions

- Next, you will need to install SST-Elements. Follow the instructions provided on the above link.

- Once you have SST-CORE and SST-Elements installed, you can download the exercise files from the following repository:

https://github.com/sstsimulator/sst-tutorials/tree/master/exercises

- Run the script using the following command:

sst --model-options="--config=miranda.cfg" ex4.py

Note: you can use the appropriate exercise file name instead of ex4.py

This will run the simulation of the SAXPY algorithm using the Miranda generator. You can adjust the configuration in the miranda.cfg file to suit your simulation needs.
It's also worth mentioning that it's good to read the tutorials provided in the exercise repository to understand how it works and how to use it correctly.

