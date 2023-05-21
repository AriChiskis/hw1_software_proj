from math import dist
import sys

def kmeans(k : int, iter: int, input_data):
    # parseing input
    input_data = open(input_data) if type(input_data) is str else input_data
    points = []
    for line in input_data:
        if line:
            line = line.split(',')
            points.append([float(scalar) for scalar in line])
            print("asdddddddddd", line[-1])
    number_of_points = len(points)
    if number_of_points == 0: raise ValueError("An Error Has Occurred")

    # handling errors
    if not (k in range(2, number_of_points)):
        raise ValueError("Invalid number of clusters!") 
    if not (iter in range(2, 1000)):
        raise ValueError("Invalid maximum iteration!")

    # call the functions that does the heavy lifting of the algorithm
    centroids = kmeans_sub(k, points, iter)
    for point in centroids:
        s = ""
        for coodinate in range(len(point)-1):
            s += formatting(str(round(point[coodinate],4))) +','
        print(s + formatting(str(round(point[-1],4))))    
    return 
    

def kmeans_sub(k: int, points: list, iter: int):
    # intializing 
    epsilon: float = 0.001
    centroids = [points[_] for _ in range(k)]
    new_centroids = [points[_] for _ in range(k)]
    delta = float('inf')
    dimension: int = len(points[0])

    # iterations
    while iter > 0 and delta >= epsilon:
        # print("iteration number: " ,iter)
        delta = 0
        # find closest centoid to the current point & adding it
        clusters = [[] for _ in range(k)]
        for point in points:
            index, min_distance = 0, float('inf')
            for i, other_point in enumerate(centroids):
                curr_distance = dist(point, other_point)
                if curr_distance < min_distance:
                    index = i
                    min_distance = curr_distance
            clusters[index].append(point)


        # Update centroids
        for index in range(k):
            # getting the new centoid
            new_centroids[index] = [0.0 for _ in range(dimension)]
            num_of_points = len(clusters[index])
            for point in clusters[index]:
                for coordinate in range(dimension):
                    new_centroids[index][coordinate] += point[coordinate] / num_of_points

            # comparing the new centoid to the old one
            delta += dist(new_centroids[index], centroids[index])
            centroids[index] = new_centroids[index]

        iter -= 1
    return centroids

# used for the print in the end of the funcition
def formatting(add: str) -> str:
    if add[0] == "-" and len(add) < 7:
        add += "0"*(7-len(add))
    if add[0] != "-" and len(add) < 6:
        add += "0"*(6-len(add))
    return add

if __name__ == "__main__":
    if len(sys.argv) == 4:
        k, iteration_number, file = int(sys.argv[1]), int(sys.argv[1]), sys.argv[3]
    else:
        k, iteration_number, file = int(sys.argv[1]), 200, sys.argv[2]

    kmeans(k, iteration_number, file)