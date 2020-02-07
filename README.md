# Biquad-Cascade-Sound-Filter

A Unix filter in C (i.e., data processor from stdin to stdout) consisting of a simple yet useful algorithm, and then use Unix system calls for pipes, fork, and exec to create a pipeline of multiple instances of these filters.

The biquad filter takes 5 positive real numbers as arguments to use as the coefficients for the filter. To run the biquad filter on in.wav and recieve output as out.wav, the shell script is as shown below:

    ./unwav < in.wav \
    | ./biquad 1 0 1 -0.7 0 \
    | ./biquad 1 1.18 1 -1.58 0.81 \
    | ./biquad 4.42e-3 1 0 0 0 \
    | ./towav > out.wav
                 
The real power lies in the pipelining of biquad filters consecutively, so the cascade filter is made to take s 5n command line arguments (these are parameters for n biquad filters), where n ≥ 1, and creates a pipeline of n biquad filters. Example:

    ./cascade 1 0 1 -0.7 0 1 1.18 1 -1.58 0.81 4.42e-3 1 0 0 0
    
should create a pipeline like:

    ./ biquad 1 0 1 -0.7 0 \
    | ./ biquad 1 1.18 1 -1.58 0.81 \
    | ./ biquad 4.42e-3 1 0 0 0

To run the cascade filter on in.wav and recieve output as out.wav, the shell script is as shown below:

    ./ unwav < ugly . wav \
    | ./ cascade 1 0 1 -0.7 0 1 1.18 1 -1.58 0.81 4.42 e -3 1 0 0 0 \
    | ./ towav > out . wav
