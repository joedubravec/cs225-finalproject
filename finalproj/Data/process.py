#Outputs a json file containing a single python dictionary in json form
#Key is a string representing an artists name, and a node in a graph
#Value is a list (signified in the string by brackets) containing every node the Node(key) points to

import json
file = open("unique_tracks.txt", "r",encoding="utf8")

lines = file.readlines()
file.close()

fileToMake = open("output.json", "w")
newLines = []
nodes = []
#Isolate artist and their collabs
for line in lines:
    index1 = line.find("<SEP>")
    index2 = line.find("<SEP>", index1 + 5)
    index3 = line.find("<SEP>", index2 + 5)
    if ("/" in line[index2:index3]):
        newLine = line[index2+5:index3]
        newLines.append(newLine)
        artist = newLine[:newLine.find("/")].strip()
        if artist in nodes:
            continue
        else:
            nodes.append(artist.strip())

directedConnections = {}
for node in nodes:
    directedConnections[node] = []
master = {"artists" : []}

for song in newLines:
    people = song.split("/")
    artist = people[0].strip()
    people = people[1:]
    temp = {}

    for person in people:
        temp = {"main":person.strip(), "featuredOn":[artist]}

        if person.strip() in nodes:
            for dict in master["artists"]:
                if (dict["main"] == person.strip()):
                    if (artist in dict["featuredOn"]):
                        continue
                    else:
                        dict["featuredOn"].append(artist)
        else:
            nodes.append(person.strip())
            master["artists"].append(temp)



fileToMake.write(json.dumps(master,indent = 2))



    
fileToMake.close()