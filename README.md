# Artist Collaboration Graph
Utilizes a database of songs to create a graph of main and featured artists. Analysis includes basic DFS as well as Kosaraju and Brandes algorithms. 
## Codebase
**This project uses C++ for all major implementations & Python for data preprocessing**
* Data analysis executable located at `/finalproj/main.cpp`
* Graph class is implemented in `graph.h` and `graph.cpp` within the `/finalproj` directory
  * This class includes JSON processing as well as all analysis algorithms
* Makefile is located at `/finalproj/Makefile`
* JSON files for test data and our selected dataset can be found in `/finalproj/data`
* JSON data preprocessing preprocessing is located at `/finalproj/data/process.py`
* Full test suite can be found within `/finalproj/tests`

## Dependencies
* [mp_lists](https://courses.engr.illinois.edu/cs225/fa2021//doxygen//mp_lists/index.html)
* [nlohmann/json](https://github.com/nlohmann/json)

## Usage
### I/O
Data MUST be pulled from [Million Song Dataset](http://millionsongdataset.com/sites/default/files/AdditionalFiles/unique_artists.txt) and run through preprocessing (`process.py`) in order for analysis to be completed. 
 * Output of `process.py` is stored at `Data/output.json`

Input data for analysis is defined by passing the filepath of the desired JSON file to the execution command.

### Analysis (Main) Executable
**Build (within `/finalproj`):** `make finalproj`

**Run (within `/finalproj`):** `./finalproj` `[INPUT FILEPATH.json]`

`[INPUT FILEPATH.json]` defaults to `./Data/output.json` (output of `process.py`)

Runs all algorithms on passed data and outputs results to console.

### Test Suite
Tests have been included to cover all major functions:
* Graph construction

  * Tests basic functionality of graph class (such as node and edge creation).

* DFS
* Kosaraju's algorithm
* Brandes algorithm
* JSON read/write

    * Aggregate of all other tests except uses a JSON data input, mimicking how our real dataset is stored. Ensures JSON based graph construction works as intended and doesn't break any algorithms.

Each of these groups can be found in its own directory.

### Test Executable
**Build (within `/finalproj`):** `make test`

**Run (within `/finalproj`):** `./test` (complete test suite)

Single function:
* tests_dfs.cpp: `./test "[dfs]"`
* tests_graph_construction.cpp: `./test "[constructor]"`
* tests_json.cpp: `./test "[json]"`
* tests_kosaraju.cpp: `./test "[kosaraju]"`
* tests_brandes.cpp: `./test "[brandes]"`

Specific test case: `./test "TEST NAME"`

## Maintenence
This code created and maintained by Ryan Boone, Joe Dubravec and Eric Hegemann as a final project for CS 225 at UIUC.
