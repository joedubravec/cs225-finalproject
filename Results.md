# Results and Conclusions
This project attempts to tackle the question of "How connected is the music industry?" Deliverables for this project are:
* Data preprocessing script written in Python `/finalproj/Data/process.py`
* JSON file with input data resulting from preprocessing `/finalproj/Data/output.json`
* Our goals for this project `Goals.md `
* A log containing summaries of our development each week `Development.md`
* Our documentation `README.md`
* A functional code base including:
    * A graph class with DFS, Kosaraju's, and Brandes algorithms implemented `/finalproj/graph.cpp`
    * A comprehensive test suite `/finalproj/tests`
* A [video presentation](https://mediaspace.illinois.edu/media/t/1_2owdoaqb)


## Data 
Our project's data set was sourced from a list of 1 million songs. We filitered this list to only include songs that had multiple artists collaborating. Our python script then organized this into a JSON file for analysis. 

## Goals and Results
To illustrate the success of reaching our goals, we will be using the graph generated by `main.cpp` when the following commands are run:

    make finalproj
    ./finalproj

The below portion of `main.cpp`, lines 12-16, loads our dataset into our graph class:

    string path = "./Data/output.json";
    if(argc == 2) {  
        path =  argv[1];
    }
    Graph artistCollabs = Graph(path);

The graph `artistCollabs` will be used throughout this final writeup.

### DFS Traversal

Our goal was to implement a DFS traversal in O(V+E) time that returned a vector of the vertices it visited in DFS order. When run on our dataset, the returned vector has a size of 7,403. This value is equal to the amount of vertices in the graph, which is evidence that all nodes were visited and no nodes were double counted.

`main.cpp` line 25:

    std::cout<< "Running DFS visits " + to_string(artistCollabs.dfs().size()) 
    + " unique nodes." <<std::endl;

Output:

    >>Running DFS visits 7403 unique nodes.

    
    
Further, individual node by node order checks conducted in our test suite on a smaller data set (found in the file `./finalproj/tests/tests_dfs.cpp`) give us full confidence the DFS traversal works as intended.

A sub-goal of our DFS was to use it to find the two artists who had the longest path between them. By using our DFS wrapper function `longestConnection()` we were able to find that T-Pain and Lil Wayne had the longest path between them out of all artists in our graph.

`main.cpp` line 27:

    std::cout<< artistCollabs.longestConnection() <<std::endl;

Output:

    >>The longest connection is between T-Pain and Lil Wayne with a component size of 12, out of 5121 connected components.

This function also tells us the number of connected components in the graph. This is done by counting the number of calls that originate in the main DFS to the DFS helper function. Having 5,121 connected components indicates that the music industry is fairly unconnected, and artists who collaborate tend to only collaborate with one or two others. This is how we used our DFS to provide insight into our leading question.

### Finding Strongly Connected Components with Kosaraju's Algorithm

Strongly connected components in a directed graph occur when there is a path between every vertex in a set of vertices. This set of vertices is called a strongly connected component. These sets of vertices can range from 1 node to size - 1 nodes. Kosaraju's algorithm is used to find these (sub)sets of vertices in O(V+E) time and can be summarized into 3 main steps:

1. Get the DFS order of the graph
2. Reverse all the edges of the graph
3. Take the DFS of the new graph in the order of step 1

Our implementation of Kosaraju's algorithim returns a `vector<vector<GraphNodes*>>`, where each interior vector is the set of nodes in a strongly connected component. Furthermore, our algorithm only makes note of strongly connected components of size > 1 to avoid polluting our results. Finally, to accommodate Step 2 a reverse helper function was created (which has test cases in `/finalproj/tests/tests_kosaraju.cpp`).

`main.cpp` line 29:

    std::cout<< "Running Kosaraju's algorithm shows us there are " + to_string(artistCollabs.kosaraju().size()) 
    + " strongly connected components." <<std::endl;

Output:

    >>Running Kosaraju's algorithm shows us there are 0 strongly connected components.

Unfortunately our dataset has no strongly connected components. A manual analysis of our main dataset and extensive testing on a smaller dataset confirms that the algorithm is working properly and our main dataset is faulty. The lack of strongly connected components may be related to a variety of factors such as:

* Bias in how the dataset was originally structured, favoring certain artists who appear as the "main" artist
    * It should be noted that we couldn't find anything obvious (i.e. alphabetization) that would cause this type of bias
* Social hierarchy in the music industry where "lesser" artists are always listed as featured artists, while well-known artists rarely get formally featured

This second reason provides an instresting insight into our leading question. Although there does appear to be heavy collaboration in the music industry, artists who feature others on their songs don't like to get featured themselves. 


### Finding Betweeness Centrality with Brande's Algorithm

Betweenness Centrality is a measurement of how "central" each node in a graph is. In other words, the betweenness centrality of a node is a measure of how easy it is to reach that node from any other given node in the graph in a minimal number of steps. The Brandes algorithm is an efficient way of computing the betweenness centrality, which we can then use to find the most central artist(s) in our dataset, or the artists that have collaborated with the most other artists.

For the purposes of this project, betweenness centrality of a node `v` is defined as:

    the sum of (# of shortest paths between two nodes s and t) divided by (# of those paths that pass through node v), for all pairs of nodes {s, t} in the graph

The Brandes algorithm calculates this value by using a BFS-based search to find all these shortest paths, then walks back through the BFS in inverse order to calculate the centralities of each of the nodes. This implementation is efficient because it does not require explict calculation of each shortest path, instead relying on the nodes one edge away from the current node in the unraveling of the traversal.

While manual calculation of such a large dataset in order to verify the results is impractical, we have written and manually verified the results of several tests (in `/finalproj/tests/tests_brandes.cpp`) which gives us confidence that this algorithm works as intended.


`main.cpp` line 35:

    std::cout << "most central artist is (drumroll please): " << std::endl;

    std::cout << artistCollabs.nodes[getMostCentralArtist(artistCollabs)]->artist << std::endl;

Output:

    most central artist is (drumroll please): 
    Turbulence

## Conclusion

All in all, our group is extreamly satisfied with our project. Although we faced limitations due to our dataset, we were able to implement all of our desired algorithms. Creating clear test cases allowed us to confirm that these algorithms worked as intended, which was very rewarding. 

Circling back to our leading question, our analysis shows that the music industry is fairly unconnected. Even after filtering out solo artists, most had only worked with one or two other people. This left many connected components of size 2-3 floating around in our graph. It also appears the social hierarchy of the music industry keeps featured artists from having artists they've worked with appear on their songs. So next time you're listening to music and see a "ft. ___", you should go and listen to some of the music by that person. Chances are they probably have significantly less support than the artist you're currently listening to.
