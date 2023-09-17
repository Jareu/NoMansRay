import matplotlib.pyplot as plt
import numpy as np

def delaunay_triangulation(points):
    # Create a super-triangle that encompasses all points
    min_x = min(points[:, 0]) - 1
    max_x = max(points[:, 0]) + 1
    min_y = min(points[:, 1]) - 1
    max_y = max(points[:, 1]) + 1
    super_triangle = np.array([[min_x, min_y], [max_x, min_y], [(min_x + max_x) / 2, max_y]])

    # Initialize a list with the super-triangle
    triangles = [super_triangle]

    for p in points:
        edges_to_flip = []

        for triangle in triangles:
            if p[0] < min(triangle[:, 0]) or p[0] > max(triangle[:, 0]) or p[1] < min(triangle[:, 1]) or p[1] > max(triangle[:, 1]):
                continue

            circumcenter = np.mean(triangle, axis=0)
            circumradius = np.linalg.norm(triangle[0] - circumcenter)

            if np.linalg.norm(p - circumcenter) < circumradius:
                for i in range(3):
                    edge = (triangle[i], triangle[(i+1) % 3])
                    if (edge[0], edge[1]) not in edges_to_flip and (edge[1], edge[0]) not in edges_to_flip:
                        edges_to_flip.append(edge)
                triangles.remove(triangle)

        for edge in edges_to_flip:
            new_triangle = np.array([edge[0], edge[1], p])
            triangles.append(new_triangle)

    # Remove triangles that contain any vertex of the super-triangle
    triangles = [t for t in triangles if not any((v == super_triangle).all() for v in t)]

    return np.array(triangles)

# Example usage:
if __name__ == "__main__":
    np.random.seed(0)
    points = np.random.rand(20, 2)  # Generate 20 random 2D points

    triangles = delaunay_triangulation(points)

    # Plot the Delaunay triangulation
    plt.triplot(points[:, 0], points[:, 1], triangles)
    plt.plot(points[:, 0], points[:, 1], 'o')
    plt.show()
