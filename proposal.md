Leading Question: Our overarching question we will be investigating is "Out of artists that have collaberated with other artists, how connected is the music industry." During the exploration of this question we will look at answering who are some of the most "central" artists that have collaborated with most other artists. We will also attempt to see if we can find strongly connected components that may imply genre similarity. A succesful project will show linkages in the music industry between artists, to show us how collabrative the industry is.

Dataset Acquisition and Processing: We will be using the million song data set found [here.](http://millionsongdataset.com/sites/default/files/AdditionalFiles/unique_artists.txt) We will preprocess this data to seperate out songs that have multiple artists on it and remove artist data that is not complete or not collabrative. This will leave us with a dataset providing songs and their respective artists. Each observation in the dataset represents a song, and the artists who worked on it. We will not be collecting any edge weighting information, but will be creating a directed graph. 

Graph Construction: To illustrate we will use the following observation from the dataset: 

    "AR006821187FB5192B<SEP>94fc1228-7032-4fe6-a485-e122e5fbee65<SEP>TRMZLJF128F4269EAC<SEP>Stephen Varcoe/Choir of King's College_ Cambridge/Sir David Willcocks"

1. Node: A node represents an artist, in our dataset artists follow the last \<SEP>. If there are multiple artists on one song they are separated by either a "/" or the abbreviation "feat." where the artist listed first is the main artist, and the artist(s) listed after are the features. Thus, in this observation we have 3 nodes created (A short hand node name is listed next to the item to streamline further discussion): 
    1. Stephen Varcoe (Node A)
     2. Choir of King's College_Cambridge (Node B)
      3. Sir David Willcocks (Node C)
2. Edges: We will be creating a directed graph. If edge E leaves node V1 and enters node V2 this symbolizes artist V1 collaberated (was featured) with artist V2. If two V1 collaberates with V2 multiple times only one edge is created. There will be no weighting information collected because none of our algorithms use that information. Thus, in continuation of our example there will be two edges created as a result of this observation. Edge v will leave Node B and enter Node A, and edge w will leaves Node C and enter Node A.

Graph Algorithms
1. Traversal (DFS) - We believe this traversal will be the most beneficial based on our other planned algorithms and what kind of data we are looking for. This traversal has a time complexity of O(V + E). We expect this algo to take an input that is the nodes from the graph. With this node the traversal will prioritize finding the farthest element first, marking each node it visits as visited, keeping track of discovery edges and cross edges, and adding nodes discovered to a stack. To ensure all connected components of the graph are touched by the traversal the DFS algo will be called on each node in the list of nodes for the graph if the node has not been marked visited. Our traversal will maintain a list\<bool> that mirrors the indexing of our node list where each element is marked  true once it is visited. The DFS algo will return a list of nodes connected to the starting node in DFS order. Ultimately, we intend to use the DFS traversal to find the longest path between two nodes, which in our representation means the longest chain of collaborations between two artists. We hypothesize that this may reveal interesting things about how two seemingly completely different artists might be connected through a long chain of collaborations with other artists.

2. Brandes Algorithim - Betweenness centrality: We think this is an interesting algorithm that will help answer our central question by providing insight onto artists who are most "central" to the music industry. The time complexity of this algorithm is O(V*E). This algo will take in a connected graph and output a node that is the most "central" in the graph. If our graph is split into multiple connected components we will call the Brandes Algorithim on each component, and ultimately return the most central node for the connected component with the most nodes.

3. Kosaraju's Algorithm - Strongly connected component: This algorithim will allow us to see groupings of artists which may indicate genre. This should be testable in linear time of O(V + E). This algo will take a directed graph as an input and output 0 or more sets of nodes are sub-graphs of the original graph that are strongly connected. This is done by first traversing the tree in DFS and adding the nodes to a list in order visited, next each node in this list is visited again and added to a component representing the connected components. 

Timeline

1. Data Processing & setup (Week 1 11/8-11/15)
2. Initial code base setup & graph class (Week 2 11/15-22)
3. DFS algo and Betweenness centrality (Week 3 11/22-11/29)
4. Strongly connected component & beginning final deliverables (Week 4 11/29-12/6)
5. Creation of final report/ redmes/ video (12/6-12/13)
