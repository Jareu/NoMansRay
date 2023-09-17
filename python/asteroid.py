import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import ConvexHull

# Generate random points (you can replace this with your own point data)
np.random.seed(0)
points = np.random.rand(30, 2)  # Generates 30 random 2D points

# Compute the convex hull
hull = ConvexHull(points)

# Plot the original points
plt.plot(points[:,0], points[:,1], 'o')

# Plot the convex hull
for simplex in hull.simplices:
    plt.plot(points[simplex, 0], points[simplex, 1], 'k-')

# Connect the last point to the first point to close the hull
plt.plot(points[hull.vertices[0], 0], points[hull.vertices[0], 1], 'k-')

plt.axis('equal')
plt.show()
