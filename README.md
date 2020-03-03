# Google-Hash-Code-2020

### A solution implementation for the Google Hash Code contest, Online Qualification round.

[Problem Statement](https://storage.googleapis.com/coding-competitions.appspot.com/HC/2020/hashcode_2020_online_qualification_round.pdf)

[Input files](https://storage.googleapis.com/coding-competitions.appspot.com/HC/2020/qualification_round_2020.in.zip)

Download and place the input files into [the input directory](/input) and run `make`.

A greedy approach that evaluates all libraries and chooses the best one to start processing at every iteration.

The evaluation assigns priority to each library computed as `lib.val / pow(lib.process, PROCESS_EXPONENT)` where `val` is the total score the library would contribute if it started processing on that day, `process` is the number of days the signup process takes for that library and `PROCESS_EXPONENT` is a parameter. The calculation of `val` takes into account the number of remaining days and the already scanned books. The best result is a combination of `PROCESS_EXPONENT = 0.5` and `PROCESS_EXPONENT = 1` whose respective output files are under [exp05](/exp05) and [exp1](/exp1). Below is the score table.

|              Task              | `PROCESS_EXPONENT` |    Score    |
|--------------------------------|        :---:       |        ---: |
|   A - example                  |        Both        |          21 |
|   B - read on                  |        Both        |   5,822,900 |
|   C - incunabula               |          1         |   5,688,403 |
|   D - tough choices            |        Both        |   5,027,945 |
|   E - so many books            |          1         |   5,034,626 |
|   F - libraries of the world   |         0.5        |   5,340,296 |
|            Total               |      Combined      |  26,914,191 |
